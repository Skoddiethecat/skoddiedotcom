title: sinebeat equations
---
Sinebeat equations are the result of my interest in both [thru-zero frequency modulation](https://learningmodular.com/glossary/tzfm/) and [bytebeat equations](http://countercomplex.blogspot.com/2011/10/algorithmic-symphonies-from-one-line-of.html). The core idea is to modulate the phase index of a sine function using a bytebeat equation, rather than using a second sine function as you would in TZFM. In practice, I have found it to be pleasing to use the output of the sinebeat equation to modulate additional sine functions as this can generate interesting harmonics.

I have implemented this as an offline C program which sends its output directly to stdout, which I then use to generate a raw file by piping the output to head. This is perhaps not the most ideal implementation, however my actual programming skills are somewhat limited; and above all else, this implementation is simple. I have included a link to the source code at the bottom of the page. Usage is described at length in the comments.

I have also included a mirror of Viznut's 2011 collection of bytebeat equations. Most of the equations listed are compatible with my sinebeat program, however some of them are written for java, and may use java specific features.

I first developed this technique for use in the sine wave challenge I ran in March and April of 2018 for my Facebook group Electronic Music Philosophy. This first experiment can be found on our album [https://electronicmusicphilosophy.bandcamp.com/album/vol-7-send-me-a-sine](Vol 7: Send Me a Sine). Following this challenge, I used this technique to create the aptly-named album [Sinebeat Equations](https://skoddie.bandcamp.com/album/sinebeat-equations). While working on the album I found that the music sounded drastically different at 32k and 48k (for reference, Viznut was mostly working at 8k). Based on this, I decided to present all four equations at both sample rates so that listeners could share in my curiosity.

I am currently in the process of creating a follow up to Sinebeat Equations which will follow a more standard album structure, and hopefully be running at 44.1k and 16-bits.

###Downloads###
* [Generic Sinebeat Equations Implementation in C](/sinebeatequations/sinebeat.c)
* [Sinebeat Equations Album Source Code](/sinebeatequations/sinebeatequations.c)
* [MIRROR of Viznut's collection of bytebeats](/sinebeatequations/music_formula_collection.txt)

{{ cursor() }}