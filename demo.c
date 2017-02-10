#include "libmypaint.c"
#include "mypaint-brush.h"
#include "mypaint-fixed-tiled-surface.h"

#include "utils.h" /* Not public API, just used for write_ppm to demonstrate */

#include "canvas.h"
#include "demo.h"

static void stroke_to(MyPaintBrush *brush, MyPaintSurface *surf, float x, float y) {
    float pressure = 1.0, ytilt = 0.0, xtilt = 0.0, dtime = 1.0 / 10;
    mypaint_brush_stroke_to(brush, surf, x, y, pressure, xtilt, ytilt, dtime);
}

typedef void (*TileCallback)(uint16_t *chunk, int x, int y, int tile_size, void *user_data);

static void iterate_chunks(MyPaintTiledSurface *tiled_surface, MyPaintRectangle *roi, TileCallback callback, void *user_data) {
    const int tile_size = tiled_surface->tile_size;
    printf("MyPaintRectangle roi=(%d, %d, %d, %d) %d\n", roi->x, roi->y, roi->width, roi->height, tile_size);
    int txb = roi->x / tile_size;
    int txe = (roi->x + roi->width) / tile_size;
    int tyb = roi->y / tile_size;
    int tye = (roi->y + roi->height) / tile_size;

    int tiles_per_row = txe - txb + 1;
    int number_of_tile_rows = tye - tyb + 1;
    printf("tile = tx(%d, %d) ty(%d, %d)\n", txb, txe, tyb, tye);
    MyPaintTileRequest *requests = (MyPaintTileRequest *) malloc(tiles_per_row * sizeof(MyPaintTileRequest));
    for (int ty = tyb; ty <= tye; ty++) {
        for (int tx = txb; tx <= txe; tx++) {
            MyPaintTileRequest *req = &requests[tx - txb];
            mypaint_tile_request_init(req, 0, tx, ty, TRUE);
            mypaint_tiled_surface_tile_request_start(tiled_surface, req);
        }
        for (int tx = txb; tx <= txe; tx++) {
            mypaint_tiled_surface_tile_request_end(tiled_surface, &requests[tx]);
            callback(requests[tx - txe].buffer, tx, ty, tile_size, user_data);
        }
    }
    free(requests);
}

static void tile_callback(uint16_t *chunk, int x, int y, int tile_size, void *user_data) {
    printf("tile_callback %d, %d\n", x, y);
    canvas_put_data(chunk, x, y, tile_size);
}

void demo() {
    MyPaintBrush *brush = mypaint_brush_new();
    MyPaintFixedTiledSurface *surface = mypaint_fixed_tiled_surface_new(500, 500);

    mypaint_brush_from_defaults(brush);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_H, 0.0);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_S, 0.0);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_V, 0.0);

    /* Draw a rectangle on surface with brush */
    mypaint_surface_begin_atomic((MyPaintSurface *) surface);
//    stroke_to(brush, (MyPaintSurface *)surface, 0.0, 0.0);
//    stroke_to(brush, (MyPaintSurface *)surface, 20.0, 0.0);
//    stroke_to(brush, (MyPaintSurface *)surface, 20.0, 20.0);
//    stroke_to(brush, (MyPaintSurface *)surface, 0.0, 20.0);
//    stroke_to(brush, (MyPaintSurface *)surface, 0.0, 0.0);

//    stroke_to(brush, (MyPaintSurface *) surface, 10.0, 10.0);
//    for (int i = 11; i < 200; i++) {
//        stroke_to(brush, (MyPaintSurface *) surface, i, i + 1);
//    }

    for (int i = 10; i < 50; i+=2) {
        stroke_to(brush, (MyPaintSurface *) surface, i, i);
    }

    MyPaintRectangle roi;
    mypaint_surface_end_atomic((MyPaintSurface *) surface, &roi);

    int w = surface->tiles_width * surface->parent.tile_size;
    int h = surface->tiles_height * surface->parent.tile_size;

    //TODO: 1.get tiles from roi
    //TODO: 2.tile_request tiles
    //TODO: 3.draw dirty tile buf
    canvas_init(w, h);
    iterate_chunks((MyPaintTiledSurface *) surface, &roi, tile_callback, NULL);
    canvas_write_to_png("output_canvas.png");
    canvas_destroy();


#if 0
    // FIXME: write_ppm is currently broken
    fprintf(stdout, "Writing output\n");
    write_ppm(surface, "output.ppm");
#else
    FILE *fp = fopen("output_raw.ppm", "w");
    if (!fp) {
        perror("fopen 'output_raw.ppm'");
        exit(1);
    }
    printf("Handwritten width height %d %d\n", w, h);
    fprintf(fp, "P3\n#Handwritten\n%d %d\n255\n", w, h);
    uint16_t *data = surface->tile_buffer;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            for (int c = 0; c < 4; c++) {
                if (c < 3) fprintf(fp, "%d ", (int) (*data) / 256);
                data++;
            }
        }
        fprintf(fp, "\n");
    }
#endif

    mypaint_brush_unref(brush);
    mypaint_surface_unref((MyPaintSurface *) surface);
}