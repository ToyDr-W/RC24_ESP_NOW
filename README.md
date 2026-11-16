# 🚀 RC24_ESP_NOW
**技適対応・ESPマイコン換装用ラジコンファームウェア（ESP-NOW）**  
*Giteki-Compliant RC Firmware for ESP Microcontrollers using ESP-NOW*

**対応マイコン**: `ESP-WROOM-02 (ESP8266)` / `ESP32-C3-WROOM-02`  
**通信方式**: `ESP-NOW`（技適対応・2.4GHz帯）  
**ライセンス**: 改変・再配布時はオリジナル開発者への帰属表示（Attribution）が必要です

[🇯🇵 日本語 (Japanese)](#-日本語-japanese) | [🇺🇸 English](#-english)

---

## 🇯🇵 日本語 (Japanese)

### 📌 プロジェクト概要
技適マークのない海外製2.4GHzトイラジコンを、日本の電波法に適合したWi-Fiマイコン（**ESP-WROOM-02** / **ESP32-C3-WROOM-02**）へ換装し、ESP-NOWで動作させるためのファームウェアおよび回路資料集です。

### ✨ 主な機能・特徴
* **⚡ 自動ペアリング**: 電源を入れるだけでMACアドレスを認識し即時接続します。
* **🚗 滑らかな加減速**: PWM制御によりフルアクション制御のほか無段階のスピード調整も可能です。
* **🚀 ターボ＆汎用出力**: 前後左右に加え、ターボボタンやLED等の汎用出力に対応しています。
* **🛑 フェイルセーフ**: 電波途絶時、0.2秒以内に全モーターを自動停止します。

### 📥 データのダウンロード方法
リポジトリ右上にある緑色の **`[ <> Code ]`** ボタンをクリックし、メニューの一番下にある **`Download ZIP`** から一括ダウンロードできます。

### 📖 詳細ドキュメント・Wiki・解説ブログ
* 📘 **[GitHub Wiki (Home)](https://github.com/ToyDr-W/RC24_ESP_NOW/wiki)**（更新履歴・アーカイブ）
* 📝 **[おもちゃ修理「電子カルテ」（ブログ） ↗](https://blog.canpan.info/charts/archive/491)**

---

## 🔄 改訂履歴 (Change Log)

<details>
<summary>クリックして詳細を展開 / Click to view details</summary>

### 📄 本リポジトリの更新情報
- **2026/11/16**: v1.0.2 `専用wiki/Home` の内容をTOPページの `README` にも取込み集約して全面改修 
- **2026/11/16**: v1.0.1 本リポジトリへ登録時の `初版wikiページ` を別名で `wiki/v1.0.0_Proto` として作成 
- **2026/10/14**: v1.0.0 （GitHub開始時、安定版） 2026/3/31 汎用駆動の機能追加。

</details>

---
---

## 🇺🇸 English

### 📌 Overview
**RC24_ESP_NOW** is an open-source firmware and hardware schematic repository to retrofit 2.4GHz toy RC cars with Giteki-certified Wi-Fi modules using **ESP-NOW**.

### ✨ Key Features
* **⚡ Instant Auto-Pairing**: Automatic connection on power-up.
* **🚗 Smooth PWM Speed Control**: Proportional acceleration and deceleration.
* **🚀 Turbo & Auxiliary Outputs**: Directional controls plus turbo/LED outputs.
* **🛑 Fail-Safe Auto-Brake**: Halts motors within **0.2 seconds** on signal loss.

### 📥 How to Download
Click the green **`[ <> Code ]`** button at the top right of the repository page and select **`Download ZIP`**.

### 📖 Documentation & Acknowledgements
* 📘 **[GitHub Wiki](https://github.com/ToyDr-W/RC24_ESP_NOW/wiki)** | 📝 **[Blog](https://blog.canpan.info/charts/archive/491)**
