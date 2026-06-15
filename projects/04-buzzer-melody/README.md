# 04 — Buzzer pasivo: melodía «Estrellita» (frecuencia = tono)

Tu primera **salida de sonido**. Un buzzer pasivo toca notas según la frecuencia que le mandás —
acá toca *Estrellita, ¿dónde estás?* (Twinkle Twinkle Little Star).
Conceptualmente extiende el PWM del proyecto 03: antes variabas el *duty* (brillo); ahora variás
la *frecuencia* (tono). Y se suma el **ritmo**: cada nota tiene una frecuencia **y** una duración.

## Qué vas a aprender

- La diferencia entre **buzzer activo y pasivo**.
- **Frecuencia = tono:** más Hz → nota más aguda; menos → más grave.
- `tone()` / `noTone()` para generar sonidos.
- Cómo las **notas musicales son frecuencias** (La = 440 Hz, etc.).
- **Ritmo:** una melodía es una lista de notas, cada una con su **frecuencia** y su **duración**
  (arrays paralelos `melodia[]` + `duraciones[]` y un tempo `BEAT`).

## Activo vs Pasivo

| | Activo | Pasivo (este) |
|--|--------|---------------|
| Oscilador interno | Sí | No |
| Suena con | `digitalWrite(HIGH)` → tono fijo | `tone(pin, freq)` → tono variable |
| Sirve para | beep / alarma | melodías |
| Aspecto | sellado arriba | PCB/bobina visible abajo |

Usá el **pasivo** para este proyecto (es el que deja elegir la nota).

## Componentes
- 1 × buzzer pasivo (2 patas)
- 2 × jumpers

## Cableado

```
Buzzer PASIVO:
  pata de señal (+ si está marcada) ─► GPIO13
  otra pata                          ─► GND
```

El buzzer pasivo, manejado con onda cuadrada, **no es estricto con la polaridad**; igual, si
tiene una pata marcada con `+`, mandá esa a GPIO13.

## El concepto: frecuencia = tono

El sonido es vibración. La **frecuencia** es cuántas veces por segundo vibra el buzzer:

```
262 Hz → Do        440 Hz → La        523 Hz → Do (una octava más arriba)
   grave  ─────────────────────────────────►  agudo
```

`tone(BUZZER, 440)` hace que el pin genere una onda cuadrada a 440 Hz → el buzzer vibra a esa
frecuencia → escuchás un La. Es el mismo PWM, pero acá el oído percibe la **frecuencia como tono**
(en el LED, el ojo percibía el duty como brillo).

## Subir y probar

1. Abrí [`04-buzzer-melody.ino`](04-buzzer-melody.ino), Board = ESP32 Dev Module, Port correcto.
2. **Upload**, Serial Monitor a 115200.
3. Deberías escuchar la melodía de **«Estrellita»** repetirse.

## Experimentos

1. **Cambiá la duración** (`delay(400)`) para notas más cortas/largas.
2. **Armá una melodía:** poné las frecuencias de una canción conocida en el array `escala[]`.
3. **Pot → tono:** combiná con el proyecto 03 — usá `analogRead` del potenciómetro para elegir la
   frecuencia (`tone(BUZZER, map(raw, 0, 4095, 100, 2000))`). Un theremin casero.
4. **Sirena:** subí y bajá la frecuencia en un bucle con `millis()`.

## Nota técnica

- `tone()` / `noTone()` están soportados en el core ESP32 **3.x**. Si tu versión no los tuviera,
  la alternativa nativa es la API **LEDC**: `ledcAttach(BUZZER, 2000, 8)` y luego
  `ledcWriteTone(BUZZER, freq)` (y `ledcWriteTone(BUZZER, 0)` para callar).

## Siguiente

➡️ **05 — (próximamente):** servo SG90 (PWM aplicado a posición/ángulo).
