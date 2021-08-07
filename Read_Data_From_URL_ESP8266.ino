#include <ESP8266WiFi.h>

const char* ssid     = "Vibe";
const char* password = "987654321.";
const char* host = "rushik-parmar.000webhostapp.com";

String line;
char data[20];

void setup()
{
  Serial.begin(9600);
  delay(10);
  
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  //WiFi.mode(WIFI_AP_STA);   //Both hotspot and client are enabled
  //WiFi.mode(WIFI_AP);       //Only Access point
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  int i=0,j=0;
  
  delay(1000);
  
  WiFiClient client;
  const int httpPort = 80;
  
  if (!client.connect(host, httpPort)) 
  {
    return;
  }
  
  String url = "/b.php/";
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  
  unsigned long timeout = millis();
  
  while (client.available() == 0) 
  {
    if (millis() - timeout > 5000) 
    {
      client.stop();
      return;
    }
  } 
  
  while(client.available())
  {
    line = client.readStringUntil('\r');
    char d[line.length()];
    line.toCharArray(d,line.length());
    
    for(i=0;i<line.length();i++)
    {
      if(d[i]=='*')
      {
        break;
      }
    }
  
    for(i=i;i<line.length();i++)
    {
      data[j]=d[i];
      j++;
    }
  }
   
  Serial.println(data);
}

