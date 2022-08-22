#include <SoftwareSerial.h>


#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

SoftwareSerial mySerial(3, 1);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
    char inChar;
    String string;

static const uint8_t image_data_Saraarray[1024] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x18, 0x06, 0x00, 0x01, 0x80, 0x00, 0x63, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0xe1, 0xc0, 0x00, 0x18, 0x06, 0x00, 0x01, 0x80, 0x00, 0x63, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xe0, 0x00, 0x18, 0x06, 0x00, 0x01, 0x80, 0x00, 0x63, 0x00, 
    0x00, 0x01, 0xff, 0xe0, 0x00, 0x1c, 0x60, 0x00, 0x18, 0x07, 0xe1, 0xf1, 0x8f, 0xc0, 0x63, 0x00, 
    0x00, 0x1f, 0x00, 0x1f, 0x00, 0x0e, 0x70, 0x00, 0x18, 0x06, 0x33, 0x19, 0x8c, 0x60, 0x63, 0x00, 
    0x00, 0x70, 0x00, 0x1f, 0xe0, 0xc6, 0x30, 0x00, 0x18, 0x06, 0x33, 0x19, 0x8c, 0x60, 0x63, 0x00, 
    0x00, 0xff, 0xe0, 0x18, 0x38, 0xe3, 0x38, 0x00, 0x18, 0x06, 0x33, 0xf9, 0x8c, 0x60, 0x63, 0x00, 
    0x03, 0x00, 0x1c, 0x30, 0x3c, 0x33, 0x18, 0x00, 0x18, 0x06, 0x33, 0x01, 0x8c, 0x60, 0x63, 0x00, 
    0x0c, 0x00, 0x03, 0x60, 0x82, 0x31, 0x18, 0x00, 0x18, 0x06, 0x33, 0x01, 0x8c, 0x60, 0x63, 0x00, 
    0x18, 0x00, 0x00, 0xc1, 0x01, 0x00, 0x00, 0x00, 0x18, 0x06, 0x33, 0x09, 0x8c, 0x60, 0x63, 0x00, 
    0x30, 0x00, 0x06, 0x82, 0x08, 0x80, 0x00, 0x00, 0x18, 0x06, 0x31, 0xf1, 0x8f, 0xc0, 0x3e, 0x00, 
    0x60, 0x00, 0x09, 0x04, 0x44, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 
    0xc0, 0x00, 0x07, 0x00, 0x22, 0x40, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x0a, 0x08, 0x10, 0xe3, 0x81, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x32, 0x11, 0x00, 0xf6, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x30, 0x3e, 0x10, 0x82, 0x38, 0x00, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x47, 0xcc, 0x10, 0x04, 0x20, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x90, 0x30, 0x00, 0x10, 0xc0, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0x0a, 0x08, 0x61, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x02, 0x07, 0x85, 0x03, 0x86, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x9f, 0xe6, 0x00, 0x08, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x06, 0x00, 
    0x04, 0x3f, 0xf2, 0x80, 0x30, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x06, 0x00, 
    0x05, 0x3b, 0xf2, 0x80, 0xc0, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x00, 0x06, 0x00, 
    0x05, 0x79, 0xfa, 0x83, 0x00, 0x0f, 0xf8, 0x00, 0x3f, 0x07, 0xc3, 0xe3, 0x38, 0x0f, 0x8f, 0x00, 
    0x05, 0x3f, 0xfa, 0x84, 0x00, 0x1f, 0xf0, 0x00, 0x31, 0x8c, 0x66, 0x33, 0x60, 0x10, 0xc6, 0x00, 
    0x05, 0x7f, 0xfa, 0x90, 0x00, 0x3f, 0xe0, 0x00, 0x31, 0x8c, 0x66, 0x33, 0xc0, 0x00, 0xc6, 0x00, 
    0x05, 0x3f, 0xfa, 0x60, 0x00, 0x7f, 0xc0, 0x00, 0x31, 0x8f, 0xe7, 0xf3, 0x80, 0x0f, 0xc6, 0x00, 
    0x3d, 0x3f, 0xfe, 0x00, 0x00, 0xff, 0x80, 0x00, 0x31, 0x8c, 0x06, 0x03, 0xc0, 0x18, 0xc6, 0x00, 
    0x40, 0x9c, 0x02, 0x00, 0x01, 0xff, 0x00, 0x00, 0x31, 0x8c, 0x06, 0x03, 0x60, 0x18, 0xc6, 0x00, 
    0xb6, 0x18, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 0x31, 0x8c, 0x26, 0x13, 0x30, 0x18, 0xc6, 0x00, 
    0x4b, 0x60, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x3f, 0x07, 0xc3, 0xe3, 0x18, 0x0f, 0xc3, 0x00, 
    0xb5, 0xa0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x4a, 0xc0, 0x00, 0x00, 0x1e, 0x07, 0x80, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xb5, 0x40, 0x00, 0x00, 0x3c, 0x00, 0x40, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x41, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x3a, 0x00, 0x03, 0x07, 0xf0, 0x01, 0xe0, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0xff, 0xff, 0xfe, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x31, 0x8d, 0xc3, 0x0f, 0x87, 0xe3, 0xc0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x31, 0x8f, 0xc3, 0x18, 0xcc, 0x66, 0x20, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x31, 0x8c, 0x03, 0x18, 0xcc, 0x66, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x31, 0x8c, 0x03, 0x18, 0xcc, 0x67, 0x80, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x17, 0xf8, 0x00, 0x00, 0x31, 0x8c, 0x03, 0x18, 0xcc, 0x61, 0xe0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x09, 0xf0, 0x00, 0x00, 0x31, 0x8c, 0x03, 0x18, 0xcc, 0x60, 0x60, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x05, 0x30, 0x00, 0x00, 0x31, 0x8c, 0x03, 0x18, 0xcc, 0x64, 0x60, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x1f, 0x8c, 0x03, 0x0f, 0x87, 0xe7, 0xc0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x60, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};

AsyncWebServer server(80);

const char* ssid = ""; // Your WiFi SSID
const char* password = ""; // Your WiFi Password


/* Message callback of WebSerial */
void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  WebSerial.println(d);
  Serial.println(d);
 
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println(d);
  display.display();
  
}

void setup() {
  
    Serial.begin(57600);
    mySerial.begin(57600);
    mySerial.println("Hello, world?");
     
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    /* Attach Message Callback */
    WebSerial.msgCallback(recvMsg);
    server.begin();
    
    Wire.begin(5, 4);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    delay(2000); // Pause for 2 seconds
    display.clearDisplay();
    display.drawBitmap(0, 0, image_data_Saraarray, 128, 64, 1);
    display.display();
}


void loop() {
    if (mySerial.available() > 0) {
        mySerial.read();

    char x = mySerial.read(); //read arrived character from FIFO (say 1) and put into x as 0x31 
    Serial.println(x);  //send 0x31 to Serial Monitor to show 1 via UART Port
    WebSerial.println(x);
    display.setCursor(0,0);
    display.setTextSize(1);
    display.println(x);
    display.display();
  }

{
   display.setTextColor(SSD1306_WHITE); // Draw white text
   //display.cp437(true);         // Use full 256 char 'Code Page 437' font   
   display.display();
   while (Serial.available() == 0) {}
   delay(2);
   String inChar  = Serial.readString();
   inChar.trim();
   display.clearDisplay();
   Serial.println(inChar);
   display.setCursor(0,0);
   display.setTextSize(1);
   display.print(inChar);
   display.display();
  }
}
