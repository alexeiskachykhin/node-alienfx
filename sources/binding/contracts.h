#pragma once

#include <node.h>


class Contracts
{
public:
    static bool RequireNumberOfArguments(const v8::Arguments& args, int requiredNumberOfArguments);
    static bool RequireObjectArgument(const v8::Arguments& args, int argumentIndex);
    static bool RequireNumberArgument(const v8::Arguments& args, int argumentIndex);
    static bool RequireFunctionArgument(const v8::Arguments& args, int argumentIndex);
    static bool OptionalFunctionArgument(const v8::Arguments& args, int argumentIndex);
};


#define REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, requiredNumberOfArguments) \
    if (!Contracts::RequireNumberOfArguments(args, requiredNumberOfArguments)) \
    { \
        return scope.Close(Undefined()); \
    }

#define REQUIRE_OBJECT(scope, args, argumentIndex) \
    if (!Contracts::RequireObjectArgument(args, argumentIndex)) \
    { \
        return scope.Close(Undefined()); \
    }

#define REQUIRE_NUMBER(scope, args, argumentIndex) \
    if (!Contracts::RequireNumberArgument(args, argumentIndex)) \
    { \
        return scope.Close(Undefined()); \
    }

#define REQUIRE_FUNCTION(scope, args, argumentIndex) \
    if (!Contracts::RequireFunctionArgument(args, argumentIndex)) \
    { \
        return scope.Close(Undefined()); \
    }

#define OPTIONAL_FUNCTION(scope, args, argumentIndex) \
    if (!Contracts::OptionalFunctionArgument(args, argumentIndex)) \
    { \
        return scope.Close(Undefined()); \
    }

