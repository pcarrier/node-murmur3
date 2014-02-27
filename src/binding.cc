#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include "MurmurHash3.h"

using v8::Arguments;
using v8::Array;
using v8::Exception;
using v8::Handle;
using v8::HandleScope;
using v8::Integer;
using v8::Object;
using v8::String;
using v8::ThrowException;
using v8::Value;

using node::Buffer;

// hash32(data, seed)
Handle < Value > Hash_32(const Arguments & args)
{
        HandleScope scope;
        uint32_t result = 0;
        const uint32_t seed = args[1]->Uint32Value();
        MurmurHash3_x86_32((void *)Buffer::Data(args[0]),
                           (int)Buffer::Length(args[0]), seed, &result);
        return scope.Close(Integer::NewFromUnsigned(result));
}

// hash128$32(data, seed)
Handle < Value > Hash_128_32(const Arguments & args)
{
        HandleScope scope;
        const Handle < Array > result = Array::New(4);
        uint32_t buff[4] = { 0, 0, 0, 0 };
        const uint32_t seed = args[1]->Uint32Value();
        MurmurHash3_x86_128((void *)Buffer::Data(args[0]),
                            (int)Buffer::Length(args[0]), seed, (void *)&buff);
        result->Set(0, Integer::NewFromUnsigned(buff[0]));
        result->Set(1, Integer::NewFromUnsigned(buff[1]));
        result->Set(2, Integer::NewFromUnsigned(buff[2]));
        result->Set(3, Integer::NewFromUnsigned(buff[3]));
        return scope.Close(result);
}

// hash128$64(data, seed)
Handle < Value > Hash_128_64(const Arguments & args)
{
        HandleScope scope;
        const Handle < Array > result = Array::New(4);
        uint32_t buff[4] = { 0, 0, 0, 0 };
        const uint32_t seed = args[1]->Uint32Value();
        MurmurHash3_x64_128((void *)Buffer::Data(args[0]),
                            (int)Buffer::Length(args[0]), seed, (void *)&buff);
        result->Set(0, Integer::NewFromUnsigned(buff[0]));
        result->Set(1, Integer::NewFromUnsigned(buff[1]));
        result->Set(2, Integer::NewFromUnsigned(buff[2]));
        result->Set(3, Integer::NewFromUnsigned(buff[3]));
        return scope.Close(result);
}

void RegisterModule(Handle < Object > exports)
{
        NODE_SET_METHOD(exports, "hash32", Hash_32);
        NODE_SET_METHOD(exports, "hash128$32", Hash_128_32);
        NODE_SET_METHOD(exports, "hash128$64", Hash_128_64);
}

NODE_MODULE(murmur3, RegisterModule);
