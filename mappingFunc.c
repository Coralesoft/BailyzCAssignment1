#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"  /* Include custom random utility */
#include "mapping.h" /* Include custom mapping utility */

/* Define constants for map elements */
#define ROAD '.'
#define EMPTY_SPACE ' '
#define BORDER '*'
#define PLAYER 'P'
#define GOAL 'G'

/* Function to initialize the game map */
void initializeMap(char **map, int map_row, int map_col)
{
    int i, j;
    /* Loop through the entire 2D map array */
    for (i = 0; i < map_row; i++)
    {
        for (j = 0; j < map_col; j++)
        {
            /* Create borders on the map edges */
            if (i == 0 || i == map_row - 1 || j == 0 || j == map_col - 1)
            {
                map[i][j] = BORDER;
            }
            /* Set the initial player position */
            else if (i == 1 && j == 1)
            {
                map[i][j] = PLAYER;
            }
            /* Set the goal position */
            else if (i == map_row - 2 && j == map_col - 2)
            {
                map[i][j] = GOAL;
            }
            /* Create roads on even-indexed rows */
            else if (i % 2 == 0)
            {
                map[i][j] = ROAD;
            }
            /* Fill remaining cells with empty space */
            else
            {
                map[i][j] = EMPTY_SPACE;
            }
        }
    }
}

/* Function to place cars randomly on the map */
void placeCars(char **map, int **carPlacement, int map_row, int map_col)
{
    int i, j;
    /* Loop through rows where cars can be placed (even-indexed, excluding borders) */
    for (i = 2; i < map_row - 2; i += 2)
    {
        int randomPosition = randomUCP(1, map_col - 2);  /* Random column position */
        int carPlaced = 0;  /* Flag to check if a car is already placed on this row */

        /* Check if a car has already been placed in the current row */
        for (j = 1; j < map_col - 1; j++)
        {
            if (carPlacement[i][j] == 1)
            {
                carPlaced = 1;
                break;
            }
        }

        /* If no car is placed, place one randomly */
        if (!carPlaced)
        {
            carPlacement[i][randomPosition] = 1;
            map[i][randomPosition] = (randomUCP(0, 1) == 0) ? '<' : '>';
        }
    }
}

/* Function to display the current game map on the terminal */
void displayMap(char **map, int map_row, int map_col)
{
    int i, j;
    printf("\n");  /* Start a new line for better readability */
    /* Loop to print each cell of the map */
    for (i = 0; i < map_row; i++)
    {
        for (j = 0; j < map_col; j++)
        {
            printf("%2c ", map[i][j]);  /* Print each map cell with a space */
        }
        printf("\n");  /* Move to the next row */
    }

    /* Print game controls */
    printf("\npress w to move up\n");
    printf("press s to move down\n");
    printf("press a to move left\n");
    printf("press d to move right\n");
}
