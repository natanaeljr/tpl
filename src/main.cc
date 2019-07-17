/**
 * \file main.cc
 * \author Natanael Josue Rabello
 * \brief Entrence Point.
 * \date 2019-07-17
 * \copyright Copyright (c) 2019
 */

#include "fmt/core.h"
#include "FlexLexer.h"
#include "tpl/driver.h"

class CalcContext {
};

int main()
{
    auto ctx = CalcContext();
    auto driver = tpl::Driver(ctx);
    driver.trace_parsing = true;
    driver.trace_parsing = true;
    return driver.parse_string("hello=");
}