reads all 512 samples at once instead of 64x8

in LastReads.h, change WFB_RESAMPLE_SEGMENTS to 512

*this needs to modified for esp32 architecture or a MCU with more SRAM needs to be used to read all 512 samples at one time.
