# Win Network by App Plan

The order of work and when each step counts as done. Design decisions live
in [ideas.md](ideas.md), user-facing behavior in [behavior.md](behavior.md).
Update this file as steps finish or the direction changes.

## Goal

A standalone viewer for the per-app network usage Windows already records
in SRUM (System Resource Usage Monitor): bytes sent and received per app,
per hour, for about the last 30–60 days. Single .exe, no tray icon, no
service, nothing blocked.

Why: Windows records this data but shows no per-app upload / download
report (Settings → Data usage gives one combined number; Task Manager and
Resource Monitor show live rates only).

Started 2026-10-26 as the SRUM viewer step in ByteLeash; split into its own
project 2026-10-27.

## V0: Base repo (done 2026-10-27)

- CMake / MSVC build, doctest unit tests, `core/` and `app/` layout, docs.

## V1: Read SRUM (feasibility)

- Copy the live database (`C:\Windows\System32\sru\SRUDB.dat`, kept open
  by Windows) via a volume shadow copy, e.g. `esentutl /y ... /vss`, as
  admin.
- Open the copy with Windows' own ESE database engine (`esent.dll`, part of
  Windows, so no new dependency) and read the network usage table plus the
  ID map (app paths, user SIDs).
- `winnetbyapp.exe` prints / exports per-app bytes sent and received per
  hour (CSV).

**Done when:** the tool's per-app totals on this PC (sent + received)
agree with Settings → Data usage.

## V2: Viewer window

- Standalone Win32 window (no tray), runs as admin (one UAC prompt per
  start).
- App list with **upload and download totals** for a chosen period (last
  24 hours, 7 days, 30 days, all), sortable; svchost services shown by
  service name if SRUM records them that way.
- Per-app hourly chart (Direct2D) of sent / received; filter by network
  adapter / Wi-Fi network if useful.
- Refresh (re-copy SRUM) and CSV export.

**Done when:** you use it on your own PCs to look at what your apps send.

## V3: Review and next direction

- Write down what the data showed: surprising uploaders, patterns over
  time, apps that upload more than they download.
- Collect alerting ideas (e.g. "app X uploaded more than N MB today", "new
  app started uploading") in ideas.md.
- **Decide the next direction** (alerting, a first release, feeding
  ByteLeash) and update this plan.

**Done when:** the next direction is chosen and recorded here.
