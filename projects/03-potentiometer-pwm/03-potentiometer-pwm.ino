/*
 * 03 - Potenciómetro -> brillo del LED (ADC + PWM)
 * learn-esp32-with-claude
 *
 * Girás el potenciómetro y el LED cambia de brillo de forma gradual.
 * Dos conceptos nuevos:
 *   - ADC (analogRead): convierte el voltaje del pot (0-3.3V) en un número (0-4095).
 *   - PWM (LEDC): prende/apaga el pin miles de veces por segundo; variando el % de
 *     tiempo encendido (duty cycle) el LED "parece" tener brillo intermedio.
 *
 * Cableado:
 *   Potenciómetro (3 patas):
 *     pata extrema 1 -> 3V3
 *     pata extrema 2 -> GND
 *     pata del medio (cursor) -> GPIO34   (ADC1, solo entrada)
 *   LED:  GPIO4 -> 220Ω -> ánodo(+, larga) -> LED -> cátodo(-) -> GND   (igual que antes)
 * Board:  ESP32 Dev Module
 * Serial: 115200 baud
 */

const int POT = 34;   // entrada analógica (ADC1, input-only) -> cursor del potenciómetro
const int LED = 4;    // salida PWM -> brillo del LED

const int PWM_FREQ = 5000;   // frecuencia del PWM en Hz
const int PWM_RES  = 8;      // resolución en bits -> rango de duty 0..255

void setup() {
  Serial.begin(115200);
  // PWM real del ESP32 (periférico LEDC). Atamos el pin del LED a un canal PWM.
  // analogRead() no necesita pinMode: GPIO34 es solo entrada.
  ledcAttach(LED, PWM_FREQ, PWM_RES);
  Serial.println("Girá el potenciómetro para variar el brillo.");
}

void loop() {
  int raw = analogRead(POT);                    // 0..4095 (ADC de 12 bits)
  int brightness = map(raw, 0, 4095, 0, 255);   // escala al rango PWM de 8 bits (0..255)

  ledcWrite(LED, brightness);                   // PWM: duty cycle proporcional al brillo

  Serial.printf("pot = %4d  ->  brillo = %3d\n", raw, brightness);
  delay(50);                                    // un respiro para no inundar el Serial
}
