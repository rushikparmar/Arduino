#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

#define WIFISSID "PI" 
#define PASSWORD "123456789." 
#define TOKEN "qUQFYU2Hp4FonYoD1Wp22Zy6ztfDyGVPoziajaIz2bLfZXHOJUEzJ2w8kBzI5knh" 
#define MQTT_CLIENT_NAME "9977747353" 

#define VARIABLE_LABEL_SUBSCRIBE "servo" 
#define DEVICE_LABEL "esp32" 
// "/v1.6/devices/esp32/servo/lv"

char mqttBroker[]  = "mqtt.flespi.io";
char payload[100];
char topicSubscribe[100];

WiFiClient ubidots;
PubSubClient client(ubidots);
Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 18;

void reconnect() 
{
  
  while (!client.connected()) 
  {
    Serial.println("Attempting MQTT connection...");
    
    
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) 
    {
      Serial.println("Connected");
      client.subscribe(topicSubscribe);
    } 
    else 
    {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      
      delay(2000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  
  myservo.write(message.toInt());
  
  Serial.write(payload, length);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  
  Serial.println("The device started!");

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 400, 2500);

  WiFi.begin(WIFISSID, PASSWORD);
  

  Serial.println();
  Serial.print("Wait for WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);

  sprintf(topicSubscribe, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE);
  
  client.subscribe(topicSubscribe);
  
}

void loop() {
  if (!client.connected()) 
  {
    client.subscribe(topicSubscribe);   
    reconnect();
  }

  client.loop();
  

  delay(100);
}
