#include <mcs51/8052.h>
#include "delay.h"
#include "set.h"

void main() {
	while(1) {
		unset();
		delay(1000);
		set();
		delay(1000);
	}
}