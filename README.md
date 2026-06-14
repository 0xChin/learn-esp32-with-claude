# learn-esp32-with-claude

Aprendé electrónica y embebidos **desde cero** con un kit ESP32 y Claude Code como tutor.

Este repo nace de sesiones reales de aprendizaje guiadas por [Claude Code](https://claude.com/claude-code).
La idea: que cualquiera con un kit ESP32 pueda seguir el mismo camino, paso a paso, con un tutor
de IA que explica el *porqué* de cada cosa y no solo el *cómo*.

> **¿Arduino o ESP32?** El kit se vende como "kit de Arduino", pero la placa es un **ESP32**
> (más potente, con WiFi y Bluetooth). Programamos con el Arduino IDE por comodidad, pero el
> chip y sus reglas son las del ESP32. Por eso el repo se llama `...esp32...`.

## ¿Para quién es esto?

- Personas que **nunca tocaron electrónica** y quieren empezar bien.
- Gente que ya programa pero es nueva en hardware/embebidos.
- Cualquiera con un kit ESP32 de iniciación tirado en un cajón.

No necesitás saber electrónica previa. Sí ayuda tener ganas de romper la cabeza con cosas físicas.

## Cómo usar este repo

### Opción A — Con Claude Code (recomendado)

1. Instalá [Claude Code](https://claude.com/claude-code).
2. Cloná este repo y abrilo con Claude Code:
   ```bash
   git clone https://github.com/0xChin/learn-esp32-with-claude.git
   cd learn-esp32-with-claude
   claude
   ```
3. Pedile que te haga el onboarding. La skill incluida (`esp32-onboarding`) lo guía:
   > "hola, tengo un kit ESP32 y quiero empezar de cero"

   Claude detecta la skill y te lleva de la mano: instalar el IDE, configurar la placa,
   subir tu primer programa y armar el primer circuito.

### Opción B — Por tu cuenta

Seguí los proyectos en orden, dentro de [`projects/`](projects/). Cada uno tiene su propio
README con el cableado, el código y la explicación de los conceptos nuevos.

## El kit (referencia)

Placa principal: **NodeMcu ESP-32S de 38 pines**. El kit típico incluye protoboard, LEDs,
resistencias, sensores (DHT11, LM35, RFID, etc.), displays, motores y más. No necesitás todo
de entrada: cada proyecto dice qué componentes usa.

## Seguridad básica (leé esto una vez)

- El **puerto USB** recibe **5V** — la placa tiene un regulador que los baja a **3.3V**. Conectar
  por USB es 100% seguro, no rompe nada.
- Los **pines GPIO funcionan a 3.3V**. El regulador protege lo que *sale* de la placa, no lo que
  vos *metés* a un pin desde afuera. No le metas 5V directo a un GPIO.
- Un LED **siempre** va con resistencia en serie.
- Conectar/desconectar el USB no daña nada. En el peor caso, "no funciona" — no "se rompe".

Más detalle en [`docs/pinout-and-safe-gpios.md`](docs/pinout-and-safe-gpios.md).

## Proyectos

| #  | Proyecto | Conceptos | Estado |
|----|----------|-----------|--------|
| 01 | [Blink LED](projects/01-blink-led/) | GPIO salida, protoboard, resistencia limitadora, `millis()` no bloqueante, Serial | ✅ |
| 02 | [Botón + LED (toggle)](projects/02-button-led-toggle/) | GPIO entrada, `INPUT_PULLUP`, debounce, detección de flanco | ✅ |
| 03 | [Potenciómetro (ADC + PWM)](projects/03-potentiometer-pwm/) | Entrada analógica, ADC, PWM/brillo, `map()` | 🚧 |
| 04 | Sensor analógico (LM35 / LDR) | ADC aplicado a un sensor real | 🔜 |

## Estructura del repo

```
.
├── README.md                         # estás acá
├── docs/                             # referencia (pinout, GPIOs seguros, etc.)
├── projects/                         # un proyecto por carpeta, en orden
│   └── 01-blink-led/
│       ├── README.md                 # cableado + conceptos
│       └── 01-blink-led.ino          # el sketch
└── .claude/skills/esp32-onboarding/  # skill de onboarding para Claude Code
```

## Contribuir

¿Sumaste un proyecto nuevo o mejoraste una explicación? PRs bienvenidos. Mantené el formato:
una carpeta por proyecto, README con cableado + conceptos, código comentado.

## Licencia

MIT — ver [LICENSE](LICENSE). Usalo, copialo, compartilo.
