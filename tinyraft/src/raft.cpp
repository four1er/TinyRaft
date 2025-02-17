#include "raft.h"
#include "state.h"
#include "timer.h"

namespace tinyraft {

void Raft::ProcessTimeout(TimePoint now_time) {
  switch (current_role_) {
  case RoleState::FOLLOWER:
    FollowerTimeout(now_time);
    break;
  case RoleState::CANDIDATE:
    CandidateTimeout(now_time);
    break;
  case RoleState::LEADER:
    LeaderTimeout(now_time);
    break;
  default:
    break;
  }
}

void Raft::FollowerTimeout(TimePoint now_time) {
  if (now_time > timer_state_.election_due) {
    // election timeout
    BecomeCandidate();
    MakeElection();
  }
}

void Raft::CandidateTimeout(TimePoint now_time) {
  if (now_time > timer_state_.election_due) {
    // election timeout
    MakeElection();
  }
}

void Raft::LeaderTimeout(TimePoint now_time) {
  for (const auto &[node_id, node] : nodes_maps_) {
    if (timer_state_.node_heartbeat_due[node_id] < now_time) {
      timer_state_.node_heartbeat_due[node_id] =
          now_time + KHeartbeatTimeout / 2;
      // node->Send(CreateAppendEntriesRequest());
      // TODO: send heartbeat / append entries
    }
  }
}

void Raft::MakeElection() {}

void Raft::BecomeFollower() { current_role_ = RoleState::FOLLOWER; }
void Raft::BecomeCandidate() { current_role_ = RoleState::CANDIDATE; }
void Raft::BecomeLeader() { current_role_ = RoleState::LEADER; }
} // namespace tinyraft
