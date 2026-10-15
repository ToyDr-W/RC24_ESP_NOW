## RC24_ESP_NOW

# 🚀 技適対応・ESPマイコン換装用ラジコンファームウェア（RC24_ESP-NOW）

## 📌 はじめに (Introduction)

現在のおもちゃ修理の現場（おもちゃ病院活動）において、2.4GHzのトイラジコンは非常に大きな課題となっています。一部の現場では「技適マークがない無線機器」というだけで、トラブルを恐れて一律に**「受付不可（修理不能）」**として一蹴してしまう閉塞的な現状も垣間見られます。

しかし、おもちゃを大切に想う子どもたちの目の前で、大人の都合やルールの壁を理由に諦めてしまって良いのでしょうか。

私たちは、その閉塞感に風穴を開けたいと考えました。
法を無視して危険な電波を飛ばすのではなく、**「現代の優れた安全なテクノロジー（技適取得済みのESP-WROOM-02等）を正しく組み込むことで、適法かつ安全に、おもちゃを元通りに蘇らせる」**。これこそが、いま私たちおもちゃドクターに求められている技術的な挑戦であり、本当の意味での「地域密着型」の真摯な活動であると確信しています。

本プロジェクトは、先達の偉大なノウハウをリサーチ・吸収し、子どもたちが「安心、安全に遊べる適法ラジコン」をドクター自らの手で作り出すためのオープンソース・ファームウェアです。

<p align="center">
<img width="30%" alt="250918_RC24_ESP02 (3)" src="https://github.com/user-attachments/assets/8e3c3036-3cab-443f-853b-6ea8fdbe919f" />
<img width="30%" alt="250922_RC24_BDY (4)" src="https://github.com/user-attachments/assets/ef2ee810-e125-41b5-9c22-bd29e5c44563" />
</p>

*※安価なESP-02のほか、入手容易なESP32-C3-WROOM-02でも使えるように、両方のスケッチを同梱しています。*

*なお私の開発環境は Arduino IDE 2.3.10、esp32ボードは v3.2.1にダウングレードしています。*

---

### Project Background
In the current field of toy repairs (toy hospitals), 2.4GHz toy RCs present a significant challenge. Unfortunately, some toy hospitals uniformly refuse to accept or repair these toys simply because they lack a "technical conformity mark" (Giteki), out of fear of legal or technical compliance issues.

But should we really give up in front of children who love their toys, simply because of administrative walls?

We decided to break through this stagnant situation. Instead of illegally emitting radio waves, we can **"integrate modern, safe, and fully certified technology (such as the Giteki-certified ESP-WROOM-02) to legally and safely bring toys back to life."** We believe this is the exact technical challenge that toy doctors should embrace today, embodying the true spirit of community-based, child-first service.

This project offers an open-source firmware designed to build "legally compliant, safe RCs" by building upon the outstanding expertise of our predecessors, ensuring children can play with their repaired toys without any anxiety.

---

## 📖 詳細な解説・使い方 (Documentation & Wiki)

私を含めシニア世代ドクターの方々にも分かりやすいよう、具体的な回路図、Arduino IDEでの書き込み手順のご案内、実践的な試作報告など、詳細情報はすべて**専用のWikiページ**に集約しています。

以下の青い文字（リンク）をクリックして解説ページへお進みください。

👉 ［ **[専用Wikiページを開く](https://github.com/ToyDr-W/RC24_ESP_NOW/wiki)** ］

Detailed instructions, including hardware schematics, parts lists, and setup guides, are available on the project Wiki.
👉 ［ **[Visit the Project Wiki](https://github.com/ToyDr-W/RC24_ESP_NOW/wiki)** ］

---

## ⚖️ 免責事項 (Disclaimer)

* **自己責任での利用**: 本ソフトウェアは「現状のまま」無保証で提供されます。本ファームウェアを利用したおもちゃの修理・改造、およびリチウムイオン電池の組み込み等の作業は、すべて利用者の自己責任において行ってください。
* **法的責任の否定**: 作者（ToyDr.WATANABE）は、本ソフトウェアの使用や改造作業に起因して生じた、いかなるトラブル、機器の破損、怪我、その他の損害についても一切の責任を負いません。
* **ライセンスについて**: 開発の経緯、および先行開発者様への謝辞や配布条件の詳細は、同梱の `LICENSE` ファイルを必ずご確認ください。

* **Use at Your Own Risk**: This software is provided "as is" without any warranty. Any modifications, repairs, or battery replacements using this firmware are performed entirely at the user's own risk.
* **Limitation of Liability**: The author (ToyDr.WATANABE) shall not be liable for any claims, damages, injuries, or other liabilities arising from the use of this software.
* **License Details**: Please refer to the attached `LICENSE` file for details regarding the historical background, acknowledgments to the original developer, and redistribution terms.
