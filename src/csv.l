
%{
    #include "csv.tab.h"
%}
%option noyywrap
%option prefix="csv"


%%


\s*[0-9]+\s*        {csvlval.s = strdup(yytext); return NUMBER;}

[a-zA-Z0-9 ]*       {csvlval.s = strdup(yytext); return LABEL;}

","                     {return COMMA;}

\n                  {return NEWLINE;}

.                   ;



%%
