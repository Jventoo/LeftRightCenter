# Assignment 1 - Jack Vento
## The Program

The program is a psuedo-randomized version of the game Left, Right, Center. Player names, starting balances, and turn order are all predetermined. The only way to influence the outcome of the game are through these two inputs:
* Seed: An unsigned 32 bit integer that determines how the "randomization" will go and effectively how the game will play out.
* Number of Players: Any integer between 2 and 10 (inclusive).

Run the program using `./lrc` after compiling using `make`.

## Makefile
* `make` will compile the program to an executable named "*lrc*".
* `make clean` removes all compiler-generated files.
* `infer` is also an optional featured command, which the program passes.