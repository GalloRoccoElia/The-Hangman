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
    POST_GAME,
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
    short * wordFlags;
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


int main(int argc, char const *argv[])
{

    system("clear");

    GameState game_state;
    WordState wordState;
    char replay = 'N';

    // TITLE FASE
    initGameState(&game_state, TITLE, NOT_SET, &wordState, 0);
    printGUI(&game_state);
    getchar();
    // ripulisci buffer
    do
    {
        // PRE_GAME FASE
        initGameState(&game_state, PRE_GAME, NOT_SET, &wordState, 0);
        printGUI(&game_state);

        // Difficulty choise

        Difficulty difficulty;
        scanf("%u", &difficulty); // u sta per unsigned

        // Init game based on difficulty
        char * str = initGame(&game_state, difficulty);
        initWordState(&game_state, str);
        
        printf("FUORI WORD: %s\n", game_state.wordState->word);
        char letter;
        do
        {
            printGUI(&game_state);
            while (getchar() != '\n') {}
            printf("DENTRO PRIMA WORD: %s\n", game_state.wordState->word);
            scanf("%c", &letter);
            
            for (short i = 0; i < 10; i++)
            {
                printf("%d", game_state.wordState->wordFlags[i]);
            }
            
            printf("DENTRO WORD: %s\n", game_state.wordState->word);           
            initGameState(&game_state, IN_GAME, (game_state.difficulty), (game_state.wordState), (game_state.attempts) + checkLetter(&game_state, letter));
        } while ((game_state.attempts) > 0);

        // initGameState(&game_state, POST_GAME, NOT_SET, &wordState, 0);
        // printGUI(&game_state);

        // scanf("%*c");
        // scanf("%c", &replay);

    } while (toupper(replay) == 'Y');
    printf("FINALE: %s\n", game_state.wordState->word);

    // initGameState(&game_state, END_GAME, NOT_SET, &wordState, 0);
    // printGUI(&game_state);
    
    return 0;
}


/**
 * Initiate the state of the game, setting the attempts and the state too
 */
void initGameState(GameState * gameState, State s, Difficulty d, WordState * wState, int a) {
    gameState -> state = s;
    gameState -> difficulty = d;
    gameState -> wordState = wState;
    gameState -> attempts = a;
}

/**
 * Initiate the state of the word, setting everything needed for word check: `word` and `wordFlags`
 */
void initWordState(GameState * gState, char * w) {
    gState -> wordState -> word = w;
    short * flags = (short *)calloc(strlen(w), sizeof(short));
    gState -> wordState -> wordFlags = flags;
    return;
}

/**
 * Initializes the `game_state` by `difficulty`, also loads the words' file based on `difficulty`.
 */
char * initGame(GameState * game_state, Difficulty difficulty) {
    // GUI x difficulty
        // load del file parole
    // parser(file)
    // array con parole
    // return parola

    // in base alla difficoltà si sceglie il file e si costruisce l'array di parole
    char words[10][10] = {"sus", "aaaaaaaaa"};
    short max_attempt = (difficulty == EXTREME) ? MAX_ATTEMPT_EXTREME : MAX_ATTEMPT_BASE;

    initGameState(game_state, IN_GAME, difficulty, game_state -> wordState, max_attempt);

    // char word[] = chooseWord(words);
    char * word;
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
 */
int checkLetter(GameState * gameState, char letter) {
    char * word = gameState -> wordState -> word;
    printf("WORD%s\n", word);
    printf("LETT%c\n", letter);
    for (short i = 0; word[i] != '\0'; i++)
    {
        if (letter == word[i])
        {   
            return 0;
        }
    }
    
    return -1;
}

bool checkWord(GameState * game_state) {
    return true;
}


/**
 * Print the GUI based on the game state
 */
void printGUI(GameState * GState) {
    printf("\n");
    //system("clear");
    switch (GState -> state)
    {
    case TITLE:
        printf("╔═════════╦═════════════════════════════╗\n");
        printf("║         ║                             ║\n");
        printf("║      Hi ║                             ║\n");
        printf("║    O    ║        ╞╡╒╕Ͷ 🅶 ៳╒╕ℕ         ║\n");
        printf("║   ╱|╲   ║                             ║\n");
        printf("║    |    ║      Press any button...    ║\n");
        printf("║   ╱ ╲   ║                    by Gallo ║\n");
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
    case POST_GAME:
        printf("╔════╦════════════╦═════════════════════╗\n");
        printf("║    | AAAAAA!!!  ║      ¥ϙʊ  ∟ʘᶊᶒ      ║\n");
        printf("║    O            ║                     ║\n");
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

void printAttempts(GameState * GState) {
    for (short i = 0; i < (GState -> attempts); i++) {
        printf("♥");
    }
    for (short i = 0; i < 13 + (MAX_ATTEMPT_BASE - (GState -> attempts)); i++) {
        printf(" ");
    }
    printf("║\n");
    return;
}

void printBody(GameState * GState) {
        printf("║    O    ║                             ║\n");
        printf("║   ");
        ((GState -> attempts) < 6) ? printf("╱") : printf(" ");
        ((GState -> attempts) < 5) ? printf("|") : printf(" ");
        ((GState -> attempts) < 4) ? printf("╲") : printf(" ");
        printf("   ║                             ║\n");
        printf("║    ");
        ((GState -> attempts) < 3) ? printf("|") : printf(" ");
        printf("    ║                             ║\n");
        printf("║   ");
        ((GState -> attempts) < 2) ? printf("╱ ") : printf("  ");
        ((GState -> attempts) < 1) ? printf("╲") : printf(" ");
        printf("   ║                             ║\n");
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