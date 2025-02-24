
%{
    #include "csv.tab.h"
%}
%option noyywrap
%option prefix="csv"


%%

\s*[a-zA-Z]+[a-zA-Z0-9]*\s*      {return LABEL;}

\s*[0-9]+\s*        {return NUMBER;}


","                     {return COMMA;}

\n                  {return NEWLINE;}

.                   ;


%%
