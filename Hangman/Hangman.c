#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Parser.c"

#define MAX_ATTEMPT_BASE 6
#define MAX_ATTEMPT_EXTREME 3

typedef enum {
    TITLE,
    PRE_GAME,
    IN_GAME,
    IN_GAME_WORD_REUSED,
    POST_GAME_WIN,
    POST_GAME_LOSE,
    END_GAME,
} State;

typedef enum {
    NOT_SET = 0,
    EASY = 1,
    MEDIUM = 2,
    HARD = 3,
    EXTREME = 4,
} Difficulty;

typedef struct {
    char * word;
    bool * wordFlags;
} WordState;

typedef struct {
    State state;
    Difficulty difficulty;
    WordState * wordState;
    int attempts;
} GameState;

// Prototipes
void terminate(short int, char *);
void initGameState(GameState *, State, Difficulty, WordState *, int);
void initWordState(GameState *, char *);
char * initGame(GameState *, Difficulty);
char * chooseWord(char **);
int checkLetter(GameState *, char);
bool checkWord(GameState *);
void printGUI(GameState *);
void printAttempts(GameState *);
void printBody(GameState *);
void printWord(GameState *);


int main(int argc, char const *argv[])
{

    system("clear");

    GameState gState;
    WordState wState;
    char replay = 'N';

    // TITLE Fase
    initGameState(&gState, TITLE, NOT_SET, &wState, 0);
    printGUI(&gState);
    getchar();
    do
    {
        // PRE_GAME Fase
        initGameState(&gState, PRE_GAME, NOT_SET, &wState, 0);
        printGUI(&gState);

        // Difficulty choise
        Difficulty diff;
        scanf("%u", &diff);

        // Init game based on difficulty
        char * str = initGame(&gState, diff);
        initWordState(&gState, str);

        // IN_GAME Fase
        char letter;
        bool win;
        do
        {
            printGUI(&gState);
            while (getchar() != '\n') {} // clean the input buffer
            scanf("%c", &letter);
            initGameState(&gState, IN_GAME, (gState.difficulty), (gState.wordState), (gState.attempts) + checkLetter(&gState, letter));
            win = checkWord(&gState);
        } while ((gState.attempts) > 0 && !win);

        if (win)
        {
            initGameState(&gState, POST_GAME_WIN, NOT_SET, &wState, 0);
        }
        else
        {
            initGameState(&gState, POST_GAME_LOSE, NOT_SET, &wState, 0);
        }
        printGUI(&gState);

        while (getchar() != '\n') {} // clean the input buffer
        scanf("%*c");
        scanf("%c", &replay);

    } while (toupper(replay) == 'Y');

    initGameState(&gState, END_GAME, NOT_SET, &wState, 0);
    printGUI(&gState);
    
    return 0;
}


/**
 * Initiate the state of the game, setting the `attempts`, `difficulty` and the `state` too
 * Also initiate the `WordState`.
 */
void initGameState(GameState * gState, State s, Difficulty d, WordState * wState, int a) {
    gState -> state = s;
    gState -> difficulty = d;
    gState -> wordState = wState;
    gState -> attempts = a;
}

/**
 * Initiate the state of the word, setting everything needed for word check: `word` and `wordFlags`
 */
void initWordState(GameState * gState, char * w) {
    gState -> wordState -> word = w;
    bool * flags = (bool *)calloc(strlen(w), sizeof(bool));
    gState -> wordState -> wordFlags = flags;
    return;
}

/**
 * Initializes the `gState` by `difficulty`, also loads the words' file based on `difficulty`.
 */
