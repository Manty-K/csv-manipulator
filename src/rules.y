%{
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

stmt: assign | assignStr

assignStr: rc_or_lab ASSIGN STRING TERMINATOR

assign : rc_or_lab ASSIGN aexpr TERMINATOR

rc_or_lab : rc | LABEL

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
    | LABEL
    | LPAREN   aexpr  RPAREN   
    ;

numval : INTEGER | FLOAT

%%


