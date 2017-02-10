//
// Created by gavan on 17-2-9.
//


#include "demo.h"
#include <node.h>
#include <v8.h>
#include <uv.h>
#include <node_buffer.h>
#include <nan.h>
using namespace v8;

Persistent<Function> drawCallback;

static void fix15_to_rgba8(uint16_t *src, uint8_t *dst, int length) {
    uint8_t x1, x2, x3, x4;
    for (int i = 0; i < length; i++) {
        uint32_t r, g, b, a;

        r = *src++;
        g = *src++;
        b = *src++;
        a = *src++;

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

//        *dst++ = (r * 255 + add_r) / (1<<15);
//        *dst++ = (g * 255 + add_g) / (1<<15);
//        *dst++ = (b * 255 + add_b) / (1<<15);
//        *dst++ = (a * 255 + add_a) / (1<<15);

        x1 = (r * 255 + add_r) / (1<<15);
        x2 = (g * 255 + add_g) / (1<<15);
        x3 = (b * 255 + add_b) / (1<<15);
        x4 = (a * 255 + add_a) / (1<<15);

        if(x1 == 255 && x2 == 255 && x3 == 255){
            x4 = 0;
        }

        *dst++ = x1;
        *dst++ = x2;
        *dst++ = x3;
        *dst++ = x4;
    }
}

static void tile_callback(uint16_t *chunk, int x, int y, int tile_size, void *user_data) {
    printf("tile_callback %d, %d\n", x, y);
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    const unsigned argc = 4;
    const int size = tile_size * tile_size * 4;
    uint8_t chunk_8bit[size];
    fix15_to_rgba8(chunk, chunk_8bit, size / 4);
    Local<Value> argv[argc] = {
            Nan::NewBuffer((char*)chunk_8bit, size).ToLocalChecked(),
            Integer::New(isolate, x * tile_size),
            Integer::New(isolate, y * tile_size),
            Integer::New(isolate, tile_size)
    };
    Local<Function>::New(isolate, drawCallback)->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}

static void demoV8(const v8::FunctionCallbackInfo<Value>& args) {
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    if(args.Length() > 0 && args[0]->IsFunction()){
        Local<Function> cb = Local<Function>::Cast(args[0]);
        drawCallback.Reset(isolate, cb);
    }else{
        drawCallback.Reset();
    }
    demo(tile_callback);
}

static void Init(Handle<Object> exports) {
    Isolate* isolate = Isolate::GetCurrent();
    exports->Set(String::NewFromUtf8(isolate, "demo"), FunctionTemplate::New(isolate, demoV8)->GetFunction());
}


NODE_MODULE(demo, Init)