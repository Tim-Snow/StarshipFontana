# Starship Fontana #

This is an example C++ application using the SDL library.
It tries to be as nicely C++11 as possible but do keep in
mind that SDL is written in C and, at some stage, you have
to interface with it.

## Story ##
The evil b’Kuhn has stolen the code to Earth’s defence system.
With this code he can, at any time, defeat the entire human race.
Only one woman is brave enough to go after b’Kuhn. Will she be
Earth’s hero? Puzzle your way though the universe in the company
of Commander Fontana in **Starship Fontana**.

## Installation ##
You will have to have the SDL development libraries installed on
your system.  The easiest way to compile is to use a command-line

`$ g++ -c src/Main.cpp`
`$ g++ -o starship src/Main.o -lSDL`

which will produce an executable file called "starship" in the
top-level directory.  To execute this file do the following

`$ ./starship`
 
from the top-level directory.  The game will expect to find the
`assets` directory under its current working directory.

## Credits ##
The sprites in this game come directly from 
[SpriteLib](http://www.widgetworx.com/widgetworx/portfolio/spritelib.html) and are used
under the terms of the [CPL 1.0](http://opensource.org/licenses/cpl1.0.php).


The event system is based on [Libsigc++](http://libsigc.sourceforge.net/)
and is used under the [LGPL](http://www.gnu.org/copyleft/lgpl.html).
