#pragma once

#include "node.h"
#include "state.h"
#include "timer.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace tinyraft {
class Raft {

public:
  /**
   * @brief ProcessTimeout. We need to identify different role, when happened
   * timeout.
   * - Follower timeout: Become candidate and start election \n
   * - Candidate timeout: Start election again. \n
   * - Leader timeout: Check heartbeat timeout and send heartbeat \n
   *
   * @param [in] now_time
   */
  void ProcessTimeout(TimePoint now_time);

private:
  uint64_t id_;                  // node id
  RoleState current_role_;       // node current role
  PresistState presist_state_;   // node persist state
  VolatileState volatile_state_; // node volatile state
  uint64_t approved_vote_count_; // approved vote count
  TimerState timer_state_;       // timer state
  std::unordered_map<uint64_t, std::shared_ptr<NodeBase>> nodes_maps_;

  void FollowerTimeout(TimePoint now_time);
  void CandidateTimeout(TimePoint now_time);
  void LeaderTimeout(TimePoint now_time);

  void MakeElection();

  void BecomeFollower();
  void BecomeCandidate();
  void BecomeLeader();
};
} // namespace tinyraft
