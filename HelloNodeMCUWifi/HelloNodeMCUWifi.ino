#include <ESP8266WiFi.h>

const char* ssid = "Fairway 2.4";
const char* password = "*********";
const char* host = "maker.ifttt.com";
int Sensor = 14;
int Pirled = 12;
int Speaker= 13;
int c = 262;
int d = 294;
int e = 330;
int f = 349;
int g = 392;
int a = 440;
int b = 494;
int bf = 466;
int C = 523;
int frequency[56] = {
  c, d, f, d, a, a, g, c, d, f, d, g, g, f, e, d, c, d, f, d, f, g, e, d, c, c, g, f,
  c, d, f, d, a, a, g, c, d, f, d, C, e, f, e, d, c, d, f, d, f, g, e, d, c, c, g, f};
int duration[56] = {
  120, 120, 120, 120, 360, 360, 720, 120, 120, 120, 120, 360, 360, 480, 120, 240, 120, 120, 120, 120,
  480, 240, 360, 120, 480, 240, 480, 960,
  120, 120, 120, 120, 360, 360, 720, 120, 120, 120, 120, 360, 360, 480, 120, 240, 120, 120, 120, 120,
  480, 240, 360, 120, 480, 240, 480, 960};


void setup() {
    Serial.begin(115200);

    Serial.println("Email from Node Mcu");
    delay(100);

    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());  

    }

void loop() {  
      
  long state= digitalRead(Sensor);
  if (state == HIGH)
  { Serial.println("Motion detected");
    digitalWrite( Pirled , HIGH);
    for(int i=0; i<56; i++)
    { 
    tone(Speaker, frequency[i]); 
    delay(duration[i]);
    }
    
   WiFiClient client; 
           const int httpPort = 80;  
            if (!client.connect(host, httpPort)) 
      {  
                  Serial.println("connection failed");  
            return;} 
          
    
          
                    String url = "/trigger/Test/with/key/d3yQCmCxTGg8cIohL2ofvkClJxH8YVJqo4shwDnXO3R"; 

          
                    Serial.print("Requesting URL: ");
                    Serial.println(url);
                 
                     client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                                    "Host: " + host + "\r\n" +   
                                           "Connection: close\r\n\r\n");    
                      }
          
  else
   Serial.println("NO motion detected");
    digitalWrite( Pirled , LOW);
  delay(1000);
          
      
}
