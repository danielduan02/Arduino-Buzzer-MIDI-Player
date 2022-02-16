# Arduino-Buzzer-MIDI-Player
A buzzer controlled using an Arduino that can play any music provided the MIDI file for it exists.

Features:
  - Recieves MIDI serially from any MIDI software.
  - Uses LCD monitor to report note frequency and MIDI pitch for debugging purposes.
  - Uses a potentiometer to adjust volume of the buzzer.
  - Only able to play one note at a time.
  - Able to handle chords and multiple voices by prefering the highest note, which tends to be the melody for most pieces.

Software that I used:
  - The Hairless MIDI <-> Serial Bridge (https://projectgus.github.io/hairless-midiserial/)
  - MidiEditor (https://www.midieditor.org/)
  - Virutal MIDI Piano Keyboard (https://vmpk.sourceforge.io/)
  - LoopMIDI (https://www.tobias-erichsen.de/software/loopmidi.html)

Required Libraries:
  - Arduino MIDI Library (https://github.com/FortySevenEffects/arduino_midi_library)
  - Arduino LiquidCrystal Library


