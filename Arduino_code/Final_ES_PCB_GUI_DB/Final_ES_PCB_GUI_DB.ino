#include <Wire.h>
#include <Firebase_ESP_Client.h>
#include <Arduino.h>
#include <WiFi.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "time.h"
#include <WebServer.h>
#include <SPIFFS.h>

#define SDA_1 6
#define SCL_1 7
TwoWire I2Cone = TwoWire(0);

#define I2C_Freq 400000

// Variables for Firebase
// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "LAPTOP-ORL3UTLV 7786"
#define WIFI_PASSWORD "SidNHP_13"



  // Insert Firebase project API Key
#define API_KEY "AIzaSyDKEu5sJ_H1bAhDOjOOF19m1KqRTY-cUYs"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "jeeveshpathakiit247@gmail.com"
#define USER_PASSWORD "12345678"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://pulseplotterend-default-rtdb.europe-west1.firebasedatabase.app/"

// Create AsyncWebServer object on port 80
WebServer server(80);

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Variables to save database paths
String databasePath;
String vattaPath = "/vatta";
String pittaPath = "/pitta";
String kaphaPath = "/kapha";
String timePath = "/timestamp";
String parentPath;
int timestamp;

FirebaseJson json;

const char* ntpServer = "pool.ntp.org";

#define I2C_Freq 400000

float IR1;
float IR2;
float IR3;
float vatta;
float pitta;
float kapha;

unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 10;



MAX30105 particleSensor1;
MAX30105 particleSensor2;
MAX30105 particleSensor3;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

int data = 0;       //For GUI    
char userInput;

void TCA9548A(uint8_t bus){
  I2Cone.beginTransmission(0x70);  // TCA9548A address
  I2Cone.write(1 << bus);          // send byte to select bus
  I2Cone.endTransmission();
}


void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void handleRoot() {
  String html = readFile("/index.html");
  server.send(200, "text/html", html);
}

void handleVaata() {
  server.send(200, "text/plain", String(IR1));
}

void handlePitta() {
  server.send(200, "text/plain", String(IR2));
}

void handleKapha() {
  server.send(200, "text/plain", String(IR3));
}

String readFile(const char *filename) {
  String content = "";
  File file = SPIFFS.open(filename, "r");
  if (file) {
    while (file.available()) {
      content += (char)file.read();
    }
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }
  return content;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");
  I2Cone.begin(SDA_1, SCL_1, I2C_SPEED_FAST);


  // Initialize SPIFFS
    if(!SPIFFS.begin()){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  // Connecting to WiFi
  initWiFi();



  // Setting up Firebase
  // Assign the api key (required)
  configTime(0, 0, ntpServer);
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;


  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);
  
  // Update database path
  databasePath = "/UsersData/" + uid + "/readings";

  


  

  TCA9548A(0);
  // Initialize sensor
  if (!particleSensor1.begin(I2Cone, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power first. ");
    while (1);
  }

  TCA9548A(1);
  if (!particleSensor2.begin(I2Cone, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power second .");
    while (1);
  }

  TCA9548A(2);
  if (!particleSensor3.begin(I2Cone, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power third .");
    while (1);
  }



  TCA9548A(0);
  //Setup to sense a nice looking saw tooth on the plotter
  byte ledBrightness = 0x1F; //Options: 0=Off to 255=50mA
  byte sampleAverage = 8; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 3; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  int sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 4096; //Options: 2048, 4096, 8192, 16384
  particleSensor1.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings



  TCA9548A(1);
  particleSensor2.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings

  TCA9548A(2);
  particleSensor3.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings

  //Arduino plotter auto-scales annoyingly. To get around this, pre-populate
  //the plotter with 500 of an average reading from the sensor

  //Take an average of IR readings at power up
  TCA9548A(0);
  const byte avgAmount = 64;
  long baseValue1 = 0;
  for (byte x = 0 ; x < avgAmount ; x++)
  {
    baseValue1 += particleSensor1.getIR(); //Read the IR value
  }
  baseValue1 /= avgAmount;

  //Pre-populate the plotter so that the Y scale is close to IR values
  for (int x = 0 ; x < 500 ; x++)
    Serial.println(baseValue1);

  // For second sensor
  TCA9548A(1);
  long baseValue2 = 0;
  for (byte x = 0 ; x < avgAmount ; x++)
  {
    baseValue2 += particleSensor2.getIR(); //Read the IR value
  }
  baseValue2 /= avgAmount;

  //Pre-populate the plotter so that the Y scale is close to IR values
  for (int x = 0 ; x < 500 ; x++)
    Serial.println(baseValue2);


  // For third sensor
  TCA9548A(2);
  long baseValue3 = 0;
  for (byte x = 0 ; x < avgAmount ; x++)
  {
    baseValue3 += particleSensor3.getIR(); //Read the IR value
  }
  baseValue3 /= avgAmount;

  //Pre-populate the plotter so that the Y scale is close to IR values
  for (int x = 0 ; x < 500 ; x++)
    Serial.println(baseValue3);


  server.on("/", HTTP_GET, handleRoot);
  server.on("/vaataurl", HTTP_GET, handleVaata);
  server.on("/pittaurl", HTTP_GET, handlePitta);
  server.on("/kaphaurl", HTTP_GET, handleKapha);

  server.begin();
}





void loop()
{
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    TCA9548A(0);
    IR1 = particleSensor1.getIR(); //Send raw data to plotter
    Serial.print(IR1);
    Serial.print(",");
  
    delay(10);
    TCA9548A(1);
    
    //Serial.print("{{Sensor 2}}");
    IR2 = particleSensor2.getIR(); //Send raw data to plotter
    Serial.print(IR2);
    Serial.print(",");
  
    delay(10);
    TCA9548A(2);
    //Serial.print("{{Sensor 3}}");
    IR3 = particleSensor3.getIR(); //Send raw data to plotter
    Serial.print(IR3);
  
    delay(10);
    Serial.println();

 //Get current timestamp
timestamp = getTime();
//Serial.print ("time: ");
//Serial.println (timestamp);

parentPath= databasePath + "/" + String(timestamp);

json.set(vattaPath.c_str(), String(IR1));
json.set(pittaPath.c_str(), String(IR2));
json.set(kaphaPath.c_str(), String(IR3));
json.set(timePath, String(timestamp));

server.handleClient();

Serial.printf("", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
  }
}
