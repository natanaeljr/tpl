// #pragma once

#include <iostream>
#include <istream>
#include <sstream>
#include <limits>
#include <list>
#include <array>

#include "token.h"

namespace tpl {

class Lexer {
   public:
    Lexer() = delete;

    static auto Scan(std::istream& istream) -> std::list<Token>
    {
        std::list<Token> tokens;

        while (istream.good()) {
            int c = istream.get();

            switch (c) {
                /* COMMENT */
                case '#': {
                    // ignore all following characters until end-of-line
                    istream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    istream.get();  // extract the '\n' lastly
                    break;
                }
                /* STRING LITERAL */
                case '"':
                case '\'': {
                    std::stringstream ss;
                    int last_d = '\0';
                    while (istream.good()) {
                        int d = istream.get();
                        if (d == c && last_d != '\\') {
                            break;
                        } else if (d == '\n' || istream.eof()) {
                            // create token
                            throw std::runtime_error("unterminated string");
                        }
                        last_d = d;
                        ss << (char)d;
                    }
                    std::cout << "string is: " << (char)c << ss.str() << (char)c << '\n';
                    Token token = Token::Type::STRING;
                    tokens.emplace_back(token);
                    break;
                }
            }

            // break;
        }

        return {};
    }
};

} /* namespace tlp */

int main()
{
    std::istringstream iss{ R"(#'''
    '\'"hello"\'': "'wor'ld\"")" };
    tpl::Lexer::Scan(iss);

    return 0;
}