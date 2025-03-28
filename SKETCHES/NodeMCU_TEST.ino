/*
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# RFID MFRC522 / RC522 Library : https://github.com/miguelbalboa/rfid # 
#                                                                     # 
#                 Installation :                                      # 
# NodeMCU ESP8266/ESP12E    RFID MFRC522 / RC522                      #
#         D2       <---------->   SDA/SS                              #
#         D5       <---------->   SCK                                 #
#         D7       <---------->   MOSI                                #
#         D6       <---------->   MISO                                #
#         GND      <---------->   GND                                 #
#         D1       <---------->   RST                                 #
#         3V/3V3   <---------->   3.3V                                #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

*/



//----------------------------------------Include the NodeMCU ESP8266 Library---------------------------------------------------------------------------------------------------------------//
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


//----------------------------------------Include the SPI and MFRC522 libraries----------------//
//----------------------------------------Download the MFRC522 / RC522 library here: https://github.com/miguelbalboa/rfid
#include <SPI.h>
#include <MFRC522.h>
#include "PageIndex.h" //--> Include the contents of the User Interface Web page, stored in the same folder as the .ino file

#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router



#define SS_PIN      D2  
#define RST_PIN     D1  


MFRC522 mfrc522(SS_PIN, RST_PIN); 
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;


//----------------------------------------SSID and Password of your WiFi router----------------//
const char* ssid = "Bobby 2.4G Network";  //--> Your wifi router ssid
const char* password = "1Dog3Birds95";  //--> Your wifi router password
//---------------------------------------------------------------------------------------------//


ESP8266WebServer server(80);  //--> Server on port 80

int readsuccess;
byte readcard[4];
char str[32] = "";
String StrUID;




//******************************************************************************************//
//------------------------------------------SETUP-------------------------------------------//
//******************************************************************************************//

void setup() {
  Serial.begin(9600); //--> Initialize serial communications with the PC
  SPI.begin();      //--> Init SPI bus
  mfrc522.PCD_Init(); //--> Init MFRC522 card

  delay(500);

  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); 
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot); //--> Routine to handle at root location. This is to display web page.
  server.on("/UIDResult", handleUIDResult);  //--> Routine for handling handleUIDResult procedure calls

  server.begin(); //--> Start server
  Serial.println("HTTP server started");
  Serial.println("");

  Serial.println("Please tag a card or keychain to see the UID !");
  Serial.println("");
}
//-----------------------------------------------------------------------------------------//


//******************************************************************************************//
//------------------------------------------LOOP-------------------------------------------//
//******************************************************************************************//

void loop() {
  server.handleClient();  //--> Handle client requests
}
//-----------------------------------------------------------------------------------------//


//******************************************************************************************//
//----------Procedure for reading and obtaining a UID from a card or keychain---------------//
//******************************************************************************************//

  int getid() {  
    // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
    byte block;
    byte len;
    //-------------------------------------------
    
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return 0;
    }
    
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return 0;
    }


    
    Serial.println(F("**Card Detected:**"));
    byte buffer1[18];
    block = 4;
    len = 18;
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid));
    
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Authentication failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return 0;
    }
    
    status = mfrc522.MIFARE_Read(block, buffer1, &len);
    
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Reading failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return 0;
     }
    
    String StrUID = "";
    
    for (uint8_t i = 0; i < 16; i++) {
      StrUID += (char)buffer1[i];
      
    }
    
    StrUID.trim();
    Serial.print(StrUID);
    
    
    Serial.println(F("\n**End Reading**\n"));
    delay(1000);
    
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    return 1;
  }
//------------------------------------------------------------------------------------------//




//******************************************************************************************//
//---------Procedure to change the result of reading an array UID into a string-------------//
//******************************************************************************************//

void array_to_string(byte array[], unsigned int len, char buffer[]) {
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}
//------------------------------------------------------------------------------------------//



//******************************************************************************************//
//-----This routine is executed when you open NodeMCU ESP8266 IP Address in browser---------//
//******************************************************************************************//

  void handleRoot() {
    String s = MAIN_page; //--> Read HTML contents
    server.send(200, "text/html", s); //--> Send web page
  }


//******************************************************************************************//
//----------------Procedure for sending UID reading results to web page---------------------//
//******************************************************************************************//

  void handleUIDResult() {
    readsuccess = getid();
   
    if(readsuccess) {
      digitalWrite(ON_Board_LED, LOW); //--> Led on board is turned on as an indicator of successful UID reading
      server.send(200, "text/plane", StrUID); //--> Send Temperature value only to client ajax request
      
      Serial.println(StrUID);
      Serial.println(""); 
      Serial.println("Please tag a card or keychain to see the UID !");
      Serial.println("");  
      digitalWrite(ON_Board_LED, HIGH); //--> Led on board is turned off as an indicator that the UID has been printed
    }
  }

//-------------------------------------------------------------------------------------------//
