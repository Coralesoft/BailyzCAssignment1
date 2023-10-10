#include <stdio.h>
#include "player.h"
#include "mapping.h"

/* Helper function to update the player's new position on the map */
void updatePosition(char **map, int *playerRow, int *playerCol, int newRow, int newCol, char *originalCell)
{
    /* Place the original content back into the old position */
    map[*playerRow][*playerCol] = *originalCell;

    /* Store the new cell's original content */
    *originalCell = map[newRow][newCol];

    /* Update player coordinates */
    *playerRow = newRow;
    *playerCol = newCol;

    /* Place the player in the new position */
    map[*playerRow][*playerCol] = 'P';
}

/* Main function for handling player movements */
void playerMovement(char **map, int *playerRow, int *playerCol, char input, int map_row, int map_col, char *originalCell)
{
    /* Current cell occupied by the player */

    /* Placeholder for the cell the player is about to enter */
    char nextCell;

    /* Coordinates for the next move */
    int newRow, newCol;

    /* Switch case for user input */
    switch (input)
    {
    /* Move up */
    case 'w':
        newRow = *playerRow - 1;
        newCol = *playerCol;

        /* Check if newRow is within map boundary */
        if (newRow >= 0)
        {
            nextCell = map[newRow][newCol];
            /* If the next cell is empty or a special spot or goal, move */
            if (nextCell == ' ' || nextCell == '.' || nextCell == 'G')
            {

                updatePosition(map, playerRow, playerCol, newRow, newCol, originalCell);
            }

        }
        break;

    /* Move down */
    case 's':
        newRow = *playerRow + 1;
        newCol = *playerCol;

        /* Check if newRow is within map boundary */
        if (newRow < map_row)
        {
            nextCell = map[newRow][newCol];

            /* If the next cell is empty or a special spot or goal, move */
            if (nextCell == ' ' || nextCell == '.' || nextCell == 'G')
            {
                updatePosition(map, playerRow, playerCol, newRow, newCol, originalCell);
            }
        }
        break;

    /* Move left */
    case 'a':
        newRow = *playerRow;
        newCol = *playerCol - 1;

        /* Check if newCol is within map boundary */
        if (newCol >= 0)
        {
            nextCell = map[newRow][newCol];

            /* If the next cell is empty or a special spot, move */
            if (nextCell == ' ' || nextCell == '.'|| nextCell == 'G')
            {
                updatePosition(map, playerRow, playerCol, newRow, newCol, originalCell);
            }
        }
        break;

    /* Move right */
    case 'd':
        newRow = *playerRow;
        newCol = *playerCol + 1;

        /* Check if newCol is within map boundary */
        if (newCol < map_col)
        {
            nextCell = map[newRow][newCol];

            /* If the next cell is empty or a special spot, move */
            if (nextCell == ' ' || nextCell == '.'|| nextCell == 'G')
            {
                updatePosition(map, playerRow, playerCol, newRow, newCol, originalCell);
            }
        }
        break;
    }
}
