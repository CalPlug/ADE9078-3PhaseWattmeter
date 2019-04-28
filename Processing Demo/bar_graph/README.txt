This is a demo that has implementation for A_voltage and B_voltage.
This demo can be easily extended for all I,V,P

There is a problem right now that if the microcontroller isn't syncd properly with processing3,
there will be a serialEvent error. This happens about 50% of the time but as long as both processing3
and the micocontroller start at the same time and no bad values are given, it should be fine.
I'm not sure how to implement an ACK NAK system but it would fix this problem.

bar_graph_test.ino is arduino code that simulates connection to an ADE9078 with much less data.
If testing the bar_graph.pde with bar_graph_test.ino make sure to set max
frequency to 6 (or whatever your max frequency is) to avoid errors.
