set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Threads REQUIRED)
link_libraries(Threads::Threads)
# yalantinglibs 由顶层 CMakeLists 通过 add_subdirectory 引入，
# 其 INTERFACE 目标 yalantinglibs::yalantinglibs 已存在，无需再 find_package。
link_libraries(yalantinglibs::yalantinglibs)

add_executable(rpc_server rpc_server.cpp)
add_executable(rpc_client rpc_client.cpp)
