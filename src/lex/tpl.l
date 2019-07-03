%{
#include "tpl/token.h"
%}

decimal [-+][1-9][0-9]*

%%
decimal  { return static_cast<int>(tpl::Token::Type::DECIMAL); }
%%
