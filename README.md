# ESP32 Wi-Fi Scanner (PlatformIO)

## Overview

Простой Wi-Fi сканер для ESP32, написанный на Arduino framework и собираемый через PlatformIO.

Поддерживает:

* ESP32 (классический, Xtensa)
* ESP32-C3 (RISC-V, USB CDC)

Выводит:

* SSID
* RSSI
* канал
* тип шифрования

---

## Hardware Support

| Плата    | Поддержка | Особенности                 |
| -------- | --------- | --------------------------- |
| ESP32    | ✅         | UART Serial                 |
| ESP32-C3 | ✅         | USB CDC (нужно доп. конфиг) |

---

## Установка

```bash
git clone https://github.com/che711/esp32-wifi-scan/
cd esp32-wifi-scan
```

Убедись, что установлен PlatformIO:

```bash
pio --version
```

---

## Конфигурация PlatformIO

### ESP32-C3 (рекомендуется для Super Mini)

```ini
[env:esp32c3]
platform = espressif32
board = esp32-c3-devkitm-1
framework = arduino
monitor_speed = 115200

build_flags =
  -DARDUINO_USB_MODE=1
  -DARDUINO_USB_CDC_ON_BOOT=1
```

---

### ESP32 (DevKit)

```ini
[env:esp32]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
```

---

## Запуск

### Важно
Yказывай флаг `-e` усли у тебя несколько environments.

---

### ESP32-C3

```bash
pio run -e esp32c3 -t upload -t monitor
```

---

### ESP32

```bash
pio run -e esp32 -t upload -t monitor
```

---

## Определение порта

```bash
pio device list
```

или:

```bash
ls /dev/tty*
```

---

## 🧠 Особенности ESP32-C3

ESP32-C3 использует **native USB**, а не UART.

### Симптомы проблем:

* Serial Monitor пустой
* порт есть, но нет вывода

### Решение:

1. Включить USB CDC:

   ```ini
   build_flags =
     -DARDUINO_USB_MODE=1
     -DARDUINO_USB_CDC_ON_BOOT=1
   ```

2. Ждать Serial в коде:

```cpp
Serial.begin(115200);

unsigned long start = millis();
while (!Serial && millis() - start < 3000) {
  delay(10);
}
```

---

## 📡 Ограничения

* ESP32 / ESP32-C3 поддерживают только **2.4 GHz**.  5 GHz не поддерживается

---

## 📦 Зависимости

* Arduino framework (PlatformIO)
* WiFi library (встроенная)

---

## Полезные команды

```bash
# Сборка
pio run

# Заливка
pio run -t upload

# Монитор
pio device monitor

# Только нужная плата
pio run -e esp32c3 -t upload

# Список устройств
pio device list
```

---

## Статус

* [x] ESP32 поддержка
* [x] ESP32-C3 поддержка
* [x] Serial debugging
* [x] Wi-Fi scan

---

## License

MIT
