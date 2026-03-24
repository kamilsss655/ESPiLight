/*
2026 by kamilsss655

Emulate ELRO 800 RF Remote

- you can send multiple codes based on serial input
*/

#include <ESPiLight.h>

#define TRANSMITTER_PIN 13

ESPiLight rf(TRANSMITTER_PIN);

// Buffer to hold last received command
String lastCmd = "";

void setup() {
  Serial.begin(115200);
  Serial.println("Starting..");
  Serial.println("Ready. Send JSON command over Serial...");
  Serial.println("For example: {\"systemcode\":1,\"unitcode\":2,\"on\":1}");
  delay(1000);
}

void sendBurst(void) {
  // send MANY times (this is key!)
  unsigned long start = millis();
  rf.send("elro_800_switch", lastCmd.c_str());
  // rf.send("kaku_contact", lastCmd.c_str());
  delay(5);  // small gap like real remotes
}

// Toggle state of elro 800 switch evrey 2 s
void loop() {
  // Read serial input if available
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (lastCmd.length() > 0) {
        Serial.print("TXing last command: ");
        Serial.println(lastCmd);
        sendBurst();
        lastCmd = "";  // <-- clear buffer after sending
      }
    } else {
      lastCmd += c;
    }
  }

  // rf.send("elro_800_switch", "{\"systemcode\":1,\"unitcode\":1,\"on\":1}");
  // delay(2000);
  // rf.send("elro_800_switch", "{\"systemcode\":1,\"unitcode\":1,\"off\":1}");
  // delay(2000);
}