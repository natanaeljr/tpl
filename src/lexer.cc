#include <iostream>
#include <istream>
#include <sstream>
#include <limits>
#include <list>
#include <array>

#include "tpl/token.h"

/***************************************************************************************/

namespace tpl {

/**
 * \brief Lexer class, performs lexical analysis.
 *
 * Lexical analysis, lexing or tokenization is the process of converting a sequence of
 * characters into a sequence of tokens (strings with an assigned and thus identified
 * meaning).
 */
class Lexer {
   public:
    /**
     * \brief Delete constructor, Lexer is static class.
     */
    Lexer() = delete;

    /**
     * \brief Scan a stream for lexemes.
     * Convert the sequence of characters into a sequence of tokens.
     */
    static std::list<Token> Scan(std::istream& istream) noexcept(false)
    {
        std::list<Token> tokens;

        /* Scan stream while there is input available */
        for (char c = '\0', last_c = c; istream.get(c); last_c = c) {
            switch (c) {
                /* COMMENT */
                case '#': {
                    // ignore all following characters until end-of-line
                    istream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                /* STRING LITERAL */
                case '"':
                case '\'': {
                    std::string str = ScanString(istream, c);
                    Token token = { Token::Type::STRING, std::move(str) };
                    tokens.emplace_back(std::move(token));
                    break;
                }
                /* OPERATORS */
                case ':': {
                    std::string str = { static_cast<char>(c), '\0' };
                    Token token = { Token::Type::OPERATOR, std::move(str) };
                    tokens.emplace_back(std::move(token));
                }
            }
        }

        return tokens;
    }

   private: /****************************************************************************/
    /**
     * \brief
     */
    static std::string ScanString(std::istream& istream,
                                  const char terminator) noexcept(false)
    {
        std::stringstream ss;

        /* Scan string while:
         * - there is input available
         * - is not the end-of-line
         * - terminator not found
         */
        for (char c = '\0', last_c = c;; last_c = c) {
            istream.get(c);
            if (c == '\n' || istream.eof()) {
                throw std::runtime_error("unterminated string");
            }
            if (c == terminator && last_c != '\\') {
                break;
            }
            ss << static_cast<char>(c);
        }

        return ss.str();
    }
};

}  // namespace tpl

int main()
{
    std::istringstream input{ R"(
#'''" comment \'"'
'\'"hello"\'': "'wor'ld\""
field: [a, b, c, d]
key: "value"
    )" };

    std::istringstream input2{ "#''" };

    std::istringstream input3{ "" };

    try {
        auto tokens = tpl::Lexer::Scan(input3);

        for (auto& token : tokens) {
            std::cout << "token: '" << token.type().name();
            std::cout << "', lexeme: '" << token.lexeme() << "'\n";
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}