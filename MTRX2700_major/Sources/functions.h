

#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

typedef struct {
    char name[100];
    int amount;
} item;

unsigned long laserValueArr[10];
int totalNumItems = 1;

// shelf parameters
int shelf_distance = 1500;
int back_shelf_distance = 2000;
int box_depth = 100;
int item_address = 1;

// state parameters
int prev_state = 0; // start on a gap state
int current_state;

unsigned long handleLaserValues(unsigned long laserValue, unsigned long *laserArr);
void dermineOccurence(int current_state, item** itemArray);


#endif
                                        
