/*******************************************************************
   An example of bot that echos back any messages received
*                                                                  *
   written by Giacarlo Bacchio (Gianbacchio on Github)
   adapted by Brian Lough
*******************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>//esto no borra

// Initialize Wifi connection to the router
char ssid[] = "ALSW";     // your network SSID (name)
char password[] = "2526-4897"; // your network key
char cocacola[] = "Cocacola";
int bomba1 = 0;
int bomba2 = 4;
int bomba3 = 13;
int bomba4 = 12;


// Initialize Telegram BOT
#define BOTtoken "734969352:AAGE5Ix7OsOalqNRrYnXjnn5aGnmOHzDqmY"  // your Bot Token (Get from Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

void setup() {
  Serial.begin(115200);

  pinMode(bomba1, OUTPUT);
  pinMode(bomba2, OUTPUT);
  pinMode(bomba3, OUTPUT);
  pinMode(bomba4, OUTPUT);

  digitalWrite(bomba1, 0);
  digitalWrite(bomba2, 0);
  digitalWrite(bomba3, 0);
  digitalWrite(bomba4, 0);
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      for (int i = 0; i < numNewMessages; i++) {
        //bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
        if (bot.messages[i].text == cocacola) {
          Serial.println("Quiere una cocacola");
          bot.sendMessage(bot.messages[i].chat_id, "Su orden esta en proceso", "");
          digitalWrite(bomba1, 1);
          delay(1000);
          digitalWrite(bomba1, 0);
          bot.sendMessage(bot.messages[i].chat_id, "Su orden esta lista", "");
        }
        else if () {

        }
        else if () {

        }
        else {
          bot.sendMessage(bot.messages[i].chat_id, "No esta en el menu", "");
          bot.sendMessage(bot.messages[i].chat_id, "1. Cocacola", "");
        }
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
