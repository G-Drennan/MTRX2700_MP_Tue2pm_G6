# MTRX2700 Major Project

## Table of contents
- [Group Members](#group-members)
- [Project Outline](#project-outline)
- [System Overview](#system-overview)
- [User Instructions](#user-instructions)
- [Testing Process](#testing-process)



## Group Members
Group 6 members:  
- Jack
- Simran
- Antonio
- Giaan
- Kazlani
- Wei-Ming

## Project Outline
The problem to be solved is that at the end of the day in a supermarket, shelf restockers are required to go around the store, find missing stock and replenish it. The solution to this tedious task is using a robot to go around the store (after closing time) and build an inventory of missing stock. This would allow restockers to more efficiently complete their tasks as they would know exactly how much of each item needs to be replenished. 

To complete this task, the robot would move around on a track, using LiDAR and servo motors to determine the number of items at each location. To simplify this, it is assumed every item has the same dimensions as a cereal box. Given the robot will run on a track that is parallel to the shelves, the number of missing boxes can be easily calculated by:

Number of missing boxes = (measured distance - distance to front of shelf) / width of box

By treating each item location as a street address, the need to differentiate items is removed - instead of analysing the colour and shape of a house to determine who owns it, use the street address and corresponding database linking addresses to owners to determine who owns the house. To determine the “street address” we are using a small gap between products which is offset from the back of the shelf (at a distance ≠ a distance made from boxes) which are counted from a reference point at the start of the aisle. 

The number of missing items at each location updates an inventory which can then be printed at the push of a button.

## System Overview 
The PTU used consists a Lidar sensor, 2 servo motors and an IMU. This will all be controlled using the Dragon 12 Board. To complete the task, the system is divided into 7 modules which includes:
- Building inventory

This module outputs the inventory list to the serial port 1. It does this thru interrupts after the macrocrontroler has countted the number of each item.

It takes in the size of the inventory array and asigns each item a name from item_0 to max item_9 as the items names are not unique to each product.

"|  item_X    X  |  item_X    X  |  item_X    X  |\n" 

Outputting ends at a new line.

Th function within this module num2char is limited to numbers between 0-9, and thus limits the numebr of itmes that the program can output. 
- Obtaining laser values

Laser values will be used to determine the distance from current possition to the object distance. This is done by getting the rising edge and falling edge from PORT T and determine half the period of the PWM wave using these values.
- Filtering laser values

Filter the laser values so to get accurate readings. This is done by averaging out a range of laser values.
- Using avg to determine the state/number of boxes

Using the distance obtained to determine the number of items left. The depth of the shelf and box is constant, by knowing both these values, the total number of boxes can be obtained and hence knowing the amount of items being taken off the shelf. The value will also be display thru 7 segment on the Dragon board. 
- Appropriately updating the inventory

Constantly updating the inventory to get the latest results. Interupt will be used to get all the value and update to the inventory.
- Initialising and controlling the servos

Move the servo so to scane multiple rows and columns of the given shelf. This can be done by changing the duty cycle of PWM 45 and PWM 67 to get the desired angle. 
- Integration and serial input/output 

Updating the user. The terminal get readings from PORT 1 thru interupt to achieve constant update and output. 
## User Instructions 
 
### Setting up the Hardware 
1. Connect the 69 Pin Ribbon Cable interconnecting Dragon board and PTU.
2. Power the Dragon board using the USB cable. 
3. Start the PTU by power it with a power socket.   

### Setting up the Software 
Launch CodeWarrior   
Open MTRX_2700_major.mcp  

### Setting up the Serial Terminal  
For simulation:
- Select “Full Chip Simulation”. 
- Run the debugger. 
- Open component and select "Terminal".
- Right click on the terminal and configure ports to SCI1.

For Dragon Board:
- Select “HCS12 Serial Monitor”. 
- Connect the board from SCI1 to the computer using a cable.
- Find and adjust the COM port to where the SCI1 is mapped to the Device Manager. 
- Run the code.  

## Testing Process  
### PTU module 
Light pulses are sent continuously thru the PTU triggered by a Dragon board. The light pulse hit an object and reflect back, forming a PWM values which it will be modified to get a distance value to the object.
Test of the module is done as follows:
1. Measure the distances of a placed object from the PTU.
2. compare the actual lengths to the average lengths given out from the module.
3. The output distance compares to the actual distance should not be too far off, +-5cm.
4. Adjust the samples to get the best readings.
5. Use a few different distances to test it out. 

### Servo module 
There are two servos in total, one controls the elivation while the other control anzimuth. The range of both servos can orientate from 20 to 160 degrees. The servos are controled thru the duty cycle.
Test of the module is done as follows:
1. Run the program while connected to the Dragon board and PTU.
2. Observe the movement of the servo.
3. Stop the servo movement to measure the actual angle and compare with the input angle.
4. Adjust the duty cycle accordingly to get accurate readings.
5. Adjust the time of the movement accordingly so to give the PTU enough time to get values.

### Serial module 
For serial interfacing, a table will be formed to output the number of items scanned. 
Test of the module is done as follows:
1. Run the code with the Dragon board and PTU connected.
2. On a terminal to observe if the program is working (is it outputing what it should be?).
3. Test it with different number of items.

### Sub-module (7 segment display)
There are 4 seven segments on the Dragon Board. The 4 seven segments can be controled thru PORT B and PORT P. PORT B controls the number displayed on the 7segment while PORT P controls which 7segment to be used. 
Test of the module is done as follows:
1. Run the program with PTU and Dragon board connected.
2. Scan the items and observe the changes of the 7segment.
3. Test it with different number of items.
