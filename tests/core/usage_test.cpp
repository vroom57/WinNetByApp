#include <doctest/doctest.h>

#include "winnetbyapp/usage.h"

using namespace winnetbyapp;

TEST_CASE("records are summed per app and sorted by bytes sent") {
    std::vector<UsageRecord> records = {
        {"chrome.exe", 0, 100, 5000},
        {"onedrive.exe", 0, 900, 10},
        {"chrome.exe", 3600, 50, 2000},
    };
    std::vector<AppTotal> totals = totalsByApp(records, 0, 7200);
    REQUIRE(totals.size() == 2);
    CHECK(totals[0].app == "onedrive.exe");
    CHECK(totals[0].bytes_sent == 900);
    CHECK(totals[1].app == "chrome.exe");
    CHECK(totals[1].bytes_sent == 150);
    CHECK(totals[1].bytes_received == 7000);
}

TEST_CASE("only records inside the period count") {
    std::vector<UsageRecord> records = {
        {"a.exe", 3599, 1, 1},   // Before the period.
        {"a.exe", 3600, 10, 20}, // First second of the period.
        {"a.exe", 7200, 100, 100},  // End is excluded.
    };
    std::vector<AppTotal> totals = totalsByApp(records, 3600, 7200);
    REQUIRE(totals.size() == 1);
    CHECK(totals[0].bytes_sent == 10);
    CHECK(totals[0].bytes_received == 20);
}

TEST_CASE("ties keep app name order") {
    std::vector<UsageRecord> records = {
        {"b.exe", 0, 5, 0},
        {"a.exe", 0, 5, 0},
    };
    std::vector<AppTotal> totals = totalsByApp(records, 0, 1);
    REQUIRE(totals.size() == 2);
    CHECK(totals[0].app == "a.exe");
    CHECK(totals[1].app == "b.exe");
}

TEST_CASE("no records gives no totals") {
    CHECK(totalsByApp({}, 0, 100).empty());
}
