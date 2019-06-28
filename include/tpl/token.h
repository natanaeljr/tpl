#pragma once

#include <string>
#include "njr/enum_t.h"

/***************************************************************************************/

namespace tpl {

/**
 * \brief Token representation class.
 *
 * A token is a pair consisting of a token type and an optional attribute value. The token
 * name is an abstract symbol representing a kind of lexical unit, e.g., a particular
 * keyword, or sequence of input characters denoting an identifier. The token types are
 * the input symbols that the parser processes.
 */
class Token {
   public:
    /** Possible Token types */
    enum class Type {
        /* char sequences */
        IDENTIFIER,  // _ a-z A-Z 0-9
        STRING,      // "...", '...'
        /* numbers */
        DECIMAL,      // [-|+] 0-9
        HEXADECIMAL,  // 0x (0-9 a-z A-Z)
        OCTAL,        // 0c (0-9 a-z A-Z)
        FLOAT,        // 0-9 . 0-9 f e [-|+] 0-9
        /* specifics */
        OPERATOR,   // ! ~ - = : | ..
        BRACKET,    // () [] {} <>
        SEPARATOR,  // ,
        /* other */
        EMBEDDED,  // embeded char sequence, `...`
    };
    //!< non-tokens: # '\'

    /**
     * \brief Construct a Token.
     * \param type Token type.
     * \param lexeme Token lexeme.
     */
    Token(Type type, std::string lexeme) : type_{ type }, lexeme_{ lexeme } {}

    /**
     * \brief Destruct a Token.
     */
    ~Token() noexcept {}

    /**
     * \brief Get this token type.
     *
     * Token Type identifies the token pattern.
     * A pattern is a description of the form that the lexemes of a token may take. In the
     * case of a keyword as a token, the pattern is just the sequence of characters that
     * form the keyword. For identifiers and some other tokens, the pattern is more
     * complex structure that is matched by many strings.
     */
    ::njr::enum_t<Type> type() const { return type_; }

    /**
     * \brief Get this token lexeme.
     *
     * Lexeme is sequence of characters in the source program that matches the pattern for
     * this token type and is identified by the lexical analyzer as an instance of this
     * token.
     */
    const std::string& lexeme() const { return lexeme_; }

   private:
    /*! Token type */
    Type type_;
    /*! Token lexeme */
    std::string lexeme_;
};

// see: https://yaml.org/refcard.html

// PrimitiveTypes ?
// SemanticTypes ?

} /* namespace tpl */

/**
 * \brief Get the name of the Token Type stringfied.
 */
template<>
constexpr const char* ::njr::enum_t<tpl::Token::Type>::name() const
{
    using tpl::Token;
    switch (enum_) {
        case Token::Type::IDENTIFIER: return "identifier";
        case Token::Type::STRING: return "string";
        case Token::Type::DECIMAL: return "decimal";
        case Token::Type::HEXADECIMAL: return "hexadecimal";
        case Token::Type::OCTAL: return "octal";
        case Token::Type::FLOAT: return "float";
        case Token::Type::OPERATOR: return "operator";
        case Token::Type::BRACKET: return "bracket";
        case Token::Type::SEPARATOR: return "separator";
        case Token::Type::EMBEDDED: return "embedded";
    }
    return nullptr;
}