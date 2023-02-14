# DocumentacionTFM
Trabajo Fin de Máster

Configuración del protocolo CoAP en un entorno OpenFlow para la detección de vulnerabilidades

Entorno

main1.cpp --> este archivo ha sido creado para que pueda ser utilizado por una placa ESP8266 con un sensor de temperatura y humedad DHT11 y que hagan de cliente en un entorno CoAP enviando paquetes con información al servidor

main2.cpp --> este archivo ha sido creado para que pueda ser utilizado por una placa ESP8266 que hará de cliente solicitando información al servidor

index.js --> este archivo escrito en lenguaje JavaScript, hará de servidor enviando y recibiendo información de los clientes

client.js --> archivo en lenguaje Javascript que hará la función de cliente y solicitará información al servidor. Realizará peticiones get con la opción observe para que esté continuamente recibiendo paquetes del servidor

Creación de redes virtuales SDN con Mininet.

prueba1.py --> Ejemplo de creación de una red con un host
prueba2.py --> Topología de red formada por 6 hosts y 3 switches con un bucle.
