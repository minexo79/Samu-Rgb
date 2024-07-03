#include "utils.h"
#include "ws2812.h"

ws2812 ws2812_strip(1);

color_t color[3] = 
{
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255}
};
int color_index = 0;

int main (void)
{
    std::cout << "Samu RGB Program Init" << std::endl;

    ws2812_strip.begin();

    for(;;)
    {
        std::cout << "Color index: " << color_index << std::endl;
        ws2812_strip.setPixelColorAt(0, color[color_index]);
        ws2812_strip.show();

        color_index = (color_index + 1) % 3;

        sleep(1);
    }


    return 0;
}