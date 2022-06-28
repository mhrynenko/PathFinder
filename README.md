<h1 align='center'> PathFinder </h1>

### Description
PathFinder is a program that finds all the shortest paths between all the points, using information about the bridges that connect them. The program:
- reads data from a file. Its name is specified as a command-line argument
- finds all the shortest paths between each combination of two islands
- prints the paths using the FIFO (first) rule for the islands to the standard output. 


For realization I chose Floyd–Warshall algorithm that is used for finding shortest paths in a directed weighted graph with positive or negative edge weights (but with no negative cycles).

#### Some examples of working
**Input:**  
4  
Greenland-Bananal,8  
Fraser-Greenland,10  
Bananal-Fraser,3  
Java-Fraser,5  

**Result:**   
<p align="center">
  <img src="https://user-images.githubusercontent.com/108219165/176184034-497d4623-2b57-4bac-8bd4-7b7724df6f0d.png" />
</p>

**Input:**  
5  
A-B,11  
A-C,10  
B-D,5  
C-D,6  
C-E,15  
D-E,4  

**Result:**   
<p align="center">
  <img src="https://user-images.githubusercontent.com/108219165/176185220-60141e9f-ffe6-47c8-810f-99a5be1cad8e.png" />
  <img src="https://user-images.githubusercontent.com/108219165/176185230-3d667553-7d08-4529-beb9-102ad598eac1.png" />
</p>

**Error handling:**  
<p align="center">
  <img src="https://user-images.githubusercontent.com/108219165/176190202-68acd91f-a611-4801-a0eb-d0be564ec689.png"/>
</p>

### How to start
In folder with cloned project use `make` to compile project.

Start program with `./pathfinder [filename]` where 'filename' is a file with information about islands and bridges
