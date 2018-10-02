## Introduction
This example demonstrates how to use the Treasure Data REST API to send data from mbed OS to Treasure Data. In this example we will grab device information on the CPU, Heap, Stack and System information and forward it on to treasure data to log. 

## Pre-Requisites
- Treasure Data Account
- Treasure Data REST API Key
- Mbed OS Account


## How to use
1) Copy / Paste your Treasure Data API key into the mbed_app.json file
1) If using Wifi copy / paste the SSID / Password into the mbed_app.json file
1) Create Database called `test_database` for the program to send data to
1) Compile and Run code on board (`mbed compile --target auto --toolchain GCC_ARM --flash --sterm`)
1) View data in Treasure Data

### What does this look like?
// TODO: Video


### What if i'm not using Wifi? Or a different Wifi?
Thats awesome! In this program we are using the ism43362 wifi on the ST IOT01A board, but if you have a different board just swap out the network driver and change the config setting in the `mbed_app.json` file and you're good to go! All the NSAPI IP based drivers are compatible, so it works with Wifi, Ethernet, Cellular, ...etc. 

## How is this working?
See the readme on the [Treasure Data REST API Library](https://github.com/blackstoneengineering/mbed-os-treasuredata-rest).

## Liscense
Apache 2.0