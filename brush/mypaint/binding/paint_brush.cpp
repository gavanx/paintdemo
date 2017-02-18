//
// Created by gavan on 17-2-18.
//
#include "paint_brush.h"

using namespace v8;

//TODO: refactor common binding
static void addMethod(Isolate* isolate, Local<Object> &obj, const char* methodName, FunctionCallback method){
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, method);
    Local<Function> fn = tpl->GetFunction();
    fn->SetName(String::NewFromUtf8(isolate, methodName));
    obj->Set(String::NewFromUtf8(isolate, methodName), fn);
}

static void init(const v8::FunctionCallbackInfo<Value>& args) {
}

static void stroke(const v8::FunctionCallbackInfo<Value>& args) {
}

static void dispose(const v8::FunctionCallbackInfo<Value>& args) {
}

void exportPaintBrush(Handle<Object> exports) {
    Isolate* isolate = Isolate::GetCurrent();
    Local<Object> PaintBrush = Object::New(isolate);
    addMethod(isolate, PaintBrush, "init", init);
    addMethod(isolate, PaintBrush, "stroke", stroke);
    addMethod(isolate, PaintBrush, "dispose", dispose);

    exports->Set(String::NewFromUtf8(isolate, "PaintBrush"), PaintBrush);
}