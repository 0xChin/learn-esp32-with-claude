# 01 — Blink LED (no bloqueante)

Tu primer circuito real: un LED externo que parpadea, controlado por el ESP32.
Sencillo a la vista, pero introduce los fundamentos sobre los que se construye todo lo demás.

## Qué vas a aprender

- Cómo está cableada por dentro una **protoboard**.
- Por qué un LED necesita una **resistencia limitadora** y cómo calcularla.
- Configurar y escribir un **GPIO de salida**.
- El idiom **no bloqueante** con `millis()` (y por qué `delay()` es un anti-patrón en cuanto el programa crece).
- Usar el **Monitor Serial** para debug.

## Componentes

- 1 × LED (cualquier color)
- 1 × resistencia 220Ω
- 2 × jumpers
- 1 × protoboard
- El ESP32 montado a caballo sobre el canal central de la protoboard

## Cableado

```
GPIO4 ──► [220Ω] ──► ánodo (+, pata larga) ──► LED ──► cátodo (−, pata corta) ──► GND
```

Notas:
- El LED tiene **polaridad**: pata **larga = ánodo (+)**, pata **corta = cátodo (−)**.
  Del lado del cátodo el encapsulado tiene un **chaflán plano**.
- La resistencia va **en serie**; da igual si la ponés antes o después del LED.
- Si lo conectás al revés, simplemente **no enciende** — no se daña nada. Dalo vuelta y listo.

### ¿Por qué 220Ω?

La corriente por el LED es aproximadamente:

```
I = (V_pin − V_led) / R = (3.3V − ~2V) / 220Ω ≈ 6 mA
```

Suficiente para que se vea bien, y muy por debajo del límite del pin (~12–20 mA recomendado en ESP32).
La resistencia evita que el LED (y el pin) reciban más corriente de la que toleran.

### ¿Por qué GPIO 4?

Es un pin "limpio": no es strapping pin, no es input-only, no está reservado al flash.
Ver [`docs/pinout-and-safe-gpios.md`](../../docs/pinout-and-safe-gpios.md) para el mapa completo
de qué GPIO podés usar libremente.

## Subir el código

1. Abrí [`01-blink-led.ino`](01-blink-led.ino) en el Arduino IDE.
2. `Tools → Board → ESP32 Dev Module`.
3. `Tools → Port → /dev/cu.usbserial-*` (o el que aparezca al conectar la placa).
4. Click en **Upload** (→).
5. Abrí el **Serial Monitor** (lupa, arriba a la derecha) a **115200 baud**.

Deberías ver el LED parpadeando cada 500 ms y los mensajes `LED -> 1 / LED -> 0` en el monitor.

## El concepto clave: `millis()` vs `delay()`

`delay(500)` **congela** tu código medio segundo. Mientras tanto no podés leer un botón,
atender WiFi ni hacer nada. En cuanto tu programa hace más de una cosa, `delay()` se vuelve
un problema.

El patrón no bloqueante guarda *cuándo* hiciste algo por última vez y, en cada vuelta del `loop()`,
pregunta "¿ya pasó suficiente tiempo?":

```cpp
if (now - lastToggle >= INTERVAL) { ... }
```

Así el `loop()` gira miles de veces por segundo, libre para atender otras tareas, y solo cambia
el LED cuando corresponde. Es la base de las **máquinas de estados** que vas a usar de acá en más.

## Experimentos para fijar el concepto

1. Cambiá `INTERVAL` a 2000 y volvé a subir — confirma que controlás el ritmo.
2. Hacé un patrón asimétrico (200 ms encendido, 1000 ms apagado). Pista: vas a necesitar
   dos intervalos distintos según `ledState`.
3. Agregá un segundo LED en otro GPIO parpadeando a otra frecuencia — imposible de hacer
   limpio con `delay()`, trivial con `millis()`.

## Siguiente

➡️ **02 — Botón + LED (toggle):** agregamos un pulsador con `INPUT_PULLUP` y debounce
para encender/apagar el LED. (Próximamente.)
