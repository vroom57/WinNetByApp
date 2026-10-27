# Win Network by App: ideas and decisions

Working notes, design decisions and open questions. This file is the
source of truth for design; update it when decisions change. Steps are in
[plan.md](plan.md).

## What it is

A standalone Windows app (single .exe, no tray icon, no service) that
lists every app with its **upload and download** over time, read from
SRUM, the System Resource Usage Monitor that Windows runs all the time.
It only reads; nothing is blocked or changed.

## Decisions

- **2026-10-27: split out of ByteLeash.** The SRUM viewer was step V1–V3
  of ByteLeash's plan. It's useful on its own as a single .exe, so it's a
  separate GPLv3 project. ByteLeash may use it or its data later.
- **2026-10-27: name.** "Win Network by App" (repo `WinNetByApp`, exe
  `winnetbyapp.exe`): describes what it does for non-technical users.
- **2026-10-27: network usage only.** SRUM also records CPU time, energy
  and app run time; those are out of scope for now.
- **No third-party runtime dependencies.** SRUM is read with Windows' own
  ESE API (`esent.dll`), so nothing extra ships.

## What exists already

- **Settings → Network & internet → Advanced network settings → Data
  usage:** per-app totals for 30 days per adapter, but one combined number
  (no up / down split).
- **Task Manager → App history:** combined network column, Store apps by
  default; not a report. **Resource Monitor → Network:** live per-process
  send / receive rates, no totals.
- **Third-party:** NirSoft NetworkUsageView (freeware, not open source)
  and srum-dump (a forensics tool that exports SRUM to spreadsheets).
- Conclusion: the data exists, but nothing simple and open source shows it
  split into up and down for everyday users. That's the gap.

## Technical notes (to verify in V1)

- Database: `C:\Windows\System32\sru\SRUDB.dat`, an ESE ("JET Blue")
  database, held open by Windows (Diagnostic Policy Service). Read a copy
  made through a volume shadow copy (`esentutl /y <file> /vss /d <copy>`
  is built into Windows); needs admin. The copy may need ESE recovery
  before it opens cleanly (srum-dump has notes on this).
- Network data usage table (per srum-dump and public write-ups, verify):
  `{973F5D5C-1D90-4944-BE8E-24B94231A174}`, columns include `TimeStamp`,
  `AppId`, `UserId`, `InterfaceLuid`, `L2ProfileId`, `BytesSent`,
  `BytesRecvd`. `AppId` / `UserId` are indexes into `SruDbIdMapTable`
  (app path or name, user SID).
- Granularity is about **one row per app per hour**; Windows writes to the
  database on its own schedule (roughly hourly), so the last hour or so
  isn't there yet. Retention is roughly 30–60 days.
- `InterfaceLuid` / `L2ProfileId` tell which adapter and which Wi-Fi
  network, which could split home vs. other networks.
- Clean up the temporary copy after reading, and don't leave it where
  other users can read it (it records every user's apps).

## Open questions

1. How does SRUM name svchost services, Store apps and system traffic? How
   should the viewer group them? (ByteLeash's `core/app_identity` has
   rules for version folders and service hosts that could be reused.)
2. Does SRUM count LAN traffic separately or at all?
3. Is the hourly lag acceptable, or should a live layer (ETW, as in
   ByteLeash's probe) fill in the last hour later?
4. Should the app relaunch itself elevated, or require "Run as
   administrator"? (Manifest `requireAdministrator` is simplest.)
5. Alerting ideas: collect them in V3, after using the viewer.
