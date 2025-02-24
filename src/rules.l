%{
    #include "rules.tab.h"

%}
%option noyywrap
%option prefix="rules"
%%

"r"              {return RSYM;}

"c"              {return CSYM;}

[0-9]+            {ruleslval.s = strdup(yytext);  return INTEGER;}

[0-9]+(\.[0-9]+)?      { ruleslval.s = strdup(yytext);  return FLOAT;}

"("                        {ruleslval.s = strdup(yytext); return LPAREN;}
")"                        {ruleslval.s = strdup(yytext); return RPAREN;}


"+"     { ruleslval.s = strdup(yytext);  return PLUS;}
"-"     { ruleslval.s = strdup(yytext);  return MINUS;}
"*"     { ruleslval.s = strdup(yytext);  return MUL;}
"/"     { ruleslval.s = strdup(yytext);  return DIV;}

"<-"            {return ASSIGN;}

\n                  {return NEWLINE;}

[\t ]                 ;

.                 ;

%%