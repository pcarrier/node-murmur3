
#include <node.h>
#include <nan.h>
#include "MurmurHash3.h"

using namespace v8;


void Hash32(const Nan::FunctionCallbackInfo<Value>& info) {
  uint32_t result = 0;
  const uint32_t seed = info[1]->Uint32Value();
  MurmurHash3_x86_32((void *)node::Buffer::Data(info[0]),
                      (int)node::Buffer::Length(info[0]), seed, &result);

  Local<Number> num = Nan::New(result);

  info.GetReturnValue().Set(num);
}

void Hash_128_32(const Nan::FunctionCallbackInfo<Value>& info) {
  Local<Array> result = Nan::New<Array>(4);
  uint32_t buff[4] = { 0, 0, 0, 0 };
  const uint32_t seed = info[1]->Uint32Value();
  MurmurHash3_x86_128((void *)node::Buffer::Data(info[0]),
                      (int)node::Buffer::Length(info[0]), seed, (void *)&buff);
  result->Set(0, Integer::NewFromUnsigned(Isolate::GetCurrent(), buff[0]));
  result->Set(1, Integer::NewFromUnsigned(Isolate::GetCurrent(), buff[1]));
  result->Set(2, Integer::NewFromUnsigned(Isolate::GetCurrent(), buff[2]));
  result->Set(3, Integer::NewFromUnsigned(Isolate::GetCurrent(), buff[3]));

  info.GetReturnValue().Set(result);
}

void Hash_128_64(const Nan::FunctionCallbackInfo<Value>& info) {
  Local<Array> result = Nan::New<Array>(4);
  uint32_t buff[4] = { 0, 0, 0, 0 };
  const uint32_t seed = info[1]->Uint32Value();
  MurmurHash3_x64_128((void *)node::Buffer::Data(info[0]),
                      (int)node::Buffer::Length(info[0]), seed, (void *)&buff);
  result->Set(0, Integer::NewFromUnsigned(Isolate::GetCurrent(), buff[0]));
  result->Set(1, Integer::NewFromUnsigned(Isolate::GetCurrent(), buff[1]));
  result->Set(2, Integer::NewFromUnsigned(Isolate::GetCurrent(), buff[2]));
  result->Set(3, Integer::NewFromUnsigned(Isolate::GetCurrent(), buff[3]));

  info.GetReturnValue().Set(result);
}

void Init(Local<Object> exports) {
  exports->Set(Nan::New("hash32").ToLocalChecked(),
              Nan::New<FunctionTemplate>(Hash32)->GetFunction());
  exports->Set(Nan::New("hash128$32").ToLocalChecked(),
              Nan::New<FunctionTemplate>(Hash_128_32)->GetFunction());
  exports->Set(Nan::New("hash128$64").ToLocalChecked(),
               Nan::New<FunctionTemplate>(Hash_128_64)->GetFunction());
}

NODE_MODULE(addon, Init)
