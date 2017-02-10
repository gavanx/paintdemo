//
// Created by gavan on 17-2-9.
//

#include "demo.h"

static void fix15_to_rgba8(uint16_t *src, uint8_t *dst, int length)
{
    for (int i = 0; i < length; i++) {
        uint32_t r, g, b, a;

        r = *src;
        g = *src;
        b = *src;
        a = *src;

        // un-premultiply alpha (with rounding)
        if (a != 0) {
            r = ((r << 15) + a/2) / a;
            g = ((g << 15) + a/2) / a;
            b = ((b << 15) + a/2) / a;
        } else {
            r = g = b = 0;
        }

        // Variant A) rounding
        const uint32_t add_r = (1<<15)/2;
        const uint32_t add_g = (1<<15)/2;
        const uint32_t add_b = (1<<15)/2;
        const uint32_t add_a = (1<<15)/2;

        *dst++ = (r * 255 + add_r) / (1<<15);
        *dst++ = (g * 255 + add_g) / (1<<15);
        *dst++ = (b * 255 + add_b) / (1<<15);
        *dst++ = (a * 255 + add_a) / (1<<15);
    }
}

static void tile_callback(uint16_t *chunk, int x, int y, int tile_size, void *user_data) {
    const int size = tile_size * tile_size;
    printf("tile_callback %d, %d, %d\n", x, y, size);
    uint8_t chunk_8bit[size * 4];
    fix15_to_rgba8(chunk, chunk_8bit, size);
}

int main(int argc, char argv[]){
    demo(tile_callback);
}