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
<p align="center">
<img width="60%" alt="250920_RC24" src="https://github.com/user-attachments/assets/2848ddc7-0e38-44e9-8e20-8f7d54332ac8" />
</p>

### ✨ 主な機能・特徴
* **⚡ 自動ペアリング**: 電源を入れるだけでMACアドレスを認識し即時接続します。
* **🚗 滑らかな加減速**: PWM制御によりフルアクション制御のほか無段階のスピード調整も可能です。
* **🚀 ターボ＆汎用出力**: 前後左右に加え、ターボボタンやLED等の汎用出力に対応しています。
* **🛑 フェイルセーフ**: 電波途絶時、0.2秒以内に全モーターを自動停止します。
<p align="center">
<img width="40%" alt="250920_RC24_CTR (4)" src="https://github.com/user-attachments/assets/152f625d-9f30-4170-841a-1466d5137f5f" />
<img width="40%" alt="250926_ESP02_VTR" src="https://github.com/user-attachments/assets/8d26ec9c-0fd8-49ab-bacf-5a5c39c2b48c" />
<br>
<img width="40%" alt="250922_RC24_BDY (6)" src="https://github.com/user-attachments/assets/009e8f9c-b476-49ed-9875-21c0b7df5490" />
<img width="40%" alt="250927_RC24_No2 (4)" src="https://github.com/user-attachments/assets/53dbb4ea-41d3-4428-a5cd-c00c4c7d9d7d" />
<br>
<a href="https://github.com/user-attachments/files/34935448/RC24_ESP02_cost.pdf"><img width="60%" alt="RC24_ESP02_cost" src="https://github.com/user-attachments/assets/ee56452a-367a-486e-b06e-00c501b19af4" /></a>
<br>
開発元でファームウェア書き込み済みの `アセンブリを実費頒布` していましたが、
<br>
「価格高騰のため頒布を当面休止します。(2026年8月)」と、ご案内がありました。
</p>
当方の手持ち在庫も残り少ないですが、いざマイコン換装の対象となる案件では躊躇することなく使っていきたいので、本リポジトリに登録しておきます。

### 📥 データのダウンロード方法
最新の回路図およびプログラム一式をダウンロードするには、 リポジトリ右上にある緑色の **`[ <> Code ]`** ボタンをクリックし、メニューの一番下にある **`Download ZIP`** から一括ダウンロードできます。
若しくは、[ここをクリックしてください。 ⬇️](https://github.com/ToyDr-W/RC24_ESP_NOW/archive/refs/heads/main.zip)
ダウンロード（42.3 MBのZIPファイル）が直ちに開始されます。

### 📖 詳細ドキュメント・Wiki・解説ブログ
*※外部サイトは Ctrl（MacはCmd）キーを押しながらクリックすると別タブで開けます。*

*   👉 **オリジナル開発者：名張市つつじが丘おもちゃ病院様の解説記事**
    *   [２．４ＧＨｚラジコン用ファームウェア（ＥＳＰ－ＷＲＯＯＭ－０２）の改善（汎用駆動を追加） ↗](https://tutujith.blog.fc2.com/blog-entry-1029.html)
<p align="center">
<img width="30%" alt="２．４ＧＨｚラジコン用ファームウェア（ＥＳＰ０２）開発ボード回路図" src="https://github.com/user-attachments/assets/3ec03dbf-f80e-4f93-9d7f-6da58c180ffc" />
<img width="30%" alt="２．４ＧＨｚラジコン用ファームウェア（ＥＳＰ０２）の改善（汎用駆動を追加）換装回路図コントローラ側フルアクション" src="https://github.com/user-attachments/assets/fe277228-8867-4b7e-8af7-2bb15f8f4378" />
<img width="30%" alt="２．４ＧＨｚラジコン用ファームウェア（ＥＳＰ０２）の改善（汎用駆動を追加）換装回路図車体側" src="https://github.com/user-attachments/assets/14c3ed89-d3ba-4a07-8d90-aa1ed9a19012" />
</p>

*   👉 **おもちゃ修理「電子カルテ」（ToyDr.わたなべ個人ブログ）**
    *   [「技適マークなし」のラジコンを、適法に治療する方法 ↗](https://blog.canpan.info/charts/archive/491)
<p align="center">
<img width="40%" alt="250920_RC24_CTR (2)" src="https://github.com/user-attachments/assets/31204058-d2ee-49a4-8827-f2ee287ff22a" />
<img width="40%" alt="250922_RC24_BDY (2)" src="https://github.com/user-attachments/assets/ab47b118-2cfa-4d05-a44c-23b41224e521" />
</p>
本プロジェクトの**回路図、詳しい使い方やカスタマイズ方法などの日本語解説**は、専用の**Wiki（ウィキ）ページ**にて（以下のリンクから最新の解説ページへ移動して）ご参照ください。

👉<a href="https://github.com/ToyDr-W/RC24_ESP_NOW/wiki/Home" target="_blank">📖 ESP02マイコン換装用ファームウェア解説・回路図（Wikiページ）へ移動する</a>

---

## ⚖️ ライセンスとオリジナル開発者への謝辞

本プログラムの根幹となる素晴らしい設計やアイデアは、**名張市つつじが丘おもちゃ病院 院長 Dr.大泉氏**が築き上げられた卓越した技術と成果物に基づいています。

この素晴らしい先行技術の存在があったからこそ、私たちは2.4GHzラジコンの適法修理という「ハイテク治療」の恩恵にあずかることができています。開発者様への深い敬意と感謝とともに、本プログラムを改変して再配布・共有される場合は、オリジナルと区別できるよう「改変した旨」を付記していただくようお願いいたします。

---

## 🔄 改訂履歴 (Change Log)

<details>
<summary>クリックして詳細を展開 / Click to view details</summary>

### 📄 本リポジトリの更新情報
- **2026/11/16**: v1.0.2 `専用wiki/Home` の内容をTOPページの `README` にも取込み集約して `README` を全面改修 
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
* **🚗 Smooth Acceleration & Full-Action Control**: Supports both full-action directional control and stepless speed adjustment via PWM.
* **🚀 Turbo & Auxiliary Outputs**: Directional controls plus turbo/LED outputs.
* **🛑 Fail-Safe Auto-Brake**: Halts motors within **0.2 seconds** on signal loss.

### 📥 How to Download
Click the green **`[ <> Code ]`** button at the top right of the repository page and select **`Download ZIP`**.

### 📖 Documentation & Acknowledgements
* 📘 **[GitHub Wiki](https://github.com/ToyDr-W/RC24_ESP_NOW/wiki)** | 📝 **[Blog](https://blog.canpan.info/charts/archive/491)**
