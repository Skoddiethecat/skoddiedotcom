## {{ page["post"] }}

*Posted on <!--{ page["date"] }-->*

I haven't seriously blogged in....I don't actually know how long, but the script I use to build this website supports blogging and I wanted to consolidate some of my personal notes, so why not make them public?

### Markov Chains

I recently built a [currently broken] twitter bot with a lot of stolen code that randomly generates gibbrish tweets that parse as genuine sentences by using Markov chains. Here is the Github link for those interested; but be warned, it's a total mess: [catgirl.ebooks](https://github.com/Skoddiethecat/catgirl.ebooks). The concepts used are from a blog post by Shabda Raaj at this link: [Generating pseudo random text with Markov chains using Python](https://www.agiliq.com/blog/2009/06/generating-pseudo-random-text-with-markov-chains-u/)

While the code is heavily stolen (and heavily refactored), the concept behind it is really interesting to me, and should be adaptable to random generation of coherent music which may be less gibberish than the text is. If we convert a large corpus of MIDI data into a database of note tuples followed by possible third notes we should be able to generate arbitrarily long melodies that make some degree of musical sense. Due to the shift from prose to music however, we're presented with the following challenges:

* Music is written in different key signatures. This may either artificially shrink the corpus, or create very dissonant (pseudo-chromatic) melodies. One possible solution would be to quantize (round) notes off to fit within a certain key signature, though this means that every melody will be diatonic. Maybe there is a middle ground of quantizing but throwing a few accidentals in harmonically logical positions?
* Do we store note duration along with note value? Both options could have vastly different results and may be worth exploring.
* Should we evaluate the corpus at a per-note level, or in some ideal grouping? I think it's worth noting that my twitter bot evaluates the corpus at a per-word level and not a per-letter.
* Purely Markov chain based generation will create music with little, or at least an uneven meter. Should we solve this using the hamfisted approach of generating one measure at a time?
* If we generate a measure at a time, how do we create harmonic rhythm? Is this predefined, or can it be algorithmic?
* Perhaps most importantly, so far this is only a melody. How can we generate an entire track using Markov chains? How can we generate an entire album?
* Is any of this truly possible? From what I understand about the MIDI format, getting note duration may be easier said than done.
<br />
<br />
### TempleOS

I need to take a brief moment, for some reason, and talk about TempleOS. I recently watched a documentary on it (google it), and beyond being personally fascinated by the pathos behind it, I was very intrigued by the algorithmic music generation that Terry Davis created. I have no plans to dive into the actual code he used to generate it, but it sounds like he did some clever tricks with repeating phrases to give them a more 'musical' quality. In the words of Adam Neely and many others, repetition legitimizes. So, even with musical phrases that some describe as 'uncanny', they can still satisfy some degree of musicality by having an overarching structure that includes an amount of repetition. This leads me to believe that incorporating the same concepts with Markov chain generation of the actual phrases may end well. I think having a degree of randomness in the structure will be important as well. Listening to a few of Terry's 'hymns' they do seem to have the same AABB structure as one another, though this may have represented his personal preference.

### Song Arrangement

Disregarding percussion for a moment, we should consider how to go from generating a melody to generating a full piece of music. In additional, we will potentially need to have: bass, chords, counter melodies, and orchestration. We will also need an overarching structure, as mentioned in the previous section.

#### Bass

So the bass line should obviously be somehow related to the melody. The easiest way to do this would be to generate a rhythm, and mirror the note from the melody down 2-3 octaves. We could also make it more independent by creating a database of bass lines only, then applying the same key rules as we did on the melody. Obviously this may create harmonic issues, so we could go a step further and create a bass line depending on what chord we're currently in, but I feel like the more we go down this path the further we get from Markov chains. The other important thing to note with bass is that bass lines are often slower than melodies (save ghost notes), so perhaps it's worth putting an upper bound on note division. Perhaps having a target 'sum' of note durations that should add up to some amount less than the melody's 'sum' makes more sense. This could pretty easily be implemented with a while loop. I'm also curious if it's possible to implement ghost notes, which are the backbone of my IRL bass playing. I'd have to give some more thought on this though, I'm not sure of how to bring it together right now.

#### Chords
So if we're generating the melody one bar at a time we could compare those notes against a database of chords and randomly pick a chord that matches them, though that gets a little far from Markov chains again. If we built the first chord based on the first note of the melody in the section, and the second chord from the first note in the second bar, we could then compare those against a corpus to continue to generate chords for the duration. One issue would be that the melody and chords would gradually become decoupled, but regressively modifying parts of the melody to fit within the chord is definitely a possibility as well. My biggest concern here is generating a corpus, because while I can easily find a **HUGE** amount of arbitrary midi files and rip them apart to get melodies, I don't know that a similar source of chord progressions and harmonic rhythm is available. Speaking of, harmonic rhythm is a very relevant concern as well, and one that I'm not totally sure how to approach. I would like a little variation in it, but there are some conventions used to prevent it sounding like chaos. Another thing worth noting is that while the primary function of the chords is to drive some sort of polyphonic voice, we can use it to inform the bass line, and other aspects of the song as well. Thinking more and more, chords may be where to start rather than melodies, assuming I can build a corpus of them.

#### Counter Melodies

These, of course, will be entirely optional, and I'm imagining them as being generated with the same process as the primary melody, but played more quietly, and with a few more constraints. Some unordered thoughts:

* Diatonic only
* Never faster than the primary melody
* Maybe lower pitched than the melody, but not by no more than an octave and often less. Perhaps using regressive algorithms?
* Quieter than the melody, perhaps by a randomly variable amount
<br />
<br />
#### Orchestration

I think there is a *lot* of opportunity for interesting things here. We can use the default general MIDI groupings of instruments for the most part, but I also like the idea of sending instrument changes somewhat frequently. Of course that also makes me wonder, how can we incorporate Markov chains? I'm almost entirely stumped here. Maybe I can scrape MIDI files for common instrument changes and then create a (somewhat flat) corpus based on that data. I would, however, absolutely like to map velocity data into a corpus. The trick with that is perhaps needing to do it in relation to note duration, or at a per-quarter note level to avoid completely random emphasis.

#### Structure

I think I may need to be extremely hamfisted with this. I have no awareness of any scrapable data for overall song structure (verse, chorus, verse, chorus, bridge, outro?), but I would like it to vary a little from song to song. Given that structure is actually my weakest area in music composition overall, this may be the most valuable part of the exercise.

### Percussion

Percussion should be much easier than nearly everything else. I think doing it on a per-measure basis may be wisest to impart a strong sense of timing, but I can also see using larger structures to determine when parts are coming in and out. Genre will be very important, as seeding the corpus with too many styles will result in complete chaos. It may be worth experimenting with, but I can see it getting out of hand easily. I could also use the harmonic rhythm to regressively influence the percussion, allowing for emphasis in line with the chord changes (or not) depending on what is being built.

___

I've kind of run out of steam, but I think this went well for my first round of notes. I'm going to think on this some, and will probably blog more as/if this project progresses. Until then, #maketechnoqueeragain.{{ cursor() }}