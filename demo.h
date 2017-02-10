//
// Created by gavan on 17-2-9.
//

#ifndef LIBMYPAINT_DEMO_H_H
#define LIBMYPAINT_DEMO_H_H

#include <mypaint-glib-compat.h>
#include <stdint.h>
G_BEGIN_DECLS

typedef void (*TileCallback)(uint16_t *chunk, int x, int y, int tile_size, void *user_data);

void demo(TileCallback tileCallback);

G_END_DECLS

#endif //LIBMYPAINT_DEMO_H_H
