/**
 * -------------------------------------------------------------------------
 *  Project: Serial-Based Relay Control (ESP32)
 *  Author : Suraj Rathod (Electrical & IoT Engineer)
 *  Description:
 *      This program controls two relays using serial commands.
 *      Commands:
 *          ON1  - Turn ON Relay 1
 *          OFF1 - Turn OFF Relay 1
 *          ON2  - Turn ON Relay 2
 *          OFF2 - Turn OFF Relay 2
 *
 *  Layered PlatformIO migration (same commands and active-low behaviour):
 *      poc/relay_control/main.cpp
 *      Build: cd firmware && pio run -e poc_relay_control
 *
 *  NOTE:
 *      Most relay modules are ACTIVE LOW:
 *          LOW  = Relay ON
 *          HIGH = Relay OFF
 *
 *      Make sure your relay module follows the same logic.
 * -------------------------------------------------------------------------
 */

#define RELAY1_PIN 27   // GPIO pin for Relay 1
#define RELAY2_PIN 14   // GPIO pin for Relay 2

void setup() {
  Serial.begin(115200);

  // Configure relay pins as output
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  // Initialize relays to OFF state (Active LOW → HIGH = OFF)
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);

  // Startup Information
  Serial.println("=== Relay Control POC ===");
  Serial.println("Available Commands:");
  Serial.println("  ON1  - Turn ON Relay 1");
  Serial.println("  OFF1 - Turn OFF Relay 1");
  Serial.println("  ON2  - Turn ON Relay 2");
  Serial.println("  OFF2 - Turn OFF Relay 2");
  Serial.println("--------------------------------");
}

void loop() {

  // Check if user has entered a command in Serial Monitor
  if (Serial.available()) {

    // Read command from serial input
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove extra spaces/newlines

    // -------- Relay 1 Control --------
    if (command.equalsIgnoreCase("ON1")) {
      digitalWrite(RELAY1_PIN, LOW);   // Relay ON
      Serial.println("Relay 1 → ON");
    }
    else if (command.equalsIgnoreCase("OFF1")) {
      digitalWrite(RELAY1_PIN, HIGH);  // Relay OFF
      Serial.println("Relay 1 → OFF");
    }

    // -------- Relay 2 Control --------
    else if (command.equalsIgnoreCase("ON2")) {
      digitalWrite(RELAY2_PIN, LOW);   // Relay ON
      Serial.println("Relay 2 → ON");
    }
    else if (command.equalsIgnoreCase("OFF2")) {
      digitalWrite(RELAY2_PIN, HIGH);  // Relay OFF
      Serial.println("Relay 2 → OFF");
    }

    // -------- Invalid Command --------
    else {
      Serial.println("Invalid Command!");
      Serial.println("Use: ON1, OFF1, ON2, OFF2");
    }
  }
}
