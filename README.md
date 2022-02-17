# Arduino-Buzzer-MIDI-Player
A buzzer controlled using an Arduino that can play any music provided the MIDI file for it exists.

Features:
  - Recieves MIDI serially from any MIDI software.
  - Uses LCD monitor to report note frequency and MIDI pitch for debugging purposes.
  - Uses a potentiometer to adjust volume of the buzzer.
  - Only able to play one note at a time.
  - Able to handle chords and multiple voices by prefering the highest note, which tends to be the melody for most pieces.

Programming Language Used:
  - C++

Components used:
  - Arduino UNO R3
  - LCD1602 Module
  - Potentiometer 10k x2
  - Passive Buzzer
  - Red 5mm LED
  - 330 Ohm Resistor
  - Jumper Wires
  - Solderless Breadboard

Software used:
  - Arduino IDE 1.8.19
  - [The Hairless MIDI <-> Serial Bridge v0.4](https://projectgus.github.io/hairless-midiserial/)
  - [MidiEditor v3.3.0](https://www.midieditor.org/)
  - [Virutal MIDI Piano Keyboard v0.8.6](https://vmpk.sourceforge.io/)
  - [loopMIDI v1.0.16](https://www.tobias-erichsen.de/software/loopmidi.html)

Required Libraries:
  - [Arduino MIDI Library v5.02](https://github.com/FortySevenEffects/arduino_midi_library)
  - Arduino LiquidCrystal Library v1.07


Demonstration with Beethoven's Moonlight Sonata 3rd Movement: https://youtu.be/twwLpDgBtcI
