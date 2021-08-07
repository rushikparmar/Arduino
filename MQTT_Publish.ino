#include <WiFi.h>
#include <PubSubClient.h>

#define WIFISSID "PI" 
#define PASSWORD "123456789." 
#define TOKEN "HEkDHa9KZqSAfgQGGeVHAacE7YS5eqEJSMdoMaYBpFZuLEYfIHN7GNBDBjwDy1ce" 
#define MQTT_CLIENT_NAME "9977747353" 

#define VARIABLE_LABEL "in" 

#define DEVICE_LABEL "esp32" 

char mqttBroker[]  = "mqtt.flespi.io";
char payload[100];
char topic[150];


char str_sensor[10];


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


void setup()
{
  Serial.begin(115200);
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

}

void loop() 
{
  if (!client.connected()) 
  {  
    reconnect();
  }

  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL); // Adds the variable label
  
  float sensor = random(25);
  
  Serial.print("Value of Sensor is:- ");
  Serial.println(sensor);
  
  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(sensor, 4, 2, str_sensor);
  
  sprintf(payload, "%s {\"value\": %s}}", payload, String(sensor)); // Adds the value
  Serial.println("Publishing data to Cloud");
  client.publish(topic, payload);
  client.loop();
  delay(1000);
}
