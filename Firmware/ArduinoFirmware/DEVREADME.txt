This document was prepared by David Brady, the previous main developer for the ADE9078 library. This document is meant to help the next
developer avoid some setbacks and to help jumpstart some progress.

To run code on arduino, go download arduino (google it to install). Then, read the actual README for instructions on how to setup library in arduino.

To run code, open a .ino file under examples and hit the run button in arduino sketch. You can compile while hooked up to nothing. To run with the actual
ADE chip, you'll need to hookup the wires betwen the ADE chip and arduino, and then you can upload. Instructions are elsewhere for this. This document is just mean
for the code.

Note: Use .h for headers and .cpp for other. Don't use .hpp or .c
Not exactly sure why on this. Apparently this is common in arduino libraries?

Will go file by file now, starting with .h to give the general architecture.

ADE9078.h
First, those vars called READ and WRITE aren't actually important. They don't change if you'll read or write in the SPI functions. What determines that
is the command header, and I'll take this as the first opportunity to say READ THE DATASHEET. I'll repeat that a lot.

The initialization struct is a struct that will contain values used in the initialize function. These values are set in the demo file.
Keep the struct in the class instead of just passing once to initialize, since this allows us to reinitialize with new settings down
the rode just by editing the struct and calling initialize again.

WARNING. THIS IS MOST LIKELY A BUG.
	The initialization setting is a private member of the ADE class. I believe it should be public, so the demo file can actually edit it.
Currently in the demo files, a new initialization settings struct is being made and setup... but the one that is being used is the one inside the ADE class.
The demo file probably needs to change so that it edits the struct inside the class (and the struct needs to be public instead of private for this)


Let's jump to LastReads.h for a bit

This file just holds a bunch of structs. It's all the data we're ever going to read. The read functions are all in ADE9078.cpp, and it stores
data in these structs. It's called LastReads because when you read again, previous data is overwritten. The demo files access this struct to
print out.

Let's jump to ADE9078registers.h
It's just a bunch of lines mapping names to the registers. It also has all the comments the datasheet had so you can quickly access notes. If you have a bug,
one of the things to check is that the registers you're talking to are the right ones. It's possible we made a typo when typing all that out. So far though,
I haven't found one.


ADE9078Calibrations.h
An EE on my team found some calibration values that are used in the decimalize functions in the cpp file. Not sure what they really mean honestly.
This file just has some defines with then numbers he found, and I use these values in the ADE9078.cpp file

Time for ADE9078.cpp
First thing that might stand out is the ESP ifdef. There's another thing this code might be able to run on (haven't tested) called an ESP32. The defines you see
related to this are just so we choose to run different code based on if we're hooked up to an arduino or esp32. Because these 2 devices are slightly different,
you'll see a lot of really similar code in the SPI functions, but they share some other code written.

For programmers: Consider using function pointers for SPI functions instead of these defines to make it possible to separate esp and arduino code. This would
clean it up quite a bit.

Following are a bunch of read functions. We call spiRead16 or spiRead32 based on the register size. Sometimes we "decimalize" it before returning.

Now, you'll see some duplicate stuff going on. For example, getInstVoltageA/B/C and readVoltage
They do the same thing. This code was based off the ADE7953 code, and we followed the style of A/B/C functions from them. However, the new way to do this is with
our lastReads struct. Once you know the readVoltage is working, delete the three functions for getInstVoltageA/B/C. There are a lot of these duplicates, this was just
one example.

I won't talk much about initialize here. It's heavily commented. Just know that there is probably more configuration to do. Our power readings weren't working (except.. I think reactive power was working). WFB was reading trash values (like they were all around -100 or so). More on WFB soon.

SPI functions.
Honestly, not much to say here other than READ THE DATASHEET! All these functions do is what the datasheet says to do. If you want to understand these functions, read
the SPI part of the datasheet (I think around page 60?) to see what's going on.

Waveform Buffering (WFB)
Go to the datasheet, read the whole waveform buffering section. Then reread the resampled waveform buffering part. Then go to the WFB_CFG register in the last
pages of the datasheet (where they say what every bit is). After that, you can look at the code.

The waveform buffering functions were just my attempt to turn what the datasheet said into code. There is something wrong with them, as it was reading bad values.
I have no idea what the error is...
ConfigureWFB just builds the content to configure the register with and writes it.
IsDoneSampling checks if a certain bit is 1 or 0. Datasheet said it'd be 1 when done. I don't think this function worked.
spiBurstResampledWFB reads data in. If I remember correctly, in blocks of 64. In the resampledWFB demo, we call this 8 times, so that we read all 512 slots.
It'd be easier to read all 512 at once, but there isn't enough memory for that.. Hence the 8 reads of 64. This means we have to calculate where to start reading.
The demo file handles that calculation. There are a lot of print statements in here.. that was just me debugging. They aren't important

Something that had me stuck for 2 weeks: Memory on the user side (so in your demo files) is READ ONLY when declared outside of functions. I was trying to make arrays
with this memory and write to it... but that resulted in undefined behavior. I believe you have to declare variables inside of a function (means redeclaring every loop)
if you want to use variables in the demo side.

And one last time, read the datasheet. It'll save you time. You don't have to read all of it. Skim it (like read titles, or first sentences of paragraphs), read the parts
that seem important. I remember pages.. 50-end were all helpful. Before that, it was more engineering related. Still, skim the whole thing. There's info everywhere, and
details are important.
