//#define DECODE_NEC            // DECODE_NEC
//#include <IRremote.hpp>       // Do not change header order.
#include <Stepper.h>


const int buttonPin1 = 2;
const int buttonPin2 = 3;


constexpr uint8_t RECV_PIN {12};
constexpr uint16_t S1 = 0x10;  // Remote button 1
constexpr uint16_t S2 = 0x11;  // Remote button 2

int buttonState1 = 0;
int buttonState2 = 0;
int buttonIR     = 0;

// steps for full 360-degree rotation
int stepsPerRevolution = 2048;

// set a speed for the stepper motor
int rpm = 10;

// initialize stepper library on pins 8 - 11
// pin order IN1, IN3, IN2, IN4
Stepper myStepper (stepsPerRevolution, 8, 10, 9, 11);
/*
int16_t irReceive() {
  uint16_t received{0};
  
  if (IrReceiver.decode()) {
    //IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    if (IrReceiver.decodedIRData.protocol == NEC) {
      received = IrReceiver.decodedIRData.command;
      Serial.print("Command: 0x");
      Serial.println(received, HEX);
    }
    IrReceiver.resume();
  }
  return received;
}
*/

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  myStepper.setSpeed(rpm);
  /*
  IrReceiver.begin(RECV_PIN);
  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(RECV_PIN);
  */
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonIR = 0x00;
  //buttonIR = irReceive(); //Almacena el valor recibido en una variable
  
  if ((buttonState1 == HIGH) || (buttonIR == S1)) {
    Serial.println("Turning 1...");
    myStepper.step(stepsPerRevolution);
    delay(1000);
  } else if((buttonState2 == HIGH) || (buttonIR == S2)) {
    Serial.println("Turning 2...");
    myStepper.step(-stepsPerRevolution);
    delay(1000);
  } else {
    // Detiene el motor
    myStepper.step(0);
    Serial.println("stop");
  }
}
