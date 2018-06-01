/*
This code is used to send an unsigned 8-bit char to stdout.
Once compiled, stdout can be piped to a raw file, and then
rendered into a wav using the BASH commands below.
Theoretically this can be piped direclty to /dev/dsp, but
I haven't tested it as my development system uses the
Linux subsystem sitting on top of Windows 10.

To turn this code into an album run the following*:

sudo apt-get install sox
gcc -o sinebeatequations sinebeatequations.c -lm
./sinebeatequations | head -c 64M > sinebeatequations.raw
sox -r 48000 -c 1 -t u8 sinebeatequations.raw sinebeatequations.wav

To generate the cover image run the following:

sudo apt-get imagemagick
./sinebeatequations | head -c 64M | convert -size 8192x8192 -depth 8 gray:- sinebeatequations.png

This is the code that was specifically used to generate the album Sinebeat Equations: https://skoddie.bandcamp.com/album/sinebeat-equations
There is a more generic version of this code at: https://gist.github.com/Skoddiethecat/9c2cb88f2f28eccd246c3a857e7a7d5d

*the released album includes reverb. Also, the code for track 4 is
slightly different than the song title. This is because the code
was a little easier to write with a standard if rather than an iif.
The track should still generate identically using the song title,
which I wrote after rendering the whole album. I wanted to preserve
here the exact source used to generate the album. For some real fun
try rendering it at sample rates other than the two presented.

Accounts of my accumen with C have been greatly overstated.
*/

#include <stdio.h>
#include <math.h>
#include <stdint.h>

const int iSampleRate = 48000; //specify sample rate here

uint8_t sinco(int iCarrier, int iSampleRate, unsigned long ulIndex){return (sin(iCarrier * (2 * M_PI) * ulIndex / iSampleRate) * 127) + 128;}

unsigned long phaseindex1(unsigned long t){return (t&48>>t%13)&(((t%64==0)?t>>2:t<<2)>>((t%64)/16))&((t%6==0)?(37&t>>11):(11&t<<37))|(t&t>>5)&(t*3<<4)&((t&2048)?((t>>11)/4):(t>>7))-2;}

unsigned long phaseindex2(unsigned long t){return sinco(128, iSampleRate, sinco(64, iSampleRate, (((((t%256)?(t>>4):(t<<4))-7))/2)|((t>>63)|(((9-(1^4&(t>>11)))|(t&t%((t%1024==0)?1023:1024))-256|(t&(t-16)>>23)))|((((t%4096==0)?t>>5:t<<3)>>((t%256)/32)|(t*3>>13))/1024)/1)));}

unsigned long phaseindex3(unsigned long t){return sinco(150, iSampleRate, sinco(75, iSampleRate, (t%511)^(t&t%255)|(t&t%511)|(t&t%1023)|(t|t%2047)));}

unsigned long phaseindex4drums(unsigned long t){
	int iDrums;
	if (t<(2*1024*1024)){iDrums = 3;}
	else if (t<(4*1024*1024)){iDrums = 6;}
	else if (t<(6*1024*1024)){iDrums = 5;}
	else if (t<(8*1024*1024)){iDrums = 9;}
	else if (t<(10*1024*1024)){iDrums = 8;}
	else if (t<(12*1024*1024)){iDrums = 7;}
	else if (t<(14*1024*1024)){iDrums = 4;}
	else {iDrums = 10;}
	
	
	
	return t>>iDrums;
}

unsigned long phaseindex4(unsigned long t){return sinco(128, iSampleRate, sinco(64, iSampleRate, ((phaseindex4drums(t)|(t>>(4-(1^7&(t>>14))))|(9015+(t%8192)?((t*9)%4096):t/2)/2))));}

void main(){
    unsigned long t;
	
	int iCarrier = 64;
	int iMBytes = 16;
	
    for(t=0; t<iMBytes*1024*1024; t++){
        putchar(sinco(iCarrier, iSampleRate, phaseindex1(t)));
    }
	t = 0;
	
	iCarrier = 512;
	iMBytes = 16;
    for(t=0; t<iMBytes*1024*1024; t++){
        putchar(sinco(iCarrier, iSampleRate, phaseindex2(t)));
    }
	t = 0;
	
	iCarrier = 300;
	iMBytes = 16;
    for(t=0; t<iMBytes*1024*1024; t++){
        putchar(sinco(iCarrier, iSampleRate, phaseindex3(t)));
    }
	t = 0;
	
	iCarrier = 256;
	iMBytes = 16;
    for(t=0; t<iMBytes*1024*1024; t++){
        putchar(sinco(iCarrier, iSampleRate, phaseindex4(t)));
    }
	t = 0;	
	
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