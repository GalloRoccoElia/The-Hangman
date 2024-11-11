# Hangman Game

### Overview
Hangman is a classic word-guessing game where the player tries to uncover a hidden word by guessing letters one at a time. With each incorrect guess, a part of a hangman figure is drawn, and the player loses a life. 
The objective is to guess the entire word correctly before the figure is completely drawn and the game is over.

_Wikipedia_: https://en.wikipedia.org/wiki/Hangman_(game)  


## Implementation
### States
The game takes shape thanks to the memorization of its state `GameState` which stores information such as:
- __State__: [TITLE, PRE_GAME, IN_GAME, POST_GAME, END_GAME];
- __Difficulty__: [EASY, MEDIUM, HARD, EXTREME];
- __Attempts__: #number of attempts, as well as lives;
- __WordState__: To memorize the word to guess, use
Based on the `GameState.state`, the `GUI` is printed on the `CLI`.

### Difficulty, words and Parser
In the directory there is a `.c` file named `Parser` that has the task of loading the file (chosen based on difficulty) containing the words to guess.

### `CLI` and `GUI`
The `CLI` plays an essential role in the game both for taking input and
for output. Using the `stdio.h` library, a standard GUI is created based on the information contained in the `GameState`.

## Diagram
<div align="center"><img src="https://github.com/GalloRoccoElia/The-Hangman/blob/The-Hangman/Hangman%20Graph.svg"></div>
