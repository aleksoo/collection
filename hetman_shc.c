#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

short int n = 4;                // Size of checker;
int max_s = 100;                // Number of max steps;
int visibility = 1;             // Displays additional information in console, change to 1 to enable, change to 0 to disable;

void simple_hill(void);         // Starts Simple Hill Climbing Algorithm;
void rand_hetman(short*);       // Generates initial random state of checker;
void neighbour(short*);         // Moves one random queen to random place in column;
int evaluation(short*);         // Returns number of conflicts on checker in passed state;
void printCombination(short*);  // Prints checker of passed state;
void randomizer(void);          // Sets seed;
void values(short*);            // Prints locations of queens;


int main(void)
{
    simple_hill();
    return 0;
}

void simple_hill(void)
{
    randomizer();

        // Setting initial state and it's evaluation;
    short *queen;
    queen = (short*)(malloc(n * sizeof(short)));
    rand_hetman(queen);
    int eval = evaluation(queen);

        // Setting temporary state for neighbour state generating purposes;
    short int *queen_temp;
    queen_temp = (short*)(malloc(n * sizeof(short)));
    memcpy((void*)queen_temp, (void*)queen,  sizeof(short)*(n+1));
    int eval_temp = eval;

    printf("First state\n");
    printCombination(queen); // Prints initial state;

    int k = 0; // Steps counter

    while (k < max_s) // We try to find solution in "max_s" steps;
    {
        neighbour(queen_temp);
        eval_temp = evaluation(queen_temp);
        if(visibility) printCombination(queen_temp);

        if (eval_temp <= eval) // Checking if new state is better (or equal), if yes, we put newly generated state in current state;
        {
            memcpy((void*)queen, (void*)queen_temp,  sizeof(short)*(n+1));
            eval = eval_temp;
            if(visibility)
            {
                printf("=====NEW STATE=====\nNumber of conflicts: %d\n", eval);
                printCombination(queen);
            }
        }

        if (eval == 0) // Found solution;
        {
            printf("Found solution in %d steps\n", k);
            printCombination(queen);
            break;
        }

        k++;
    }

    if (k >= max_s)
    {
        printf("\nCan\'t find solution in %d steps\nNumber of conflicts: %d\nFinal state\n\n", max_s, eval);
        printCombination(queen);
    }

    free(queen);
}

void neighbour(short *queen_move)
{
    short i = rand() % n; // Randomly chosen queen in "i" column;
    short temp = queen_move[i];
    queen_move[i] = (short)(rand() % n);
    while (temp == queen_move[i]) queen_move[i] = rand() % n; // Generating new row for chosen queen until it is different than given one;
    if(visibility) printf("\nQueen in %d column is now in %d row\n\n", i, queen_move[i]);
}

int evaluation(short *queen)
{
    int collisions = 0;
    int i = 0, j = 0;
    for (i = 0; i<n-1; i++)
    {
        for (j = i+1; j<n; j++)
        {
            if ( queen[i] == queen[j] || ( abs(i - j) == abs(queen[i] - queen[j]) ) )
            {
                if(visibility) printf("Conflict occurs on tiles %d-%d & %d-%d\n", i, queen[i], j, queen[j]);
                collisions++;
            }
        }
    }
    if(visibility) printf("Number of conflicts: %d\n\n", collisions);
    return collisions;
}

void rand_hetman(short *queen_new)
{
    int i;
    for (i = 0; i<n; i++) queen_new[i] = (short)(rand() % n);
}

void printCombination(short *queen)
{
    int x, y, i, j;
    printf("  ");
    for (i = 0; i<n; i++) printf("%d", i);
    for (i = 0; i<n; i++)
    {
        printf("\n%d ", i);
        for (j = 0; j<n; j++)
        {
            if (queen[j] == i) printf("H");
            else printf("+");
        }
        printf(" %d ", i);
    }
    printf("\n  ");
    for (i = 0; i<n; i++) printf("%d", i);
    printf("\n\n");
}

void values(short *hetman)
{
    short i = 0;
    for (i = 0; i<n; i++)   printf("\n%d - %d\n", i, hetman[i]);
}

void randomizer(void)
{
    int seed;
    time_t tt;
    seed = time(&tt);
    srand(seed);
}
