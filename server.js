var coap = require('coap'); 

var port = 5683;
var numero = 5;
var tempC, tempF, humedad;
coap.createServer(function(req, res) {
    console.info('CoAP device got a request for %s', req.url);
    console.log(req.headers);
    if(req._packet.payload.toString()[0]!=undefined && req.url=="/post"){
        tempC = req._packet.payload.toString()[0]+req._packet.payload.toString()[1]+req._packet.payload.toString()[2]+
        req._packet.payload.toString()[3]+req._packet.payload.toString()[4]+req._packet.payload.toString()[5]+" ºC ";
        tempF = req._packet.payload.toString()[6]+req._packet.payload.toString()[7]+req._packet.payload.toString()[8]+
        req._packet.payload.toString()[9]+req._packet.payload.toString()[10]+req._packet.payload.toString()[11]+" ºF ";
        humedad = req._packet.payload.toString()[12]+req._packet.payload.toString()[13]+req._packet.payload.toString()[14] +
         req._packet.payload.toString()[15]+req._packet.payload.toString()[16]+req._packet.payload.toString()[17]+" % humedad ";
    }
    switch (req.url) { 
        case "/post":
            if(req._packet.payload.toString()[1]!="a"){
                console.log(tempC.toString()+tempF.toString()+humedad.toString());                
            }else{
                console.log("Error de lectura");
            }
            break
        case "/get":
            console.log("Modulo");
            if(req._packet.payload.toString()[1]!="a"){
                console.log(tempC.toString()+tempF.toString()+humedad.toString());                
            }else{
                console.log("Error de lectura");
            }
            break
        case "/obs":
            let counter = 0;
            var interval = setInterval(function() {
                res.setOption('Content-Format', 'application/json');
                res.code = '2.05';
                res.write(JSON.stringify({
                    tempC, tempF, humedad
                }));
            }, 10000);
            res.on('finish', function(err) {
                clearInterval(interval)
            })
            break;
        case "/mitm":
            console.log("Conseguido")
        break;
        default:
            respond(5);
    }
}).listen(port, function() {
    console.log("CoAP server started on port %s", port)
}); //#E


function respond(res, content) { //#F 
  if (content) {
    res.setOption('Content-Format', 'application/json');
    res.code = '2.05';
    if(res.toString!="{}")
        res.end(JSON.stringify(content));
}}
