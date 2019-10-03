
#define DDR_SPI DDRB
#define DD_SS PB4
#define DD_MOSI PB5
#define DD_MISO PB6
#define DD_SCK PB7

void SPI_init();
void SPI_transmit(char cData);
char SPI_receive(void);
