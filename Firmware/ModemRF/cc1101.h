// Chipcon
// Product = CC1101
// Chip version = A   (VERSION = 0x04)
// Crystal accuracy = 10 ppm
// X-tal frequency = 26 MHz
// RF output power = 0 dBm
// RX filterbandwidth = 541.666667 kHz
// Deviation = 127 kHz
// Datarate = 249.938965 kBaud
// Modulation = (1) 2-GFSK
// Manchester enable = (0) Manchester disabled
// RF Frequency = 868.299866 MHz
// Channel spacing = 199.951172 kHz
// Channel number = 0
// Optimization = Sensitivity
// Sync mode = (3) 30/32 sync word bits detected
// Format of RX/TX data = (0) Normal mode, use FIFOs for RX and TX
// CRC operation = (1) CRC calculation in TX and CRC check in RX enabled
// Forward Error Correction = (0) FEC disabled
// Length configuration = (1) Variable length packets, packet length configured by the first received byte after sync word.
// Packetlength = 255
// Preamble count = (2)  4 bytes
// Append status = 1
// Address check = (0) No address check
// FIFO autoflush = 1
// Device address = 0
// GDO0 signal selection = ( 6) Asserts when sync word has been sent / received, and de-asserts at the end of the packet
// GDO2 signal selection = (41) CHIP_RDY
#define FSCTRL1  0x0C  // Frequency synthesizer control.
#define FSCTRL0  0x00  // Frequency synthesizer control.
#define FREQ2    0x21  // Frequency control word, high byte.
#define FREQ1    0x65  // Frequency control word, middle byte.
#define FREQ0    0x6A  // Frequency control word, low byte.
#define MDMCFG4  0x2D  // Modem configuration.
#define MDMCFG3  0x3B  // Modem configuration.
#define MDMCFG2  0x13  // Modem configuration.
#define MDMCFG1  0x22  // Modem configuration.
#define MDMCFG0  0xF8  // Modem configuration.
#define CHANNR   0x00  // Channel number.
#define DEVIATN  0x62  // Modem deviation setting (when FSK modulation is enabled).
#define FREND1   0xB6  // Front end RX configuration.
#define FREND0   0x10  // Front end RX configuration.
#define MCSM0    0x18  // Main Radio Control State Machine configuration.
#define FOCCFG   0x1D  // Frequency Offset Compensation Configuration.
#define BSCFG    0x1C  // Bit synchronization Configuration.
#define AGCCTRL2 0xC7  // AGC control.
#define AGCCTRL1 0x00  // AGC control.
#define AGCCTRL0 0xB0  // AGC control.
#define FSCAL3   0xEA  // Frequency synthesizer calibration.
#define FSCAL2   0x2A  // Frequency synthesizer calibration.
#define FSCAL1   0x00  // Frequency synthesizer calibration.
#define FSCAL0   0x1F  // Frequency synthesizer calibration.
#define FSTEST   0x59  // Frequency synthesizer calibration.
#define TEST2    0x88  // Various test settings.
#define TEST1    0x31  // Various test settings.
#define TEST0    0x09  // Various test settings.
#define FIFOTHR  0x07  // RXFIFO and TXFIFO thresholds.
#define IOCFG2   0x29  // GDO2 output pin configuration.
#define IOCFG0D  0x06  // GDO0 output pin configuration. Refer to SmartRF® Studio User Manual for detailed pseudo register explanation.
#define PKTCTRL1 0x0C  // Packet automation control.
#define PKTCTRL0 0x05  // Packet automation control.
#define ADDR     0x00  // Device address.
#define PKTLEN   0xFF  // Packet length.
