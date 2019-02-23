#include "callback.h"


namespace demo {

void Init(Local<Object> exports, Local<Object> module) {
  NODE_SET_METHOD(exports, "callback_uv_async", RunCallback_uv_async);
  NODE_SET_METHOD(exports, "callback_uv_queue_work", RunCallback_uv_queue_work);
}


NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

}  // namespace demo