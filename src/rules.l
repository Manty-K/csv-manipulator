%{
    #include "rules.tab.h"

%}
%option noyywrap
%option prefix="rules"
%%

\"([^\"]*)\"			{ ruleslval.s = strndup(yytext+1,yyleng-2);return STRING; }

"r"              {return RSYM;}

"c"              {return CSYM;}

[0-9]+            {ruleslval.s = strdup(yytext);  return INTEGER;}

[0-9]+(\.[0-9]+)?      { ruleslval.s = strdup(yytext);  return FLOAT;}

\$[a-z]+[a-zA-Z0-9]*        {ruleslval.s = strdup(yytext); return LABEL; }

";"                         {ruleslval.s = strdup(yytext); return TERMINATOR;}

"("                        {ruleslval.s = strdup(yytext); return LPAREN;}
")"                        {ruleslval.s = strdup(yytext); return RPAREN;}


"+"     { ruleslval.s = strdup(yytext);  return PLUS;}
"-"     { ruleslval.s = strdup(yytext);  return MINUS;}
"*"     { ruleslval.s = strdup(yytext);  return MUL;}
"/"     { ruleslval.s = strdup(yytext);  return DIV;}

"<-"            {return ASSIGN;}

\n                  ;

[\t ]                 ;

.                 ;

%%