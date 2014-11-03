#include "mbed.h"

Serial async_port(p9,p10);
DigitalOut red(p25);
DigitalOut green(p26);
DigitalOut strobe(p7);
DigitalIn switch1(p5);
Serial pc(USBTX,USBRX);
char switchword;
char recdval;
int main() {
    async_port.baud(9600);
    while(1) {
        switchword = 0xa0;
        if(switch1==0)
            switchword|=0x1;
        strobe =1;
        wait_us(10);
        strobe =0;
       // pc.printf("Put data :%d\n",switchword);
        async_port.putc(switchword);
        if(async_port.readable()==1)
            recdval = async_port.getc();
        red=0;
        green=0;
        recdval&=0x03;
        if(recdval==1)
           red=1;
        else
           green = 1;
    }
}
