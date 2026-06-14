/*
 * 01 - Blink LED (no bloqueante)
 * learn-esp32-with-claude
 *
 * Parpadea un LED externo en GPIO 4 usando millis() en vez de delay(),
 * para que el loop() nunca se bloquee. Imprime el estado por Serial.
 *
 * Cableado:  GPIO4 -> 220Ω -> ánodo(+, pata larga) -> LED -> cátodo(-, pata corta) -> GND
 * Board:     ESP32 Dev Module
 * Serial:    115200 baud
 */

const int LED = 4;                       // GPIO de propósito general (no strapping, no input-only)
const unsigned long INTERVAL = 500;      // ms entre cambios de estado
unsigned long lastToggle = 0;            // timestamp del último cambio
bool ledState = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  // Idiom no bloqueante: ¿pasó INTERVAL desde el último cambio?
  if (now - lastToggle >= INTERVAL) {
    lastToggle = now;
    ledState = !ledState;
    digitalWrite(LED, ledState);
    Serial.printf("LED -> %d  (t=%lu ms)\n", ledState, now);
  }

  // loop() queda libre: acá podrías leer sensores, atender WiFi, etc.
  // sin que el blink se "trabe". Ese es el punto de no usar delay().
}
