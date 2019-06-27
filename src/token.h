#pragma once

namespace tpl {

class Token {
   public:
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
    //< non-tokens: # '\'

    Token(Type type) : type_{ type }
    {
    }

    ~Token()
    {
    }

    Type type()
    {
        return type_;
    }

   private:
    Type type_;
};

// see: https://yaml.org/refcard.html

// PrimitiveTypes ?
// SemanticTypes ?

} /* namespace tpl */
