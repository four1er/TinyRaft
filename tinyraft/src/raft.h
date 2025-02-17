#pragma once

#include "node.h"
#include "state.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace tinyraft {
class Raft {

public:
  void ProcessTimeout();

private:
  uint64_t id_;                  // node id
  RoleState current_role_;       // node current role
  PresistState presist_state_;   // node persist state
  VolatileState volatile_state_; // node volatile state
  uint64_t approved_vote_count_; // approved vote count
  TimerState timer_state_;       // timer state
  std::unordered_map<uint64_t, std::shared_ptr<NodeBase>> nodes_maps_;
};
} // namespace tinyraft
