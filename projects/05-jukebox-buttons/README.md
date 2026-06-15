# 05 — Jukebox: 2 canciones + 2 botones

Combinás todo lo anterior: **entrada** (botones, proyecto 02) + **salida de sonido** (buzzer,
proyecto 04). Dos botones eligen qué canción suena. Y aparece un concepto de programación clave:
las **funciones**.

## Qué vas a aprender

- **Funciones con parámetros:** una sola `tocar()` reproduce cualquier melodía → no repetís código.
- Combinar **varias entradas** (2 botones) con una salida.
- **Silencios (rests):** notas con valor `0` para las pausas (Mario las tiene).
- Reutilizar conceptos: `INPUT_PULLUP` (02), `tone()` y ritmo (04).

## Componentes
- 1 × buzzer pasivo
- 2 × pulsadores
- Jumpers

## Cableado

```
Buzzer:   señal ─► GPIO13   ·  otra pata ─► riel −
Botón 1:  una pata ─► GPIO14 ·  otra pata ─► riel −     (Estrellita)
Botón 2:  una pata ─► GPIO27 ·  otra pata ─► riel −     (Mario)
```

- Los botones van **a caballo del canal**, con sus dos patas en **columnas distintas (diagonal)**,
  igual que en el proyecto 02. Usan el **pull-up interno** → activos en bajo (apretado = LOW).
- GPIO14 y GPIO27 son de propósito general y soportan `INPUT_PULLUP` (a diferencia de 34–39).

## El concepto nuevo: funciones

Sin funciones, tendrías que copiar el bucle de "tocar" por cada canción. En cambio, definís una vez:

```cpp
void tocar(int notas[], int duraciones[], int n, int beat) {
  // recorre la canción y la reproduce
}
```

y la llamás con cada melodía:

```cpp
tocar(estrellita, estrellitaDur, estrellitaN, 350);   // botón 1
tocar(mario,      marioDur,      marioN,      150);   // botón 2
```

Una **función** es un bloque de código con nombre que recibe **parámetros** (acá: el array de
notas, el de duraciones, cuántas son, y el tempo) y hace su trabajo. Evita repetir y es la base
para organizar programas más grandes.

> Detalle: cada canción tiene su propio **tempo** (`beat`). Estrellita a 350 ms/negra (tranquila),
> Mario a 150 ms (rápida y saltarina).

## Subir y probar

1. Abrí [`05-jukebox-buttons.ino`](05-jukebox-buttons.ino), Board = ESP32 Dev Module, Port correcto.
2. **Upload**, Serial Monitor a 115200.
3. Apretá **botón 1** → suena Estrellita. **Botón 2** → suena Mario.

## Experimentos

1. **Tercera canción + tercer botón** (tenés 5 pulsadores).
2. **Interrumpible:** ahora la canción suena entera (bloqueante) y no podés cambiarla a mitad.
   Versión avanzada: reproducir nota por nota chequeando los botones entre notas (máquina de
   estados con `millis()`), para poder cortar/cambiar en cualquier momento.
3. **Pot → tempo:** sumá el potenciómetro (03) para acelerar/frenar la canción girando la perilla.

## Nota

La reproducción es **bloqueante** (`delay`): mientras suena una canción, el ESP32 no atiende otra
cosa. Para este proyecto está bien; el experimento 2 muestra cómo hacerlo no bloqueante.

## Siguiente

➡️ **06 — (próximamente):** servo SG90 (PWM aplicado a posición/ángulo).
