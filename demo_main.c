//
// Created by gavan on 17-2-9.
//

#include "demo.h"
#include <stdio.h>

static void fix15_to_rgba8(uint16_t *src, uint8_t *dst, int length) {
    for (int i = 0; i < length; i++) {
        uint32_t r, g, b, a;

        r = *src;
        g = *src;
        b = *src;
        a = *src;

        // un-premultiply alpha (with rounding)
        if (a != 0) {
            r = ((r << 15) + a / 2) / a;
            g = ((g << 15) + a / 2) / a;
            b = ((b << 15) + a / 2) / a;
        } else {
            r = g = b = 0;
        }

        // Variant A) rounding
        const uint32_t add_r = (1 << 15) / 2;
        const uint32_t add_g = (1 << 15) / 2;
        const uint32_t add_b = (1 << 15) / 2;
        const uint32_t add_a = (1 << 15) / 2;

        *dst++ = (r * 255 + add_r) / (1 << 15);
        *dst++ = (g * 255 + add_g) / (1 << 15);
        *dst++ = (b * 255 + add_b) / (1 << 15);
        *dst++ = (a * 255 + add_a) / (1 << 15);
    }
}

static void tile_callback(uint16_t *chunk, int x, int y, int tile_size, void *user_data) {
    const int size = tile_size * tile_size;
    printf("tile_callback %d, %d, %d\n", x, y, size);
    uint8_t chunk_8bit[size * 4];
    fix15_to_rgba8(chunk, chunk_8bit, size);
}


void draw_test(uint16_t color_r, uint16_t color_g, uint16_t color_b, uint16_t opacity) {
    uint32_t opa_a = mask[0] * (uint32_t) opacity / (1 << 15); // topAlpha
    uint32_t opa_b = (1 << 15) - opa_a; // bottomAlpha
    rgba[3] = opa_a + opa_b * rgba[3] / (1 << 15);
    rgba[0] = (opa_a * color_r + opa_b * rgba[0]) / (1 << 15);
    rgba[1] = (opa_a * color_g + opa_b * rgba[1]) / (1 << 15);
    rgba[2] = (opa_a * color_b + opa_b * rgba[2]) / (1 << 15);
}

int test_demo_rr(float rr, float hardness) {
    float opa;
    if (rr > 1) {
        opa = 0;
    } else if (rr < hardness) {
        opa = rr + 1 - (rr / hardness);
    } else {
        opa = hardness / (1 - hardness) * (1 - rr);
    }
    const uint16_t opa_ = opa * (1 << 15);
    printf("test_demo rr=%f opa=%f opa_=%d \n", rr, opa, opa_);
}

int test_main() {
    float hardness = 0.8f;
    for (float rr = 0.005f; rr <= 1.006f; rr += 0.005f) {
        test_demo_rr(rr, hardness);
    }
}

int main(int argc, char argv[]) {
    test_main();

//    demo(tile_callback);
}