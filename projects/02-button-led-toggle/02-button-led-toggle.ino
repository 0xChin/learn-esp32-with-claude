/*
 * 02 - Botón + LED (toggle con debounce)
 * learn-esp32-with-claude
 *
 * Un pulsador enciende/apaga el LED (toggle). Lee el botón con la resistencia
 * pull-up INTERNA del ESP32 (INPUT_PULLUP), así que el pin reposa en HIGH y
 * baja a LOW al presionar (lógica "activa en bajo"). Hace debounce por software
 * para ignorar el rebote mecánico del contacto.
 *
 * Cableado:
 *   LED:    GPIO4 -> 220Ω -> ánodo(+, pata larga) -> LED -> cátodo(-) -> GND
 *   Botón:  GPIO13 -> una pata del pulsador ; pata opuesta -> GND
 *           (sin resistencia externa: usamos el pull-up interno)
 * Board:   ESP32 Dev Module
 * Serial:  115200 baud
 */

const int LED = 4;
const int BUTTON = 13;                    // INPUT_PULLUP: reposa HIGH, presionado LOW
const unsigned long DEBOUNCE_MS = 50;     // ventana de estabilidad

bool ledOn = false;
int lastReading = HIGH;                   // última lectura cruda
int stableState = HIGH;                   // estado ya "deboucneado"
unsigned long lastChangeMs = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);          // habilita la resistencia pull-up interna
  digitalWrite(LED, ledOn);
  Serial.println("Listo. Presioná el botón para alternar el LED.");
}

void loop() {
  int reading = digitalRead(BUTTON);

  // 1) Si la lectura cruda cambió, (re)arranca el reloj de debounce.
  if (reading != lastReading) {
    lastChangeMs = millis();
    lastReading = reading;
  }

  // 2) Si la lectura se mantuvo estable más que DEBOUNCE_MS, la damos por buena.
  if (millis() - lastChangeMs >= DEBOUNCE_MS) {
    if (reading != stableState) {
      stableState = reading;

      // 3) Flanco de bajada (HIGH -> LOW) = botón recién presionado.
      if (stableState == LOW) {
        ledOn = !ledOn;                   // toggle
        digitalWrite(LED, ledOn);
        Serial.printf("Botón -> LED %s\n", ledOn ? "ON" : "OFF");
      }
    }
  }
}
