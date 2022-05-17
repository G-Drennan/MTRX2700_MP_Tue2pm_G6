# MTRX2700 Major Project

## Table of contents
- [Group Members](#group-members)
- [Project Outline](#project-outline)
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



## output inventory list
output ends at a new line

limited to num of items between 0-9, and the items names are not unique to each product.


In the future, the item names could be unique to each location and the num of items can be expanded to numbers greater than 9. 
