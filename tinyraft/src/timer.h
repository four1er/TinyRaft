#pragma once

#include <chrono>

namespace tinyraft {

using TimePoint = std::chrono::steady_clock::time_point;
using Duration = std::chrono::milliseconds;

TimePoint GetTimeNow();

static constexpr std::chrono::milliseconds KElectionTimeout =
    std::chrono::milliseconds(5000);
static constexpr std::chrono::milliseconds KHeartbeatTimeout =
    std::chrono::milliseconds(1000);
static constexpr std::chrono::milliseconds KRpcTimeout =
    std::chrono::milliseconds(10000);

class Timer {

public:
  Timer(Duration interval) : interval_(interval) {}

  void start() {
    start_time_ = std::chrono::steady_clock::now();
    is_running_ = true;
  }

  bool has_expired() const {
    if (!is_running_)
      return false;
    auto now = std::chrono::steady_clock::now();
    return (now - start_time_) >= interval_;
  }

private:
  TimePoint start_time_;
  Duration interval_;
  bool is_running_ = false;
};

} // namespace tinyraft
