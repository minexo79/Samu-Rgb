#include <iostream>
#include <cstring>
#include <vector>

extern "C"
{
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
    #include <linux/spi/spidev.h>
}

#define SPI_DEVICE      "/dev/spidev0.0"
#define SPI_MODE        SPI_MODE_0      // CPOL = SPI_MODE_0
#define SPI_BIT_WORD    8               // 8 bits per word
#define SPI_SPEED       6400000         // 6.4MHz for WS2812B