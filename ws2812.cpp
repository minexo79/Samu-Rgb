#include "ws2812.h"

uint8_t cnt = 0;

ws2812::ws2812(int _pixel_count)
{
    pixel_count = _pixel_count;

    spi_buffer.resize((pixel_count * 12));
}

ws2812::~ws2812()
{
    
}

int ws2812::begin()
{
    fd = open(spi_device.c_str(), O_RDWR);

    if (fd < 0) 
    {
        perror("Failed to open SPI device");
        return -1;
    }

    if (ioctl(fd, SPI_IOC_WR_MODE, &spi_mode) < 0)
    {
        perror("Failed to set SPI mode");
        return -2;
    }

    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bits) < 0)
    {
        perror("Failed to set SPI bits per word");
        return -3;
    }

    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed) < 0)
    {
        perror("Failed to set SPI speed");
        return -4;
    }

    std::cout << "SPI speed: " << spi_speed << " Hz" << std::endl;
    return 0;
}

void ws2812::setPixelColorAt(int pixel_index, color_t color)
{
    if (pixel_index > -1)
    {
        encodeByte(pixel_index, color.green);
        encodeByte(pixel_index, color.red);
        encodeByte(pixel_index, color.blue);

        cnt = 0; // reset idx counter
    }
}

void ws2812::encodeByte(int pixel_index, uint8_t byte) 
{
    uint8_t push_data = 0x0;
    for (int i = 7; i >= 0; --i)
    {
        // detect the bit value, and combine to push_data
        push_data |= ((byte >> i) & 0x1) ? 0b0111 : 0b0100; // 1: 0b0111, 0: 0b0100

        if (!(i % 2)) 
        {
            uint32_t idx = (pixel_index * 12) + (cnt++);

            // std::cout << "Push Index: " << idx << " / Push data: " << std::hex << (int)push_data << std::endl;
            spi_buffer[idx] = push_data;
            push_data = 0x0;
            continue;
        }

        // TODO: Add RST signal

        push_data <<= 4;
    }
}

int ws2812::show() 
{
    struct spi_ioc_transfer spi = {};
    memset(&spi, 0, sizeof(spi));

    spi.tx_buf          = reinterpret_cast<unsigned long>(spi_buffer.data());
    spi.len             = spi_buffer.size();
    spi.speed_hz        = SPI_SPEED;
    spi.bits_per_word   = SPI_BIT_WORD;

    if (ioctl(fd, SPI_IOC_MESSAGE(1), &spi) < 0) 
    {
        perror("SPI transfer failed");
        return -1;
    }

    return 0;
}