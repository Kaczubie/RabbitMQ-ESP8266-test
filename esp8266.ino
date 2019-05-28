#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "WIFI_SSID";
const char* password =  "WIFI_PASS";
const char* mqttServer = "192.168.0.22";
const int mqttPort = 1883;
const char* mqttUser = "guest";
const char* mqttPassword = "guest";
 
WiFiClient espClient;
PubSubClient client(espClient);
int inPin = 0;
void setup() {
  pinMode(inPin, INPUT_PULLUP);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
      
    }
  }
 
  client.publish("test/hello", "Hello from ESP8266");
  Serial.print("Message sent ");
  
}
void send_btn_pressed_msg(){
  client.publish("test/hello", "Button pressed");
  Serial.print("Message sent ");
}
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  int val = 0;
  while(1){
    val = digitalRead(inPin);
    
    if(!val){
        val = digitalRead(inPin);
        Serial.println("Button pressed  ");
        Serial.println(val);
        send_btn_pressed_msg();
        while(!val){
          val = digitalRead(inPin);
          delay(20);
        }
    }
     else{
      delay(20);
      }
    }
  
}
