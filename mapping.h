#ifndef MAPPING_H
#define MAPPING_H

void initializeMap(char **map, int map_row, int map_col);
void placeCars(char **map, int **carPlacement, int map_row, int map_col);
void displayMap(char **map, int map_row, int map_col);

#endif
