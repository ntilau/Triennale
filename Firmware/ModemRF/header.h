#include <cc1101.h>

// Registri non definiti da SmartRF
#define  IOCFG1   0x2E
#define  IOCFG0   IOCFG0D
#define  SYNC1    0xD3
#define  SYNC0    0x91
#define  MCSM2    0x07
#define  MCSM1    0x30
#define  WOREVT1  0x87
#define  WOREVT0  0x6B
#define  WORCTRL  0xF8
#define  RCCTRL1  0x41
#define  RCCTRL0  0x00
#define  PTEST    0x7F
#define  AGCTEST  0x3F

// spi_write(REGNAME | ACCESSTYPE)
#define  WrSg 0x00 // Scrittura singolo reg
#define  WrBt 0x40 // Scrittura a burst su reg consecutivi
#define  RdSg 0x80 // Lettura singolo reg
#define  RdBt 0xC0 // Lettura a burst

// Indirizzi
#define  _IOCFG2   0x00
#define  _IOCFG1   0x01
#define  _IOCFG0   0x02
#define  _FIFOTHR  0x03
#define  _SYNC1    0x04
#define  _SYNC0    0x05
#define  _PKTLEN   0x06
#define  _PKTCTRL1 0x07
#define  _PKTCTRL0 0x08
#define  _ADDR     0x09
#define  _CHANNR   0x0A
#define  _FSCTRL1  0x0B
#define  _FSCTRL0  0x0C
#define  _FREQ2    0x0D
#define  _FREQ1    0x0E
#define  _FREQ0    0x0F
#define  _MDMCFG4  0x10
#define  _MDMCFG3  0x11
#define  _MDMCFG2  0x12
#define  _MDMCFG1  0x13
#define  _MDMCFG0  0x14
#define  _DEVIATN  0x15
#define  _MCSM2    0x16
#define  _MCSM1    0x17
#define  _MCSM0    0x18
#define  _FOCCFG   0x19
#define  _BSCFG    0x1A
#define  _AGCTRL2  0X1B
#define  _AGCTRL1  0X1C
#define  _AGCTRL0  0X1D
#define  _WOREVT1  0X1E
#define  _WOREVT0  0X1F
#define  _WORCTRL  0X20
#define  _FREND1   0X21
#define  _FREND0   0X22
#define  _FSCAL3   0X23
#define  _FSCAL2   0X24
#define  _FSCAL1   0X25
#define  _FSCAL0   0X26
#define  _RCCTRL1  0X27
#define  _RCCTRL0  0X28
#define  _FSTEST   0X29
#define  _PTEST    0X2A
#define  _AGCTEST  0X2B
#define  _TEST2    0X2C
#define  _TEST1    0X2D
#define  _TEST0    0X2E

// Strobes
#define  SRES     0X30
#define  SFSTXON  0X31
#define  SXOFF    0X32
#define  SCAL     0X33
#define  SRX      0X34
#define  STX      0X35
#define  SIDLE    0X36
                      
#define  SWORD    0X38 
#define  SPWD     0X39
#define  SFRX     0X3A
#define  SFTX     0X3B
#define  SWORRST  0X3C
#define  SNOP     0X3D
#define  PATABLE  0X3E
#define  TXFIFO   0X3F
#define  RXFIFO   0X3F

#define  PARTNUM  SRES|RdBt
#define  VERSION  SFSTXON|RdBt
#define  FREQEST  SXOFF|RdBt
#define  LQI   SCAL|RdBt
#define  RSSI  SRX|RdBt
#define  MARCSTATE   STX|RdBt
#define  WORTIME1 SIDLE|RdBt
#define  WORTIME0 0X37|RdBt
#define  PKTSTATUS   SWORD|RdBt
#define  VCO_VC_DAC  SPWD|RdBt
#define  TXBYTES  SFRX|RdBt
#define  RXBYTES  SFTX|RdBt
#define  RCCTRL1_STATUS SWORRST|RdBt
#define  RCCTRL0_STATUS SNOP|RdBt