char * initGame(GameState * gState, Difficulty diff) {
    // GUI x difficulty
        // load del file parole
    // parser(file)
    // array con parole
    // return parola

    // in base alla difficoltà si sceglie il file e si costruisce l'array di parole
    // la lunghezza della stringa non deve superare word[][n]
    char words[10][10] = {"Telefono", "dddddddd"};
    short max_attempt = (diff == EXTREME) ? MAX_ATTEMPT_EXTREME : MAX_ATTEMPT_BASE;

    initGameState(gState, IN_GAME, diff, gState -> wordState, max_attempt);

    // char word[] = chooseWord(words);
    char * word = (char *)malloc(strlen(words[0]) * sizeof(char));
    strcpy(word, words[0]);

    return word;
}

/**
 * Choose a randomic word from the array
 */
char * chooseWord(char ** words) {
    char * word;

    // random

    return word;
}

/**
 * Check if the letter is in the word.
 * Returns -1 if it's not, 0 otherwise
 * Also updates the `wordFlags`
 */
int checkLetter(GameState * gState, char letter) {
    char * word = gState -> wordState -> word;
    for (short i = 0; word[i] != '\0'; i++)
    {
        if (letter == word[i])
        {   
            // update the wordFlags
            for (; i < strlen(word); i++)
            {
                if (letter == word[i])
                {
                    gState -> wordState -> wordFlags[i] = true;
                }
            }
            return 0;
        }
    }
    
    return -1;
}


/**
 * Check if the word has been guessed.
 * Retruns `false` if it's not, `true` otherwise
 */
bool checkWord(GameState * gState) {
    for (short i = 0; i < strlen(gState -> wordState -> word); i++)
    {
        if (gState -> wordState -> wordFlags[i] == false)
        {
            return false;
        }
    }
    return true;
}


/**
 * Print the GUI based on the game state
 */
void printGUI(GameState * GState) {
    printf("\n");
    system("clear");
    switch (GState -> state)
    {
    case TITLE:
        printf("╔═════════╦═════════════════════════════╗\n");
        printf("║         ║                             ║\n");
        printf("║      Hi ║                             ║\n");
        printf("║    O    ║        ╞╡╒╕Ͷ 🅶 ៳╒╕ℕ         ║\n");
        printf("║   ╱|╲   ║                             ║\n");
        printf("║    |    ║        Press ENTER ...      ║\n");
        printf("║   ╱ ╲   ║                             ║\n");
        printf("╠═════════╬═════════════════════════════╝\n");
        printf("╙ PROMPT: ╨ $ ");
        break;
    case PRE_GAME:
        printf("╔═════════════════╦═════════════════════╗\n");
        printf("║      Select     ║         TYPE        ║\n");
        printf("║      difficulty ║                     ║\n");
        printf("║    O            ║     1  \"easy\"       ║\n");
        printf("║   ╱|╲           ║     2  \"medium\"     ║\n");
        printf("║    |            ║     3  \"hard\"       ║\n");
        printf("║   ╱ ╲           ║     4  \"ĘᶍŤƦƎ៳ɇ\"    ║\n");
        printf("╠═════════╦═══════╩═════════════════════╝\n");
        printf("╙ PROMPT: ╨ $ ");
        break;
    case IN_GAME:
        printf("╔════╦════╦═════════════════════════════╗\n");
        printf("║    |    ║ ATTEMPS: ");
        printAttempts(GState);
        printBody(GState);
        printf("║         ║                             ║\n");
        printf("╠═════════╬═════════════════════════════╝\n");
        printf("╙ PROMPT: ╨ $ ");
        break;
    case IN_GAME_WORD_REUSED:
        printf("╔═════════════════╦═════════════════════╗\n");
        printf("║      word r     ║                     ║\n");
        printf("║                 ║                     ║\n");
        printf("║    O            ║                     ║\n");
        printf("║   ╱|╲           ║                     ║\n");
        printf("║    |            ║                     ║\n");
        printf("║   ╱ ╲           ║                     ║\n");
        printf("╠═════════╦═══════╩═════════════════════╝\n");
        printf("╙ PROMPT: ╨ $ \n");
        break;
    case POST_GAME_WIN:
        printf("╔════╦════════════╦═════════════════════╗\n");
        printf("║    /            ║       You Win       ║\n");
        printf("║      close call ║                     ║\n");
        printf("║    O            ║       Replay?       ║\n");
        printf("║   ╱|╲           ║                     ║\n");
        printf("║    |            ║       Y     N       ║\n");
        printf("║   ╱ ╲           ║                     ║\n");
        printf("╠═════════╦═══════╩═════════════════════╝\n");
        printf("╙ PROMPT: ╨ $ ");
        break;
    case POST_GAME_LOSE:
        printf("╔════╦════════════╦═════════════════════╗\n");
        printf("║    | AAAHgrh..  ║      ¥ϙʊ  ∟ʘᶊᶒ      ║\n");
        printf("║    X            ║                     ║\n");
        printf("║   ╱|╲           ║       Replay?       ║\n");
        printf("║    |            ║                     ║\n");
        printf("║   ╱ ╲           ║       Y     N       ║\n");
        printf("║                 ║                     ║\n");
        printf("╠═════════╦═══════╩═════════════════════╝\n");
        printf("╙ PROMPT: ╨ $ ");
        break;
    case END_GAME:
        printf("╔═══════════════════════════════════════╗\n");
        printf("║ Credit: Gallo Rocco Elia              ║\n");
        printf("║                                       ║\n");
        printf("║                                       ║\n");
        printf("║                                       ║\n");
        printf("║                             For More: ║\n");
        printf("║    https://github.com/GalloRoccoElia  ║\n");
        printf("╚═══════════════════════════════════════╝\n");
        break;
    default:
        break;
    }
}

