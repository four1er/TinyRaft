#pragma once

#include <cstdint>
#include <string>

namespace tinyraft {

struct Address {
  std::string ip;
  uint32_t port;
};

struct NodeBase {
  Address address;
};

}; // namespace tinyraft
