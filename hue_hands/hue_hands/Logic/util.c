/*
 * util.c
 *
 * Created: 3/20/2019 1:35:52 PM
 *  Author: danin
 */ 
#include "../Include/util.h"
 
 void wait(double ms)
 {
	 for (int i = 0; i<ms; i++)
	 {
		 _delay_ms(1);
	 }
 }