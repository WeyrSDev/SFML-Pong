===============================================================================
PONG with SFML - Copyright (c) 2015 Sebastian 'SeriousITGuy' Brack
This source code is distributed under the ZLIB/PNG license.
See license.txt for more information.
===============================================================================

Pong clone written in C++14 with SFML 2.3.2

Only Player vs Computer is available at the moment.
Player vs Player and Computer vs Computer will be available in a later version.

Console output in debug build is very verbose atm, which is intended.
Release build is more quiet regarding console output.

Controls in menus:
Use Up / Down / Enter to move and select menu entries

Controls ingame:
Up   : Move paddle up
Down : Move paddle down
ESC  : Goto pause screen
F12  : Capture screenshot
       (defaults to "screenshot.png" so new shots overwrite old)

In debug build the following controls are enabled:

F1   : Toggle debug info display
F2   : Toggle ball movement
F3   : Toggle single frame mode
F4   : Advance one frame in single frame mode
       (does nothing if not in single frame mode)