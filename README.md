# TinyRaft

一个用 C++20 编写的 Raft 共识算法学习项目，目前处于**骨架阶段**：状态定义、消息定义和超时处理框架已经搭好，选举、日志复制等核心逻辑尚未实现（详见文末「完成度与 TODO」）。

RPC 层计划使用 [yalantinglibs](https://github.com/alibaba/yalantinglibs) 的 coro_rpc（基于协程），以 git submodule 形式引入。

## 核心设计

代码按 Raft 论文（In Search of an Understandable Consensus Algorithm）的结构组织：

- **角色状态机**：节点分为 Follower / Candidate / Leader 三种角色，`Raft::ProcessTimeout()` 根据当前角色分发超时事件：
  - Follower 选举超时 → 转为 Candidate 并发起选举；
  - Candidate 选举超时 → 重新发起选举；
  - Leader 心跳超时 → 到期后应向各节点发送心跳（发送动作尚未实现，仅更新了下一次到期时间）。
- **状态划分**（`state.h`）：与论文一致地区分为持久状态（当前任期、投票给谁、日志条目）、易失状态（commitIndex、lastApplied、以及 Leader 视角下每个节点的 nextIndex / matchIndex）和定时器状态（选举到期时间、各节点的心跳与 RPC 到期时间）。
- **消息定义**（`message.h`）：定义了消息类型枚举和 `VoteRequest` / `VoteResponse`、`AppendEntriesRequest` / `AppendEntriesResponse` 结构体。
- **时间工具**（`timer.h`）：基于 `std::chrono::steady_clock`，超时常量为选举 5000ms、心跳 1000ms、RPC 10000ms。

## 目录结构

```
TinyRaft/
├── CMakeLists.txt          # 顶层构建（C++20，GCC 下开启 -fcoroutines）
├── yalantinglibs/          # git submodule：RPC / 协程库
└── tinyraft/
    ├── src/                # Raft 核心（静态库 tiny_raft_lib）
    │   ├── raft.h/.cpp     # Raft 类：超时处理与角色切换
    │   ├── state.h         # 角色、持久/易失/定时器状态定义
    │   ├── message.h       # RPC 消息结构体定义
    │   ├── node.h          # 节点地址结构
    │   ├── timer.h/.cpp    # 时间点工具与超时常量
    │   └── raft_rpc.h/.cpp # RequestVote / AppendEntries 处理函数（未实现）
    └── example/            # yalantinglibs coro_rpc 的 echo 演示
        ├── rpc_server.cpp  # 监听 9000 端口，注册 echo 处理函数
        └── rpc_client.cpp  # 调用 echo 并打印返回值
```

## 构建

依赖：CMake ≥ 3.15、C++20 编译器（已在 g++ 13.3 + CMake 3.28 上验证）。

```shell
# 克隆（带 submodule）
git clone --recurse-submodules https://github.com/four1er/TinyRaft.git
# 或者克隆后单独初始化 submodule
git submodule update --init

cmake -B _build
cmake --build _build
```

构建产物：

- `_build/tinyraft/src/libtiny_raft_lib.a`：Raft 核心静态库（当前只包含 `raft.cpp`）；
- `_build/tinyraft/example/rpc_server`、`_build/tinyraft/example/rpc_client`：RPC 演示程序。

## 运行示例

example 是 yalantinglibs coro_rpc 的 echo 演示（与 Raft 逻辑尚未接通），先启动服务端再运行客户端：

```shell
./_build/tinyraft/example/rpc_server   # 监听 9000 端口
./_build/tinyraft/example/rpc_client   # 输出：from server: hello coro_rpc
```

## 完成度与 TODO

如实说明当前未完成的部分：

- [ ] **选举逻辑未实现**：`Raft::MakeElection()` 是空函数；`RequestVote` / `AppendEntries` 处理函数（`raft_rpc.cpp`）只有声明、函数体为空，且该文件尚未加入构建（`src/CMakeLists.txt` 目前只编译 `raft.cpp`）。
- [ ] **心跳/日志发送未实现**：Leader 超时处理只更新各节点的心跳到期时间，实际发送处是 TODO。
- [ ] **日志复制与提交未实现**：日志追加、commitIndex 推进、状态机应用、快照（InstallSnapshot）均未实现，相关消息类型仅有定义。
- [ ] **节点尚不可直接运行**：`Raft` 类还没有构造函数与对外入口把各部分串起来；`state.h` 中声明的 `GetNewId()` 也暂无实现。
- [ ] **RPC 与 Raft 未接通**：example 仅验证 coro_rpc 的收发，尚未承载 Raft 消息。
