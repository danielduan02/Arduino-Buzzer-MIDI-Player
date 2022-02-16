/* 
 * Arduino MIDI Player 
 *  
 * Author: Daniel Duan
 * Date: 25/01/2022
 * 
 * Description: Reads incoming midi data and plays it on a buzzer. Uses Hairless MIDI <-> Serial Bridge to
 *              deliver midi messages serially. Uses LCD for debugging, and also flashes an LED.
 * 
 * 
 */




#include <MIDI.h>
#include <LiquidCrystal.h>



// LCD pins
#define rs 7
#define enable 8
#define d4 9
#define d5 10
#define d6 11
#define d7 12

// Other pins
#define LED_PIN 5
#define BUZZER_PIN 3

LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

// Custom MIDI.h settings so it works with hairless
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct CustomBaudRateSettings : public MIDI_NAMESPACE::DefaultSerialSettings {
  static const long BaudRate = 115200;
};

#if defined(ARDUINO_SAM_DUE) || defined(USBCON) || defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)
    // Leonardo, Due and other USB boards use Serial1 by default.
    MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings> serialMIDI(Serial1);
    MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>> MIDI((MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>&)serialMIDI);
#else
    MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings> serialMIDI(Serial);
    MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>> MIDI((MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>&)serialMIDI);
#endif
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Information about the last note played 
static byte lastPitch = 0;
uint32_t timeAtLastNote = 0;

/*
 *  Converts midi pitch to a frequency
 *  @param pitch - midi pitch decoded from the message
 */
uint16_t midiToFrequency(byte pitch) {
  double result = pow(2, ((pitch - 69.0) / 12.0)) * 440;
  return result;
}


// Automatically called when we recieve a Note On message.
void handleNoteOn(byte channel, byte pitch, byte velocity)
{

  
  uint32_t timeSinceLastNote = millis() - timeAtLastNote;

  // If two notes come at the same time, we player the one with the higher pitch
  if ((timeSinceLastNote > 1) || (pitch > lastPitch)) {
    uint16_t frequency = midiToFrequency(pitch);
    lastPitch = pitch;
    
    lcd.clear();
    lcd.print(String("Pitch: ") + String(pitch));
//    lcd.print(String("Time: ") + String(timeSinceLastNote));
    lcd.setCursor(0, 1);
    lcd.print(String("Freq: ") + String(frequency) + String("Hz"));


    digitalWrite(LED_PIN, HIGH);

    // tone() cannot play notes lower than 31Hz (which corresponds to a midi pitch of 23), and instead makes a very high pitch sound.
    if (pitch > 23) {
      tone(BUZZER_PIN, frequency);
    }

    timeAtLastNote = millis();
  }
}

// Automatically called when we recieve a Note Off message.
void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  lcd.clear();
  digitalWrite(LED_PIN, LOW);
  
  // Prevents a previous note's Note Off message from ending the new note prematurely.
  if (pitch == lastPitch) {
      noTone(BUZZER_PIN);
  }

}


void setup() {
  // Lets the MIDI library know what functions to call for note on and note off events
  
  // Initialize MIDI
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  
  Serial.begin(115200);

  // LCD
  lcd.begin(16, 2);

  // LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);

//  lcd.print("Now playing:");
//  lcd.setCursor(0, 1);
//  lcd.print("Moonlight Sonata 3rd mvt");
}

void loop() {
  // put your main code here, to run repeatedly:
  MIDI.turnThruOff();    // stops the input from being fed back to the output
  MIDI.read();
}
