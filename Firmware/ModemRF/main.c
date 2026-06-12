#include <18f4620.h>
#fuses INTRC_IO,WDT, NOPROTECT, BROWNOUT, MCLR
#use delay(clock=16000000)
#use rs232( baud=38400, xmit=PIN_C6, rcv=PIN_C7, bits=8, parity=N)

// PIC
#define  SSPCON1  0xFC6
#define  SSPSTAT  0xFC7

#define  TxLed PIN_B0
#define  RxLed PIN_B1
#define  SI PIN_C5
#define  S0 PIN_C4
#define  SCLK   PIN_C3
#define  CSn   PIN_C2
#define  GDO2  PIN_C1
#define  GDO0  PIN_C0

// CC1101
#include "header.h"

char RxBuffer[10], TxBuffer[10];
char i=0, j=0, temp=0;
char PacketStatus=0, MARCS=0, PacketLengthTx=0, FirstByte=0;
char TxFIFOBytes=0, RxFIFOBytes=0;
short CRC_Ok=FALSE;
short ForceTx=FALSE;
char ToSend=0;

void Blink();
void CCBurstConfig();
void InitInfos();
void CheckStatus();
void PrintStatus();
void CalibrationRoutine();
void SendStrobe(char Strobe);
void SetRegister(char Address, char Value);

#INT_RDA
void RDA_isr(){ 
   temp = getc();
   /*
   output_high(TxLed);
   delay_ms(100);
   output_low(TxLed);
   putc(temp);
   */
   if(ToSend==0){
      switch(temp){
         case 0xAA:
            PacketLengthTx=5;
            TxBuffer[ToSend]=0xAA;
            ToSend++;
            break;
         case 0x63:
            PacketLengthTx=2;
            TxBuffer[ToSend]=0x63;
            ToSend++;
            break;
         case 0x67:
            PacketLengthTx=2;
            TxBuffer[ToSend]=0x67;
            ToSend++;
            break;
         case 0x69:
            PacketLengthTx=2;
            TxBuffer[ToSend]=0x69;
            ToSend++;
            break;
      }
   } else if(ToSend>0){
      if((ToSend+1)==PacketLengthTx){
         TxBuffer[ToSend]=temp;
         ToSend=0;
         ForceTx=TRUE;
      } else{
         TxBuffer[ToSend]=temp;
         ToSend++;
      }
   }
}

void main(){

   setup_oscillator(OSC_16MHZ);

   setup_spi(SPI_MASTER|SPI_L_TO_H|SPI_CLK_DIV_4); // SCLK @ 4MHz
   *SSPSTAT |= 0x40;
   output_high(CSn);
   setup_wdt(WDT_ON);

   SendStrobe(SRES);
   CCBurstConfig();   
   //InitInfos();     
   CalibrationRoutine();
   Blink();
   
   SetRegister(_PKTCTRL1,0x08);// No Status
   SetRegister(_PKTCTRL0,0x04);// Fixed length
   SetRegister(_PKTLEN,0x05);
   SetRegister(_MCSM1,0x30);// OFF to Rx
   SetRegister(_MCSM0,0x08);// AutoCal Idle to Tx o Rx
   SetRegister(PATABLE, 0x0F); // -20 dBm
   
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

   while(TRUE){
      
      restart_wdt();

      // RICEZIONE
      //****************************************************
      if(ForceTx==FALSE){
         CheckStatus();
         //PrintStatus();
         if(MARCS!=13 || MARCS!=14 || MARCS!=15) SendStrobe(SRX);
         if(MARCS==17) SendStrobe(SFRX);
         if(CRC_Ok){
            output_high(RxLed);
            //delay_us(1000);
            output_low(CSn);
            spi_write(RXFIFO|RdBt);
            FirstByte = spi_read(0);
            switch(FirstByte){
               case 0xAA:
                  for(j=0;j<4;j++) RxBuffer[j] = spi_read(0);
                  output_high(CSn);
                  putc(0xAA);
                  for(j=0;j<4;j++) putc(RxBuffer[j]);
                  break;
               case 0x63:
                  for(j=0;j<4;j++) RxBuffer[j] = spi_read(0);
                  output_high(CSn);
                  putc(0x63);
                  putc(RxBuffer[0]);
                  break;
               case 0x65:
                  for(j=0;j<4;j++) RxBuffer[j] = spi_read(0);
                  output_high(CSn);
                  putc(0x65);
                  putc(RxBuffer[0]);
                  break;
               case 0x67:
                  for(j=0;j<4;j++) RxBuffer[j] = spi_read(0);
                  output_high(CSn);
                  putc(0x67);
                  putc(RxBuffer[0]);
                  break;
               case 0x69:
                  for(j=0;j<4;j++) RxBuffer[j] = spi_read(0);
                  output_high(CSn);
                  putc(0x69);
                  putc(RxBuffer[0]);
                  break;
               default:
                  output_high(CSn);
                  break;
            }
            output_low(RxLed);
            ToSend=0;
            ForceTx=FALSE;
            //CheckStatus();
            //PrintStatus();
         }  
      }
     
      // TRASMISSIONE
      //****************************************************

      if(ForceTx==TRUE){
         //Blink();
         output_high(TxLed);
         SendStrobe(STX);
         output_low(CSn);
         spi_write(TXFIFO|WrBt);
         for(i=0; i<5; i++) spi_write(TxBuffer[i]);
         output_high(CSn);
         //SendStrobe(STX);
         do{CheckStatus();/*PrintStatus();*/} while(MARCS==19);
         if(MARCS==22) SendStrobe(SFTX);
         for(i=0; i<5; i++) TxBuffer[i]=0;
         ForceTx=FALSE;
         output_low(TxLed);
      }
      
      
   }
}

