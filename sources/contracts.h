#pragma once

#include <node.h>


class Contracts
{
public:
    static v8::Handle<v8::Value> RequireNumberOfArguments(const v8::Arguments& args, int requiredNumberOfArguments);
    static v8::Handle<v8::Value> RequireObjectArgument(const v8::Arguments& args, int argumentIndex);
    static v8::Handle<v8::Value> RequireNumberArgument(const v8::Arguments& args, int argumentIndex);
};


#define REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, requiredNumberOfArguments) \
    if (!Contracts::RequireNumberOfArguments(args, requiredNumberOfArguments).IsEmpty()) \
    { \
        return scope.Close(Undefined()); \
    }

#define REQUIRE_OBJECT(scope, args, argumentIndex) \
    if (!Contracts::RequireObjectArgument(args, argumentIndex).IsEmpty()) \
    { \
        return scope.Close(Undefined()); \
    }

#define REQUIRE_NUMBER(scope, args, argumentIndex) \
    if (!Contracts::RequireNumberArgument(args, argumentIndex).IsEmpty()) \
    { \
        return scope.Close(Undefined()); \
    }


