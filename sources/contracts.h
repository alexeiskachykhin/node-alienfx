#pragma once

#include <node.h>


class Contracts
{
public:
    static void RequireNumberOfArguments(const v8::Arguments& args, int requiredNumberOfArguments);
    static void RequireObjectArgument(const v8::Arguments& args, int argumentIndex);
    static void RequireNumberArgument(const v8::Arguments& args, int argumentIndex);
};
