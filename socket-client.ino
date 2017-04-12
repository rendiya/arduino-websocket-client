#include <SPI.h>

#include <Dhcp.h>
#include <Ethernet.h>

#include <WebSocketClient.h>

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
int count = 0;
void setup() {
  // start serial port:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip, myDns);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  Serial.println("starting WebSocket client");
  client.begin();

  while (client.connected()) {
    Serial.print("Sending hello ");
    Serial.println(count);

    // send a hello #
    client.beginMessage(TYPE_TEXT);
    client.print("hello ");
    client.print(count);
    client.endMessage();

    // increment count for next message
    count++;

    // check if a message is available to be received
    int messageSize = client.parseMessage();

    if (messageSize > 0) {
      Serial.println("Received a message:");
      Serial.println(client.readString());
    }

    // wait 5 seconds
    delay(1000);
  }

  Serial.println("disconnected");
}



