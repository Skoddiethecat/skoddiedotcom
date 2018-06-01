/*
This code is used to send an unsigned 8-bit char to stdout.
Once compiled, stdout can be piped to a raw file, and then
rendered into a wav using the BASH commands below.
Theoretically this can be piped direclty to /dev/dsp, but
I haven't tested it as my development system uses the
Linux subsystem sitting on top of Windows 10.
Notes: Requires sox, length can be controlled with head.

gcc -o [program_name] [program_name].c -lm
./[program_name] | head -c [length] > [program_name].raw
sox -r [sample_rate] -c 1 -t u8 [program_name].raw [program_name].wav

Example:
gcc -o sinebeat sinebeat.c -lm
./sinebeat | head -c 4M > sinebeat.raw
sox -r 8000 -c 1 -t u8 sinebeat.raw sinebeat.wav

In the source itself, the bytebeat is specified in the phaseindex
function after return. This function calculates the index
for the phase accumulator. This drives the sinco (Sine NCO) function.
If the index incremented by 1 each sample, the resulting audio would be
the carrier frequency. I currently have the simple bytebeat (t&t>>8)
specified. To try a different one, simply replace this code. A
collection of known bytebeat algorithms can be found at:
https://bit.ly/2vFAXLF

Specify a carrier frequency and a sample rate, both in hz, in the main
function. Normally when working with bytebeats we don't specify a sample
rate since this can be controlled when adding the header. Here it is
needed to correctly calculate the frequency of the carrier.

Some interesting effects can be created by modifying the frequency of
the carrier over time, however I've kept this gist intentionally simple.

Accounts of my accumen with C have been greatly overstated.
*/

#include <stdio.h>
#include <math.h>
#include <stdint.h>

uint8_t sinco(int iCarrier, int iSampleRate, unsigned long ulIndex){return (sin(iCarrier * (2 * M_PI) * ulIndex / iSampleRate) * 127) + 128;}

unsigned long phaseindex(unsigned long t){return t&t>>8;} //specify bytebeat algorithm after return

void main(){	
    unsigned long t;
    const int iCarrier = 500; //specify carrier frequency here
    const int iSampleRate = 8000; //specify sample rate here
        
    for(t=0;;t++){
        putchar(sinco(iCarrier, iSampleRate, phaseindex(t)));
    }
}

/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/