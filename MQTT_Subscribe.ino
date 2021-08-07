#include <WiFi.h>
#include <PubSubClient.h>

#define WIFISSID "PI" 
#define PASSWORD "123456789." 
#define TOKEN "HEkDHa9KZqSAfgQGGeVHAacE7YS5eqEJSMdoMaYBpFZuLEYfIHN7GNBDBjwDy1ce" 
#define MQTT_CLIENT_NAME "9977747566353" 

#define VARIABLE_LABEL_SUBSCRIBE "led" 
#define DEVICE_LABEL "esp32" 
// "/esp32/led"

//#define led LED_BUILTIN 
#define led 2 
char mqttBroker[]  = "mqtt.flespi.io";
char payload[100];
char topicSubscribe[100];

WiFiClient ubidots;
PubSubClient client(ubidots);


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
  
  
  if (message == "0.0") 
  {
    digitalWrite(led, LOW);
  } 
  else 
  {
    digitalWrite(led, HIGH);
  }
  
  Serial.write(payload, length);
  Serial.println();
}


void setup() 
{
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  
  pinMode(led, OUTPUT);

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

  sprintf(topicSubscribe, "/%s/%s", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE);
  //   /esp32/led
  client.subscribe(topicSubscribe);
}

void loop() 
{
  if (!client.connected()) 
  {
    client.subscribe(topicSubscribe);   
    reconnect();
  }

  client.loop();
  delay(1000);
}
