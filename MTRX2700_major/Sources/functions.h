#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[10];
    int amount;
} item;

#define shelf_distance 850;
#define back_shelf_distance 1350;
#define offset 50;
#define box_depth 100.0;
#define error_range 25;

extern volatile int item_address;
extern volatile int prev_state;
extern volatile int current_state;
extern volatile int shelf;

double handleLaserValues(unsigned long laserValue, unsigned long *laserArr, int angle);
void determineOccurence(item* current_item);
void initialiseInventoryContents(item** itemArray);
void freeMemory(item** itemArray, int numItems);

#endif
                           
