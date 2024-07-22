#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <TimeLib.h>

const int RXPin = 4, TXPin = 5;
const uint32_t GPSBaud = 9600;
SoftwareSerial gps_module(RXPin, TXPin);

#define time_offset   19800     //in seconds 5:30Hrs
char Time[]  = "00:00:00";
char Date[]  = "00-00-2000";
byte last_second, Second, Minute, Hour, Day, Month;
int Year;

TinyGPSPlus gps;

//float gps_speed;
//float no_of_satellites;
//String satellite_orientation;

const char* ssid     = "WiFi_SSID";
const char* password = "WiFi_Password";

// Supabase credentials
String API_URL = "SUPABASE_URL";
String API_KEY = "SUPABASE_API_KEY";
String TableName = "SUPABASE_TABLE_NAE";
const int httpsPort = 443;

// Sending interval of the packets in seconds
int sendinginterval = 1;

HTTPClient https;
WiFiClientSecure client;

unsigned int move_index = 1;

void setup() {
  Serial.begin(115200);    // Baud Rate
  Serial.println();
  gps_module.begin(GPSBaud);
  client.setInsecure();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void checkGPS() {
  if (gps.charsProcessed() < 10) {
    Serial.println(F("No GPS detected: check wiring."));
  }
}

void loop() {
  while (gps_module.available() > 0) {
    if (gps.encode(gps_module.read()))
      displayInfo();
    // delay(1000);
  }
}

void displayInfo() {
  if (gps.location.isValid()) {
    float latitude = (gps.location.lat());
    float longitude = (gps.location.lng());
    // float speed=gps.speed.kmph();
    GetTime();
    // Assuming the row to update has an id of 1
    String rowID = "1"; 
    String url = API_URL + "/rest/v1/" + TableName + "?id=eq." + rowID;
    
    https.begin(client, url);
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Prefer", "return=representation");
    https.addHeader("apikey", API_KEY);
    https.addHeader("Authorization", "Bearer " + API_KEY);
    
    // Creating JSON payload
    String isoDateTime = String(Year) + "-" + String(Month) + "-" + String(Day) + "T" + String(Hour) + ":" + String(Minute) + ":" + String(Second) + "-05:30";
    
    
    // Creating JSON payload
    String jsonPayload = "{\"LAT\":" + String(latitude, 6) + ",\"LONG\":" + String(longitude, 6) + ",\"updated_at\":\"" + isoDateTime + "\"}";
    
    int httpCode = https.sendRequest("PATCH", jsonPayload);   // Send the request
    
    String payload = https.getString();
    Serial.println(httpCode);   // Print HTTP return code
    Serial.println(payload);    // Print request response payload
    https.end();
    
    Serial.print("LAT:  ");
    Serial.println(latitude, 6);
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
    Serial.println(Time);
    Serial.println(Date);
    // Serial.println(speed);
  }
  // delay(1000 * sendinginterval);      //Adjust your Delay
  // delay(100);
  Serial.println();
}

void GetTime()
{
      // get time from GPS module
      if (gps.time.isValid())
      {
        Minute = gps.time.minute();
        Second = gps.time.second();
        Hour   = gps.time.hour();
      }

      // get date drom GPS module
      if (gps.date.isValid())
      {
        Day   = gps.date.day();
        Month = gps.date.month();
        Year  = gps.date.year();
      }

      if(last_second != gps.time.second())  // if time has changed
      {
        last_second = gps.time.second();

        // set current UTC time
        setTime(Hour, Minute, Second, Day, Month, Year);
        // add the offset to get local time
        adjustTime(time_offset);

        // update time array
        Time[6] = second() / 10 + '0';
        Time[7] = second() % 10 + '0';
        Time[3]  = minute() / 10 + '0';
        Time[4] = minute() % 10 + '0';
        Time[0]  = hour()   / 10 + '0';
        Time[1]  = hour()   % 10 + '0';

        // update date array
        Date[8] = (year()  / 10) % 10 + '0';
        Date[9] =  year()  % 10 + '0';
        Date[3]  =  month() / 10 + '0';
        Date[4] =  month() % 10 + '0';
        Date[0]  =  day()   / 10 + '0';
        Date[1]  =  day()   % 10 + '0';
      }

}
