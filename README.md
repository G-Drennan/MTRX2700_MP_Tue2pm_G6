# MTRX2700 Major Project

## Table of contents
- [Group Members](#group-members)
- [Project Outline](#project-outline)
- [System Overview](#system-overview)
- [User Instructions](#user-instructions)
- [output inventory list](#output-inventory-list)



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

An inventory to store the number of items the sensor identified.
- Obtaining laser values

Laser values will be used to determine the distance from current possition to the object distance.
- Filtering laser values

Filter the laser values so to make it readable to all.
- Using avg to determine the state/number of boxes

Using the distance obtained to determine the number of items left. The depth of the shelf and box is constant, by knowing both these values, the total number of boxes can be obtained and hence knowing the amount of items being taken off the shelf.
- Appropriately updating the inventory

Constantly updating the user.
- Initialising and controlling the servos

Move the servo so to scane multiple rows and columns of the given shelf.
- Integration and serial input/output 

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

## output inventory list
This module outputs the inventory list to the serial port 1. It does this thru interrupts after the macrocrontroler has countted the number of each item.

It takes in the size of the inventory array and asigns each item a name from item_0 to max item_9 as the items names are not unique to each product.

"|  item_X    X  |  item_X    X  |  item_X    X  |\n" 

Outputting ends at a new line.

Th function within this module num2char is limited to numbers between 0-9, and thus limits the numebr of itmes that the program can output.  


In the future, the item names could be unique to each location and the num of items can be expanded to numbers greater than 9. 
