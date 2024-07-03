#include "utils.h"

typedef struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;


class ws2812
{
    public:
        ws2812(int _pixel_count);
        ~ws2812();
        int begin();
        void setPixelColor(color_t color);
        int show();
    private:
        int pixel_count             = 1;
        int fd                      = 0;
        std::string spi_device      = SPI_DEVICE;
        uint8_t spi_mode            = SPI_MODE;
        uint8_t spi_bits            = SPI_BIT_WORD;
        uint32_t spi_speed          = SPI_SPEED;
        std::vector<uint8_t>& spi_buffer = *new std::vector<uint8_t>;

        void encodeByte(uint8_t byte);
};