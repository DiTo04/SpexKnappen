//my web site, replace with yours
#define DST_IP "89.255.239.232"

//Define the pin for the on board LED
int led = 13;

//Initialize Device
void setup() {
  //Enable the Onboard LED to act as a Status indicator light
  pinMode(led,OUTPUT);
  //Set the speed for communicating with the ESP8266 module
  Serial.begin(115200);
  //Send a series of flashes to show us we are in the bootup phase.
  blinkcode();
  //Reset the ESP8266
  Serial.println("AT+RST");
  //Wait for the WiFi module to bootup
  delay(5000);
  //Switch the chip to "client" mode
  Serial.println("AT+CWMODE=1");
  //Connect to our Wireless network NOTE: change SSID to your wireless
  //network and PASSWORD to the key used to join the network.
  Serial.println("AT+CWJAP=\"ONE E1003\",\"Internet\"");
  //Once again blink some lights because it is fun!
  blinkcode ();
}

void loop() {
  boolean shoudLedBlink = checkIfSomeBodyWhantsIn();
  
  //Check the returned header & web page. Looking for a keyword. I used YES12321
  if (shoudLedBlink) {
    //If the string was found we know the page is up and we turn on the LED status
    //light to show the server is ONLINE
    digitalWrite(led,HIGH);
  } else {
    //If the string was not found then we can assume the server is offline therefore
    //we should turn of the light.
    digitalWrite(led,LOW);
  }  
  //Introduce a delay timer before we finish and go back to the begining.
  delay (500);
}

boolean checkIfSomeBodyWhantsIn() {
  //Open a connection to the web server
  String cmd = "AT+CIPSTART=\"TCP\",\""; //make this command: AT+CPISTART="TCP","192.168.88.35",80
  cmd += DST_IP;
  cmd += "\",80";
  Serial.println(cmd);
  
  //wait a little while for 'Linked'
  delay(300);
  
  //This is our HTTP GET Request change to the page and server you want to load.
  cmd = "GET /state HTTP/1.1\r\n";
  cmd += "Host: 89.255.239.232\r\n\r\n";
  
  //The ESP8266 needs to know the size of the GET request
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length()); //Ska vara 45.
  
  //Look for the > prompt from the esp8266
  if(Serial.find(">")){
    //Send our http GET request
    Serial.println(cmd);
  } else {
    //Something didn't work...
    Serial.println("AT+CIPCLOSE");
  }
  if (Serial.find("true")) {
    //If the string was found we know the page is up and we turn on the LED status
    //light to show the server is ONLINE
    return true;
  } else {
    //If the string was not found then we can assume the server is offline therefore
    //we should turn of the light.
    return false;
  }
  delay(1000);
  //Be great people and close our connection.
  Serial.println("AT+CIPCLOSE");
  
}

void blinkcode() {
  //Simply loop a few times flashing the status light (this is used during boot up)
  int i;
  for (i = 1; i <= 10; i++){
    delay (100);
    digitalWrite(led,HIGH);
    delay (100);
    digitalWrite(led,LOW);
  }
}
