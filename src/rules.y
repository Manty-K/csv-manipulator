%{
    int ruleslex(void);
    void ruleserror(const char *);
%}
%define api.prefix {rules}

%token ASSIGN NEWLINE RSYM CSYM
%token <s> INTEGER FLOAT PLUS MINUS MUL DIV LPAREN RPAREN

%type numval

%union {

    int i;
    float f;
    char * s;
}

%start assign


%%
// stmts: stmt
//     | stmts stmt
//     | NEWLINE
//     ;

// stmt : assign

rc : RSYM INTEGER CSYM INTEGER

assign : rc ASSIGN aexpr


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


