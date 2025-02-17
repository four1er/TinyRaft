#pragma once
#include "message.h"
#include <string>

namespace tinyraft {

inline VoteResponse RequestVote(VoteRequest request);

inline AppendEntriesResponse AppendEntries(AppendEntriesRequest request);
} // namespace tinyraft
