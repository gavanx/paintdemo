#include "libmypaint.c"
#include "mypaint-brush.h"
#include "mypaint-fixed-tiled-surface.h"

#include "utils.h" /* Not public API, just used for write_ppm to demonstrate */

#include "canvas.h"
#include "demo.h"
#include <time.h>

static void stroke_to(MyPaintBrush *brush, MyPaintSurface *surf, float x, float y) {
    float pressure = 1.0, ytilt = 0.0, xtilt = 0.0, dtime = 1.0 / 10;
    mypaint_brush_stroke_to(brush, surf, x, y, pressure, xtilt, ytilt, dtime);
}


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
            callback(requests[tx - txb].buffer, tx, ty, tile_size, user_data);
        }
    }
    free(requests);
}

static void tile_callback(uint16_t *chunk, int x, int y, int tile_size, void *user_data) {
    printf("tile_callback %d, %d\n", x, y);
    canvas_put_data(chunk, x, y, tile_size);
}

static int randx(int min, int max) {
    return rand() / (float) (RAND_MAX) * (max - min) + min;
}

char *read_file(const char *path) {
    long file_size = -1L;
    FILE *file = fopen(path, "r");

    if (!file) {
        printf("could not open '%s'\n", path);
        perror("fopen");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    char *buffer = (char *) malloc(sizeof(char) * file_size);
    size_t result = fread(buffer, 1, file_size, file);

    fclose(file);

    if (!result) {
        free(buffer);
        return NULL;
    }
    return buffer;
}


void demo(TileCallback tileCallback) {
    MyPaintBrush *brush = mypaint_brush_new();
    MyPaintFixedTiledSurface *surface = mypaint_fixed_tiled_surface_new(1024, 768);

    const char *path = "/home/data/work/sharp/nw/paint/libmypaint/tests/brushes/calligraphy.myb";
//    path = "../../../tests/brushes/charcoal.myb";
//    path = "../../../tests/brushes/marker_fat.myb";
//    path = "../../../tests/brushes/knife.myb";
//    path = "../../../tests/brushes/pen.myb";
    mypaint_brush_from_string(brush, read_file(path));
//    mypaint_brush_from_defaults(brush);


    // student: #70da65
    float r = 0.2902 , g = 0.5647, b = 0.8863;// teacher: #4a90e2  '0.2902', '0.5647', '0.8863'
//    float r = 1.0, g = 0.0, b = 0.0;
    rgb_to_hsv_float(&r, &g, &b);
    printf("rgb_to_hsv_float h s v %f %f %f\n", r, g, b);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_H, r);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_S, g);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_V, b);

    srand((unsigned) time(NULL));

    /* Draw a rectangle on surface with brush */
    mypaint_surface_begin_atomic((MyPaintSurface *) surface);

    int bPoint = 0;

    if (bPoint || 1) {
        stroke_to(brush, (MyPaintSurface *) surface, 10.0, 10.0);
        stroke_to(brush, (MyPaintSurface *) surface, 15.0, 10.0);
//    stroke_to(brush, (MyPaintSurface *) surface, 200.0, 200.0);
//    stroke_to(brush, (MyPaintSurface *) surface, 0.0, 200.0);
//    stroke_to(brush, (MyPaintSurface *) surface, 0.0, 0.0);
    }

    if(!bPoint){
//    stroke_to(brush, (MyPaintSurface *) surface, 10.0, 10.0);
        int lastx = 11;
        int lasty = 11;
        int count = 0;
        while (count < 1115 && lastx < 1024 && lasty < 768) {
            count++;
            lastx = randx(lastx - 6, lastx + 16);
            lasty = randx(lasty - 6, lasty + 16);
            stroke_to(brush, (MyPaintSurface *) surface, lastx, lasty);
        }

        count = 0;
        while (count < 1115 && lastx > 0 && lasty > 0) {
            count++;
            lastx = randx(lastx - 16, lastx + 6);
            lasty = randx(lasty - 16, lasty + 6);
            stroke_to(brush, (MyPaintSurface *) surface, lastx, lasty);
        }
    }



    r = 1.0, g = 0.0, b = 0.0;
    rgb_to_hsv_float(&r, &g, &b);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_H, r);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_S, g);
    mypaint_brush_set_base_value(brush, MYPAINT_BRUSH_SETTING_COLOR_V, b);
    if(1){
        for (int i = 10; i < 500; i += 1) {
            stroke_to(brush, (MyPaintSurface *) surface, i, 500 - i);
        }
    }

    MyPaintRectangle roi;
    mypaint_surface_end_atomic((MyPaintSurface *) surface, &roi);

    printf("randx %d\n", randx(2, 6));

    int w = surface->tiles_width * surface->parent.tile_size;
    int h = surface->tiles_height * surface->parent.tile_size;

    //TODO: 1.get tiles from roi
    //TODO: 2.tile_request tiles
    //TODO: 3.draw dirty tile buf
    canvas_init(w, h);
    iterate_chunks((MyPaintTiledSurface *) surface, &roi, tileCallback, NULL);
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