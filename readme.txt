===============================================================================
PONG with SFML - Copyright (c) 2015 Sebastian 'SeriousITGuy' Brack
This source code is distributed under the ZLIB/PNG license.
See license.txt for more information.
===============================================================================

Pong clone written in C++14 with SFML 2.3.2

Build with Visual Studio 2015 on Windows 7
and with CLion 1.2 / GCC 5.2 on Ubuntu 15.10
===============================================================================

Annotations:

Only Player vs Computer is available at the moment.
Player vs Player and Computer vs Computer will be available in a later version.

Console output in debug build is very verbose atm, which is intended.
Release build is more quiet regarding console output.

===============================================================================

Controls in menus:
Use Up / Down / Enter to move and select menu entries

Controls in game:
Up   : Move paddle up
Down : Move paddle down
ESC  : Go to pause screen
F12  : Capture screenshot

In debug build the following controls are enabled:

F1   : Toggle debug info display
F2   : Toggle ball movement
F3   : Toggle single frame mode
F4   : Advance one frame in single frame mode
       (does nothing if not in single frame mode)
F5   : Instantly win the game to move to game over screen
F6   : Instantly loose the game to move to game over screen

===============================================================================

Changelog:

Build 14:
 - Added CMake support
 - Added fixes for GCC compiler

Build 13:
 - Added base entity class with debug drawing capabilities
 - Added 'Restart' option to pause state
 - Added date time functions to core
 - Screenshot's now include date and time in file names, no overwriting anymore
 - Added timestamp to log system
 - Refactored collision model and physics handling
 - Removed 'add friction on collision', new reflection model is being worked on
 - Removed unnecessary fonts

Build 12:
 - changed game entities from OpenGL primitives to real graphics
 - Heavily tweaked logging system
 - Added graphical debug system

BUILD 11:
 - Minor game changes
 - Completely isolated core framework code from game code
 
BUILD 10:
 - Added logging system to core framework
 - Added credit state ( Main Menu -> Credits )
 
BUILD 6:
 - Added StateStack to support multiple game states
 - Added TitleState and MenuState
 
BUILD 2:
 - First playable prototype

===============================================================================
