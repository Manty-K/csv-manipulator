%{
    int ruleslex(void);
    void ruleserror(const char *);
%}
%define api.prefix {rules}

%token ASSIGN RSYM CSYM TERMINATOR
%token <s> INTEGER FLOAT PLUS MINUS MUL DIV LPAREN RPAREN

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

assign : rc ASSIGN aexpr TERMINATOR

rc : RSYM INTEGER CSYM INTEGER

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


