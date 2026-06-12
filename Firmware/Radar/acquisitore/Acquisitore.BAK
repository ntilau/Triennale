#include "acquisitore.h"

#bit PLL_ENABLE=0xf9b.6

void DigPot(int dato);
void DataTX(long I, long Q);

int GAIN=0x00,CLUTTER_CANCELLATION=0,i;
int head=0xaa;


#int_rda
Leggi_RS232()
{

   switch ( fgetc(RS232) )
   {
      case 0x67:
      {
         GAIN=fgetc(RS232);
         DigPot(GAIN);
         //fprintf(rs232,"\n\rGain changed to %U\n\r",gain);
         break;
      }

      case 0x69:
      {
         if(fgetc(RS232)==0x69)
            Reset_cpu();
         break;
      }

      case 0x65:
      {
         //fprintf(RS232,"\n\rIPERCONNESSO\n\r");
         fputc(0x65,RS232);
         fputc(0x65,RS232);
         break;
      }

      case 0x63:
      {
         CLUTTER_CANCELLATION=fgetc(RS232);
         switch ( CLUTTER_CANCELLATION )
         {
            case 0x00:
            {
               output_low(pin_b5);     //disabilita la soppressione di clutter
               //fprintf(rs232,"\n\rClutter cancellation inhibited\n\r",gain);
               break;
            }

            case 0xff:
            {
               output_high(pin_b5);    //abilita la soppressione di clutter
               //fprintf(rs232,"\n\rClutter cancellation available\n\r",gain);
               break;
            }

            case 0x0f:
            {

               output_low(pin_b5);
               delay_ms(50);
               output_high(pin_b5);
               //fprintf(rs232,"\n\rClutter cancellation toggle\n\r",gain);
               break;
            }

            default:
            {

            }
            break;

         }

      }

      default:
      {

      }
      break;

   }


}

void main()
{

   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);


   setup_adc_ports(AN0_TO_AN1|VSS_Vref);
   setup_adc(ADC_CLOCK_INTERNAL|ADC_TAD_MUL_0);
   setup_oscillator(osc_8mhz);

   setup_spi(SPI_MASTER|SPI_H_TO_L|SPI_CLK_DIV_4);
   PLL_ENABLE=1;

   restart_wdt();

  while(1)
   {

      long I,Q;

      set_adc_channel(0);
      I=read_adc();
      set_adc_channel(1);
      Q=read_adc();

      DataTX(I, Q);
      delay_ms(3);
      restart_wdt();

   }


}

void DigPot(int dato)
{
   output_low(pin_c2);
   spi_write(dato);
   output_high(pin_c2);

}

void DataTX(long I, long Q)
{

   fputc(head,rs232);
   fputc(make8(I,1),rs232);
   fputc(make8(I,0),rs232);
   fputc(make8(Q,1),rs232);
   fputc(make8(Q,0),rs232);

}

