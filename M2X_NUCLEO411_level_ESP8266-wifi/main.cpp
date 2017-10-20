#include "mbed.h"
#include "M2XStreamClient.h"
#include "ESP8266Interface.h"
#include "TCPSocketConnection.h"
#include "hcsr04.h"
 
DigitalOut LED(LED1);
//D12 TRIGGER D11 ECHO
HCSR04 sensor(D12, D11);

/*
*  ESP8266 Wifi Config for nucleo 411
*/
ESP8266Interface wifi(D8,D2,D3,"jared","Nanotechhh",115200); // TX,RX,Reset,SSID,Password,Baud 

//
// Fill these field in from you ATT M2X Account
//
char deviceId[] = "3153fc9bcfb6d089685b9b68d8c5b04b"; // Device you want to push to
char streamName[] = "height"; // Stream you want to push to
char m2xKey[] = "4f89a31afd10f8589e055c63dc17e8c6"; // Your M2X API Key or Master API Key

int main()
{   
    // Set the baud rate that is used to communicate back to the computer to 115,200
    Serial pc(USBTX, USBRX);
    pc.baud(115200);
    pc.printf("Starting...\r\n");

    // connect to wifi
    wifi.init(); //Reset
    wifi.connect(); //Use DHCP
    if(wifi.connect()==0)
    {
        LED=1;
        
        }
    else
    {
        LED=!LED;
        }
    //pc.printf("IP Address is %s \n\r", wifi.getIPAddress());

    // Initialize the M2X client
    Client client;
    M2XStreamClient m2xClient(&client, m2xKey,1,"52.22.150.98"); // api-m2x.att.com
    
    int ret;
     long distance ;

    while (true) {
        // send height value to M2X every 1 seconds
        distance = sensor.distance();   
        pc.printf("distance  %d \r\n",distance);
        ret = m2xClient.updateStreamValue(deviceId, streamName, distance);
        pc.printf("send() returned %d\r\n", ret);
        wait(1.0);
    }
}
