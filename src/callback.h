#ifndef _CALLBACL_H_
#define  _CALLBACL_H_

#include <node.h>
#include <stdlib.h>
#include "uv.h"
#include <windows.h>


using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Persistent;
using v8::Null;
using v8::Object;
using v8::String;
using v8::Value;

void RunCallback_uv_async(const FunctionCallbackInfo<Value>&);
void RunCallback_uv_queue_work(const FunctionCallbackInfo<Value>&);

#endif