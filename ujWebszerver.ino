#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Set WiFi credentials
#define WIFI_SSID "Arduino_305"
#define WIFI_PASS "Ardu1n0_3o5"

// Create a new web server
ESP8266WebServer webserver(80);


IPAddress ip(192, 168, 0, 26);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

// Handle Root
void rootPage() { 
  webserver.send(200, "text/html", "<h1>Helló 2 world</h1>"); 
}

// Handle 404
void notfoundPage(){ 
  webserver.send(404, "text/plain", "404: Not found"); 
}

//Led felkapcsolás
void ledFELkapcsolas(){
  digitalWrite(D5,HIGH);
  webserver.send(200,"text/plain","OK");
}

//Led lekapcsolás
void ledLEkapcsolas(){
  digitalWrite(D5,LOW);
  webserver.send(200,"text/plain","OK");
}

void setup()
{
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  pinMode(D5,OUTPUT);

  //Begin WiFi
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.println(".");
     delay(500); }

  // WiFi Connected
  Serial.print("Kapcsolódva! IP címe: ");
  Serial.println(WiFi.localIP());

  // Start Web Server
  webserver.on("/hello", rootPage);
  webserver.on("/ledBE", ledFELkapcsolas);
  webserver.on("/ledLE", ledLEkapcsolas);
  webserver.onNotFound(notfoundPage);

  webserver.begin();
//192.168.0.101
}

// Listen for HTTP requests
void loop(void){ 
  webserver.handleClient(); 

}