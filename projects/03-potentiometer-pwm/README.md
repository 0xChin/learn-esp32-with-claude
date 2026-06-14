# 03 — Potenciómetro → brillo del LED (ADC + PWM)

Salimos del mundo digital (HIGH/LOW) y entramos al **analógico**: valores continuos.
Girás una perilla y el LED se atenúa o intensifica de forma gradual.

## Qué vas a aprender

- **ADC** (`analogRead`): leer un **voltaje variable** (0–3.3V) como un número (0–4095).
- Cómo funciona un **potenciómetro** como **divisor de tensión**.
- **PWM** (`analogWrite`): simular un voltaje intermedio prendiendo/apagando muy rápido (*duty cycle*).
- **`map()`**: reescalar un rango de números a otro.
- Por qué se usan **pines ADC1** (34–39) y qué tienen de especial.

## Componentes

- 1 × potenciómetro 10K (3 patas)
- El LED + resistencia 220Ω del proyecto anterior
- Jumpers

## Cableado

```
Potenciómetro (3 patas):
   pata extrema 1 ─────► 3V3
   pata del medio ─────► GPIO34      (cursor / wiper → entrada ADC)
   pata extrema 2 ─────► GND

LED (igual que antes):
   GPIO4 ─► [220Ω] ─► ánodo(+, larga) ─► LED ─► cátodo(−, corta) ─► GND
```

> El potenciómetro **no tiene polaridad entre las extremas**: podés intercambiar cuál va a 3V3
> y cuál a GND (solo se invierte el sentido de giro). La del **medio** sí es siempre el cursor.

### ¿Por qué GPIO34?

Es un pin de **ADC1** (34–39), *input-only*. Dos motivos:
- **ADC1 funciona aunque uses WiFi** (ADC2 no — comparte hardware con la radio).
- Son pines pensados para lectura analógica.

Recordá: 34–39 son **solo entrada** (no pueden ser salida ni tener pull-up). Perfecto para un sensor. Ver [`docs/pinout-and-safe-gpios.md`](../../docs/pinout-and-safe-gpios.md).

## Los conceptos

### El potenciómetro = divisor de tensión

Por dentro es una pista resistiva con un cursor que se desliza. Las dos extremas van a 3V3 y
GND; el cursor entrega un voltaje **proporcional a su posición**:

```
3V3 ──[ pista resistiva ]── GND
            ▲ cursor
   giro a un extremo → 0V   ·   al medio → ~1.65V   ·   al otro extremo → 3.3V
```

### ADC: voltaje → número

El ESP32 tiene un **conversor analógico-digital de 12 bits**: mide el voltaje del cursor y lo
mapea a un entero:

```
0V → 0        1.65V → ~2048        3.3V → 4095
```

`analogRead(34)` te devuelve ese número.

### PWM: cómo un pin digital "finge" brillo intermedio

Un pin digital solo da 0V o 3.3V — no puede dar 1.6V. El truco del **PWM** es prender y apagar
**miles de veces por segundo**, variando cuánto tiempo está encendido (el *duty cycle*):

```
duty 25%  ▁▇▁▇▁▇   → LED tenue
duty 50%  ▄▄▄▄▄▄   → medio
duty 90%  ▇▇▇▇▇▇   → casi pleno
```

Tu ojo no ve el parpadeo (es demasiado rápido), solo percibe el **brillo promedio**.

En el ESP32 el PWM lo maneja un periférico dedicado, el **LEDC**. Se usa así:
```cpp
ledcAttach(LED, 5000, 8);   // atá el pin a un canal PWM: 5 kHz, 8 bits (duty 0..255)
ledcWrite(LED, brillo);      // 0 = apagado, 255 = pleno
```

### `map()`: reescalar rangos

El ADC da 0–4095, pero `analogWrite` espera 0–255. `map()` convierte de un rango al otro:

```cpp
brightness = map(raw, 0, 4095, 0, 255);
```

## Subir y probar

1. Abrí [`03-potentiometer-pwm.ino`](03-potentiometer-pwm.ino), Board = ESP32 Dev Module, Port correcto.
2. **Upload**, abrí el Serial Monitor a 115200.
3. Girá la perilla: el LED cambia de brillo y el monitor imprime `pot = ... -> brillo = ...`.

## Experimentos

1. **Invertí el brillo:** `map(raw, 0, 4095, 255, 0)` — la perilla ahora atenúa al revés.
2. **Umbral digital:** prendé el LED a pleno solo si `raw > 2048`, si no apagado. Volvés a lo digital partiendo de una señal analógica.
3. **Potenciómetro → frecuencia de parpadeo** en vez de brillo: usá el valor del pot como el
   `INTERVAL` de un blink no bloqueante (`millis()`, proyecto 01).
4. Mirá los valores crudos en reposo: el ADC del ESP32 es algo **ruidoso** y **no perfectamente
   lineal** cerca de los extremos. Es normal.

## Notas

- Usamos la API **LEDC** (`ledcAttach()` / `ledcWrite()`), el PWM nativo del ESP32. Existe también
  `analogWrite()` (estilo Arduino), pero en algunas versiones del core no maneja bien el pin —
  LEDC es lo confiable y lo "correcto" en ESP32, y te da control de frecuencia y resolución.
- Este sketch usa `delay(50)` por simplicidad. Para combinarlo con otras tareas, lo pasarías a
  `millis()` no bloqueante (como en el proyecto 01).

## Siguiente

➡️ **04 — (próximamente):** sensor analógico real (LM35 temperatura o LDR/fotorresistencia),
reusando lo que aprendiste de ADC acá.
