#include <stdio.h>
#include <stdlib.h>
#include </home/gallo_rocco_elia/Lab2/Hangman/Parser.c>
#include <assert.h>

int main(int argc, char const *argv[])
{
    // GUI difficulty
    short int difficulty;
    scanf("%hd", &difficulty);
    printf("%hd\n", difficulty);

    // words = init_game(difficulty)
    // word = choose_word(words)

    // replay

    return 0;
}


/**
 * Initializes the game loading the words' file based on `difficulty`.
 * Returns an `array` of chars
 */
void init_game() {
    // GUI x difficulty
        // load del file parole
    // parser(file)
    // array con parole
    // return array
}

/**
 * Choose a randomic word from the array
 */
char * choose_word(char ** words) {
    char * word;

    // random

    return word;
}

void print_GUI() {

}


// TO DO
/**
 * Terminate the session with an error message
 * type error [0, 1, ..., 3]
 */
void terminate(short int type_error, char * massage) {
    assert((type_error >= 0) && (type_error <= 2));
    printf("%s", massage);
    exit(type_error);
}

