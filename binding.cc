// Copyright 2013 Bradley Matusiak

#pragma comment (lib, "user32.lib") //Manually add this librar

#include <v8.h>
#include <node.h>

using namespace node;
using namespace v8;

static Handle<Value> KeyMap(const Arguments& args) {
    HandleScope scope;
    
    Local<Function> cb = Local<Function>::Cast(args[0]);
    
    Handle<Value> argv[6];
    
    Handle<Array> keyArray = v8::Array::New(256);
            
    argv[0] = Undefined();
    
    for (unsigned i = 0; i < 256; i++)
    {
        if (GetAsyncKeyState(i) & 0x8000)
        { 
            keyArray->Set(i, v8::Integer::New(1));
        }
        else 
            keyArray->Set(i, v8::Integer::New(0));
    }
    
    argv[1] = keyArray;
    
    argv[2] = Integer::New(GetKeyState(VK_NUMLOCK) & 0x0001);
    
    argv[3] = Integer::New(GetKeyState(VK_CAPITAL) & 0x0001);
    
    argv[4] = Integer::New(GetKeyState(VK_SCROLL) & 0x0001);
    
    POINT mousePos;
    
    Handle<Array> mouseCordsArray = v8::Array::New(2);
    
    if (GetCursorPos(&mousePos))
    {
        mouseCordsArray->Set(0, v8::Integer::New(mousePos.x));
         
        mouseCordsArray->Set(1, v8::Integer::New(mousePos.y));
         
        argv[5] = mouseCordsArray;
    }
    else
    {
        mouseCordsArray->Set(0, v8::Integer::New(-1));
        
        mouseCordsArray->Set(1, v8::Integer::New(-1));
        
        argv[5] = mouseCordsArray;
    }
    
    cb->Call(Context::GetCurrent()->Global(), 6, argv);
    
    return Undefined();
}
void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "KeyMap", KeyMap);
}

NODE_MODULE(binding, init);