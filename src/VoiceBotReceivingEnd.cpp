#include <Arduino.h>
#include <WiFi.h>
#include <credentials.h>

int ledPin = 32;

int motorIn1 = 13;
int motorIn2 = 12;
int motorIn3 = 27;
int motorIn4 = 26;

int trigPin = 25;
int echoPin = 33;
long timeTaken;
int calculatedDistance;

char data;
String fullData;

WiFiServer server(80);
String receivedString;

void setup() {
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);

  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
}

void sendHttpResponse(WiFiClient client, int statusCode, const String& contentType, const String& content) {
  //Sending a response back to the client to confirm a successful request
  client.println("HTTP/1.1 " + String(statusCode) + " OK");
  client.println("Content-Type: " + contentType);
  client.println("Connection: close");
  client.println();
  client.println(content);
}

void processRequest(WiFiClient client, const String& request) {
  //Processing the received request here.
  //For simplicity, we'll just print the received request to the Serial monitor.
  Serial.println("Received request: " + request);
  
  //Sending a response back to the client (Python program).
  String responseContent = "String received successfully!";
  sendHttpResponse(client, 200, "text/plain", responseContent);
}

//Methods for movement
void forward(){
  //Right wheel
  digitalWrite(motorIn1, LOW); 
  digitalWrite(motorIn2, HIGH);
  //Left wheel
  digitalWrite(motorIn3, LOW); 
  digitalWrite(motorIn4, HIGH);
}
void backward(){
  //Right wheel
  digitalWrite(motorIn1, HIGH); 
  digitalWrite(motorIn2, LOW);
  //Left wheel
  digitalWrite(motorIn3, HIGH); 
  digitalWrite(motorIn4, LOW);
}
void left(){
  //Right wheel
  digitalWrite(motorIn1, LOW); 
  digitalWrite(motorIn2, LOW);
  //Left wheel
  digitalWrite(motorIn3, HIGH);  //Motor rotates clockwise
  digitalWrite(motorIn4, LOW);
}
void right(){
  //Right wheel
  digitalWrite(motorIn1, HIGH); //Motor rotates anticlockwise 
  digitalWrite(motorIn2, LOW);
  //Left wheel
  digitalWrite(motorIn3, LOW); 
  digitalWrite(motorIn4, LOW);
}

void stop(){
  digitalWrite(motorIn1, LOW); 
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW); 
  digitalWrite(motorIn4, LOW);
}

void loop() {
  
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        fullData = client.readString();
        data = fullData[fullData.length() - 1];
        
        if (request.indexOf("POST") != -1) {
          processRequest(client, request);  
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);

          timeTaken = pulseIn(echoPin, HIGH);

          calculatedDistance = (0.034*timeTaken) / 2; 

          if (calculatedDistance > 5){
            if (data == 'F'){
              forward();
            } 

            else if (data == 'B'){
              backward();
            }

            else if (data == 'R'){
              right();
            }

            else if (data == 'L'){
              left();
            }
          }

          else {
            digitalWrite(ledPin, HIGH);
            delay(3000);
          }
        }
          break;
      }
    }
    client.stop();
    Serial.println("Client disconnected.");
  }
delay(1000);
stop();
digitalWrite(ledPin, LOW);
} 
