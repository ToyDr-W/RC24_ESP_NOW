//ESP32-C3-WROOM-02をESP_NOWでﾄｲﾗｼﾞの操作を行うｺﾝﾄﾛｰﾗ側のｽｹｯﾁ


#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>


//==============================================
//ｱﾌﾟﾘｹｰｼｮﾝ設定値
//==============================================
#define WIFI_CHANNEL 1
static uint8_t CTR_MAC[6]={0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
            //ｺﾝﾄﾛｰﾗ側のMACｱﾄﾞﾚｽはﾌﾞﾛｰﾄﾞｷｬｽﾄ
#define LOOP_TMR  50      //ﾒｲﾝﾙｰﾌﾟ周期[ms]


//==============================================
//ﾎﾟｰﾄ割当て
//==============================================
//CCPﾃﾞｼﾞﾌﾟﾛ動作のときは前後進操作ﾎﾞﾘｭｰﾑからTOUTﾋﾟﾝへｱﾅﾛｸﾞ入力する
#define LED_STS 1
#define SW_FWD  4
#define SW_BAK  5
#define SW_LFT  10
#define SW_RGT  19
#define SW_TRB  6
#define SW_MODE 20    //ﾌﾟｯｼｭﾎﾞﾀﾝの動作ﾓｰﾄﾞ(内部ﾌﾟﾙｱｯﾌﾟ)
        //　(H=ﾓｰﾒﾝﾄﾓｰﾄﾞ､L=ﾄｸﾞﾙﾓｰﾄﾞ)
#define SW_GPOUT  9 //ﾌﾟｯｼｭ操作入力(負論理､内部ﾌﾟﾙｱｯﾌﾟ)
#define VOL1  2   //前後進操作ﾎﾞﾘｭｰﾑ
#define VOL2  0   //右左折操作ﾎﾞﾘｭｰﾑ(右左折ﾌﾟﾛﾎﾟ制御は未実装)


//==============================================
//大域変数
//==============================================
static uint8_t car_mac[6];    //ｺﾝﾄﾛｰﾗ側(自分)のMACｱﾄﾞﾚｽ
static uint8_t bdy_mac[6];    //車体側のMACｱﾄﾞﾚｽ
static char pear_sts;     //ﾍﾟｱﾘﾝｸﾞ状態(0=未､1=受信済､2=登録済)

struct SEND_MSG       //送信ﾒｯｾｰｼﾞ構造体
  {
    unsigned char drv;  //前後進の制御値
    unsigned char str;  //ｽﾃｱﾘﾝｸﾞの制御値
    unsigned char trb;  //ﾀｰﾎﾞの制御値
    unsigned char gpout;  //ﾌﾟｯｼｭﾎﾞﾀﾝの制御値
  } send_msg;

struct RECV_MSG       //受信ﾒｯｾｰｼﾞ構造体
  {
  char id[4];     //識別子｢RC24｣を設定
  char bdy_mac[6];    //車体側のMACｱﾄﾞﾚｽ
  } recv_msg;


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
  if(status)        //送信結果で
  {
    digitalWrite(LED_STS,LOW);  //　通信異常表示
  }
  else
  {
    digitalWrite(LED_STS,HIGH); //　通信正常表示
  }
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

  //受信ﾒｯｾｰｼﾞを取込む
  memcpy(&recv_msg,data,sizeof(recv_msg));
  if(memcmp(recv_msg.id,"RC24",4))
  {
    Serial.printf("ID=%4.4s\n",recv_msg.id);
    return;
  }

  //車体側MACｱﾄﾞﾚｽの取込み
  memcpy(bdy_mac,recv_msg.bdy_mac,sizeof(bdy_mac));
  Serial.print("bdy_mac");
  printMacAddress(bdy_mac);
  Serial.println();

  //ﾍﾟｱﾘﾝｸﾞ受信表示
  if(pear_sts==0) pear_sts=1;
}


