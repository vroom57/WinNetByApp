# Security policy

## Reporting a vulnerability

Please report security problems privately, not in a public issue:

1. Go to the repository's **Security** tab.
2. Choose **Report a vulnerability**
   ([direct link](https://github.com/vroom57/WinNetByApp/security/advisories/new)).
3. Describe the problem, the steps to reproduce it, the Win Network by App
   version and Windows version, and what an attacker could do with it.

The report is visible only to you and the maintainer. We can discuss it,
work on a fix privately, and publish an advisory once a fix is available.
Win Network by App is a personal project, so responses are best effort.

## Supported versions

Win Network by App hasn't had a release yet. Until it does, reports should
be against the latest code on `main`. Once releases start, only the latest
release will receive security fixes.

## What counts as a vulnerability

Win Network by App runs as administrator and makes a temporary shadow copy
of a system database, so the most important problems are ones that let
something gain privileges or tamper with the system through it, for
example:

- Getting code to run as administrator through the app, for example by
  planting a file or DLL where it looks for one, or by crafting a database
  copy it reads.
- Making the app write, overwrite or delete files outside its own temporary
  copy.
- Leaving shadow copies or temporary copies of the SRUM database behind
  where other users can read them. The database records what every user's
  apps did.

Win Network by App only reports what Windows recorded. Apps that Windows
doesn't record, or records under another name, aren't vulnerabilities;
please open a regular issue for those.
