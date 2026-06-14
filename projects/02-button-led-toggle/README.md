# 02 — Botón + LED (toggle con debounce)

Agregamos **entrada**: un pulsador que enciende y apaga el LED. Parece trivial, pero
esconde tres conceptos que vas a usar siempre: entradas flotantes, resistencias pull-up
y debounce.

## Qué vas a aprender

- Leer un **GPIO de entrada** con `digitalRead()`.
- Por qué una entrada **"flotante"** da lecturas basura, y cómo lo resuelve una **pull-up**.
- Usar la **pull-up interna** del ESP32 (`INPUT_PULLUP`) y ahorrarte un componente.
- **Lógica activa en bajo:** presionado = `LOW`.
- Qué es el **rebote de contacto** (bounce) y cómo hacer **debounce por software**.
- Detectar un **flanco** (transición) en vez de un nivel — la base de un toggle.

## Componentes

- Todo lo del proyecto [01](../01-blink-led/) (LED en GPIO4 + 220Ω)
- 1 × pulsador (los "switches con tope" del kit)
- 2 × jumpers más

## Cableado

Dejá el LED como en el proyecto 01 y sumá el botón:

```
LED:    GPIO4  ──► [220Ω] ──► ánodo(+) ──► LED ──► cátodo(−) ──► GND
Botón:  GPIO13 ──► pata del pulsador
        pata opuesta del pulsador ──► GND
```

**No lleva resistencia externa**: activamos la pull-up interna por software.

### Cómo va el pulsador en la protoboard

Los pulsadores táctiles de 4 patas **no** tienen 4 contactos independientes. Por dentro:

- Las **dos patas de un mismo lado están siempre unidas**.
- Los **dos lados se conectan solo cuando lo presionás**.

```
   1 ┌───┐ 2          1-2  : siempre unidas (mismo lado)
     │   │            3-4  : siempre unidas (mismo lado)
   3 └───┘ 4          1-3 / 2-4 : se unen SOLO al presionar
```

Montalo **a caballo sobre el canal central** de la protoboard (igual que el ESP32): así las
patas de un lado quedan separadas de las del otro por el canal. Tomás **una pata de un lado**
→ GPIO13, y **una pata del otro lado** → GND.

> ⚠️ Error clásico: montarlo girado 90°, de modo que las dos patas que usás estén en el mismo
> lado (siempre unidas). Resultado: el LED queda fijo, como si el botón estuviera siempre
> apretado. Si te pasa, girá el pulsador 90°.

### ¿Por qué GPIO 13?

Pin de propósito general, no strapping, no input-only — seguro para una entrada con pull-up.
(Ver [`docs/pinout-and-safe-gpios.md`](../../docs/pinout-and-safe-gpios.md).)

## Los conceptos

### Entrada flotante y pull-up

Un pin de entrada sin conectar a nada es una antena: capta ruido y `digitalRead()` devuelve
HIGH/LOW al azar. Necesitás que repose en un nivel definido.

Con `INPUT_PULLUP`, el ESP32 conecta internamente una resistencia entre el pin y 3.3V. Eso
mantiene el pin en **HIGH** cuando el botón está suelto. Al presionar, conectás el pin a GND,
que "gana", y el pin cae a **LOW**. Por eso la lógica es **activa en bajo**:

```
suelto     → HIGH
presionado → LOW
```

Es el patrón estándar y te evita cablear una resistencia externa.

### Rebote (bounce) y debounce

Un contacto mecánico no cierra limpio: durante unos milisegundos "rebota" y genera una
ráfaga de HIGH/LOW. Sin tratarlo, un solo apretón se leería como decenas de pulsaciones y el
LED parpadearía caótico.

El **debounce** ignora cambios hasta que la lectura se mantenga estable un rato (`DEBOUNCE_MS`,
50 ms acá). Recién entonces aceptamos el nuevo estado. Fijate que está hecho con `millis()`,
**no** con `delay()`: el `loop()` nunca se bloquea.

### Flanco, no nivel

Queremos alternar el LED **una vez por pulsación**, no mientras el botón está apretado. Por eso
el toggle se dispara solo en la **transición** HIGH→LOW (flanco de bajada), comparando el estado
nuevo contra el anterior (`stableState`). Detectar flancos en vez de niveles es un patrón que
vas a repetir mucho.

## Subir y probar

1. Abrí [`02-button-led-toggle.ino`](02-button-led-toggle.ino), Board = ESP32 Dev Module, Port correcto.
2. **Upload**, abrí el Serial Monitor a 115200.
3. Cada pulsación: el LED alterna y el monitor imprime `Botón -> LED ON/OFF`.

## Experimentos

1. Bajá `DEBOUNCE_MS` a 1 y apretá rápido: vas a ver toggles dobles/erráticos (el bounce real).
   Volvé a 50.
2. Cambiá la lógica para que el LED esté encendido **solo mientras** mantenés el botón
   (nivel, no flanco). ¿Qué parte del código sobra para eso?
3. Agregá un segundo botón en otro GPIO que controle un segundo LED, sin usar `delay()`.

## Siguiente

➡️ **03 — (próximamente):** entrada analógica con el potenciómetro (ADC) para variar la
frecuencia del parpadeo o el brillo (PWM).
