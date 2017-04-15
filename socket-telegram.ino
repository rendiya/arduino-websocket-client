#include <SPI.h>

#include <Dhcp.h>
#include <Ethernet.h>

#include <WebSocketClient.h>
String token="258162066:AAG4hY807MImx0HtZVPrMvTRK0RHa42HTiY";
char message;
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(10,42,0,2);
IPAddress myDns(8,8,8,8);

EthernetClient ethernet;

//IPAddress server(192,168,137,1);
//IPAddress server(163,172,179,222);
char server[] = "echo.ayoklinik.com";

int port = 3000;

WebSocketClient client = WebSocketClient(ethernet, server, port);
long randNumber;
void setup() {
  // start serial port:
  Serial.begin(9600);
  randomSeed(analogRead(0));
  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip, myDns);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  randNumber = random(300);
  randNumber = random(10, 20);
  WebSocket(String(randNumber));

}


void WebSocket(String message){
  Serial.println("starting WebSocket client");
  client.begin();
  Serial.println(message);

  while (client.connected()) {
    Serial.print("Sending ");
    Serial.print(message);

    // send a hello #
    client.beginMessage(TYPE_TEXT);
    client.print("read|"+token);
    //client.print(message);
    client.endMessage();

    // increment count for next message

    // check if a message is available to be received
    int messageSize = client.parseMessage();

    if (messageSize > 0) {
      Serial.println("Received a message:");
      Serial.println(client.readString());
    }
    delay(10000);
  }

  Serial.println("disconnected");
}

