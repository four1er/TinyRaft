set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定源文件
set(SOURCE_FILES
   raft.cpp
)

# 创建一个静态库
add_library(tiny_raft_lib STATIC ${SOURCE_FILES})
