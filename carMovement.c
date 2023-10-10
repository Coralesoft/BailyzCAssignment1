#include "carMovement.h"
#include <stdlib.h>
#include <stdio.h>

void moveCars(char **map, int **carPlacement, int map_row, int map_col)
{
    int i, j, k;  /* Declare k here */

    /* Allocate memory for newCarPlacement array */
    int **newCarPlacement = (int **)malloc(map_row * sizeof(int *));
    if (newCarPlacement == NULL)
    {
        fprintf(stderr, "Memory allocation failed for newCarPlacement. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    /* Initialize newCarPlacement array to zeros */
    for (i = 0; i < map_row; i++)
    {
        newCarPlacement[i] = (int *)malloc(map_col * sizeof(int));
        if (newCarPlacement[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for newCarPlacement row. Exiting.\n");
            /* Use k here, now that it has been declared at the top */
            for (k = 0; k < i; k++)
            {
                free(newCarPlacement[k]);
            }
            free(newCarPlacement);
            exit(EXIT_FAILURE);
        }

        for (j = 0; j < map_col; j++)
        {
            newCarPlacement[i][j] = 0;
        }
    }


    /* Loop through each cell in map to calculate new positions and directions for cars */
    for (i = 2; i < map_row - 2; i += 2)
    {
        for (j = 1; j < map_col - 1; j++)
        {
            if (carPlacement[i][j] == 1)
            {
                char currentCar = map[i][j];
                int newPosition = j;
                char newDirection = currentCar;

                /* Check for rightward facing cars */
                if (currentCar == '>')
                {
                    /* Handle right edge condition */
                    if (j == map_col - 2)
                    {
                        newPosition = j - 1;
                        newDirection = '<';
                    }
                    else
                    {
                        newPosition = j + 1;
                    }
                }
                /* Check for leftward facing cars */
                else if (currentCar == '<')
                {
                    /* Handle left edge condition */
                    if (j == 1)
                    {
                        newPosition = j + 1;
                        newDirection = '>';
                    }
                    else
                    {
                        newPosition = j - 1;
                    }
                }

                /* Update the car's new position and direction */
                newCarPlacement[i][newPosition] = 1;
                map[i][newPosition] = newDirection;
            }
        }
    }

    /* Clear old car placements from the map */
    for (i = 2; i < map_row - 2; i += 2)
    {
        for (j = 1; j < map_col - 1; j++)
        {
            if (carPlacement[i][j] == 1 && newCarPlacement[i][j] == 0)
            {
                map[i][j] = '.';
            }
        }
    }

    /* Update the carPlacement array with new positions */
    for (i = 0; i < map_row; i++)
    {
        for (j = 0; j < map_col; j++)
        {
            carPlacement[i][j] = newCarPlacement[i][j];
        }
    }

    /* Free dynamically allocated memory for newCarPlacement */
    for (i = 0; i < map_row; i++)
    {
        free(newCarPlacement[i]);
    }
    free(newCarPlacement);
}
