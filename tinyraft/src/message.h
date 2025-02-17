#pragma once

#include <cstdint>
#include <vector>

namespace tinyraft {

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

struct MessageBase {
  MessageType type; // message type, see MessageType
  uint32_t term;    // current term
  uint32_t from;    // rpc sender id
  uint32_t to;      // rpc receiver id
};

struct VoteRequest : public MessageBase {
  static constexpr MessageType k_type = MessageType::REQUEST_VOTE_REQUEST;
  uint32_t candidate_id;   // equal to MessageBase::from
  uint32_t last_log_term;  // candidate's last log term
  uint32_t last_log_index; // candidate's last log index
};

struct VoteResponse : public MessageBase {
  static constexpr MessageType k_type = MessageType::REQUEST_VOTE_RESPONSE;
  uint32_t term;     // node return it self current term
  bool vote_granted; // true means candidate received vote
};

struct AppendEntriesRequest : public MessageBase {
  static constexpr MessageType k_type = MessageType::APPEND_ENTRIES_REQUEST;
  uint32_t prev_log_index;       // prev log index
  uint32_t prev_log_term;        // prev log term
  uint32_t leader_commit;        // leader commit index
  std::vector<uint32_t> entries; // log entries
};

struct AppendEntriesResponse : public MessageBase {
  static constexpr MessageType k_type = MessageType::APPEND_ENTRIES_RESPONSE;
  uint32_t term; // node return it self current term
  bool success;  // true means success
};

} // namespace tinyraft
