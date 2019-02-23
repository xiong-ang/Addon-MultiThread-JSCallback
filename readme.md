# Addon-MultiThread-JSCallback

> 当我们写Nodejs addons时，只要稍微复杂一点的工程，通常会碰到多线程模型，需要利用工作线程来进行JS端代码的回调。而v8工作在单线程模式下，为了进行有效回调，最理想的方式**不是通过工作线程直接回调，而是通过工作线程委托v8线程进行回调**。为了有效回调，我们需要：1.存储回调信息（回调函数，参数）；2.工作线程与v8线程交互，实现回调委托。

## 存储回调信息

```c++
Persistent<Function> cb;

...

void RunCallback(const FunctionCallbackInfo<Value>& args) {

  //Store callback
  Isolate* isolate = args.GetIsolate();
  Local<Function> callback = Local<Function>::Cast(args[0]);
  cb.Reset(isolate, callback);

  ...
}

```

## 工作线程委托v8线程回调
#### uv_async方式
```c++
uv_async_t async;

//Step one: v8 thread init uv_async
//async_callback_handler could be called in v8 thread 
uv_async_init(uv_default_loop(), &async, async_callback_handler);


//Step two: call js callback in async_callback_handler
void async_callback_handler(uv_async_t *handle){
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::HandleScope handleScope(isolate);

  //execute the callback
  const unsigned argc = 1;
  Local<Value> argv[] = { String::NewFromUtf8(isolate, "hello world") };
  Local<Function> callback = Local<Function>::New(isolate, cb);
  callback->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}


//Step three: call uv_async_send in worker thread,
//uv_async_send could be called in worked thread, and will trigger async_callback_handler in v8 thread
uv_async_send(&async);
```
#### uv_queue_work方式
```c++
// kick of the worker thread
// WorkAsync will run in worker thread
// After WorkAsync over, WorkAsyncComplete will be called in v8 thread
uv_queue_work(uv_default_loop(), &request, WorkAsync, WorkAsyncComplete);
```


## Reference
1. [Asynchronous addons](https://nodeaddons.com/c-processing-from-node-js-part-4-asynchronous-addons/)
2. [V8 Multithreaded function](https://stackoverflow.com/questions/31207454/v8-multithreaded-function)
3. [Callback NodeJS Javascript function from multithreaded C++ addon](https://stackoverflow.com/questions/36987273/callback-nodejs-javascript-function-from-multithreaded-c-addon)