void Blink(){
   for(i=0; i<10; i++){
   output_high(TxLed);
   output_high(RxLed);
   delay_ms(100);
   output_low(TxLed);
   output_low(RxLed);
   delay_ms(100);
   }
}

void CCBurstConfig(){
   char ConfReg[47] = {IOCFG2, IOCFG1, IOCFG0, FIFOTHR, SYNC1, SYNC0, PKTLEN, PKTCTRL1, PKTCTRL0, ADDR, CHANNR, FSCTRL1, FSCTRL0, FREQ2, FREQ1, FREQ0, MDMCFG4, MDMCFG3, MDMCFG2, MDMCFG1, MDMCFG0, DEVIATN, MCSM2, MCSM1, MCSM0, FOCCFG, BSCFG, AGCCTRL2, AGCCTRL1, AGCCTRL0, WOREVT1, WOREVT0, WORCTRL, FREND1, FREND0, FSCAL3, FSCAL2, FSCAL1, FSCAL0, RCCTRL1, RCCTRL0, FSTEST, PTEST, AGCTEST, TEST2, TEST1, TEST0};
   output_low(CSn);
   while(input(GDO2)) Blink();
   spi_write(0x00 | WrBt); 
   for (i=0; i<47; i++){
      spi_write(ConfReg[i]);
   }
   output_high(CSn);
}

void InitInfos(){
   char ReadRegs[0x30];
   output_low(CSn);
   spi_write(0x00|RdBt);
   for(i=0; i<0x30; i++) ReadRegs[i] = spi_read(0);
   output_high(CSn);
   printf("\n\r***************************************************************************\n\r");
   for(i=0; i<0x30; i++) printf("%X=%X\t", i, ReadRegs[i] );
   printf("\n\r***************************************************************************\n\r");
}

void CheckStatus(){ // circa 10us
   output_low(CSn);
   spi_write(PKTSTATUS);
   PacketStatus = spi_read(PKTSTATUS);
   spi_write(MARCSTATE);
   MARCS = spi_read(0);
   spi_write(TXBYTES);
   TxFIFOBytes = spi_read(0);
   spi_write(RXBYTES);
   RxFIFOBytes = spi_read(0);
   output_high(CSn);
   CRC_Ok = bit_test(PacketStatus,7);
}

void PrintStatus(){
   printf("\n\rMARCSTATE = %d, PACKETSTATUS = %X, TXFIFO = %d, RXFIFO = %d", MARCS, PacketStatus,TxFIFOBytes, RxFIFOBytes);
}

void CalibrationRoutine(){
   CheckStatus();
   if(MARCS!=1){
      SendStrobe(SIDLE);
      delay_ms(1);
   }
   SendStrobe(SCAL);
   delay_ms(1);
}

void SendStrobe(char Strobe){
   output_low(CSn);
   spi_write(Strobe);
   output_high(CSn);
}

void SetRegister(char Address, char Value){
   output_low(CSn);
   spi_write(Address|WrSg);
   spi_write(Value);
   output_high(CSn);
}   