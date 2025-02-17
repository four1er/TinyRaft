#pragma once

#include <string>
#include <string_view>
inline std::string echo(std::string_view str) {
  return std::string("from server: ") + std::string(str);
}
