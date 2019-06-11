Please calibrate max value to the max value that is read from the data. If you don't know, just make it a moderatly high like 100000.

has implementation for 3 phases and neutral.
neutral current is taken from data (for non-blondel compliant).
neutral voltage is calculated in the demo by summing Av, Bv, and Cv.

to remove a certain phase, comment it out in the serialEvent

Also supports blondel-compliant full current by summing two currents.
