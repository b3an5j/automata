# Automata

A cellular automata is a form of zero-player game, beginning with a board of cells in some configuration and then proceeding to generate future iterations of the board according to some pre-defined rules. Perhaps the most famous cellular automata is [Conway’s Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), in which cells on the board are considered either ’living’ or ’dead’, and swap between states based on their own state and how many cells in their immediate vicinity are alive. Other than the initial board creation, cellular automata do not require any input from a player to continue developing, hence the term ‘zero-player’ game.

## Usage
**`Usage: automata [options] ... [arg]\n`**


### Options

#### Required options
##### -t=<n> or --total=<n>
**Non-negative integer**. Specifies the total number of iterations of the automata to be performed.
The initial board state counts as iteration 0;
every time the board is updated, another iteration has been completed.

##### -s=<n> or --step=<n>
**Positive integer**. Specifies when to print out the current board state.
The state of the board on iteration 0 is always printed out after that, the board should be printed only on the completion of every nth iteration.
For instance, -s = 3 means that iterations 0, 3, 6, 9, and so on would be printed.

##### -l=<n> or --lower=<n>
**Non-negative integer, smaller than *upper* option**. Specifies the minimum number of neighbours a cell must have to be alive in the next iteration.

##### -u=<n> or --upper=<n>
**Integer no larger than 8**. Specifies the maximum number of neighbours a cell can have to be alive in the next iteration.


#### Optional options
##### -w or --wrap
If present, this flag causes the automata to execute in wrapping mode.



### Arg
A single string, specifying rows of the board one by one in order from top to bottom.
Rows will be separated by the forward slash '/'.\
\
**Board MUST be a rectangle**; one line cells are allowed.\
For instance, `101110`.\
\
Maximum size of the board is **10*10**, which means the biggest input would be\
`XXXXXXXXXX/XXXXXXXXXX/XXXXXXXXXX/XXXXXXXXXX/XXXXXXXXXX/XXXXXXXXXX/XXXXXXXXXX/XXXXXXXXXX/XXXXXXXXXX/XXXXXXXXXX`

For instance,\
`./automata 0101/0001/1100`\
would create a 3x4 board as follows:
```
0101
0001
1100
```
---
### **Acknowledgements**
#### Makefile related
https://www.gnu.org/prep/standards/html_node/Makefile-Conventions.html
https://www.gnu.org/software/make/manual/html_node/index.html
https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
https://stackoverflow.com/questions/3375697/what-are-the-useful-gcc-flags-for-c
https://stackoverflow.com/questions/519342/what-is-the-difference-between-i-and-l-in-makefile
https://stackoverflow.com/questions/24005166/gnu-make-silent-by-default
https://www.youtube.com/watch?v=z4uPHjxYyPs

#### Linux bash related
https://en.wikipedia.org/wiki/Chmod
https://tecadmin.net/tutorial/bash-scripting/bash-command-arguments/
https://stackoverflow.com/questions/125281/how-do-i-remove-the-file-suffix-and-path-portion-from-a-path-string-in-bash

#### others
https://dev.to/talhabalaj/setup-visual-studio-code-for-multi-file-c-projects-1jpi
https://stackoverflow.com/questions/1052818/create-a-pointer-to-two-dimensional-arrays
https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax
