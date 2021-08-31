#include "CTBot.h"
CTBot myBot;

String ssid = "Cucu Mbah";     // Sesuikan dengan nama wifi anda
String pass = "gimangimangiman"; // sesuaikan password wifi
String token = "1030483206:AAEtjghLvsv8a5XQ9Y7GSaFAKdYQN4dK4s8"; // token bot telegram yang telah dibuat

String data;
char c;

void setup() {
	Serial.begin(115200);
	Serial.println("Starting TelegramBot...");

	myBot.wifiConnect(ssid, pass);

	myBot.setTelegramToken(token);

	// check if all things are ok
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");

}

void loop() {
	TBMessage msg;

	if (myBot.getNewMessage(msg)) {

		if (msg.text.equalsIgnoreCase("RELAY ON")) {              
			myBot.sendMessage(msg.sender.id, "RELAY is now ON");  //kirim pesan ke bot telegram
		  Serial.print("RELAY ON");
		}
		else if (msg.text.equalsIgnoreCase("RELAY OFF")) {        
			myBot.sendMessage(msg.sender.id, "RELAY is now OFF"); 
		  Serial.print("RELAY OFF");
		}
    else if (msg.text.equalsIgnoreCase("TEMPERATURE")) {
      Serial.print("TEMPERATURE");
    }
		else {                                                    
			// membalas pesan selain kode diatas
			String reply;
			reply = (String)"Welcome " + msg.sender.username + (String)". Command: RELAY ON, RELAY OFF, TEMPERATURE.";
			myBot.sendMessage(msg.sender.id, reply);         
		}
	}
  
  while(Serial.available()>0){
    delay(10);
    c = Serial.read();
    data += c;
  }
  if (data.length()>0) {
    myBot.sendMessage(msg.sender.id, data + " Celcius Degrees");
    delay(10);
    data = "";
  }

	delay(500);
}
