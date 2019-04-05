## Introduction
This example demonstrates how to use the Treasure Data REST API to send data from mbed OS to Treasure Data. In this example we will grab device information on the CPU, Heap, Stack and System information and forward it on to treasure data to log. 

## Pre-Requisites
- Treasure Data Account
- Treasure Data REST API Key
- Mbed OS Account


## How to use
1) Copy / Paste your Treasure Data API key into the mbed_app.json file
1) If using Wifi copy / paste the SSID / Password into the mbed_app.json file
1) Create Database in your Treasure Data account called `test_database` for the program to send data to
1) Compile and Run code on board (`mbed compile --target auto --toolchain GCC_ARM --flash --sterm`) (or (compile it in the online compiler)[http://os.mbed.com/compiler?import=https://github.com/BlackstoneEngineering/mbed-os-example-treasuredata-rest])
1) View data in Treasure Data (it will take 3-5 minutes to appear)

### What does this look like?
[![How to send data from Mbed OS to Treasure Data with HTTPS](https://img.youtube.com/vi/_tqD6GLMHQA/0.jpg)](https://www.youtube.com/watch?v=_tqD6GLMHQA)



### What if i'm not using Wifi? Or a different Wifi?
Thats awesome! In this program we are using the ism43362 wifi on the ST IOT01A board, but if you have a different board just swap out the network driver and change the config setting in the `mbed_app.json` file and you're good to go! All the NSAPI IP based drivers are compatible, so it works with Wifi, Ethernet, Cellular, ...etc. 

## How is this working?
See the readme on the [Treasure Data REST API Library](https://github.com/blackstoneengineering/mbed-os-treasuredata-rest).

## Troubleshooting

### SSL Failure
If over time the SSL cert expires you will need to replace the cert in `treasuredata-sslcert.h`. You can do this by running ` openssl s_client -connect in.treasuredata.com:443 -showcerts ` and replacing the cert with the lat one in the chain that is displayed. 

### HTTP failures
Try a different access point, double check you changed your Treasure Data API keys and the SSID / Password for the wifi are set correctly in `mbed_app.json`. 

## Liscense
Apache 2.0
