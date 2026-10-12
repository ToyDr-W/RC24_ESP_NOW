//ESP32-C3-WROOM-02をESP_NOWでﾄｲﾗｼﾞの操作を行う車体側のｽｹｯﾁ


#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>


//==============================================
//ｱﾌﾟﾘｹｰｼｮﾝ設定値
//==============================================
#define WIFI_CHANNEL 1
static uint8_t CTR_MAC[6]={0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
            //ｺﾝﾄﾛｰﾗ側のMACｱﾄﾞﾚｽはﾌﾞﾛｰﾄﾞｷｬｽﾄ
#define RCV_TMR   200         //無通信監視時間[ms]


//==============================================
//ﾎﾟｰﾄ割当て
//==============================================
#define LED_STS   19
#define OUT_FWD   4
#define OUT_BAK   5
#define OUT_LFT   10
#define OUT_RGT   1
#define OUT_TRB   6
#define PWMCH_FWD 4
#define PWMCH_BAK 5
#define OUT_GPOUT 7 //汎用駆動(正論理)
#define IO9   9 //IO8


//==============================================
//大域変数
//==============================================
static uint8_t ctr_mac[6]={255,255,255,255,255,255};
            //ｺﾝﾄﾛｰﾗ側のMACｱﾄﾞﾚｽ(ﾌﾞﾛｰﾄﾞｷｬｽﾄ)
static uint8_t bdy_mac[6];      //車体側(自分)のMACｱﾄﾞﾚｽ

static struct RECV_MSG        //受信ﾒｯｾｰｼﾞ構造体
  {
    unsigned char drv;    //前後進の制御値
    unsigned char str;    //ｽﾃｱﾘﾝｸﾞの制御値
    unsigned char trb;    //ﾀｰﾎﾞの制御値
    unsigned char gpout;    //ﾌﾟｯｼｭﾎﾞﾀﾝの制御値
  } recv_msg;

static struct SEND_MSG        //送信ﾒｯｾｰｼﾞ構造体
  {
    char id[4];     //識別子｢RS24｣を設定
    char bdy_mac[6];    //車体側のMACｱﾄﾞﾚｽ
  } send_msg;

static unsigned long tmr;     //起動後の時間[ms]
static int rcv_tmr=-1;        //無通信監視ﾀｲﾏｰ[ms]


//==============================================
//MACｱﾄﾞﾚｽ表示
//==============================================
void printMacAddress(const uint8_t* macaddr)
{
  Serial.print("{");
  for(int i=0;i<6; i++)
  {
    Serial.print(macaddr[i],HEX);
    if(i<5) Serial.print('.');
  }
  Serial.print("} ");
}


//==============================================
//送信ｺｰﾙﾊﾞｯｸ関数
//==============================================
void send_cb(const uint8_t* mac,esp_now_send_status_t status)
{
  printMacAddress(mac);
  Serial.printf("send=%i\n",status);
}


//==============================================
//受信ｺｰﾙﾊﾞｯｸ関数
//==============================================
void recv_cb(const esp_now_recv_info_t *recv_info,const uint8_t *data,int len)
{
  printMacAddress(recv_info->src_addr);
  Serial.printf("LEN=%d\n",len);

  //ﾒｯｾｰｼﾞ長確認
  if(len!=sizeof(recv_msg)) return;

  //制御値を取込む
  memcpy(&recv_msg,data,sizeof(recv_msg));
  Serial.printf("%2.2x%2.2x%2.2x%2.2x\n",
    recv_msg.drv,recv_msg.str,recv_msg.trb,recv_msg.gpout);

  //無通信監視ﾀｲﾏｰ
  rcv_tmr=RCV_TMR;      //無通信監視ﾀｲﾏｰを初期化する
}


//==============================================
//初期設定
//==============================================
void setup(void) 
{
  esp_now_peer_info_t peer_info;    //peer情報

  //ｼﾘｱﾙﾎﾟｰﾄ設定
  Serial.begin(115200);
  Serial.println();

  //ﾋﾟﾝﾓｰﾄﾞ設定
  pinMode(LED_STS,OUTPUT);
  pinMode(OUT_LFT,OUTPUT);
  pinMode(OUT_RGT,OUTPUT);
  pinMode(OUT_TRB,OUTPUT);
  pinMode(OUT_FWD,OUTPUT);
  pinMode(OUT_BAK,OUTPUT);
  ledcAttach(PWMCH_FWD,400,9);    //PWM周波数400Hzm､9ﾋﾞｯﾄ
  ledcAttach(PWMCH_BAK,400,9);
  pinMode(OUT_GPOUT,OUTPUT);    //汎用駆動をL
  delay(10);        //10ms待つ
  pinMode(IO9,OUTPUT);      //IO9をLにしておく

  //空きﾎﾟｰﾄの始末
  pinMode(0,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(18,INPUT_PULLUP);

  //WiFi設定
  WiFi.mode(WIFI_STA);      //ｽﾃｰｼｮﾝﾓｰﾄﾞの設定
  WiFi.macAddress(bdy_mac);   //車体側(自分)のMACｱﾄﾞﾚｽを取得する
  Serial.print("BDY_MAC");
  printMacAddress(bdy_mac);
  Serial.println();
  WiFi.disconnect();      //一旦切断する(ESP32のおまじない
  esp_wifi_set_channel(WIFI_CHANNEL, WIFI_SECOND_CHAN_NONE);
            //自分のﾁｬﾈﾙを固定

  //ESP_NOW設定
  if(esp_now_init())      //ESP_NOWを初期化
  {
    Serial.println("esp_now_init() ERROR");
    ESP.restart();
  }
  memcpy(peer_info.peer_addr,CTR_MAC,6);
  peer_info.channel=WIFI_CHANNEL;   //相手のﾁｬﾈﾙを設定
  peer_info.encrypt=false;
  esp_now_add_peer(&peer_info);   //相手を追加
  esp_now_register_send_cb(send_cb);  //送信ｺｰﾙﾊﾞｯｸを登録する
  esp_now_register_recv_cb(recv_cb);  //受信ｺｰﾙﾊﾞｯｸを登録する
  Serial.println("setup OK");

  //ｼｽﾃﾑﾀｲﾏｰ初期化
  tmr=millis();
}


//==============================================
//ﾒｲﾝﾙｰﾌﾟ
//==============================================
void loop(void) 
{
  unsigned char fwd=0,bak=0,lft=0,rgt=0;  //駆動履歴
  unsigned int i;
  unsigned long l;


  //ﾍﾟｱﾘﾝｸﾞ
  if(rcv_tmr<0)
  {
    Serial.println("Pearing");
    memcpy(send_msg.id,"RC24",sizeof(send_msg.id));
            //ﾍﾟｱﾘﾝｸﾞﾒｯｾｰｼﾞIDを設定する
    memcpy(send_msg.bdy_mac,bdy_mac,sizeof(send_msg.bdy_mac));
            //車体側MACｱﾄﾞﾚｽを設定する
    esp_now_send(ctr_mac,(uint8_t *)&send_msg,sizeof(send_msg));
            //ｺﾝﾄﾛｰﾗへ送信する
    delay(200);     //ﾍﾟｱﾘﾝｸﾞﾒｯｾｰｼﾞ送信周期
    return;
  }

  //全停止処理
  if(rcv_tmr==0)        //無通信のとき
  {
    //全停止する
    ledcWrite(PWMCH_FWD,0);   //停止する
    ledcWrite(PWMCH_BAK,0);
    digitalWrite(OUT_LFT,LOW);
    digitalWrite(OUT_RGT,LOW);
    digitalWrite(OUT_TRB,LOW);
    digitalWrite(OUT_GPOUT,LOW);
    fwd=0;        //履歴を初期化
    bak=0;
    lft=0;
    rgt=0;
    digitalWrite(LED_STS,LOW);  //通信異常表示
    return;       //車体の駆動を飛ばす
  }

  //操縦処理
  else if(rcv_tmr==RCV_TMR)   //受信済みのとき
  {
    rcv_tmr--;      //操縦処理済みにする

    //前後進の駆動
    i=recv_msg.drv;     //前後進制御量を得る
    if(i>131) i-=3;     //ﾆｭｰﾄﾗﾙの不感帯を設定する
    else if(i<125) i+=3;
    else i=128;
    if(i>128)     //前進のとき
    {
      i=(i-128)*5;    //PWM値を決める
      if(i>511) i=511;
      ledcWrite(PWMCH_BAK,0); //後進を止める
      if(!bak)    //後進していなかったら
      {
        ledcWrite(PWMCH_FWD,i);
            //前進する
        fwd=1;
      }
      bak=0;
    }
    else if(i<128)      //後進のとき
    {
      i=(128-i)*5;    //PWM値を決める
      if(i>511) i=511;
      ledcWrite(PWMCH_FWD,0); //前進を止める
          if(!fwd)    //前進していなかったら
      {
        ledcWrite(PWMCH_BAK,i);
            //後進する
        bak=1;
      }
      fwd=0;
    }
    else        //停止のとき
    {
      ledcWrite(PWMCH_FWD,0); //前進を止める
      ledcWrite(PWMCH_BAK,0); //後進を止める
      fwd=0;
      bak=0;
    }

    //右左折の駆動
    if(recv_msg.str>200)    //左折のとき
    {
      digitalWrite(OUT_RGT,LOW);
            //右折を止める
      if(!rgt)    //右折していなかったら
      {
        digitalWrite(OUT_LFT,HIGH);
            //左折する
        lft=1;
      }
      rgt=0;
    }
    else if(recv_msg.str<50)  //右折のとき
    {
      digitalWrite(OUT_LFT,LOW);
            //左折を止める
      if(!lft)    //左折していなかったら
      {
        digitalWrite(OUT_RGT,HIGH);
            //右折する
        rgt=1;
      }
      lft=0;
    }
    else
    {
      digitalWrite(OUT_LFT,LOW);
            //左折を止める
      digitalWrite(OUT_RGT,LOW);
            //右折を止める
    }

    //ﾀｰﾎﾞの駆動
    if(recv_msg.trb>200)    //ｵﾝのとき
    {
      digitalWrite(OUT_TRB,HIGH);
            //ｵﾝする
    }
    else if(recv_msg.trb<50)  //ｵﾌのとき
    {
      digitalWrite(OUT_TRB,LOW);
            //ｵﾌする
    }

    //汎用駆動(正論理でﾋﾟﾝ出力する)
    if(recv_msg.gpout>200)    //ｵﾝのとき
    {
      digitalWrite(OUT_GPOUT,HIGH);
            //ｵﾝする
    }
    else if(recv_msg.gpout<50)  //ｵﾌのとき
    {
      digitalWrite(OUT_GPOUT,LOW);
            //ｵﾌする
    }

    digitalWrite(LED_STS,HIGH); //通信正常表示
  }

  //受信ﾀｲﾏｰ更新
  l=millis();       //現ﾀｲﾏｰを得る
  i=l-tmr;        //経過時間を求める
  rcv_tmr-=i;       //受信ﾀｲﾏｰから経過時間を減算して
  if(rcv_tmr<0) rcv_tmr=0;    //　負になったら0に規制する
  tmr=l;          //現ﾀｲﾏｰを記憶しておく
//  Serial.printf("%ld %d\n",tmr,rcv_tmr);
}

