#include "rpc_server.h"
#include <ylt/coro_rpc/coro_rpc_client.hpp>

using namespace coro_rpc;
using namespace async_simple::coro;

Lazy<void> test_client() {
  coro_rpc_client client;
  co_await client.connect("localhost", /*port =*/"9000");
  auto r = co_await client.call<echo>("hello coro_rpc"); //传参数调用rpc函数
  std::cout << r.value() << std::endl;
}

int main() { syncAwait(test_client()); }
