// Copyright 2013 Bradley Matusiak

#include <v8.h>
#include <node.h>

using namespace node;
using namespace v8;

struct reqStruct
{
    ssize_t result;
    Persistent<Function> callback;
};

void CBWorker(uv_work_t* req)
{
    reqStruct* request = (reqStruct*)req->data;
}

void CBAfter(uv_work_t* req)
{   
    HandleScope scope;

    reqStruct* request = (reqStruct*)req->data;
    
    delete req;

    Handle<Value> argv[5];
    
    Handle<Array> keyArray = v8::Array::New(256);
            
    argv[0] = Undefined();
    
    for (unsigned i = 0; i < 256; i++)
    {
        if (GetAsyncKeyState(i) & 0x8000)
        { 
            keyArray->Set(i, v8::Integer::New(1));
        }else 
            keyArray->Set(i, v8::Integer::New(0));
    }
    
    argv[1] = keyArray;
    
    argv[2] = Integer::New(GetKeyState(VK_NUMLOCK) & 0x0001);
    
    argv[3] = Integer::New(GetKeyState(VK_CAPITAL) & 0x0001);
    
    argv[4] = Integer::New(GetKeyState(VK_SCROLL) & 0x0001);
    
    TryCatch try_catch;

    request->callback->Call(Context::GetCurrent()->Global(), 5, argv);

    if (try_catch.HasCaught()) 
    {
        FatalException(try_catch);
    }

    request->callback.Dispose();

    delete request;
}


static Handle<Value> KeyMap(const Arguments& args)
{

    HandleScope scope;

    if ( args[0]->IsFunction() )
    {
        Local<Function> callback = Local<Function>::Cast(args[0]);

        reqStruct* request = new reqStruct;
        
        request->callback = Persistent<Function>::New(callback);

        uv_work_t* req = new uv_work_t();
        
        req->data = request;

        uv_queue_work(uv_default_loop(), req, CBWorker, CBAfter);
    }
    else
    {
        return ThrowException(Exception::TypeError(String::New("Callback missing")));
    }

    return Undefined();
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "KeyMap", KeyMap);
}

NODE_MODULE(binding, init);