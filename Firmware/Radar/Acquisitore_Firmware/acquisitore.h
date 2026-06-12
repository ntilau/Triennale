#include <18F2420.h>
#device adc=12
#fuses intrc, nolvp, NOWDT,NOBROWNOUT
#use delay(clock=32000000,RESTART_WDT)
#use rs232(stream=rs232, baud=38400, parity=N, xmit=PIN_C6, rcv=PIN_C7, bits=8)
