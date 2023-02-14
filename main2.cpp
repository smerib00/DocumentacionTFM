#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "coap_client.h"

//instance for coapclient
coapClient coap;

//WiFi connection info
const char* ssid = "";
const char* password = "";

//ip address and default port of coap server in which your interested in
IPAddress ip(192,168,1,134);
int port = 5683;
char* path = "get";

void callback_response(coapPacket &packet, IPAddress ip, int port);

// coap client response callback
void callback_response(coapPacket &packet, IPAddress ip, int port) {
    Serial.println("*************");
    char p[packet.payloadlen + 1];
    memcpy(p, packet.payload, packet.payloadlen);
   // p[packet.payloadlen] = NULL;
    Serial.println(p);
    //response from coap server
    if (packet.type == 3 && packet.code == 0) {
        Serial.begin(9600);
        Serial.println("ping ok");
    }
    Serial.println(packet.options->number);
    Serial.println(p);
}

void setup() {
    String datos="";
    //bits por segundo. Tiene que ser 9600 porque si no, no se entiende lo que imprime.
    Serial.begin(9600);
    
    WiFi.begin(ssid, password);
    Serial.println(" ");

    // Connection info to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        yield();
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    // Print the IP address of client
    Serial.println(WiFi.localIP());

    // client response callback.
    // this endpoint is single callback.
    coap.response(callback_response);
    // start coap client
    coap.start();
}

void loop() {
    String datos="";
    datos = coap.get(ip, port, path);
    Serial.println(datos);
    //state = coap.loop();
    delay(10000);//Sobre 10 segundos
}
