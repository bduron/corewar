Corewar
======

Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors") compete for control of a virtual computer.
These battle programs are written in an abstract assembly language called Redcode.

42 Version
======

We don't use the same set of assembly instruction as the original Corewar and we have some modulo limitation about the distance to read and write.
This project was the final project of the Algorithm branch and we wrote it has a team with :
* [cedric](https://github.com/cpoulet)
* [kevin](https://github.com/kcosta42)
* [pierre](https://github.com/wolrajhti)
* and me

Our vizualisator
======

[![giphy.gif](https://raw.githubusercontent.com/cpoulet/Corewar/master/gif/Corewar.gif)](https://raw.githubusercontent.com/cpoulet/Corewar/master/gif/Corewar.gif)

[![Life.gif](https://raw.githubusercontent.com/cpoulet/Corewar/master/gif/Life.gif)](https://raw.githubusercontent.com/cpoulet/Corewar/master/gif/Life.gif)

Usage
======

./corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>
* -a        : Prints output from "aff" (Default is to hide it)
* -d N      : Dumps memory after N cycles then exits
* -s N      : Runs N cycles, dumps memory, pauses, then repeats
* -v N      : Verbosity levels, can be added together to enable several
 * - 0 : Show only essentials
 * - 1 : Show lives
 * - 2 : Show cycles
 * - 4 : Show operations (Params are NOT litteral ...)
 * - 8 : Show deaths
 * - 16 : Show PC movements (Except for jumps)
* -i        : Ncurses output mode
