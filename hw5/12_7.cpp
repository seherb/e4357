//Program Example 12.7 : Ethernet write
#include "mbed.h"
#include "Ethernet.h"

Ethernet eth;
char data[]={0xB9,0x46};

int main() {
	while (1) {
		eth.write(data, 0x02);
		eth.send();
		wait(0.2);
	}
}