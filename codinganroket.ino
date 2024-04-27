#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

#define RELAY_PIN 2

#define DHTPIN 27  //DHT OneWire pin dan tipenya DHT11
#define DHTTYPE DHT11
String PHONE = ""; //bisa digunakan oleh berbagai nomor ponsel
String msg;

DHT dht(DHTPIN, DHTTYPE);

void setup() { //fungsi setup dan serial komunikasi antara sim800l dan esp32

  Serial.begin(115200);
  Serial.println("Initializing Serial... ");

  Serial2.begin(9600);
  Serial2.println("Initializing GSM module...");

  dht.begin();
  
  ReceiveMode();
  delay(1000);
}

void loop()
{
  while (Serial2.available())
  {
    parseData(Serial2.readString()); //mengambil fungsi parseData untuk mengolah SMS 
  }
  doAction(); //sebagai fungsi yang diperlukan saat mengolah SMS
  while (Serial.available())
  {
    Serial2.println(Serial.readString());
  }

}

void ReceiveMode(){        //membuat sim800l di serial2 di Receive mode
  Serial2.println("AT");   //jika sim berjalan dengan baik maka layar monitor akan menampilkan "OK"
  Serial2.println("AT+CMGF=1"); //konfigurasi TEXT mode
  Serial2.println("AT+CNMI=1,2,0,0,0"); //konfigurasi sim800l di serial2 untuk menangani sms yang diterima nanti
}

void parseData(String buff) { //fungsi untuk mengolah SMS
  Serial.println(buff);

  unsigned int index;

  //menghilangkan perintah "AT Command" dari respons String 
  index = buff.indexOf("\r");
  buff.remove(0, index + 2);
  buff.trim();

  if (buff != "OK") {
    index = buff.indexOf(":");
    String cmd = buff.substring(0, index);
    cmd.trim();

    buff.remove(0, index + 2);

    //mengurai pesan dari Serial2 menjadi Serial buffer string
    if (cmd == "+CMT") {
      //membuat memori data yang baru masuk di lokasi baru dan menyimpannya di temp
      index = buff.lastIndexOf(0x0D); //mencari lokasi dari CR (pesan balasan)
      msg = buff.substring(index + 2, buff.length()); //menulis balasan untuk variable "msg" 
      msg.toLowerCase(); //mengubah isi pesan ke dalam lowercase
      Serial.println(msg);

      index = buff.indexOf(0x22); //mencari lokasi untuk pesan line pertama 
      PHONE = buff.substring(index + 1, index + 15); //menulis nomor telepon sebagai variable PHONE
      Serial.println(PHONE);

    }
  }
}

void doAction() // fungsi yang akan diolah menjadi sms sesuai kodenya
{
  if (msg == "hello")
  {
    Serial.print("Selamat datang di Roket Cihuy! \n\nDengan beragam fitur yang tersedia, kami siap memberikan pengalaman terbaik yang akan memudahkan Anda dalam mencapai tujuan Anda.\nBerikut ini beberapa fitur unggulan yang dapat Anda nikmati: \n1) rc_0\n2) rc_1"); //menampilkan hasilnya di serial monitor
    Reply("Selamat datang di Roket Cihuy! \n\nDengan beragam fitur yang tersedia, kami siap memberikan pengalaman terbaik yang akan memudahkan Anda dalam mencapai tujuan Anda.\nBerikut ini beberapa fitur unggulan yang dapat Anda nikmati: \n1) rc_0\n2) rc_1");
  }
  else if (msg == "rc_0")
  {
    float h = dht.readHumidity();         // pembacaan suhu dan kelembaban pada sensor
    float t = dht.readTemperature();
    Reply("DHT11\n SUHU = "+String(t,1)+" C"+" \n KELEMBABAN ="+String(h,1)+" %");
  }
  else if (msg == "rc_1")
  {
    Serial.print("Anggota Kelompok: \nJati, Mutiara, Haikal, M. Nauan, Maulana, Josephin, Cindy, \n Alia, Cantika, dan Ahmad S.");
    Reply("Anggota Kelompok: \nJati, Mutiara, Haikal, M. Nauan, Maulana, Josephin, Cindy, \n Alia, Cantika, dan Ahmad S.");
  }

  PHONE = ""; // memulai ulang pesan string PHONE
  msg = "";   // memulai ulang pesan string msg
}

void Reply(String text) // fungsi balasan yang akan dikirimkan 
{
  Serial2.println("AT+CMGF=1\r");
  delay(1000);
  Serial2.println("AT+CMGS=\"" + PHONE + "\"\r");
  delay(1000);
  Serial2.println(text);
  delay(100);
  Serial2.write(0x1A); //ascii code untuk ctrl+z, DEC->26, HEX->0x1A
  delay(1000);
  Serial.println("SMS Sent Successfully.");
}