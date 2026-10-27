#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace winnetbyapp {

// Network usage records and per-app totals. Strings are UTF-8.

// One SRUM network usage row: what one app sent and received in one period
// (SRUM records about one row per app per hour).
struct UsageRecord {
    std::string app;               // App path or name from SRUM's ID map.
    std::int64_t time = 0;         // Start of the period, Unix seconds (UTC).
    std::uint64_t bytes_sent = 0;
    std::uint64_t bytes_received = 0;
};

struct AppTotal {
    std::string app;
    std::uint64_t bytes_sent = 0;
    std::uint64_t bytes_received = 0;
};

// Sums the records with from <= time < to per app. Sorted by bytes sent,
// most first; ties by app name.
std::vector<AppTotal> totalsByApp(const std::vector<UsageRecord>& records,
                                  std::int64_t from, std::int64_t to);

}  // namespace winnetbyapp
