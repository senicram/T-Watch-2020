[![PlatformIO](https://github.com/lunokjod/watch/workflows/PlatformIO/badge.svg)](https://github.com/lunokjod/watch/actions/) ![ViewCount](https://views.whatilearened.today/views/github/lunokjod/watch.svg)



# Fork of lunokjod/watch (LilyGo TWatch 2020 lunokIoTWatch firmware)
Modifications Copyright (C) 2025 Marcin Cz

[If you like it buy me a coffe!]()

[Changes 12.2025]
- Apps can consistently return to the main menu instead of the watchface, enabling customizable back navigation across all applications.
- The menu paginator now remembers the last selected item by persisting the selection across app instances, restoring it when the menu is reopened instead of always starting at the first entry.
- Applied latest security patches and code optimization by updating espressif32 4.4.0 -> 6.3.0
  

## Espressif32 6.3.0 tests summary table

| # | Feature | Sub-Test | Status | Notes | Date Tested |
|:-:|:---------|:----------|:--:|:-------------|:--------:|
| 1 | **Power On/Off** | Device boots normally | ✅ | | 12.2025 |
| | | No crashes during startup | ✅ | | 12.2025 |
| 2 | **Display** | Graphics render correctly | ✅ | | 12.2025 |
| | | No flickering or corruption | ✅ | | 12.2025 |
| 3 | **BLE Connectivity** | Bluetooth scan finds devices | ✅ | | 12.2025 |
| | | Pairing works | ⬜ | | |
| | | HID input responsive | ⬜ | | |
| 4 | **WiFi Connectivity** | WiFi scan functions | ⬜ | | |
| | | Network connection stable | ⬜ | | |
| | | OTA updates (if enabled) | ⬜ | | |
| 5 | **Storage** | File system operations work | ✅ | | 12.2025 |
| | | Database queries functional | ✅ | | 12.2025 |
| | | NVS storage accessible | ⬜ | | |
| 6 | **Sensors** | Accelerometer/gyro data | ⬜ | | |
| | | Touch input responsive | ✅ | | 12.2025 |
| | | Battery level accurate | ✅ | | 12.2025 |
| 7 | **Audio** | Sounds play without distortion | ✅ | | 12.2025 |
| | | Volume control works | ⬜ | | |

## Dependencies Table

| Dependency | Current | Latest | Status | V3 Safe |
|---|---|---|---|---|
| espressif32 Platform | 6.3.0 | 6.3.0 | ✅ Latest | ⚠️ Testing ongoing |
| NimBLE-Arduino | 2.3.7 | 2.3.7 | ✅ Latest | ✅ |
| ArduinoNvs | 2.5.0 | 2.10.0 | ⚠️ Needs update | ✅ |
| QRCode | 0.0.1 | 0.0.1 | ✅ Latest | ✅ |
| Arduino_JSON | 0.1.0 | 0.2.0 | ⚠️ Needs update | ✅ |
| ESP8266Audio | 1.9.7 | 2.4.1 | ⚠️ Needs update | ✅ |
| TTGO TWatch Library | 1.4.3 Git | 1.4.3 Git | ✅ Current | ✅ Optimized |
| Ticker | 2.0.0 | 4.4.0 | ⚠️ Needs update | ✅ |
| LittleFS | 2.0.0 | 2.11.2 | ⚠️ Needs update | ✅ |
| Arduino-esp32 | 2.0.0 | 3.3.5 | ⚠️ Needs update | |
| FS | 2.0.0 | 3.3.5 | ⚠️ Needs update, Part of Arduino-esp32|  | 
| HTTPClient | 2.0.0 | 3.3.5 | ⚠️ Needs update, Part of Arduino-esp32 | ✅ |
| SPI | 2.0.0 | 3.3.5 | ⚠️ Needs update, Part of Arduino-esp32 | ✅ |
| WiFi | 2.0.0 | 3.3.5 | ⚠️ Needs update, Part of Arduino-esp32 | ✅ |
| WiFiProv | 2.0.0 | 3.3.5 | ⚠️ Needs update, Part of Arduino-esp32 | ✅ |
| ESP32 BLE Arduino | 2.0.0 | 3.3.5 | ⚠️ Needs update, Part of Arduino-esp32 | ✅ |
| Sqlite3Esp32 | 2.5.0 | 3.3.5 | ⚠️ Needs update, Part of Arduino-esp32 | ✅ |
| miniz | 3.1.0 Git | 3.1.0 Git | ✅ Current | ✅ |
| Arduino-Lua | Git Latest| Git Latest | ✅ Current | ✅ |
| BLE_HID_Client | Latest Git | Latest Git | ✅ Latest | ✅ |

**Legend:**
- ⬜ Not Tested - Test not yet performed
- 🟨 Testing - Currently in progress
- ✅ Pass - Feature working correctly
- ❌ Fail - Feature not working, needs investigation
- ⚠️ Partial - Some aspects work, others have issues


## Product Comparison
| Feature             | T-Watch-2019                                                                                          | T-Watch-2020-V1                                                                 | T-Watch-2020-V2                                                                   | T-Watch-2020-V3                                                                    | T-Block / T-Block-V1                                                        | LilyPi                                                                                                        |
| ------------------- | ----------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------- | --------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------- | --------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------- |
| **Product**         | [T-Watch-2019](https://www.aliexpress.com/item/33038999162.html)                                      | [T-Watch-2020-V1](https://www.aliexpress.com/item/4000971508364.html)           | [T-Watch-2020-V2](https://www.aliexpress.com/item/1005002264354524.html)          | [T-Watch-2020-V3](https://www.aliexpress.com/item/1005002053650442.html)           | [T-Block](https://www.aliexpress.com/item/1005001824993604.html)            | [LilyPi](https://www.aliexpress.com/item/1005001447548347.html)                                               |
| **Core**            | [ESP32-D0WDQ6](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_cn.pdf)    | ESP32-D0WDQ6                                                                    | ESP32-D0WDQ6                                                                      | ESP32-D0WDQ6                                                                       | ESP32-D0WDQ6                                                                | [ESP32-WROVER-B](https://www.espressif.com/sites/default/files/documentation/esp32-wrover-b_datasheet_cn.pdf) |
| **PSRAM**           | 16 MB                                                                                                 | 16 MB                                                                           | 16 MB                                                                             | 16 MB                                                                              | 16 MB                                                                       | 16 MB                                                                                                         |
| **Flash**           | 8 MB                                                                                                  | 8 MB                                                                            | 4 MB                                                                              | 8 MB                                                                               | 8 MB                                                                        | 8 MB                                                                                                          |
| **PMU**             | [AXP202](https://github.com/Xinyuan-LilyGO/LilyGo-HAL/tree/master/AXP202)                             | AXP202                                                                          | AXP202                                                                            | AXP202                                                                             | AXP202                                                                      | ❌                                                                                                             |
| **IMU**             | [BMA423](https://github.com/Xinyuan-LilyGO/LilyGo-HAL/tree/master/BMA423)                             | BMA423                                                                          | BMA423                                                                            | BMA423                                                                             | [MPU6050](https://github.com/Xinyuan-LilyGO/LilyGo-HAL/tree/master/MPU6050) | ❌                                                                                                             |
| **TFT**             | [1.54″ 240×240 ST7789V](https://github.com/Xinyuan-LilyGO/LilyGo-HAL/blob/master/DISPLAY/ST7789V.pdf) | Same                                                                            | Same                                                                              | Same                                                                               | [1]                                                                         | [1]                                                                                                           |
| **Touch Screen**    | [FT6336](https://github.com/Xinyuan-LilyGO/LilyGo-HAL/tree/master/TOUCHSCREEN)                        | FT6336                                                                          | FT6336                                                                            | FT6336                                                                             | [1]                                                                         | [1]                                                                                                           |
| **RTC**             | [PCF8563](https://github.com/Xinyuan-LilyGO/LilyGo-HAL/tree/master/RTC)                               | PCF8563                                                                         | PCF8563                                                                           | PCF8563                                                                            | PCF8563                                                                     | PCF8563                                                                                                       |
| **Infrared Sensor** | ❌                                                                                                     | ✅                                                                               | ✅                                                                                 | ✅                                                                                  | ❌                                                                           | ❌                                                                                                             |
| **Scalable**        | ✅                                                                                                     | ❌                                                                               | ✅                                                                                 | ❌                                                                                  | ✅                                                                           | ✅                                                                                                             |
| **Microphone**      | [1]                                                                                                   | ❌                                                                               | ❌                                                                                 | [SPM1423HM4H](https://github.com/Xinyuan-LilyGO/LilyGo-HAL/tree/master/MICROPHONE) | [1]                                                                         | ❌                                                                                                             |
| **GPS**             | [1]                                                                                                   | ❌                                                                               | [Quectel L76K](https://github.com/Xinyuan-LilyGO/LilyGo-HAL/tree/master/L76K)     | ❌                                                                                  | [1]                                                                         | ❌                                                                                                             |
| **Decoder**         | [1]                                                                                                   | [MAX98357A](https://github.com/Xinyuan-LilyGO/LilyGo-HAL/tree/master/MAX98357A) | ❌                                                                                 | MAX98357A                                                                          | [1]                                                                         | ❌                                                                                                             |
| **Tactile**         | [1]                                                                                                   | ✅ (IO)                                                                          | [DRV2605](https://github.com/Xinyuan-LilyGO/LilyGo-HAL/tree/master/DRV2605) (I²C) | ✅ (IO)                                                                             | [1]                                                                         | ❌                                                                                                             |
| **Button**          | ✅                                                                                                     | ✅ [2]                                                                           | ✅ [2]                                                                             | ✅ [2]                                                                              | ✅ [2]                                                                       | ✅                                                                                                             |



<img src="./doc/watchface0.png" width="120" /> <img src="./doc/playground0.png" width="120" /> <img src="./doc/playground3.png" width="120" /> <img src="./doc/settime.png" width="120" /> <img src="./doc/battery.png" width="120" /> <img src="./doc/ble_upload.png" width="120" /> <img src="./doc/mainmenu_provisioning.png" width="120" /> <img src="./doc/provisioning.png" width="120" />

* Note: under heavy development (not ready for everyday use)


* Supported devices:
 * lilyGo TWatch 2020 series v1
 * lilyGo TWatch 2020 series v2
 * lilyGo TWatch 2020 series v3 (both battery and UART/TTL) 380mAh and 500mAh (planned 400mAh & 470mAh version)

* You can set WiFi credentials ("Home>Settings>Prov") via QR using:
  * Android device: https://play.google.com/store/apps/details?id=com.espressif.provsoftap (select WiFi provisioning using WiFi)
  * Apple iOS: https://apps.apple.com/us/app/esp-softap-provisioning/id1474040630

* The BluetoothLE pairing can be archieved via "Home>Settings>Pair" can use BatON https://play.google.com/store/apps/details?id=com.limi.baton on Android to remote battery monitoring

* Can use Gadgetbridge https://www.gadgetbridge.org/ and receive android notifications on watch (use "BANGLEJS esprunio" as device)



## Basic usage:

* Use button to wake/sleep the watch
* When screen goes on, the watchface appears
* Long button push for poweroff

## What does:
* WiFi time sync once every 24h (using network time protocol NTP)
* WiFi weather sync every 30 minutes, needs online account (set your openWeather key in "openWeatherKey.txt" at same level as platformio.ini before build) more info: https://openweathermap.org/
* Wake up every 15 minutes to monitor the user pose (future sleep monitor)
* Wake up every activity (steps monitor app Home>Steps)
 * BLE GATT support
  * Pairing with random pin (see "Home>Settings>Pair" on main menu)
   * Remove current bonded devices
  * BLE Battery standard notification. Can use BatON https://play.google.com/store/apps/details?id=com.limi.baton on Android to remote battery monitoring
  * Man in the middle resistant (BLE)
 * Color themes
 * Multiple watchfaces (call for designers!)
 * Screen orientation
 * OTA update (wireless)
 * Gadgetbridge compatibility (BangleJS-esprunio) for android/iOS notifications
 * Media player
 * Handwritting trainable keyboard
 * BLE zone location
 * omdb Posters api
 * Launch lamp on gesture (put your arms down and double tap or PEK)
 * Deep sleep: Put your watch with the screen ON facing to plane surface and the stripes points up
 * Wakeup: Simply wear-it on your wrist, the watch boots up, PEK and doubleTap already works
 * Lua scripting
 * UI rich controls with layouting via (LuI)
 * 3D engine control on LuI
 * Handwritting reconeisance

## Full application list:

**OUTDATED**

[See outdated app gallery](src/app/README.md)

## Hardware support:
 * BMA423 support (including during sleep)
 * AXP202 support (including sleep)
 * haptic and vibration support
 * ST7789V support (lilygo TFT_eSPI)
 * Partial RTC support (system sync)
 * MAX98357A (mp3 playback support)
 * WiFi (via provisioning)
 * BLE (work in progress) issues while wifi is in use
 * IR work, but only can send with this hardware (useless by now, I want to do jokes!)

### Pending to implement:
* Multiple apps (seamless)
* Add first launch application assistant to set or omit the desired setup parts
* PDM Mic (voice assistant)
* RTC (alarm features)
* espNow (locate other family watches, icon chat availiable)
* Custom activities (hidden app availiable for testing)
* feedbacked apps (what do you need?)
* Web installer: https://espressif.github.io/esptool-js/
 * User customizable night hours, during this time, the system don't allow to reply anything inmediatly(delayed send guarantees don't send stupid messages to others by accident)
 * Menú must remember the last used or better: reorder the list with user preferences (app usage counters)
 * hive mode (wireless mesh, share info with other lunokIoT, without infrastructure)

