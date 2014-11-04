#include "contracts.h"

using namespace v8;


Handle<Value> Contracts::RequireNumberOfArguments(const Arguments& args, int requiredNumberOfArguments)
{
    HandleScope scope;

    if (args.Length() < requiredNumberOfArguments)
    {
        char exceptionMessage[32];
        _snprintf(exceptionMessage, sizeof exceptionMessage, "Function expects %d parameters.", requiredNumberOfArguments);

        Local<Value> exception = Exception::Error(String::New(exceptionMessage));
        ThrowException(exception);

        return scope.Close(Undefined());
    }

    return scope.Close(Handle<Value>());
}

Handle<Value> Contracts::RequireObjectArgument(const Arguments& args, int argumentIndex)
{
    HandleScope scope;

    if (!args[argumentIndex]->IsObject())
    {
        char exceptionMessage[64];
        _snprintf(exceptionMessage, sizeof exceptionMessage, "Argument %d must be of type object.", argumentIndex + 1);

        Local<Value> exception = Exception::TypeError(String::New(exceptionMessage));
        ThrowException(exception);

        return scope.Close(Undefined());
    }

    return scope.Close(Handle<Value>());
}

Handle<Value> Contracts::RequireNumberArgument(const v8::Arguments& args, int argumentIndex)
{
    HandleScope scope;

    if (!args[argumentIndex]->IsNumber())
    {
        char exceptionMessage[64];
        _snprintf(exceptionMessage, sizeof exceptionMessage, "Argument %d must be of type number.", argumentIndex + 1);

        Local<Value> exception = Exception::TypeError(String::New(exceptionMessage));
        ThrowException(exception);

        return scope.Close(Undefined());
    }

    return scope.Close(Handle<Value>());
}
