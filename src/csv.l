
%{
    #include "csv.tab.h"
%}
%option noyywrap
%option prefix="csv"


%%

\s*[a-zA-Z]+[a-zA-Z0-9]*\s*      {csvlval.s = strdup(yytext); return LABEL;}

\s*[0-9]+\s*        {csvlval.s = strdup(yytext); return NUMBER;}


","                     {return COMMA;}

\n                  {return NEWLINE;}

.                   ;


%%
