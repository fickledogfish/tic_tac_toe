Tic Tac Toe
===========

Following what I did in the [Combat Simulator][combatsim], the [second game challenge][challenge] proposes a game of Tic Tac Toe.

Again, this is probably over-complicated with types and the Board class, but it works as I want.

Instructions
============

To compile and run this program, all you need is [CMake][cmake] and a C++ compiler that supports C++11.

If you are not familiar with CMake, the instructions are simple: make a build directory inside the project tree and, from inside of it, call CMake poiting to the folder above. It will generate the necessary files to build the program in your machine; in a \*nix system:

```
mkdir build; cd build; cmake ..; make
```

will create the `main` executable inside the `build` directory.

In a Windows machine, apparently CMake generates Visual Studio files. Check the documentation.

[cmake]: https://cmake.org/
[combatsim]: https://github.com/fickledogfish/combat_simulator
[challenge]: https://youtu.be/gm2yPC65X78
