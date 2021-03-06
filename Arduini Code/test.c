//zoomkat 4-04-12
//simple client test
//for use with IDE 1.0
//open serial monitor and send an e to test
//for use with W5100 based ethernet shields
//note that the below bug fix may be required
// http://code.google.com/p/arduino/issues/detail?id=605
//the arduino lan IP address { 192, 168, 1, 102 } may need
//to be modified modified to work with your router.

#include <SPI.h>
#include <Ethernet.h>

int ledPin = 13;                // choose the pin for the LED
int inputPin = 6;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "http://162.243.208.111/";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(54,175,222,246);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup(){
  pinMode(ledPin, OUTPUT);      // declare LED as output
   pinMode(inputPin, INPUT);
     // declare sensor as input
   Serial.begin(9600);
   while (!Serial) {
     ; // wait for serial port to connect. Needed for native USB port only
   }
   // start the Ethernet connection:
   if (Ethernet.begin(mac) == 0) {
     Serial.println("Failed to configure Ethernet using DHCP");
     // try to congifure using IP address instead of DHCP:
     Ethernet.begin(mac, ip);
   }
   // give the Ethernet shield a second to initialize:
   delay(1000);
   Serial.println("connecting...");
  //Ethernet.begin(mac, ip, gateway, gateway, subnet);
  Serial.println("Better client test 4/04/12"); // so I can keep track of what is loaded
  Serial.println("Send an e in serial monitor to test"); // what to do to test
}

void loop(){
  // check for serial input
  val = digitalRead(inputPin);  // read input value
   if (val == HIGH) {            // check if the input is HIGH
     digitalWrite(ledPin, HIGH);  // turn LED ON
     if (pirState == LOW) {
       // we have just turned on
       Serial.println("Motion detected!");
       // We only want to print on the output change, not state
       pirState = HIGH;
       sendGET(1);
     }
   } else {
     digitalWrite(ledPin, LOW); // turn LED OFF
     if (pirState == HIGH){
       // we have just turned of
       Serial.println("Motion ended!");
       // We only want to print on the output change, not state
       pirState = LOW;
       sendGET(0);
     }
   }




}


void sendGET(int val) //client function to send/receive GET request data.
{
  if (client.connect(myserver, 80)) {  //starts client connection, checks for connection
    Serial.println("connected");
    client.println("GET /api/" +val + " HTTP/1.1");
    client.println(); //end of get request
  }
  else {
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }

  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
    Serial.print(c); //prints byte to serial monitor
  }

  Serial.println();
  Serial.println("disconnecting.");
  Serial.println("==================");
  Serial.println();
  client.stop(); //stop client

}
