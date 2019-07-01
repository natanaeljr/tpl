#include <gtest/gtest.h>

#include <sstream>

#include "tpl/lexer.h"

/***************************************************************************************/
namespace tpl {

class LexerTester : public Lexer {
   public:
    // Expose private methods for testing
    using tpl::Lexer::Scan;
    using tpl::Lexer::ScanDecimal;
    using tpl::Lexer::ScanIdentifier;
    using tpl::Lexer::ScanString;
};

}  // namespace tpl

/***************************************************************************************/
TEST(LexTesting, ScanDecimal)
{
    tpl::LexerTester lexer;
    {  // All numbers until EOF
        std::stringstream ss{ "1234567890" };
        EXPECT_EQ("1234567890", lexer.ScanDecimal(ss));
    }
    {  // until other character
        std::stringstream ss{ "435.432" };
        EXPECT_EQ("435", lexer.ScanDecimal(ss));
    }
    {  // until EOL
        std::stringstream ss{ "94532\n123" };
        EXPECT_EQ("94532", lexer.ScanDecimal(ss));
    }
    {  // start with letter
        std::stringstream ss{ "sd123" };
        EXPECT_EQ("", lexer.ScanDecimal(ss));
    }
}