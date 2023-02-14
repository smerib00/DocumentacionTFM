const coap = require("node-coap-client").CoapClient;

coap
.observe(
    "coap://192.168.1.134:5683/obs",
    "get",
    function(response) {
        if(response.payload.toString()!="{}")
            console.log(response.payload.toString());
    },
)
.then(() => { /* observing was successfully set up */ })
.catch(err => { console.error(err) })
