#pragma once

#include <cstdint>

/**
 * @brief different message type
 *
 */
enum MessageType : uint32_t {
  NONE = 0,
  LOG_ENTRY = 1,
  REQUEST_VOTE_REQUEST = 2,
  REQUEST_VOTE_RESPONSE = 3,
  APPEND_ENTRIES_REQUEST = 4,
  APPEND_ENTRIES_RESPONSE = 5,
  INSTALL_SNAPSHOT_REQUEST = 6,
  INSTALL_SNAPSHOT_RESPONSE = 7,
  COMMAND_REQUEST = 8,
  COMMAND_RESPONSE = 9,
};
