# Sparrow24 BLE Calculator Firmware

## マニュアル

最上段の 4 キー左から

- 1. Bluetooth キーボードモード
- 2. 電卓モード
- 3. 電卓モード時、計算結果をキーコードとして送る
- 4. Backspace

ディスプレイ裏の LED の状態表示は以下のようになっております。

- 青 電卓モード、BLE 接続あり
- 紫 電卓モード、BLE 接続なし
- 橙 キーボードモード、BLE 接続あり
- 赤 キーボードモード、BLE 接続なし

キー入力を変更したい場合、button.cpp の KEY_ASSIGNS を変更してください。

## 現状の問題

- 一度接続済みキーボードに再接続すると、うまくキーが送られないことがある

## ファームウェアの書き込み方法

ビルドガイドのファームウェアのアップロード方法を確認ください。

https://github.com/74th/sparrow24-ble-calculator-buildguide#%E3%83%95%E3%82%A1%E3%83%BC%E3%83%A0%E3%82%A6%E3%82%A7%E3%82%A2%E3%81%AE%E3%82%A2%E3%83%83%E3%83%97%E3%83%AD%E3%83%BC%E3%83%89%E6%96%B9%E6%B3%95

## features

- ESP32 マイコンで Bluetooth キーボードにする
  - Kailh HotSwap ソケットに対応し、キースイッチが交換可能
  - テンキーで一般的な 2U キーが 3 つある
  - 1 個の 2U スイッチの代わりに、2 個の 1U スイッチとしても使うことができる
  - テンキーの他に、追加で 4 キーを備える
- 電卓機能を持つ
  - OLED でくっきりきれいに表示される
  - 有理数で計算する（0.1 が計算できる）
  - 桁が溢れたら浮動小数点で表示する
- 電卓の結果をキーボード入力として打鍵できる
- 電卓モードか、キーボードモードか、電源オフ状態か、LED の色で判別可能
- USB-C の電源に対応する
- 電池駆動に対応する
- 電池駆動の場合、スイッチを押すとレギュレータが ON になり、初めて ESP32 に電源が入る（つまり、未使用時の待機電力が低い）
- ESP32 から GPIO でレギュレータを OFF にして ESP32 の電源をオフにすることができる（つまり、ESP32 で一定時間未使用であることを検出してマイコンの電源をオフにできる）
- OLED ディスプレイと ESP32 の電源のレギュレータが別になり、OLED の電源オンオフの ESP32 への影響を抑える
- ESP32 のファームウェアを書き換えることができるよう UART のポートを持ち、RESET、EN ボタンを備える
- ESP32 のデバッグ実行ができるよう JTAG のポートを持つ（JTAG として使わない場合も、GPIO として何かをつなげたりして遊べる。M5Stack は JTAG ポート使えないのよね。）

- Making a Bluetooth Keyboard with an ESP32 Microcontroller
  - Support for Kailh Hot Swap sockets and interchangeable keyswitches
  - Has three 2U keys, typical for numeric keypad
  - Can be used as two 1U switches instead of one 2U switch
  - Has an additional 4 keys in addition to the numeric keypad
- Has a calculator function
  - OLED display for a clear and crisp display
  - Calculates with rational numbers (0.1 can be calculated)
  - Display in floating point if digits overflow
- The result of the calculator can be typed as keyboard input.
- LED color can be used to determine if the device is in calculator mode, keyboard mode, or powered off
- Supports USB-C power supply
- Supports battery power
- When battery-powered, pressing the switch turns on the regulator and turns on the ESP32 for the first time (i.e., low standby power when not in use).
- The regulator can be turned off via GPIO from the ESP32 to turn off power to the ESP32 (i.e., the ESP32 can detect that the microcontroller has not been used for a certain period of time and turn off power to the microcontroller).
- Separate regulators for the OLED display and ESP32 power supply to reduce the effect of OLED power on/off on the ESP32.
- A UART port is provided for rewriting the ESP32 firmware, and RESET and EN buttons are provided.
- A JTAG port for debugging ESP32 (even if you don't use it as a JTAG port, you can play with it by connecting something as a GPIO; M5Stack doesn't have a JTAG port)

Translated with www.DeepL.com/Translator (free version)

## License

GPL v3

ESP32 BLE Keyboard Libraries のライセンスが明らかになった場合には、LGPL v3 に変更します。

## Semantics 回路図

[./docs/semantics.pdf](./docs/semantics.pdf)

## Libraries

- OLED Display: https://akizukidenshi.com/download/ds/akizuki/so1602awwb-uc-wb-u_akizuki_manu.pdf
- Adfruit NeoPixel Library (LGPL v3) : https://github.com/adafruit/Adafruit_NeoPixel
- Bluetooth LE Keyboard library for the ESP32 (GPL v3?) : https://github.com/T-vK/ESP32-BLE-Keyboard
- GNU Multi-Precision Library for Arduino (LGPL ?) https://github.com/CAFxX/gmp-ino
  - GNU Multi-Precision Library (LGPL v2/v3) : https://gmplib.org/

## footprint, semantics libraries

- Power USB-C Socket UJC-HP-3-SMT-TR https://www.snapeda.com/parts/UJC-HP-3-SMT-TR/CUI%20Devices/view-part/ (CC-BY-SA)
- Toggle Switch 2MS1-T1-B4-VS2-Q-E-S https://componentsearchengine.com/part-view/2MS1T1B4VS2QES/Dailywell
- Cherry MX Compatible Switch https://github.com/foostan/kbd (MIT)
