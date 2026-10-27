#include "winnetbyapp/usage.h"

#include <algorithm>
#include <map>

namespace winnetbyapp {

std::vector<AppTotal> totalsByApp(const std::vector<UsageRecord>& records,
                                  std::int64_t from, std::int64_t to) {
    std::map<std::string, AppTotal> by_app;
    for (const UsageRecord& r : records) {
        if (r.time < from || r.time >= to) {
            continue;
        }
        AppTotal& total = by_app[r.app];
        total.app = r.app;
        total.bytes_sent += r.bytes_sent;
        total.bytes_received += r.bytes_received;
    }

    std::vector<AppTotal> totals;
    totals.reserve(by_app.size());
    for (auto& [app, total] : by_app) {
        totals.push_back(std::move(total));
    }
    std::stable_sort(totals.begin(), totals.end(),
                     [](const AppTotal& a, const AppTotal& b) {
                         return a.bytes_sent > b.bytes_sent;
                     });
    return totals;
}

}  // namespace winnetbyapp
