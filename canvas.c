#include <cairo.h>
#include "canvas.h"

static cairo_surface_t* surface = 0;
static cairo_t* cr = 0;

void canvas_init(int width, int height){
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create(surface);
}

void canvas_write_to_png(const char* file_path){
    cairo_surface_write_to_png(surface, file_path);
}

void canvas_put_data(uint16_t *chunk, int x, int y, int tile_size){

}

void canvas_destroy(){
    cairo_destroy(cr);
    cairo_surface_destroy (surface);
}