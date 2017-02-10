//
// Created by gavan on 17-2-9.
//


#include "demo.h"
#include <node.h>
#include <v8.h>
#include <uv.h>
using namespace v8;

Persistent<Function> drawCallback;

static void tile_callback(uint16_t *chunk, int x, int y, int tile_size, void *user_data) {
    printf("tile_callback %d, %d\n", x, y);
    Isolate *isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);
    const unsigned argc = 2;
    Local<Value> argv[argc] = {
            Integer::New(isolate, x),
            Integer::New(isolate, y)
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