animation
=========

* Compile with Debug/makefile from inside directory

* cd Debug/

* make

* must be run from base folder:

* ./Debug/animation

Mouse Control
=============

* Run with no command line args

* Shift + Mouse left to rotate view

* Shift + Mouse right to pan view

* Shift + Mouse Wheel to zoom

* Ctrl + Mouse left to choose or unselect bone

* Mouse left drag to move bone on any axis

* Mouse Right to place spline points in 3d space

* Left click speed control window to place data point

* Drag on speed control window to move data points

* Speed is 0 at bottom of window, 200 at top

Keyboard Control
===============

* While main window is focus enter these messages then enter (lowercase only):

* "play"

* "stop"

* "reset" - removes all data without saving

* "load [filename]" - to load animation sequence file assets/[filename].amc

* "save [filename]" - to save current single pose as assets/[filename].amc

* "add [filename]" - to append key frame series with single pose from assets/[filename].amc

* "add" - append a single empty pose to key frame series

* "show [time]" - skip to a given point in time

* modifying bones after adding a new pose will alter only the most recently added

