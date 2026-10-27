# How Win Network by App behaves

What users see and can rely on. Keep this in sync with the code.

**Status:** nothing user-facing yet. This file fills in as plan steps V1
and V2 land.

## Planned

- Starts with one UAC prompt (it needs admin to copy the SRUM database).
- Reads a temporary copy of the database and deletes the copy afterwards.
  It never changes the original or any other system setting.
- Shows each app's upload and download for a chosen period. Numbers are
  what Windows recorded, about hourly, so the latest hour may be missing.
