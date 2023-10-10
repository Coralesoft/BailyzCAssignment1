#ifndef PLAYER_H
#define PLAYER_H

void updatePosition(char **map, int *playerRow, int *playerCol, int newRow, int newCol, char *originalCell);
void playerMovement(char **map, int *playerRow, int *playerCol, char input, int map_row, int map_col, char *originalCell);


#endif
