#include "callback.h"


Persistent<Function> cb;
uv_async_t async;


//Step two
void async_callback_handler(uv_async_t *handle){
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope handleScope(isolate);

  //execute the callback
  const unsigned argc = 1;
  Local<Value> argv[] = { String::NewFromUtf8(isolate, "hello world") };
  Local<Function> callback = Local<Function>::New(isolate, cb);
  callback->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}


DWORD WINAPI ThreadFunc(void *data)
{
	while (true)
	{
		Sleep(500);

		//Step Four
		uv_async_send(&async);
	}
  return 0;
}


void RunCallback_uv_async(const FunctionCallbackInfo<Value>& args) {

  //Store callback
  Isolate* isolate = args.GetIsolate();
  Local<Function> callback = Local<Function>::Cast(args[0]);
  cb.Reset(isolate, callback);

  //Step one
  uv_async_init(uv_default_loop(), &async, async_callback_handler);

  //Step three
  CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
}