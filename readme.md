# Checkers AI with Minimax

Checkers AI with Minimax is a program which runs in terminal
Foobar is a Python library for dealing with word pluralization.

## Project Status

Currently this project's development has slowed to essentially a halt. It is working **only on OSX!**

## Installation

Use git to install the project from
```git
$ git clone https://github.com/mcnameel/Minimax-AI-Checkers
$ cd Minimax-AI-Checkers
$ git submodule update --init --recursive
```

## Usage

```bash
$ mkdir build
$ cd build/
$ cmake ../
$ make
```
When running this program you should enter in 8 program arguments: 
1. Number of games 
2. The algorithm for player 1 (1-7 difficulty)
3. The number of moves for player 1 to look ahead (3-4 standard, 5-6+ slow)
4. Indicates whether to use alpha-beta pruning
5. The algorithm for player 1 (1-7 difficulty)
6. The number of moves for player 1 to look ahead (3-4 standard, 5-6+ slow)
7. Indicates whether to use alpha-beta pruning

Example:

```bash
$ ./Minimax_AI_Checkers 50 3 7 0 4 4 1
```
For 50 games:

Player 1: Evaluation 7, depth 3, without alpha-beta pruning\
vs.\
Player 2: Evaluation 4, depth 4, with alpha-beta pruning

```bash
$ ./Minimax_AI_Checkers 
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)