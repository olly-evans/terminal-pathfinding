## IN-PROGRESS

### BLOG

-- Fix DFS logic --
-- make dfs more random with selection --

MACROS FOR ESCAPE CODES FOR THE LOVE OF GOD
IF AN ERROR MOVE CURSOR TO BELOW VISUALISATION.
Exiting with controls.

I incremented the pointer to my dynamically allocated array (Q->qu++), which made it no longer point to the start of the memory block returned by malloc() or realloc().

Then I passed that shifted pointer to realloc(), which is undefined behavior, because realloc() must only be called on the original pointer returned by malloc() or realloc().

This corrupted my memory layout and caused a segmentation fault when the program tried to access or resize the modified pointer.

## AGENDA
- Cursor shows when pressing arrow at the arrows in menu.
- Write a test to check abAppend bytes input.
- Vertical padding for menu. Abort if screenrows less than appropriate no.
- by printing more lines i can go past the terminal rows, user can scroll with the mouse/bar.

NEW MENU IDEA:

- selection for algorithm with numbers.
- taken to info page read in from text file.
- then you can press enter to go to visualization.
- or go back to the main menu.

- How to store/find selected algorithm in welcome menu.
- Maze algorithms.
- Random barriers.
- Control bar for visualizer.
- Legend for when algorithm is running
- Refresh after algorithm finished.
- saving a maze to a file and loading from a file.
- severe flashing in my linux terminal, background color isnt the same either.

# Notes
- vertical scrolling for welcome screen and edge stuff vertical then done w welcome screen i think.
- make headerrow just below printed bits not rows/3 doesnt make sense.

- I want vertical scrolling to work but the welcomeRows function is a complete fucking mess and so
are all of its constituent functions, work on the algorithms and have fun before coming back to fix
that shit, and really think about the logic for vertical scrolling.

# General

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
