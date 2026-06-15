/*
 * 05 - Jukebox: 2 canciones + 2 botones
 * learn-esp32-with-claude
 *
 * Dos botones eligen qué canción suena en el buzzer pasivo:
 *   Botón 1 -> "Estrellita"      Botón 2 -> "Mario Bros" (intro)
 *
 * Concepto nuevo: FUNCIONES. En vez de repetir el código de "tocar" por cada
 * canción, escribimos UNA función tocar() que reproduce cualquier melodía que le
 * pasemos (array de notas + array de duraciones).
 *
 * Cableado:
 *   Buzzer pasivo: señal -> GPIO13 ; otra pata -> GND
 *   Botón 1:       una pata -> GPIO14 ; otra pata -> GND   (INPUT_PULLUP, activo en bajo)
 *   Botón 2:       una pata -> GPIO27 ; otra pata -> GND
 * Board:  ESP32 Dev Module
 * Serial: 115200 baud
 */

const int BUZZER  = 13;
const int BOTON_1 = 14;   // Estrellita
const int BOTON_2 = 27;   // Mario

// Frecuencias de las notas (Hz). 0 = silencio (rest).
#define DO   262
#define RE   294
#define MI   330
#define FA   349
#define SOL  392
#define LA   440
#define SI   494
#define DO2  523
#define MI5  659
#define SOL5 784

// --- Canción 1: Estrellita ---
int estrellita[] = {
  DO, DO, SOL, SOL, LA, LA, SOL,
  FA, FA, MI,  MI,  RE, RE, DO,
  SOL,SOL,FA,  FA,  MI, MI, RE,
  SOL,SOL,FA,  FA,  MI, MI, RE,
  DO, DO, SOL, SOL, LA, LA, SOL,
  FA, FA, MI,  MI,  RE, RE, DO
};
int estrellitaDur[] = {
  1,1,1,1,1,1,2,  1,1,1,1,1,1,2,
  1,1,1,1,1,1,2,  1,1,1,1,1,1,2,
  1,1,1,1,1,1,2,  1,1,1,1,1,1,2
};
const int estrellitaN = sizeof(estrellita) / sizeof(estrellita[0]);

// --- Canción 2: Mario Bros (intro, simplificado) ---
int mario[] = {
  MI5, MI5, 0, MI5, 0, DO2, MI5, 0, SOL5, 0, 0, 0, SOL, 0, 0, 0
};
int marioDur[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
const int marioN = sizeof(mario) / sizeof(mario[0]);

void setup() {
  Serial.begin(115200);
  pinMode(BOTON_1, INPUT_PULLUP);
  pinMode(BOTON_2, INPUT_PULLUP);
  Serial.println("Boton 1 (GPIO14) = Estrellita  |  Boton 2 (GPIO27) = Mario");
}

// FUNCIÓN: toca una canción cualquiera.
// Recibe: el array de notas, el de duraciones, cuántas notas, y el tempo (ms por negra).
void tocar(int notas[], int duraciones[], int n, int beat) {
  for (int i = 0; i < n; i++) {
    int dur = duraciones[i] * beat;
    if (notas[i] == 0) {
      noTone(BUZZER);              // 0 = silencio
    } else {
      tone(BUZZER, notas[i]);      // frecuencia -> tono
    }
    delay(dur - 30);
    noTone(BUZZER);                // corte breve: separa notas repetidas
    delay(30);
  }
}

void loop() {
  // Botones activos en bajo (pull-up): LOW = apretado.
  if (digitalRead(BOTON_1) == LOW) {
    Serial.println("-> Estrellita");
    tocar(estrellita, estrellitaDur, estrellitaN, 350);
  }
  if (digitalRead(BOTON_2) == LOW) {
    Serial.println("-> Mario");
    tocar(mario, marioDur, marioN, 150);
  }
}
