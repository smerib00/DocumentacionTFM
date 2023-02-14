#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "coap_client.h"
#include "DHT.h"
#define DHTTYPE DHT11

//instance for coapclient
coapClient coap;

//WiFi connection info
const char* ssid = "";
const char* password = "";

//ip address and default port of coap server in which your interested in
IPAddress ip(192,168,1,134);
int port = 5683;
char* path = "post";

// Sensor DHT
const int DHTPin = 5;  //Comunicación de datos en el pin 5 (GPIO 5 -- D1)
// Iniciando sensor
DHT dht(DHTPin, DHTTYPE);

// Variables temporales
static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];

DynamicJsonDocument  doc(1024);
// coap client response callback
void callback_response(coapPacket &packet, IPAddress ip, int port) {
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;

  //response from coap server
  if (packet.type == 3 && packet.code == 0) {
    Serial.begin(9600);
    Serial.println("ping ok");
  }

  Serial.println(p);
}

void setup() {
  //bits por segundo. Tiene que ser 9600 porque si no, no se entiende lo que imprime.
  Serial.begin(9600);
  dht.begin();
  
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

  float h = dht.readHumidity();
  // Leyendo temperatura en Celsius (es la unidad de medición por defecto)
  float t = dht.readTemperature();
  // Leyendo temperatura en Fahrenheit (Si es "true" la leerá en esa unidad)
  float f = dht.readTemperature(true);
  // Revisión de fallas en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Fallos al leer el sensor DHT");
    strcpy(celsiusTemp, "Fallido");
    strcpy(fahrenheitTemp, "Fallido");
    strcpy(humidityTemp, "Fallido");
  }else {
    // Calculando valores de temperatura en Celsius + Fahrenheit and Humedad
    float hic = dht.computeHeatIndex(t, h, false);
    dtostrf(hic, 6, 2, celsiusTemp);
    float hif = dht.computeHeatIndex(f, h);
    dtostrf(hif, 6, 2, fahrenheitTemp);
    dtostrf(h, 6, 2, humidityTemp);

    Serial.print("Los grados en Celsius son: ");
    Serial.print(celsiusTemp);
    Serial.print("Los grados en Fahrenheit son: ");
    Serial.print(fahrenheitTemp);
    Serial.print("Los humedad es: ");
    Serial.print(humidityTemp);
    Serial.println();
  }

  String data = (String)celsiusTemp+(String)fahrenheitTemp+(String)humidityTemp;
  char dataChar[data.length() + 1];
  data.toCharArray(dataChar, data.length() + 1);
  bool state;

  //post request
  //arguments server ip address,default port,resource name, payload,payloadlength
  int msgid = coap.post(ip, port, path, dataChar, data.length()+1);

  //state = coap.loop();

  delay(20000);
}
