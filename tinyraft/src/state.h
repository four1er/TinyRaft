#pragma once

#include "timer.h"
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace tinyraft {

static uint64_t g_id = 0;

uint64_t GetNewId();

enum RoleState {
  FOLLOWER = 0,
  CANDIDATE = 1,
  LEADER = 2,
  UNKNOWN = 3,
};

struct LogEntry {
  uint64_t term;
  std::string data;
};

struct PresistState {
  uint64_t term;              // current term
  uint64_t vote_for;          // vote to candidate id
  std::vector<LogEntry> Logs; // log entries

  uint64_t last_log_term;  // last log term
  uint64_t last_log_index; // last log index

  friend std::ostream &operator<<(std::ostream &os, const PresistState &state);
};

struct VolatileState {
  uint64_t leader_id;    // id of the leader
  uint64_t commit_index; // index of highest log entry known to be committed
  uint64_t last_applied; // index of highest log entry applied to state machine
  std::unordered_map<uint64_t, uint64_t>
      next_index; // for each server, index of the next log entry to send to
                  // that server (initialized to leader last log index + 1)
  std::unordered_map<uint64_t, uint64_t>
      match_index; // for each server, index of highest log entry known to be
                   // replicated on server
                   // (initialized to 0, increases monotonically)
};

struct TimerState {
  TimePoint election_due; // election timeout
  std::unordered_map<uint32_t, TimePoint> node_heartbeat_due;
  std::unordered_map<uint32_t, TimePoint> node_rpc_timeout;
};

} // namespace tinyraft
