#include "test.h"

int	kd(int kc)
{

	if(kc == ESC)
		exit(0);

	if(kc == MINUS){
		scale += 0.01;
	}
	if(kc == PLUS)
		scale -= 0.01;

	if (scale < 0.01)
		scale = 0.01;
	
	if (scale > 12)
		scale = 12;

	return (0);
}
