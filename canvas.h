//
// Created by gavan on 17-2-9.
//

#ifndef LIBMYPAINT_CANVAS_H
#define LIBMYPAINT_CANVAS_H

#include <stdint.h>

void canvas_init(int width, int height);
void canvas_write_to_png(const char* file_path);
void canvas_put_data(uint16_t *chunk, int x, int y, int tile_size);
void canvas_destroy();

#endif //LIBMYPAINT_CANVAS_H
