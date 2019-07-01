#include "tpl/lexer.h"

#include <limits>
#include <sstream>
#include <optional>
#include "fmt/core.h"

namespace tpl {

/***************************************************************************************/
std::list<Token> Lexer::ScanTokens(std::istream& istream) noexcept(false)
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
                std::string id = ScanIdentifier(istream);
                token = { Token::Type::IDENTIFIER, std::move(id) };
                break;
            }
            /* STRING LITERAL */
            case '"':
            case '\'': {
                std::string str = ScanString(istream, c);
                token = { Token::Type::STRING, std::move(str) };
                break;
            }
            /* NUMBERS */
            case '-': {
                int next_c = istream.peek();
                if (istream.eof() || next_c <= '0' || next_c >= '9') {
                    throw std::runtime_error("expected a negative number");
                }
            }
            case '0' ... '9': {
                istream.unget();  // reset to the first character of the number
                std::string decimal = ScanDecimal(istream);
                token = { Token::Type::DECIMAL, std::move(decimal) };
                break;
            }
            /* OPERATORS */
            case '!':
            case '~':
            case '=':
            case ':':
            case '|': {
                std::string op = { c, '\0' };
                token = { Token::Type::OPERATOR, std::move(op) };
                break;
            }
            case '.': {
                if (char d; istream.get(d) && d == '.') {
                    std::string op = { c, d, '\0' };
                    token = { Token::Type::OPERATOR, std::move(op) };
                }
                else {
                    throw std::runtime_error("did mean the operator '..' ?");
                }
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

/***************************************************************************************/
std::string Lexer::ScanIdentifier(std::istream& istream) noexcept(true)
{
    std::ostringstream ss;

    bool for_end = false;
    for (char c = '\0'; not for_end && istream.get(c);) {
        switch (c) {
            case '_':
            case 'a' ... 'z':
            case 'A' ... 'Z':
            case '0' ... '9': {
                ss << c;
                break;
            }
            case '\n': {
                for_end = true;
                break;
            }
            default: {
                for_end = true;
                istream.unget();
            }
        }
    }

    return ss.str();
}

/***************************************************************************************/
std::string Lexer::ScanString(std::istream& istream,
                              const char terminator) noexcept(false)
{
    std::ostringstream ss;

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

/***************************************************************************************/
std::string Lexer::ScanDecimal(std::istream& istream) noexcept(true)
{
    std::ostringstream ss;

    for (char c = '\0'; istream.get(c);) {
        if (c >= '0' && c <= '9') {
            ss << c;
            continue;
        }
        if (c != '\n') {
            istream.unget();
        }
        break;
    }

    return ss.str();
}

}  // namespace tpl
