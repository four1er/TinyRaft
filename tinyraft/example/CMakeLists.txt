set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Threads REQUIRED)
link_libraries(Threads::Threads)
find_package(yalantinglibs REQUIRED)
link_libraries(yalantinglibs::yalantinglibs)

add_executable(rpc_server rpc_server.cpp)
add_executable(rpc_client rpc_client.cpp)
