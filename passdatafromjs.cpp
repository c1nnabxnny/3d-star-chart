#include <v8.h>
#include <fstream>
#include <iostream>

using namespace v8;

int main() {
    // create a new V8 instance
    V8::InitializeICUDefaultLocation("");
    V8::InitializeExternalStartupData("");
    Platform* platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();

    // create a new isolate and context
    Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
        v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    Isolate* isolate = Isolate::New(create_params);
    {
        Isolate::Scope isolate_scope(isolate);
        HandleScope handle_scope(isolate);
        Local<Context> context = Context::New(isolate);
        Context::Scope context_scope(context);

        // read the JavaScript file
        std::ifstream file("coordinates.js");
        if (!file.good()) {
            std::cout << "Error: Unable to open file coordinates.js" << std::endl;
            return -1;
        }
        std::string contents((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());

        // Compile the script
        TryCatch try_catch(isolate);
        Local<Script> script;
        {
            script = Script::Compile(context,
                                    String::NewFromUtf8(isolate, contents.c_str(), NewStringType::kNormal)
                                    .ToLocalChecked()).ToLocalChecked();
        }
        if (script.IsEmpty()) {
            String::Utf8Value error(isolate, try_catch.Exception());
            std::cout << "Error: " << *error << std::endl;
            return -1;
        }

        // Run the script
        Local<Value> result;
        {
            result = script->Run(context).ToLocalChecked();
        }
        if (result.IsEmpty()) {
            String::Utf8Value error(isolate, try_catch.Exception());
            std::cout << "Error: " << *error << std::endl;
            return -1;
        }

        // Extract the exported module
        Local<Object> global = context->Global();
        Local<Value> exported_module = global
