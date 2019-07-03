#include <istream>
#include <list>

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
     * \brief Scan a stream for lexemes and generate tokens.
     */
    static std::list<Token> Scan(std::istream& istream) noexcept(false)
    {
        return Lexer{}.ScanTokens(istream);
    }

    /***********************************************************************************/
   private:
    /**
     * \brief Convert the sequence of characters into a sequence of tokens.
     */
    std::list<Token> ScanTokens(std::istream& istream) noexcept(false);

    /**
     * \brief Scan a string lexeme until terminator.
     * First character in the istream is expected to be the start of the lexeme.
     */
    std::string ScanString(std::istream& istream, const char terminator) noexcept(false);

    /**
     * \brief Scan a identifier lexeme.
     */
    std::string ScanIdentifier(std::istream& istream) noexcept(true);

    /**
     * \brief Scan a decimal lexeme.
     */
    std::string ScanDecimal(std::istream& istream) noexcept(true);

    /**
     * \brief Construct a Lexer object.
     */
    Lexer() {}

    /*! Testing class */
    friend class LexerTester;
};

}  // namespace tpl
