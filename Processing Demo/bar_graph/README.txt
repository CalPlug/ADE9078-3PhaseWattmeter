This is a demo that has implementation for all A v,i,p; B v,i,p; C v,i,p and Nuetral V, I, P
error threshold values can be set for each value (Av, Bv, neutral Voltage...)
you can set max frequency and max values

**make sure the max frequency and max value match with the data that is coming from the microcontroller
(i.e. if there are 0-10 frequencies in increments of 0.1, the max freqnecy is 100)

bar_graph_test.ino is arduino code that simulates connection to an ADE9078 with much less data.

There is a problem right now that if the microcontroller isn't syncd properly with processing3,
there will be a serialEvent error. This happens about 50% of the time but as long as both processing3
and the micocontroller start at the same time and no bad values are given, it should be fine.
I'm not sure how to implement an ACK NAK system but it would fix this problem.

Written by Enoch Chau 2019

