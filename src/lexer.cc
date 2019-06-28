#include <iostream>
#include <istream>
#include <sstream>
#include <limits>
#include <list>
#include <optional>

#include "tpl/token.h"
#include "fmt/core.h"

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
        for (char c = '\0'; istream.get(c);) {
            /* Generated token, if any */
            std::optional<Token> token;

            /* Check which pattern the first character matches */
            switch (c) {
                /* SPACES */
                case '\n':
                case ' ': {
                    continue;
                }
                /* COMMENT */
                case '#': {
                    // ignore all following characters until end-of-line
                    istream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                /* IDENTIFIERS */
                case '_':
                case 'a' ... 'z':
                case 'A' ... 'Z': {
                    istream.unget();  // reset to the first character of the identifier
                    std::string str = ScanIdentifier(istream);
                    token = { Token::Type::IDENTIFIER, std::move(str) };
                    break;
                }
                /* STRING LITERAL */
                case '"':
                case '\'': {
                    std::string str = ScanString(istream, c);
                    token = { Token::Type::STRING, std::move(str) };
                    break;
                }
                /* OPERATORS */
                case '!':
                case '~':
                case '=':
                case ':':
                case '|': {
                    std::string str = { c, '\0' };
                    token = { Token::Type::OPERATOR, std::move(str) };
                    break;
                }
                case '.': {  // TODO
                    break;
                }
                /* BRACKETS */
                case '(':
                case ')':
                case '[':
                case ']':
                case '{':
                case '}':
                case '<':
                case '>': {
                    std::string str = { c, '\0' };
                    token = { Token::Type::BRACKET, std::move(str) };
                    break;
                }
                /* SEPARATORS */
                case ',': {
                    std::string str = { c, '\0' };
                    token = { Token::Type::SEPARATOR, std::move(str) };
                    break;
                }
                /* OTHER CHARACTERS */
                default: {
                    throw std::runtime_error(fmt::format("found unknown character: {}", c));
                }
            }

            /* If a token was generated, enqueue it in the recognized tokens */
            if (token) {
                tokens.emplace_back(std::move(token.value()));
            }
        }

        return tokens;
    }

   private: /****************************************************************************/
            /**
             * \brief
             */
    static std::string ScanString(std::istream& istream, const char terminator) noexcept(false)
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
                throw std::runtime_error(fmt::format("unterminated string: {}", ss.str()));
            }
            if (c == terminator && last_c != '\\') {
                break;
            }
            ss << c;
        }

        return ss.str();
    }

    /**
     * \brief
     */
    static std::string ScanIdentifier(std::istream& istream) noexcept(false)
    {
        std::stringstream ss;

        bool id_end = false;
        for (char c = '\0'; not id_end && istream.get(c);) {
            switch (c) {
                case '_':
                case 'a' ... 'z':
                case 'A' ... 'Z':
                case '0' ... '9': {
                    ss << c;
                    break;
                }
                case '\n': {
                    id_end = true;
                    break;
                }
                default: {
                    id_end = true;
                    istream.unget();
                }
            }
        }

        return ss.str();
    }

    /***********************************************************************************/
    /*! Testing class */
    friend class LexerTester;
};

}  // namespace tpl

int main()
{
    std::istringstream input{ R"(
#'''" comment \'"'

'\'"hello"\'': "'wor'ld\""
field: [a, b, c, d]
Type= {"dummy"= Bool}
key: "value"
    )" };

    std::istringstream input2{ "#''" };

    std::istringstream input3{ "" };

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

    try {
        auto tokens = tpl::Lexer::Scan(input);

        for (auto& token : tokens) {
            fmt::print("token: {0:<{1}} | lexeme: {2}\n", token.type().name(), kTypeMaxLen,
                       token.lexeme());
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}