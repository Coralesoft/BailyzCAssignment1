#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "random.h"
#include "mapping.h"
#include "player.h"
#include "newsleep.h"
#include "terminal.h"
#include "carMovement.h"

/* Define macro for clearing screen based on OS */
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

/* Function to clear terminal screen */
void clearScreen()
{
    system(CLEAR_SCREEN);
}

/* Function to deallocate memory for map and carPlacement arrays */
void deallocateMemory(char ***map, int ***carPlacement, int map_row)
{
    int i;
    for (i = 0; i < map_row; i++)
    {
        free((*map)[i]);
        free((*carPlacement)[i]);
    }
    free(*map);
    free(*carPlacement);
}

/* Function to check and validate command line arguments */
bool checkArgs(int argc, char *argv[], int *map_row, int *map_col)
{
    /* Check correct number of arguments */
    if (argc != 3)
    {
        printf("Usage: %s <map_row> <map_col>\n", argv[0]);
        return false;
    }

    /* Convert arguments to integers */
    *map_row = atoi(argv[1]);
    *map_col = atoi(argv[2]);

    /* Validate map dimensions & Guard the integer parameters that come from an external user*/
    if (*map_row < 3 || *map_row > 101 || *map_row % 2 == 0)
    {
        printf("Invalid row size. It must be an odd number between 3 and 101.\n");
        return false;
    }
    if (*map_col < 5 || *map_col > 100)
    {
        printf("Invalid column size. It must be between 5 and 100.\n");
        return false;
    }

    return true;
}

/* Function to allocate memory for map and carPlacement arrays */
void allocateMemory(char ***map, int ***carPlacement, int map_row, int map_col)
{
    int i;
    /* Allocate memory for rows */
    *map = (char **)malloc(map_row * sizeof(char *));
    if (*map == NULL)
    {
        fprintf(stderr, "Memory allocation failed for map. Exiting.\n");
        exit(EXIT_FAILURE);  /* Terminate the program */
    }

    *carPlacement = (int **)malloc(map_row * sizeof(int *));
    if (*carPlacement == NULL)
    {
        fprintf(stderr, "Memory allocation failed for carPlacement. Exiting.\n");
        deallocateMemory(map, NULL, map_row); /* Free previously allocated memory */
        exit(EXIT_FAILURE);  /* Terminate the program */
    }

    /* Allocate memory for columns */
    for (i = 0; i < map_row; i++)
    {
        (*map)[i] = (char *)malloc(map_col * sizeof(char));
        if ((*map)[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for map row. Exiting.\n");
            deallocateMemory(map, carPlacement, i); /* Free previously allocated memory */
            exit(EXIT_FAILURE);
        }

        (*carPlacement)[i] = (int *)malloc(map_col * sizeof(int));
        if ((*carPlacement)[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for carPlacement row. Exiting.\n");
            deallocateMemory(map, carPlacement, i + 1); /* Free previously allocated memory */
            exit(EXIT_FAILURE);
        }
    }
}

/* Main function */
int main(int argc, char *argv[])
{
    /* Declare and initialize variables */
    char originalCell = ' '; /* Initialize to empty space */
    char currentCell = ' '; /* Initialize to empty space */
    int map_row, map_col; /* Map dimensions */
    char **map; /* Map array */
    int **carPlacement; /* Car positions array */
    int playerRow = 1, playerCol = 1; /* Player position */
    char userInput; /* User input for movement */
    bool gameRunning = true; /* Game status flag */

    /* Validate command line arguments */
    if (!checkArgs(argc, argv, &map_row, &map_col)) return 1;

    /* Allocate memory for map and carPlacement */
    allocateMemory(&map, &carPlacement, map_row, map_col);

    /* Initialize game settings */
    initRandom(); /* Initialize random numbers */
    disableBuffer(); /* Disable terminal buffer */
    initializeMap(map, map_row, map_col); /* Initialize map */
    placeCars(map, carPlacement, map_row, map_col); /* Place cars on the map */

    /* Main game loop */
    while (gameRunning)
    {
        clearScreen(); /* Clear screen */

        /* Mark player position */
        map[playerRow][playerCol] = 'P';

        /* Display map */
        displayMap(map, map_row, map_col);

        /* Read user input */
        userInput = tolower(getchar());

        /* Update player position */
        playerMovement(map, &playerRow, &playerCol, userInput, map_row, map_col, &originalCell);

        /* Store current cell value where player is */
        currentCell = originalCell;

        /* Move cars */
        moveCars(map, carPlacement, map_row, map_col);

        /* Check winning and losing conditions */
        if (currentCell == 'G')
        {
            /* Handle win */
            map[playerRow][playerCol] = 'P';
            clearScreen();
            displayMap(map, map_row, map_col);
            printf("Congratulations! You've won!\n");
            gameRunning = false;
        }
        else if (map[playerRow][playerCol] == '<' || map[playerRow][playerCol] == '>')
        {
            /* Handle loss */
            map[playerRow][playerCol] = 'P';
            clearScreen();
            displayMap(map, map_row, map_col);
            printf("You've hit a car. Game over.\n");
            gameRunning = false;
        }

        /* Pause briefly */
        newSleep(0.1);
    }

    /* Re-enable terminal buffer and deallocate memory */
    enableBuffer();
    deallocateMemory(&map, &carPlacement, map_row);

    return 0;
}
