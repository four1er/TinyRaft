#include "rpc_server.h"
#include <ylt/coro_rpc/coro_rpc_server.hpp>

using namespace coro_rpc;

int main() {
  coro_rpc_server server(10, 9000);
  server.register_handler<echo>();
  server.start();
  return 0;
}