//==============================================
//初期設定
//==============================================
void setup(void) 
{
  esp_now_peer_info_t peer_info;    //peer情報
  unsigned int r;


  //ｼﾘｱﾙﾎﾟｰﾄ設定
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");

  //ﾋﾟﾝﾓｰﾄﾞ設定
  pinMode(LED_STS,OUTPUT);
  pinMode(SW_FWD,INPUT_PULLUP);
  pinMode(SW_BAK,INPUT_PULLUP);
  pinMode(SW_LFT,INPUT_PULLUP);
  pinMode(SW_RGT,INPUT_PULLUP);
  pinMode(SW_TRB,INPUT_PULLUP);
  pinMode(SW_MODE,INPUT_PULLUP);
  pinMode(SW_GPOUT,INPUT_PULLUP);
  pinMode(VOL1,ANALOG);
  pinMode(VOL2,ANALOG);
  analogSetAttenuation(ADC_11db);

  //空きﾎﾟｰﾄの始末
  pinMode(7,INPUT_PULLUP);
  pinMode(0,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(18,INPUT_PULLUP);

  //WiFi設定
  WiFi.mode(WIFI_STA);      //ｽﾃｰｼｮﾝﾓｰﾄﾞの設定
  WiFi.macAddress(car_mac);   //ｺﾝﾄﾛｰﾗ側(自分)のMACｱﾄﾞﾚｽを取得する
  Serial.print("CAR_MAC");
  printMacAddress(car_mac);
  Serial.println();

  //ESP_NOW設定
  if(esp_now_init())      //ESP_NOWを初期化
  {
    Serial.println("esp_now_init() ERROR");
    ESP.restart();
  }
  esp_wifi_set_channel(WIFI_CHANNEL, WIFI_SECOND_CHAN_NONE);
            //自分のﾁｬﾈﾙを設定
  memcpy(peer_info.peer_addr,CTR_MAC,6);  //自分のMACｱﾄﾞﾚｽを設定
  peer_info.channel=WIFI_CHANNEL;   //相手のﾁｬﾈﾙを設定
  peer_info.encrypt=false;
  esp_now_add_peer(&peer_info);   //相手を追加する
  esp_now_register_send_cb(send_cb);  //送信ｺｰﾙﾊﾞｯｸを登録する
  esp_now_register_recv_cb(recv_cb);  //受信ｺｰﾙﾊﾞｯｸを登録する
  Serial.println("setup OK");
}


//==============================================
//ﾒｲﾝﾙｰﾌﾟ
//==============================================
void loop(void) 
{
  esp_now_peer_info_t peer_info;    //peer情報
  static int vol1_cal,vol2_cal;   //前後進操作ﾎﾞﾘｭｰﾑの校正値
            //　ﾌﾙｱｸｼｮﾝ制御のときは2000を設定
  static unsigned char gpout_hst;   //ﾌﾟｯｼｭﾎﾞﾀﾝ履歴
            //　(LSBが最新､0=ｵﾌ､1=ｵﾝ)
  int r;


  //送信周期を待つ
  delay(LOOP_TMR);

  //ﾍﾟｱﾘﾝｸﾞ
  Serial.printf("pear_sts=%d\n",pear_sts);
  if(pear_sts==0) return;     //ﾍﾟｱﾘﾝｸﾞﾒｯｾｰｼﾞ受信を待つ
  if(pear_sts==1)       //ﾍﾟｱﾘﾝｸﾞﾒｯｾｰｼﾞを受信したら
  {
    memcpy(peer_info.peer_addr,bdy_mac,6);
            //車体側MACｱﾄﾞﾚｽを取込む
    peer_info.channel=WIFI_CHANNEL; //WiFiﾁｬﾈﾙを設定する
    peer_info.encrypt=false;
    esp_now_add_peer(&peer_info); //車体側MACｱﾄﾞﾚｽを追加する
    esp_now_unregister_recv_cb(); //受信ｺｰﾙﾊﾞｯｸを削除する
    Serial.println("pearing OK");
    pear_sts=2;     //ﾍﾟｱﾘﾝｸﾞ済を表示

    //制御ﾀｲﾌﾟ決定
    delay(100);     //電圧安定時間
    r=analogRead(VOL1);   //ch1操作ﾎﾞﾘｭｰﾑを読む
    Serial.printf("VOL1=%d\n",r);
    if(1024<r)      //CCPﾃﾞｼﾞﾌﾟﾛ判定のとき
    {
      vol1_cal=r;   //前後進操作ﾎﾞﾘｭｰﾑの校正値を設定
      Serial.println("CCPD ");
      Serial.printf("%d\n",vol1_cal);
    }
    else        //ﾌﾙｱｸｼｮﾝ判定のとき
    {
      vol1_cal=5000;    //ﾌﾙｱｸｼｮﾝ制御の設定
      Serial.println("FULL");
    }
  }

  //前後進の設定
  if(vol1_cal==5000)      //ﾌﾙｱｸｼｮﾝのとき
  {
    if(!digitalRead(SW_FWD)) send_msg.drv=224;
    else if(!digitalRead(SW_BAK)) send_msg.drv=32;
    else send_msg.drv=128;
  }
  else          //CCPﾃﾞｼﾞﾌﾟﾛのとき
  {
    r=analogRead(VOL1)-vol1_cal;  //ADC結果を補正する
    Serial.printf("%d-",r);
    r=(r*1628)/2048;
    Serial.printf("%d-",r);
    if(r>1047) r=2047;    //ｽｹｰﾘﾝｸﾞする
    else if(r>24) r+=1000;
    else if(r>-24) r=1024;
    else if(r>-1047) r+=1047;
    else r=0;
    Serial.printf("%d\n",r);
    send_msg.drv=r/8;   //制御値に変換する
  }

  //右左折の設定
  if(!digitalRead(SW_LFT)) send_msg.str=224;
            //左折のとき
  else if(!digitalRead(SW_RGT)) send_msg.str=32;
            //右折のとき
  else send_msg.str=128;      //中立のとき

  //ﾀｰﾎﾞの設定
  if(!digitalRead(SW_TRB)) send_msg.trb=224;
            //ｵﾝのとき
  else send_msg.trb=32;     //ｵﾌのとき

  //ﾌﾟｯｼｭﾎﾞﾀﾝの設定
  if(digitalRead(SW_MODE))    //ﾓｰﾄﾞSWがｵﾌ(H)ﾓｰﾒﾝﾄﾓｰﾄﾞのとき
  {
    if(!digitalRead(SW_GPOUT)) send_msg.gpout=224;
            //ｵﾝのとき
    else send_msg.gpout=32;   //ｵﾌのとき
  }
  else          //ﾓｰﾄﾞSWがｵﾝ(L)ﾄｸﾞﾙのとき
  {
    gpout_hst<<=1;      //履歴をｼﾌﾄしておく
    if(!digitalRead(SW_GPOUT)) gpout_hst|=1;
            //現在値を記録
    if((gpout_hst&7)==1)    //ｵﾝ変化のときはﾄｸﾞﾙする
            //　50ms*2=100ms以上のｵﾌ後のｵﾝ
    {
      if(send_msg.gpout<128) send_msg.gpout=224;
            //前回がｵﾌ設定だったときはｵﾝ設定
      else send_msg.gpout=32; //前回がｵﾝ設定だったときはｵﾌ設定
    }
  }

  Serial.printf("%2.2x%2.2x%2.2x%2.2x\n",send_msg.drv,send_msg.str,send_msg.trb,send_msg.gpout);

  //車体側へ送信
  esp_now_send(NULL,(uint8_t *)&send_msg,sizeof(send_msg));
}

