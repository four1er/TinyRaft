#include "timer.h"

namespace tinyraft {

TimePoint GetTimeNow() { return std::chrono::steady_clock::now(); }

}; // namespace tinyraft
