#include <sstream>

#include "contracts.h"

using namespace std;
using namespace v8;


bool Contracts::RequireNumberOfArguments(const Arguments& args, int requiredNumberOfArguments)
{
    HandleScope scope;

    if (args.Length() < requiredNumberOfArguments)
    {
        ostringstream exceptionMessageStream;
        exceptionMessageStream << "Function expects " << requiredNumberOfArguments << " parameters.";

        string exceptionMessage = exceptionMessageStream.str();

        Local<Value> exception = Exception::Error(String::New(exceptionMessage.c_str()));
        ThrowException(exception);

        return false;
    }

    return true;
}

bool Contracts::RequireObjectArgument(const Arguments& args, int argumentIndex)
{
    HandleScope scope;

    if (!args[argumentIndex]->IsObject())
    {
        ostringstream exceptionMessageStream;
        exceptionMessageStream << "Argument " << argumentIndex + 1 << " must be of type object.";

        string exceptionMessage = exceptionMessageStream.str();

        Local<Value> exception = Exception::TypeError(String::New(exceptionMessage.c_str()));
        ThrowException(exception);

        return false;
    }

    return true;
}

bool Contracts::RequireNumberArgument(const Arguments& args, int argumentIndex)
{
    HandleScope scope;

    if (!args[argumentIndex]->IsNumber())
    {
        ostringstream exceptionMessageStream;
        exceptionMessageStream << "Argument " << argumentIndex + 1 << " must be of type number.";

        string exceptionMessage = exceptionMessageStream.str();

        Local<Value> exception = Exception::TypeError(String::New(exceptionMessage.c_str()));
        ThrowException(exception);

        return false;
    }

    return true;
}

bool Contracts::RequireFunctionArgument(const Arguments& args, int argumentIndex)
{
    HandleScope scope;

    if (!args[argumentIndex]->IsFunction())
    {
        ostringstream exceptionMessageStream;
        exceptionMessageStream << "Argument " << argumentIndex + 1 << " must be of type function.";

        string exceptionMessage = exceptionMessageStream.str();

        Local<Value> exception = Exception::TypeError(String::New(exceptionMessage.c_str()));
        ThrowException(exception);

        return false;
    }

    return true;
}

bool Contracts::OptionalFunctionArgument(const v8::Arguments& args, int argumentIndex)
{
    HandleScope scope;

    if (argumentIndex >= args.Length())
    {
        return true;
    }

    return RequireFunctionArgument(args, argumentIndex);
}
