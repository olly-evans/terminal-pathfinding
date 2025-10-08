## IN-PROGRESS

## Notes Having Implemented A*.

- How to store/find selected algorithm in welcome menu.
- Maze algorithms.
- Random barriers.
- Control bar for visualizer.

astarCell()
- For sure a better way to do this without drawGrid().

- saving a maze to a file and loading from a file.
- I think we're analysing cells multiple times, but i can't prove it :>/
- Something is drawing the grid in astarCell without drawGrid() and i dont know what...????

# Notes 
- vertical scrolling for welcome screen and edge stuff vertical then done w welcome screen i think.
- make headerrow just below printed bits not rows/3 doesnt make sense.

- I want vertical scrolling to work but the welcomeRows function is a complete fucking mess and so
are all of its constituent functions, work on the algorithms and have fun before coming back to fix
that shit, and really think about the logic for vertical scrolling.

# Binary Heap

- OS_SIZE = SIZEOF(BH) / SIZEOF(BH[0]) ////////

# General
- testing new branch.

- print info with correct padding for terminal cols.
- HORIZONTAL SCROLLING FOR SMALLER TERMINAL WIDTHS. START CURSOR AT SCREENCOLS-1.
- POTENTIALLY MAKE CX INCREMENT BY 10 OR SOMETHING OTHERWISE.

- better way to get the maximum width Con.cx can scroll.
- Better data structure i think for table data.


- Might be able to disable auto-wrap in disableRawMode(), but this will affect visualizer.
- setup welcome menu with algorithm selection using cursor.

- Could also add fn + arrkey to skip to top/bottom and far left/right.
- need to think about how user can draw barriers in a quick fashion one by one too slow and tedious to draw something meaningful.

- add button to reset everything to empty cells except perm_barriers.