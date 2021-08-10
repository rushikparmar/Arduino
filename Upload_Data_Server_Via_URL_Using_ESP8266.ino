#include <ESP8266WiFi.h>
//burning chpd vcc gpio0 gnd
//running chpd vcc gpio0 open

const char* ssid = "VIBE";
const char* password = "987654321.";

String s,a,b,c,r;

const char* host = "app-1539103048.000webhostapp.com";

void setup() 
{
  Serial.begin(9600);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() 
{
  delay(5000);
  ++value;
  
  int i=0;
  
  while(Serial.available()==0);
 
  while(Serial.available())
  {
    s+=Serial.readStringUntil('\r');
  }
 
   //s="pt=p1&tp=27.5&hb=80";
   //data format
  
  Serial.println(" ");
  Serial.println(s);
  Serial.println(" ");
  Serial.print("connecting to ");
  Serial.println(host);
 
 // Use WiFiClient class to create TCP connections

 WiFiClient client;
 
 const int httpPort = 80;
 
 if (!client.connect(host, httpPort)) 
 {
    Serial.println("connection failed");
    return;
 }
 
 // We now create a URI for the request
 
  String url = "/entervalue.php?"+s;
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" + 
  "Connection: close\r\n\r\n");
  
  unsigned long timeout = millis();
  
  while (client.available() == 0) 
  {
    if (millis() - timeout > 5000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      
      return;
    }
 }
 
  while(client.available())
  {

    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
 
 Serial.println();
 Serial.println("closing connection");
 s="";

}
