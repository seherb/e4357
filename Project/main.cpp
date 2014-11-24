#include "mbed.h"
#include "TextLCD.h"
#include "EthernetInterface.h"


const char* ECHO_SERVER_ADDRESS =  "192.168.1.120";
const int ECHO_SERVER_PORT = 9999;
#define MBED_DEV_IP       "192.168.1.128"
#define MBED_DEV_MASK     "255.255.255.0"
#define MBED_DEV_GW       "192.168.1.254"

TextLCD lcd(p15, p16, p17, p18, p19, p20,TextLCD::LCD20x4);
DigitalIn pb(p22);
DigitalIn pb2(p21);


typedef enum {
    eMainMenu,
    eSTOCK,
    eWEATHER,
} MENU;

int main()
{
    bool bchange = false;
    MENU currentMenu = eMainMenu;
    EthernetInterface eth;
    eth.init(MBED_DEV_IP, MBED_DEV_MASK, MBED_DEV_GW);
    eth.connect();
    printf("IP Address is %s\n", eth.getIPAddress());

    // Attach the address of the interrupt handler routine for pushbutton

    TCPSocketConnection socket;
    while (socket.connect(ECHO_SERVER_ADDRESS, ECHO_SERVER_PORT) < 0) {
        printf("Unable to connect to (%s) on port (%d)\n", ECHO_SERVER_ADDRESS, ECHO_SERVER_PORT);
        wait(1);
    }
    pb.mode(PullUp);
    // Delay for initial pullup to take effect
    wait(.01);
    pb2.mode(PullUp);
    wait(.01);
    lcd.printf("STOCK\n");
    lcd.printf("WEATHER\n");
    while(1) {
        switch(currentMenu) {
            case eMainMenu:

                if(bchange) {
                    printf("MAIN MENU\n");
                    lcd.cls();
                    bchange = false;
                    lcd.printf("STOCK\n");
                    lcd.printf("WEATHER\n");
                }
                if(pb ==0) {
                    currentMenu = eSTOCK;
                    bchange = true;
                }
                if(pb2 ==0) {
                    currentMenu = eWEATHER;
                    bchange = true;
                }

                break;
            case eSTOCK:

                if(bchange) {
                    printf("STOCK MENU\n");
                    lcd.cls();
                    bchange = false;
                    char stock[] = "1";
                    socket.send_all(stock, sizeof(stock) - 1);
                    char buf[1024];
                    int n = socket.receive(buf, 1024);
                    buf[n] = '\0';
                    lcd.printf("%s\n",buf);
                    printf("%s\n",buf);

                }

                if(pb ==0) {
                    currentMenu = eMainMenu;
                    bchange = true;

                }

                break;
            case eWEATHER:

                if(bchange) {
                    printf("WEATHER MENU\n");
                    lcd.cls();
                    bchange = false;

                    char weather[] = "2";
                    socket.send_all(weather, sizeof(weather) - 1);
                    char buf[1024];
                    int n = socket.receive(buf, 1024);
                    buf[n] = '\0';
                    lcd.printf("%s\n",buf);
                    printf("%s\n",buf);
                }
                if(pb ==0) {
                    currentMenu = eMainMenu;
                    bchange = true;
                }
                break;
            default:
                break;
        }
        wait(0.1);
    }
    socket.close();
    eth.disconnect();
}
