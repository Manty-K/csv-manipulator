%{
    #include "rules.tab.h"

%}
%option noyywrap
%option prefix="rules"
%%

"->"            {return ARROW;}

\n                  {return NEWLINE;}

.                 

%%