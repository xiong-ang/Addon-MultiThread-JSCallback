#include "callback.h"

Persistent<Function> _cb;
uv_work_t  request;


void WorkAsync(uv_work_t *req)
{
    Sleep(500);
}

void WorkAsyncComplete(uv_work_t *req, int status)
{
  Isolate * isolate = Isolate::GetCurrent();
  v8::HandleScope handleScope(isolate); // Required for Node 4.x

  //execute the callback
  const unsigned argc = 1;
  Local<Value> argv[] = { String::NewFromUtf8(isolate, "hello world") };
  Local<Function> callback = Local<Function>::New(isolate, _cb);
  callback->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}


void RunCallback_uv_queue_work(const FunctionCallbackInfo<Value>& args) {

  //Store callback
  Isolate* isolate = args.GetIsolate();
  Local<Function> callback = Local<Function>::Cast(args[0]);
  _cb.Reset(isolate, callback);


  // kick of the worker thread
  uv_queue_work(uv_default_loop(), &request, WorkAsync, WorkAsyncComplete);
}