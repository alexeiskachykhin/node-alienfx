#pragma once

#include <node.h>


class Contracts
{
public:
    static bool RequireNumberOfArguments(const v8::FunctionCallbackInfo<v8::Value>& args, int requiredNumberOfArguments);
    static bool RequireObjectArgument(const v8::FunctionCallbackInfo<v8::Value>& args, int argumentIndex);
    static bool RequireNumberArgument(const v8::FunctionCallbackInfo<v8::Value>& args, int argumentIndex);
    static bool RequireFunctionArgument(const v8::FunctionCallbackInfo<v8::Value>& args, int argumentIndex);
    static bool OptionalFunctionArgument(const v8::FunctionCallbackInfo<v8::Value>& args, int argumentIndex);
};


#define REQUIRE_NUMBER_OF_ARGUMENTS(args, requiredNumberOfArguments) \
    if (!Contracts::RequireNumberOfArguments(args, requiredNumberOfArguments)) \
    { \
        return; \
    }

#define REQUIRE_OBJECT(args, argumentIndex) \
    if (!Contracts::RequireObjectArgument(args, argumentIndex)) \
    { \
        return; \
    }

#define REQUIRE_NUMBER(args, argumentIndex) \
    if (!Contracts::RequireNumberArgument(args, argumentIndex)) \
    { \
        return; \
    }

#define REQUIRE_FUNCTION(args, argumentIndex) \
    if (!Contracts::RequireFunctionArgument(args, argumentIndex)) \
    { \
        return; \
    }

#define OPTIONAL_FUNCTION(args, argumentIndex) \
    if (!Contracts::OptionalFunctionArgument(args, argumentIndex)) \
    { \
        return; \
    }

