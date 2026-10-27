# Win Network by App (WinNetByApp)

Standalone Windows app (single .exe, no tray, no service) that shows how
much each app has uploaded and downloaded, read from the network usage
Windows records in SRUM. Read-only: nothing is blocked or changed. Spun off
from ByteLeash (github.com/vroom57/ByteLeash) on 2026-10-27, where it was
the "SRUM viewer" step. See docs/ideas.md for design and decisions.

## Status (2026-10-27)
- Base repo only. `core/` has `totalsByApp` (per-app sums for a period),
  unit-tested. `app/winnetbyapp.exe` is a placeholder that prints a
  version line.
- No SRUM reading yet.

## Where to pick up
**Next: plan V1**: read SRUM (copy the locked SRUDB.dat via shadow copy,
open with esent.dll, dump per-app bytes sent / received per hour to CSV).
Then V2 (viewer window), V3 (review, decide on alerting). Steps in
docs/plan.md.

## Layout
- `core/`: logic with no Windows API calls. Headers in
  `core/include/winnetbyapp/`.
- `app/`: Windows code (SRUM reading, viewer window), builds
  `winnetbyapp.exe`.
- `tests/core/`: doctest unit tests, one file per core module.
- `scripts/build.cmd [debug|release]`: finds VS, configures, builds, tests.
  Or open the folder in Visual Studio (uses CMakePresets.json). Output in
  `build/<preset>/`.
- `docs/plan.md` (steps V1–V3), `docs/ideas.md` (design source of truth),
  `docs/behavior.md` (user-facing behavior), `SECURITY.md`, `README.md`.

## Tooling
C++20, CMake, MSVC (Visual Studio Community 2026), static CRT (`/MT`),
`/W4 /WX`, doctest 2.5.3 (fetched at configure time with a pinned hash).
SRUM is read with Windows' own `esent.dll`, so no third-party runtime
dependencies. App behavior for users is documented in docs/behavior.md;
keep it in sync.

## Licensing
GPLv3 (LICENSE). If a shipped third-party dependency is ever added, ship a
combined LICENSE.txt with one labeled section per component. doctest is
test-only and doesn't ship.

## Working agreements
- Don't commit without asking. Pushing to GitHub (origin/main) is fine when
  asked to commit and push.
- Commits use the GitHub noreply address
  (190971508+vroom57@users.noreply.github.com, set globally); never the
  personal address.
- docs/ideas.md is the source of truth for design; update it when decisions
  change. Record new discussion topics there as Open questions.
- Reading SRUM needs admin (a UAC prompt the user approves); say so
  beforehand.
