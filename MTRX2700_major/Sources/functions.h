#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int amount;
} item;

<<<<<<< HEAD
#define shelf_distance 1400;
#define back_shelf_distance 1900;
#define offset 50;
#define box_depth 100;
=======
#define shelf_distance 1500;
#define back_shelf_distance 2000;
#define offset 40;
#define box_depth 80;
>>>>>>> a13ef62e23240a4bdf095cd01abea128a21e2651
#define error_range 30;

extern volatile int item_address;
extern volatile int prev_state;
extern volatile int current_state;

unsigned long handleLaserValues(unsigned long laserValue, unsigned long *laserArr);
void determineOccurence(int current_state, int prev_state, item** itemArray, item* current_item);
void initialiseInventoryContents(item** itemArray);

#endif
                           
