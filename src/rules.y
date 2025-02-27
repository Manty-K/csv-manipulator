%{
    #include "common-headers.h"
    #include "rules-controller/rules-controller.h"
    #include "rules-controller/expression-handler.h"
    int ruleslex(void);
    void ruleserror(const char *);
%}
%define api.prefix {rules}

%token ASSIGN RSYM CSYM TERMINATOR
%token <s> INTEGER FLOAT PLUS MINUS MUL DIV LPAREN RPAREN LABEL STRING

%type <s> numval

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

assign : rc ASSIGN { setIndentifier(); expressionStart();} aexpr { expressionEnd();} TERMINATOR



rc : RSYM INTEGER CSYM INTEGER      {setRC(atoi($2), atoi($4));}

aexpr: term
    | term PLUS aexpr                    {pushOperator($2);}
    |  term MINUS  aexpr               {pushOperator($2);}
    ;

term: factor                    
    |  factor MUL term              {pushOperator($2);}
    | factor DIV  term                   {pushOperator($2);}
    ;

factor: numval                          {pushNum(atof($1));}
    | rc                                {pushRC();}
    | LPAREN   aexpr  RPAREN   
    ;

numval : INTEGER | FLOAT

%%


