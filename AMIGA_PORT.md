TecnoballZ 0.93.1 for AmigaOS 3.x
=================================

TecnoballZ (TLK Games, https://linux.tlk.fr/games/TecnoballZ/), the brick
breaker after TLK's own TecnoBall on the Amiga: 50 levels in five areas and
11 guardian levels, a shop between levels where the money you catch buys
paddles, guns, extra balls and the Gigablitz. For AmigaOS 3.x on a 68040
or 68060 with an FPU and an RTG screen, on OpenGPU's SDL 1.2
(sdl12-compat).

Base: tecnoballz_0.93.1.orig.tar.gz from Debian (sha256
5915bbe9efbf79713f2b0bb23a3cd33c54272b03739db22b52bcf5e1f9ef82e8), with
Debian's patches (0.93.1-14) as the second commit. Branch
team2/tecnoballz-amiga.

Status: plays in the lab (Instance-45 on GFOpenUp 0.8.19, 6 November
2026): the menu, area 1 level 1 (the ball launched, bricks broken, a life
lost, the score), the Escape menu, Cause game over to the Top Ten with the
new score written to tecnoballz.hi, the menu again and Game Exit back to
the Shell; user/tecnoballz.conf written. The music modules and the sounds
load without an error; the lab is muted, so they were not heard there.


What you need
-------------

- A 68040 or 68060 with an FPU, AmigaOS 3.x, an RTG card (or the
  AmigaChrome lab).
- GFOpenUp 0.8.18 or later (LIBS:OpenGPU/SDL2.module). Everything else is
  in the program.


How to play
-----------

Open the TecnoballZ icon, or run TecnoballZ from a Shell. It opens a
640x480 window (TecnoballZ --full for a full screen, --320 for the small
size; the settings are kept in the drawer's user/tecnoballz.conf). The
mouse moves the paddle and its left button releases the ball; Space
releases it too, left Ctrl fires, left Alt fires the Gigablitz (or tilts),
P pauses, Escape is the menu (continue, game over, quit). The pictures,
levels, sounds and music are in the drawer's data/; the high scores are
tecnoballz.hi in the drawer.


Building
--------

    make -f amiga/Makefile.amigaos -j2 dist

with GFOpenAmigaGCC 16.2.0-open4, the OpenNDK headers, the OpenGPU kit and
the Team's static libpng and zlib (see the Makefile's head). The drawer is
dist/TecnoballZ (and dist/TecnoballZ.info).


What was changed
----------------

- src/handler_resources.cc: the data is PROGDIR:data only (a leading "/"
  is the parent drawer to AmigaDOS), and a name with a ":" is a full name,
  so the high scores are PROGDIR:tecnoballz.hi.
- src/configfile.cc: the settings are in the drawer's user/, and with no
  $USER the players get the game's own name (not a NULL pointer).
- No SDL_image or SDL_mixer 1.2 for OpenGPU's SDL 1.2:
  amiga/sdl_image_lite.c loads the game's palette PNGs as 8-bit surfaces
  with their palettes (libpng); amiga/sdl_mixer_lite.c is the Team's WAV
  mixer with the music from libmikmod 3.3.16 (amiga/libmikmod: its player,
  ProTracker and XM loaders and no-sound driver), laid out as SDL_mixer
  1.2's, since the game reads the module's position through it to play a
  tune's parts. TinyXML is the Team's copy (amiga/tinyxml, zlib licence).
- amiga/amiga_prefix.hpp: the C++ streams first in every file (the
  toolchain's pthread.h wraps read() and write() in macros once
  <unistd.h> is in). amiga/stack.c: 512 KB of stack.


Licences
--------

TecnoballZ, its pictures, levels, sounds and music: GPL 3 or later
(COPYING.txt). libmikmod: LGPL 2 or later (COPYING-libmikmod.txt). TinyXML:
zlib licence. The Amiga files (amiga/): GPL 3 or later, the AmiCradle
Team; the icons are our own GlowIcons (amiga/icons/art/tecnoballz.svg).
