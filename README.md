(IN PROGRESS)

# WELCOME TO PATH
A dynamic pathfinding algorithm visualiser written in C.

# Build

Clone the repository using:
```console
git clone https://github.com/olly-evans/terminal-pathfinding
```

Change into the new directory using:

```console 
cd foldername
```

Use make to build the project:

```console 
make run
```

Or alternatively just:
```console 
make
```

Make command alone will compile without running afterwards, the executable can then be found in the /bin/ folder and ran manually using:

```console
./bin/main
```

# Usage

After running you will see the main menu where you can select an algorithm using the arrow keys and then pressing enter.

This will then take you to the main visualisation. The cursor can be moved using the arrow keys. The start (S) and end cell (E) can be chosen using the space bar when the cursor is in the wanted position. These are the cells that the chosen algorithm will start at and then try to find a path to. Once the start and end are placed barriers (white) can be inserted to obstruct the algorithm also using the space bar, the algorithm cannot use these barriers in its search.

Once you are happy with the layout you have created for the algorithm you can press enter and the algorithm will find a path. Whether this is the shortest path or not depends on the algorithm selected.

Pink represents cells that have been considered by the algorithm whereas blue ones are cells that it is considering.

# Algorithms 

## A*
A* finds the shortest path with respect for given weights with a start and end node. I used a binary min-heap to most efficiently store the open set of nodes.

## Breadth-First Search
Breadth-first search starts at the tree root and explores all nodes at the present depth prior to moving on to the nodes at the next depth level. A queue was needed to keep track of the child nodes that were encountered but not yet explored. 

## Depth-First Search
DFS starts at the root node (selecting some arbitrary node as the root node in the case of a graph) and explores as far as possible along each branch before backtracking. A stack was needed to keep track of the nodes discovered so far along a specified branch which helps in backtracking of the graph. 

# TODO
- Vertical padding for menu. Abort if screenrows less than appropriate no.
- Fix DFS logic where occasionally it won't fully explore to depth.
- Make dfs more random with selection.
- Controls in main visualisation.

- Can randomize and place S but not E. Being overwritten by something.