#include <sstream>

#include "contracts.h"

using namespace std;
using namespace v8;


bool Contracts::RequireNumberOfArguments(const v8::FunctionCallbackInfo<Value>& args, int requiredNumberOfArguments)
{
    Isolate* isolate = args.GetIsolate();

    if (args.Length() < requiredNumberOfArguments)
    {
        ostringstream exceptionMessageStream;
        exceptionMessageStream << "Function expects " << requiredNumberOfArguments << " parameters.";

        string exceptionMessage = exceptionMessageStream.str();

        Local<Value> exception = Exception::Error(String::NewFromUtf8(isolate, exceptionMessage.c_str()));
        isolate->ThrowException(exception);

        return false;
    }

    return true;
}

bool Contracts::RequireObjectArgument(const v8::FunctionCallbackInfo<Value>& args, int argumentIndex)
{
    Isolate* isolate = args.GetIsolate();

    if (!args[argumentIndex]->IsObject())
    {
        ostringstream exceptionMessageStream;
        exceptionMessageStream << "Argument " << argumentIndex + 1 << " must be of type object.";

        string exceptionMessage = exceptionMessageStream.str();

        Local<Value> exception = Exception::TypeError(String::NewFromUtf8(isolate, exceptionMessage.c_str()));
        isolate->ThrowException(exception);

        return false;
    }

    return true;
}

bool Contracts::RequireNumberArgument(const v8::FunctionCallbackInfo<Value>& args, int argumentIndex)
{
    Isolate* isolate = args.GetIsolate();

    if (!args[argumentIndex]->IsNumber())
    {
        ostringstream exceptionMessageStream;
        exceptionMessageStream << "Argument " << argumentIndex + 1 << " must be of type number.";

        string exceptionMessage = exceptionMessageStream.str();

        Local<Value> exception = Exception::TypeError(String::NewFromUtf8(isolate, exceptionMessage.c_str()));
        isolate->ThrowException(exception);

        return false;
    }

    return true;
}

bool Contracts::RequireFunctionArgument(const v8::FunctionCallbackInfo<Value>& args, int argumentIndex)
{
    Isolate* isolate = args.GetIsolate();

    if (!args[argumentIndex]->IsFunction())
    {
        ostringstream exceptionMessageStream;
        exceptionMessageStream << "Argument " << argumentIndex + 1 << " must be of type function.";

        string exceptionMessage = exceptionMessageStream.str();

        Local<Value> exception = Exception::TypeError(String::NewFromUtf8(isolate, exceptionMessage.c_str()));
        isolate->ThrowException(exception);

        return false;
    }

    return true;
}

bool Contracts::OptionalFunctionArgument(const v8::FunctionCallbackInfo<Value>& args, int argumentIndex)
{
    if (argumentIndex >= args.Length())
    {
        return true;
    }

    return RequireFunctionArgument(args, argumentIndex);
}
