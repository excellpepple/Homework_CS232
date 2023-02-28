/**
 * fifteen.c
 *
 * Refer to Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */


/*
 * @author: Excellent Willie-Pepple
 * 1. Besides 4 × 4 (which are Game of Fifteen’s dimensions), what other dimensions does the
 * framework allow?
 *  3 x 3, 5 x 5, 6 x 6, 7 x 7, 9 x 9
 *
 * 2. With what sort of data structure is the game’s board represented?
 *
 * 3. What function is called to greet the player at game’s start?
 * greet()
 * 4. What functions do you apparently need to implement?
 * init()
 * draw()
 * move()
 * won()
 * */


#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

#ifndef INT_MAX
    #define INT_MAX 12345678
#endif // INT_MAX

// board
int board[DIM_MAX][DIM_MAX];
int winState[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void greet(void);
void init(void);
void draw(void);
short move(int tile);
short won(void);
int get_int();
int isPrime(int d);

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();
    // initialize the board
    init();

    // accept moves until game is won
    while (1)
    {
        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        printf("\n");

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Get an non-negative integer from user input
 * If the input is not non-negative integer, return INT_MAX
 */
 int get_int()
 {
    int input = 0;
    short invalid = 0;

    char c = getchar();
    if (c == '\n')
        return INT_MAX;

    while (c != '\n') 
    {
        if ((c >= '0') && ( c <= '9'))
        {
            input = input * 10 + (c - '0');
        } else {
            invalid = 1;
        }

        c = getchar();
    }

    if (invalid)
        return INT_MAX;
    else 
        return input;
 }

/**
 * Greets player.
 */
void greet(void)
{    
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // TODO
    int Dominant = (d*d) - 1;
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            int num = Dominant - (i * d + j);
            board[i][j] = num;
        }

        if(d % 2 == 0){
            board[d-1][d-2] = 2;
            board[d-1][d-3] = 1;
        }
        board[d-1][d-1] = 0;

    }
    // Initializes the WinState
    int count = 1;
    for(int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            winState[i][j] = (count <= Dominant)? count++: 0;
        }
    }



}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    printf("Board\n");
    // TODO
    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            printf("%d \t", board[i][j]);
        }
        printf("\n");

    }
    printf("\n");

//    for (int i = 0; i < d; i++){
//        for (int j = 0; j < d; j++){
//            if (winState[i][j] != 0){
//                printf("%d \t", winState[i][j]);
//            } else{
//                printf("X \t");
//            }
//        }
//        printf("\n");
////
//    }
}

/**
 * If tile borders empty space, moves tile and returns 1, else
 * returns 0.
 */
struct BoardPosition{
    int i;
    int j;
};


short move(int tile)
{
    struct BoardPosition position;
    for (int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            if (tile == board[i][j]) {
                position.i = i;
                position.j = j;
                break;
            }
        }
    }
    // check the bottom side for space
    if(position.i + 1 < d && board[position.i + 1][position.j] == 0) {
        board[position.i + 1][position.j] = board[position.i][position.j];
        board[position.i][position.j] = 0;
        return 1;
    // check the top side for space
    } else if(position.i - 1 > -1 && board[position.i - 1][position.j] == 0) {
        board[position.i - 1][position.j] = board[position.i][position.j];
        board[position.i][position.j] = 0;
        return 1;
    // check the right side for space
    } else if(position.j + 1 < d && board[position.i][position.j + 1] == 0) {
        board[position.i][position.j + 1] = board[position.i][position.j];
        board[position.i][position.j] = 0;
        return 1;
        //check  the left side for space
    } else if(position.j - 1 > -1 && board[position.i][position.j - 1] == 0) {
        board[position.i][position.j - 1] = board[position.i][position.j];
        board[position.i][position.j] = 0;
        return 1;
        /* Otherwise, return a fail. */
    } else {
        return 0;
    }
}

/**
 * Returns 1 if game is won (i.e., board is in winning configuration),
 * else 0.
 */
short won(void)
{
    // TODO
    int flag = 0;
    for (int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            if (board[i][j] != winState[i][j]) {
                flag = 0;
                break;
            }
        }
    }
    return flag;
}
