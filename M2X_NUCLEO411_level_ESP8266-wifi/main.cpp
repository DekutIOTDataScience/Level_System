#include "mbed.h"
#include "M2XStreamClient.h"
#include "ESP8266Interface.h"
#include "TCPSocketConnection.h"


/*
*  ESP8266 Wifi Config for nucleo 411
*/
ESP8266Interface wifi(D8,D2,D3,"wifiName","wifiPassword",115200); // TX,RX,Reset,SSID,Password,Baud 

//
// Fill these field in from you ATT M2X Account
//
char deviceId[] = "<deviceID>"; // Device you want to push to
char streamName[] = "<streamID>"; // Stream you want to push to
char m2xKey[] = "<deviceAPIKey>"; // Your M2X API Key or Master API Key

int main()
{
    printf("Starting...\r\n");

    // connect to wifi
    wifi.init(); //Reset
    wifi.connect(); //Use DHCP
    printf("IP Address is %s \n\r", wifi.getIPAddress());

    // Initialize the M2X client
    Client client;
    M2XStreamClient m2xClient(&client, m2xKey,1,"52.22.150.98"); // api-m2x.att.com
    
    int ret;
    volatile int randomNumber = 0;

    while (true) {
        // send a random number to M2X every 5 seconds
        randomNumber = rand();
        ret = m2xClient.updateStreamValue(deviceId, streamName, randomNumber);
        printf("send() returned %d\r\n", ret);
        wait(5.0);
    }
}