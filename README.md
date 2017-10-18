# simple-engine

I started this to have fun, brush up on cpp, and hopefully motivate some friends to do stuff outside of their day jobs.
Progress, notes, and rough plans are on trello.

My general design paradigm with this engine is to replicate the ease of use of Unity while keeping the overall system more flexible (eg. no single component limitations). Most of the architecture is a WIP nightmare as I have no real experience in _engine_ development. While a plethora of design patterns are available and well documented online I've found that most are overcomplicated or unnecessary for the scope of this project.

The current implementation should be portable, however I have yet to test this project on my Linux setup and will wait until completing development to verify.

Once I've finished the rough engine I'd like to make a small demo game then transition into working in either a lower level graphics API or possibly working on a native alternative to the canvas web application.

## Libraries

[SFML 2.4.2](https://www.sfml-dev.org/)
