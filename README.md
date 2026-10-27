# Win Network by App

See how much each app on your Windows PC has uploaded and downloaded.

Windows already keeps a record of this, about the last 30–60 days, hour by
hour, in a built-in database called SRUM (System Resource Usage Monitor).
But it never shows it to you split into upload and download. Win Network by
App reads that record and shows it as a list of apps you can sort, with a
chart for each app.

It's a single `.exe`: nothing to install, no background service, and nothing
is blocked or changed. It only reads.

## Where things stand

- **Now:** step V1, reading the SRUM data. There's nothing to download or
  run yet.
- **Details:** [docs/plan.md](docs/plan.md) (order of work),
  [docs/ideas.md](docs/ideas.md) (design notes and decisions).

## Good to know

- **It needs administrator rights.** Windows keeps the SRUM database locked,
  so the app makes a temporary copy of it, which needs admin. Expect one UAC
  prompt each time you start it.
- **It's history, not live.** Windows saves the data about once an hour, so
  the most recent hour or so won't show up yet.
- **Windows only** (Windows 10 and 11).

## Repository layout

```
WinNetByApp/
├── core/      Logic that doesn't call Windows APIs (usage totals, export)
├── app/       Windows parts: reading SRUM, the viewer window
├── tests/     Unit tests for core/
├── scripts/   Build and helper scripts
└── docs/      Plan, design notes and behavior
```

## Building

Needs Visual Studio 2022 or later with the C++ workload (it includes CMake
and Ninja).

- From a command prompt: `scripts\build.cmd` (or `scripts\build.cmd release`)
- In Visual Studio: **File → Open → Folder** and pick this folder.

## Background

Win Network by App started as a step inside
[ByteLeash](https://github.com/vroom57/ByteLeash), a project to limit how
much each app can upload. Seeing the data first turned out to be useful on
its own, so it became a separate tool.

## Contact and support

- **Bugs and feature requests:** open an
  [issue](https://github.com/vroom57/WinNetByApp/issues). Please include your
  Windows version and what you expected to happen.
- **Security problems:** please don't open a public issue. Report them
  privately as described in [SECURITY.md](SECURITY.md).

Win Network by App is a personal project, so replies are best effort.

## License

Win Network by App is licensed under the GNU General Public License v3.0.
See [LICENSE](LICENSE).
