// This example shows how to connect to LOTODA using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling.

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include <ArduinoJson.h> 

#define DHTPIN 5
#define DHTTYPE DHT21
DHT dht(DHTPIN, DHTTYPE);

#define WIFI_SSID "..."   //Enter your WIFI SSID
#define WIFI_PASSWORD "..."   //Enter your WiFi password
#define BUILTIN_LED 2
char LotodaServer[]  = "app.lotoda.vn";     //app.lotoda.vn is the default servername
int LotodaPort  = 1883;                     //1883 is the default port
char deviceId[]  = "LotodaEsp8266-0001";  //every device should have a different name
char topic[]  = "<User_ID_Key>/DHT21"; //Enter <User_ID_Key> from LOTODA system, the topic should be different for each device as well
                                            //Please create this new topic on LOTODA mobile app, in this case is "lamp/power"
char User_ID_Key[]  = "<User_ID_Key>";         //Enter <User_ID_Key> from LOTODA system
char Password_ID_Key[]  = "<Password_ID_Key>";  //Enter <Password_ID_Key> from LOTODA system

WiFiClient wifiClient;
PubSubClient client(wifiClient);
long lastMsg = 0;
char msg[50];
int value = 0;


void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output led
  Serial.begin(115200);
  delay(20);
  dht.begin();
  Serial.println("Let' start now");
}

void loop() {
  if ( !client.connected() ) {
    connect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    // Convert the value to a char array
    char tempString[8];
    // float to string
    dtostrf(t, 1, 2, tempString);
    Serial.print("Temperature: ");
    Serial.println(tempString);
    char humString[8];
    dtostrf(h, 1, 2, humString);
    Serial.print("Humidity: ");
    Serial.println(humString);

    String key1 = "{\"temperature\":";
    String key2 = ",\"humidity\":";
    String endkey =  "}";
    String str = key1 + tempString + key2 + humString + endkey; // json message
    char data[80];
    str.toCharArray(data, (str.length() + 1));
    Serial.println(str);
    client.publish(topic, data); // publish message to server
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void connect() {
  while (!client.connected()) {
    if ( WiFi.status() != WL_CONNECTED) {
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.print("Connected to ");
      Serial.println(WIFI_SSID);
    }
    client.setServer(LotodaServer, LotodaPort);
    client.setCallback(callback);
    if (client.connect(deviceId, User_ID_Key, Password_ID_Key)) {
      client.subscribe(topic);
      Serial.println("Connected to LOTODA's Server");
    } else {
      Serial.print("[FAILED] [ rc = ");
      Serial.print(client.state() );
      Serial.println(" : retrying in 5 seconds]");
      delay(5000);
    }
  }
}
