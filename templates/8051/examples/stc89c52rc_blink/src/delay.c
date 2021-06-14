#include "delay.h"

void delay(unsigned int t) {
	unsigned int a, b;
	for(a=t; a>0; a--) {
		for(b=100; b>0; b--);
	}
}