# Gearworks Engine

_A little ASCII art always helps_
```
   _____                                    _        
  / ____|                                  | |       
 | |  __  ___  __ _ _ ____      _____  _ __| | _____ 
 | | |_ |/ _ \/ _` | '__\ \ /\ / / _ \| '__| |/ / __|
 | |__| |  __/ (_| | |   \ V  V / (_) | |  |   <\__ \
  \_____|\___|\__,_|_|    \_/\_/ \___/|_|  |_|\_\___/
```

## Change log
You can read the development log in the file `CHANGELOG.md`, linked [here](CHANGELOG.md).

I also have a ClickUp list dedicated to the Gearworks Engine project; this is not public at the moment although I plan to release it at some point in the future.

## Commit guidelines
When committing to this project, do the following:
- Name the commit after the most up-to-date version included in that commit, e.g. `Version d1.4.1`.
- In the commit description, summarize the additions clearly with correct grammar and spelling because hey, this is my repo, so I get to be pedantic!
- Make sure to include any additions to the [`CHANGELOG.md`](CHANGELOG.md) file.

Whenever you update the `__PROG_VERSION_MAJOR__` or `__PROG_VERSION_MINOR__` macros, commit your changes. On the flip side: whenever you commit your changes, update the `__PROG_VERSION_MAJOR__` or `__PROG_VERSION_MINOR__` macros.

When committing a .md file, do whatever, unless it's a complete overhaul, in which case you should say something like `A complete overhaul of [this file]`. Really, just leave it as the default `Update [this file].md`.