void printAttempts(GameState * gState) {
    for (short i = 0; i < (gState -> attempts); i++) {
        printf("♥");
    }
    for (short i = 0; i < 13 + (MAX_ATTEMPT_BASE - (gState -> attempts)); i++) {
        printf(" ");
    }
    printf("║\n");
    return;
}

void printBody(GameState * gState) {
        printf("║    O    ║                             ║\n");
        printf("║   ");
        int att = gState -> attempts;
        if (gState -> difficulty == EXTREME)
        {
            (att < 3) ? printf("╱|") : printf("  ");
            (att < 2) ? printf("╲") : printf(" ");
            printf("   ║                             ║\n║    ");
            (att < 2) ? printf("|"): printf(" ");
            printf("    ║");
            printWord(gState);
            printf("║\n║   ");
            (att < 1) ? printf("╱ ╲") : printf("   ");
        }
        else {
            (att < 6) ? printf("╱") : printf(" ");
            (att < 5) ? printf("|") : printf(" ");
            (att < 4) ? printf("╲") : printf(" ");
            printf("   ║                             ║\n");
            printf("║    ");
            (att < 3) ? printf("|") : printf(" ");
            printf("    ║");
            printWord(gState);
            printf("║\n║   ");
            (att < 2) ? printf("╱ ") : printf("  ");
            (att < 1) ? printf("╲") : printf(" ");
        }
        printf("   ║                             ║\n");
}

void printWord(GameState * gState) {
    short wordLength = strlen(gState -> wordState -> word);
    short firstLetter = 14 - (short)(wordLength / 2);
    short i = 0;
    short j = 0;
    for (; i < firstLetter; i++)
    {
        printf(" ");
    }
    for (; j < wordLength; j++)
    {
        if (gState -> wordState -> wordFlags[j] == true)
        {
            printf("%c", gState -> wordState -> word[j]);
        }
        else
        {
            printf("_");
        }
    }
    for (i += j; i < 29; i++)
    {
        printf(" ");
    }
    return;
}

/**
 * Terminate the session with an error message
 * type error [0, 1, ..., 3]
 */
void terminate(short int type_error, char * massage) {
    assert((type_error >= 0) && (type_error <= 2));
    printf("%s", massage);
    exit(type_error);
}