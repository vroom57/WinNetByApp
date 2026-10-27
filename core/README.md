# core

Logic that doesn't call Windows APIs: usage records, per-app totals, and
later CSV export and app grouping. Keeping it OS-free makes it easy to
unit-test.

Anything that touches Windows (reading SRUM, the viewer window) belongs in
`app/`.
