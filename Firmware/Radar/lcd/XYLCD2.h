#include <18F4520.h>
#device adc=10
#fuses intrc, nolvp,WDT512,NOBROWNOUT
#use delay(clock=32000000,restart_wdt)
#use rs232(stream=rs232, baud=38400, parity=N, xmit=PIN_C6, rcv=PIN_C7, bits=8)
