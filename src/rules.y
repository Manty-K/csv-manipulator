%{
    #include "common-headers.h"
    #include "rules-controller/rules-controller.h"
    int ruleslex(void);
    void ruleserror(const char *);
%}
%define api.prefix {rules}

%token ASSIGN RSYM CSYM TERMINATOR
%token <s> INTEGER FLOAT PLUS MINUS MUL DIV LPAREN RPAREN LABEL STRING

%type numval

%union {

    int i;
    float f;
    char * s;
}

%start stmts


%%
stmts: stmt stmts
    |
    ;

stmt: assign
    | assignStr
    ;

assignStr: rc ASSIGN STRING TERMINATOR { assignString($3);}
    ;

assign : rc ASSIGN aexpr TERMINATOR



rc : RSYM INTEGER CSYM INTEGER      {setRC(atoi($2), atoi($4));}

aexpr: term
    | term PLUS aexpr
    |  term MINUS  aexpr;

term: factor
    |  factor MUL term
    | factor DIV  term
    ;

factor: numval  
    | rc  
    | LPAREN   aexpr  RPAREN   
    ;

numval : INTEGER | FLOAT

%%


