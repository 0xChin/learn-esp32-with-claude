/*
 * 04 - Buzzer pasivo: "Estrellita, ¿dónde estás?" (Twinkle Twinkle Little Star)
 * learn-esp32-with-claude
 *
 * El buzzer PASIVO no tiene oscilador propio: vos le das la frecuencia y él vibra a
 * esa frecuencia. Más Hz = nota más aguda; menos Hz = más grave.
 * Acá tocamos una melodía: cada nota es una FRECUENCIA y una DURACIÓN (ritmo).
 *
 * Cableado:
 *   Buzzer PASIVO (2 patas):
 *     pata de señal (+ si está marcada) -> GPIO13
 *     otra pata                          -> GND
 * Board:  ESP32 Dev Module
 * Serial: 115200 baud
 *
 * Nota: usamos tone()/noTone() (core ESP32 3.x). Alternativa nativa: LEDC
 * (ledcAttach + ledcWriteTone).
 */

const int BUZZER = 13;

// Frecuencias de las notas (Hz)
#define DO  262
#define RE  294
#define MI  330
#define FA  349
#define SOL 392
#define LA  440
#define SI  494
#define DO2 523

// Melodía de Estrellita. Cada nota tiene su frecuencia...
int melodia[] = {
  DO, DO, SOL, SOL, LA, LA, SOL,
  FA, FA, MI,  MI,  RE, RE, DO,
  SOL,SOL,FA,  FA,  MI, MI, RE,
  SOL,SOL,FA,  FA,  MI, MI, RE,
  DO, DO, SOL, SOL, LA, LA, SOL,
  FA, FA, MI,  MI,  RE, RE, DO
};

// ...y su duración (1 = negra, 2 = blanca/el doble). El último de cada frase dura más.
int duraciones[] = {
  1,1,1,1,1,1,2,
  1,1,1,1,1,1,2,
  1,1,1,1,1,1,2,
  1,1,1,1,1,1,2,
  1,1,1,1,1,1,2,
  1,1,1,1,1,1,2
};

const int N = sizeof(melodia) / sizeof(melodia[0]);  // cantidad de notas
const int BEAT = 350;                                // ms por negra (tempo)

void setup() {
  Serial.begin(115200);
  Serial.println("Estrellita, donde estas...");
}

void loop() {
  for (int i = 0; i < N; i++) {
    int dur = duraciones[i] * BEAT;     // duración total de esta nota
    tone(BUZZER, melodia[i]);           // suena la frecuencia
    delay(dur - 40);                    // la mantenemos casi toda su duración
    noTone(BUZZER);                     // pequeño silencio: separa notas repetidas
    delay(40);
  }
  delay(1500);                          // pausa antes de repetir la canción
}
