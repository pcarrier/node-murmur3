#include <node.h>
#include <node_buffer.h>
#include "MurmurHash3.h"

using v8::Array;
using v8::Integer;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::FunctionCallbackInfo;
using v8::Value;

void Double(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(Integer::NewFromUnsigned(isolate, 2 * args[0]->Uint32Value()));
}

// hash32(data, seed)
void Hash_32(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    uint32_t result = 0;
    const uint32_t seed = args[1]->Uint32Value();
    MurmurHash3_x86_32((void *)node::Buffer::Data(args[0]),
                       (int)node::Buffer::Length(args[0]), seed, &result);
    args.GetReturnValue().Set(Integer::NewFromUnsigned(isolate, result));
}

// hash128$32(data, seed)
void Hash_128_32(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const Local<Array> result = Array::New(isolate, 4);
    uint32_t buff[4] = { 0, 0, 0, 0 };
    const uint32_t seed = args[1]->Uint32Value();
    MurmurHash3_x86_128((void *)node::Buffer::Data(args[0]),
                        (int)node::Buffer::Length(args[0]), seed, (void *)&buff);
    result->Set(0, Integer::NewFromUnsigned(isolate, buff[0]));
    result->Set(1, Integer::NewFromUnsigned(isolate, buff[1]));
    result->Set(2, Integer::NewFromUnsigned(isolate, buff[2]));
    result->Set(3, Integer::NewFromUnsigned(isolate, buff[3]));
    args.GetReturnValue().Set(result);
}

// hash128$64(data, seed)
void Hash_128_64(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const Local<Array> result = Array::New(isolate, 4);
    uint32_t buff[4] = { 0, 0, 0, 0 };
    const uint32_t seed = args[1]->Uint32Value();
    MurmurHash3_x64_128((void *)node::Buffer::Data(args[0]),
                        (int)node::Buffer::Length(args[0]), seed, (void *)&buff);
    result->Set(0, Integer::NewFromUnsigned(isolate, buff[0]));
    result->Set(1, Integer::NewFromUnsigned(isolate, buff[1]));
    result->Set(2, Integer::NewFromUnsigned(isolate, buff[2]));
    result->Set(3, Integer::NewFromUnsigned(isolate, buff[3]));
    args.GetReturnValue().Set(result);
}

void Initialize(Local<Object> exports)
{
        NODE_SET_METHOD(exports, "$double", Double);
        NODE_SET_METHOD(exports, "hash32", Hash_32);
        NODE_SET_METHOD(exports, "hash128$32", Hash_128_32);
        NODE_SET_METHOD(exports, "hash128$64", Hash_128_64);
}

NODE_MODULE(murmur3, Initialize)
