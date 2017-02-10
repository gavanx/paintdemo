//
// Created by gavan on 17-2-9.
//


#include "demo.h"
#include <node.h>
#include <v8.h>
#include <uv.h>
using namespace v8;

static void demoV8(const v8::FunctionCallbackInfo<Value>& args) {
    demo();
}

static void Init(Handle<Object> exports) {
    Isolate* isolate = Isolate::GetCurrent();
    exports->Set(String::NewFromUtf8(isolate, "demo"), FunctionTemplate::New(isolate, demoV8)->GetFunction());
}


NODE_MODULE(demo, Init)