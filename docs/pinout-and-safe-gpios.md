# Pinout y GPIOs seguros (ESP32 de 38 pines)

Antes de repartir pines para sensores y actuadores, conviene saber cuáles podés usar libremente
y cuáles tienen "asteriscos". No todos los GPIO del ESP32 son iguales.

## Resumen rápido

| GPIO | ¿Usar? | Nota |
|------|--------|------|
| 0 | ⚠️ | Strapping pin (modo boot). Botón BOOT. Evitar para señales en el arranque. |
| 1 (TX) | ⚠️ | UART0 — consola serial. Lo usa el Serial Monitor. |
| 2 | ⚠️ | Strapping pin. LED onboard en muchas placas. OK para LED. |
| 3 (RX) | ⚠️ | UART0 — consola serial. |
| 4 | ✅ | Propósito general. **El que usamos en el proyecto 01.** |
| 5 | ⚠️ | Strapping pin. Debe estar HIGH en boot. Usable con cuidado. |
| 6–11 | ⛔ | **Conectados a la flash SPI interna. NO usar.** |
| 12 | ⚠️ | Strapping pin (voltaje flash). Evitar pull-up externo en boot. |
| 13 | ✅ | Propósito general. |
| 14 | ✅ | Propósito general. |
| 15 | ⚠️ | Strapping pin. |
| 16, 17 | ✅ | Propósito general. |
| 18, 19 | ✅ | Propósito general (también SPI por defecto). |
| 21, 22 | ✅ | Propósito general (I²C por defecto: SDA=21, SCL=22). |
| 23 | ✅ | Propósito general. |
| 25, 26, 27 | ✅ | Propósito general (25 y 26 tienen DAC). |
| 32, 33 | ✅ | Propósito general (ADC + touch). Los más versátiles. |
| 34, 35, 36, 39 | 📥 | **Solo entrada (input-only).** Sin pull-up interno. Ideales para sensores analógicos. |

## Reglas prácticas

- **Para empezar, usá:** 4, 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33. Sobran.
- **Nunca uses 6–11.** Están soldados a la memoria flash; tocarlos cuelga la placa.
- **Strapping pins (0, 2, 5, 12, 15):** se pueden usar como salida una vez arrancada la placa,
  pero su nivel en el momento del reset afecta el boot. Evitalos para entradas que puedan
  estar en un nivel raro al encender.
- **34, 35, 36, 39 son solo entrada:** perfectos para leer sensores (potenciómetro, LM35,
  fotorresistencia), pero **no podés** sacar señal ni activarles pull-up interno.

## ADC y un detalle importante

- El ESP32 tiene dos bloques de ADC: **ADC1** (GPIO 32–39) y **ADC2** (GPIO 0, 2, 4, 12–15, 25–27).
- ⚠️ **ADC2 no funciona mientras el WiFi está activo.** Si vas a usar WiFi + lectura analógica,
  usá pines de **ADC1** (32–39) para lo analógico.

## Voltaje (recordatorio)

Todos los GPIO son de **3.3V**. No les metas 5V directo. Si un sensor del kit entrega 5V en su
salida de señal, hace falta adaptar el nivel (divisor resistivo o level shifter) antes de
conectarlo a un pin de entrada del ESP32.

---

*Referencia general; el etiquetado físico exacto varía entre fabricantes. Cuando tengas dudas
con tu placa puntual, buscá el pinout del modelo serigrafiado en ella.*
