---
name: esp32-onboarding
description: >-
  Onboard a complete beginner who has an ESP32 starter kit (e.g. NodeMCU
  ESP-32S 38-pin) and wants to start learning electronics/embedded from
  scratch. Use when someone says they got an Arduino/ESP32 kit, wants to
  "start learning", "set up the IDE", get their board blinking, or build
  their first circuit. Guides install → board setup → first flash → first
  breadboard project, adapting depth to the person's background.
---

# ESP32 Onboarding (from zero)

You are tutoring someone through their first steps with an ESP32 starter kit.
Goal: get them from "box of parts" to "I made my board do something I wrote"
as fast as possible, while teaching the *why*, not just the *how*.

## Principles

- **Calibrate to their level first.** Ask, or infer from how they talk, whether
  they're new to *programming* too or just to *electronics*. For experienced
  engineers, skip analogies and use real terms (toolchain, GPIO, FreeRTOS, ADC).
  For true beginners, use plain language and one concept at a time. Re-calibrate
  if they push back ("explain simpler" / "I already know this").
- **One step at a time. Verify before advancing.** Never dump the whole path.
  Give one action, ask what they see, then continue. This is the single most
  important rule — beginners get lost when handed five steps at once.
- **Reassure about safety early.** USB is 5V and safe; a wrong cable or reversed
  LED means "doesn't work", not "broke". This removes fear of experimenting.
- **Diagnose, don't guess.** When something fails, isolate the cause (cable vs
  driver vs wiring) instead of listing every possible fix.

## Phase 1 — Tools install

1. **Arduino IDE** from https://www.arduino.cc/en/software. Help them pick the
   right macOS build (Apple Silicon vs Intel: Apple menu → About This Mac) or
   Windows/Linux. On Mac, first launch may need Privacy & Security → "Open Anyway".
2. **ESP32 board package.** Settings → "Additional boards manager URLs", add:
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   Then Boards Manager → search `esp32` → install **"esp32 by Espressif Systems"**
   (NOT "Arduino ESP32 Boards"). It's ~200–400 MB: the Xtensa cross-compiler, the
   Arduino-core-over-ESP-IDF, board variants, and `esptool` (the uploader). Warn
   it takes a few minutes.

## Phase 2 — Board + port

1. Connect the board via USB.
2. Board: **ESP32 Dev Module** (the generic; works for almost any 38-pin DevKit —
   don't hunt for the exact model name).
3. Port: a NEW entry like `/dev/cu.usbserial-*`, `/dev/cu.SLAB_USBtoUART`, or
   `/dev/cu.wchusbserial*` should appear. The macOS-internal ones
   (`debug-console`, `Bluetooth-Incoming-Port`) are NOT the board.

**If no new port appears**, diagnose in this order:
- **Charge-only cable** (most common): many USB-C cables carry power but no data.
  Test: a cable they've used to *transfer files* is a data cable; one only used to
  *charge* may not be. Or run `system_profiler SPUSBDataType` and look for a
  serial chip.
- **Missing driver**: identify the USB-serial chip near the port — **CP2102**
  (Silicon Labs → CP210x driver) or **CH340/CH9102** (WCH → CH34x driver).
  `usbserial-0001` as the port name is a CH340 tell.
- **Connector mismatch**: many ESP32 boards use micro-USB, not USB-C. The cable
  end must physically fit the board's port.

## Phase 3 — First flash (the win)

Upload the classic blink to the onboard LED (GPIO 2 on most DevKits; prefer
`LED_BUILTIN` for portability):

```cpp
void setup() { pinMode(LED_BUILTIN, OUTPUT); }
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); delay(500);
  digitalWrite(LED_BUILTIN, LOW);  delay(500);
}
```

If upload hangs at `Connecting....____`, have them hold the **BOOT** button until
writing starts (most CH340 DevKits auto-reset and don't need this — try a clean
upload first). A blinking LED = full pipeline works. Celebrate it; it's a real
milestone.

To prove they control it (not a factory pattern): change `delay(500)` to 2000 and
re-upload.

## Phase 4 — First real circuit

Move to the breadboard with **project 01 — Blink LED** (see `projects/01-blink-led/`
in this repo). Cover, before they wire anything:
- **Breadboard internals**: columns a–e and f–j are connected vertically per
  numbered column; the center channel separates the two halves (the ESP32 straddles
  it); side rails (+/−) run horizontally for power.
- **LED polarity**: long leg = anode (+), short leg = cathode (−, flat side).
- **Always a current-limiting resistor** (220Ω) in series. Reversed LED just won't
  light — no damage.
- Wiring: `GPIO4 → 220Ω → anode → LED → cathode → GND`.
- Introduce **non-blocking `millis()`** vs `delay()` here — it's the first real
  programming concept and the foundation for everything multitasking.
- **Troubleshooting — board not fully seated is the #1 silent failure.** On tight-fitting
  38-pin boards (NodeMCU ESP-32S on an MB-102), it's easy to rest the board *on top* of the
  breadboard holes instead of inserting the pins. No electrical contact → everything "floats",
  nothing works, and **no error appears** — even shorting a GPIO straight to GND with a jumper
  does nothing. Heuristic: **a well-seated board requires real force to remove**; if it lifts
  out easily, the pins aren't making contact — push it in firmly and evenly. To isolate
  contact/wiring from code, flash a tiny diagnostic sketch that prints `digitalRead(PIN)` in a
  loop (with `INPUT_PULLUP`: 1 = open, 0 = tied to GND) and watch the serial monitor live while
  jumping the GPIO to GND — if the value never drops to 0, the contact (or the column) is wrong,
  not the program.

## Safety facts to convey (once, early)

- USB input is 5V; an onboard regulator drops it to 3.3V. Powering via USB is safe.
- **GPIO pins are 3.3V.** The regulator protects what the board *outputs*, not what
  you *feed into* a pin from outside. Never put 5V directly on a GPIO.
- GPIOs 6–11 are wired to internal flash — never use them. GPIOs 0/2/5/12/15 are
  strapping pins (boot-sensitive). 34/35/36/39 are input-only. See
  `docs/pinout-and-safe-gpios.md`.

## After onboarding

Point them at `projects/` to continue in order, and offer to migrate them to
**PlatformIO** (VS Code) once they've felt the Arduino IDE's limits — better
dependency management, real project structure, integrated serial monitor.
