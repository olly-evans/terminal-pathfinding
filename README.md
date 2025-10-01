## IN-PROGRESS

# Notes 
- vertical scrolling for welcome screen and edge stuff vertical then done w welcome screen i think.
- make headerrow just below printed bits not rows/3 doesnt make sense.

- I want vertical scrolling to work but the welcomeRows function is a complete fucking mess and so
are all of its constituent functions, work on the algorithms and have fun before coming back to fix
that shit, and really think about the logic for vertical scrolling.

#### ACTUAL WAVES

- use capacity instead of realloc everytime we heapInsert.
- use bool instead of loops for open/closed set checks.


- drawgrid needs to run in an infinite loop.
- astar() doesnt.
- They need to be decoupled somehow.

Track which cells were updated (e.g., visited, open, closed)

Move the cursor to their terminal position

Write just that one character











# Binary Heap

- OS_SIZE = SIZEOF(BH) / SIZEOF(BH[0])


- print OPEN SET.
- why is closed only shown after button press.
- isvalidneighbours fucking with display, barriers are being added to the closed set, when should just be ignored.
- open cell->type maybe ditch.
- why do i have to press enter or any key twice after runnning?
- why is the end E being overwritten by C.
- have a look at the whole char system i think its shite.

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