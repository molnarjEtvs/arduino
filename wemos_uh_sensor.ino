#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


#define WIFI_SSID "Arduino_305"
#define WIFI_PASS "Ardu1n0_3o5"

ESP8266WebServer webserver(80);

const int trigPin = 12;
const int echoPin = 14;

const int trigPin2 = 4;
const int echoPin2 = 5;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

long duration, duration2;
float distanceCm, distanceCm2;

WiFiClient client;
HTTPClient httpClient;


void setup() {
  Serial.begin(115200); // Starts the serial communication
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Kapcsolodas a wifihez.");
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print(".");
    delay(500); 
  }

  // WiFi Connected
  Serial.print("Kapcsolódás sikeres! IP címe: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(500);
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin2, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  distanceCm2 = duration2 * SOUND_VELOCITY/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance 1 (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance 2 (cm): ");
  Serial.println(distanceCm2);
 // if(distanceCm<=5){
   // riasztasKuldese(distanceCm);
    //delay(3000);
 // }
  
}


void riasztasKuldese(float tavolsag){
    Serial.println("Hivas kezd 1");
    String data = "tavolsag="+String(tavolsag);
    const char *URL = "http://192.168.21.158/wemos_test/public/riasztas-rogzites";
    httpClient.begin(client, URL);
    Serial.println("Hivas kezd 2");
    httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
    Serial.println("Hivas kezd 3");
    httpClient.POST(data);
    Serial.println("Hivas kezd 4");
    String content = httpClient.getString();
    Serial.println("Hivas kezd 5");
    httpClient.end();
    Serial.println("Hivas kezd 6");
    Serial.println("Tartalom: ");
    Serial.println(content);
}
