# app

The Windows parts of WinNetByApp, built as `winnetbyapp.exe`:

- **Reading SRUM** (plan V1): copy the locked `SRUDB.dat` through a volume
  shadow copy and read it with Windows' own ESE engine (`esent.dll`).
- **Viewer window** (plan V2): a standalone Win32 window, no tray icon or
  service.

**Status:** placeholder. `winnetbyapp.exe` prints a version line and exits.
