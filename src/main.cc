#include <iostream>
#include <sstream>
#include <fstream>
#include "fmt/core.h"

#include "tpl/lexer.h"

namespace {
constexpr size_t kTypeMaxLen = []() constexpr
{
    size_t maxlen = 0;
    for (auto type : ::njr::enum_t<tpl::Token::Type>::values::array()) {
        if (size_t len = std::string_view(type.name()).length(); len > maxlen) {
            maxlen = len;
        }
    }
    return maxlen;
}
();
}  // namespace

/***************************************************************************************/

int main(int argc, const char* argv[])
{
    if (argc < 2) {
        fmt::print(stderr, "missing input files\n ");
        return -1;
    }
    else if (argc > 2) {
        fmt::print(stderr, "too many arguments\n");
        return -2;
    }

    std::ifstream file{ argv[1] };
    if (not file.is_open()) {
        fmt::print(stderr, "failed to open input file\n");
        return -3;
    }

    try {
        auto tokens = tpl::Lexer::Scan(file);

        for (auto& token : tokens) {
            fmt::print("token: {0:<{1}} | lexeme: {2}\n", token.type().name(),
                       kTypeMaxLen, token.lexeme());
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
