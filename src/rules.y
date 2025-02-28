%{
    #include "common-headers.h"
   #include "rules-controller/rules-controller.h"
   #include "rules-controller/expression-handler.h"
    #include "rules-controller/functions.h"
    int ruleslex(void);
    void ruleserror(const char *);
%}
%define api.prefix {rules}

%token ASSIGN RSYM CSYM TERMINATOR COLON SUM AVG MIN MAX SORT COMMA
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
    ;


assign : rc ASSIGN asnOps

asnOps : STRING TERMINATOR { assignString($1);}
    | { setIndentifier(); expressionStart();} aexpr { expressionEnd();} TERMINATOR
    | {setIndentifier();} planeOps LPAREN rc {setTl();} COLON rc {setBr();} RPAREN TERMINATOR {planeOperation();}
    | {setIndentifier();} SORT LPAREN rc {setTl();} COLON rc {setBr();} COMMA rorc RPAREN TERMINATOR {sortOperation();}
    ;
rorc: RSYM {setCurrentDirection(HORIZONTAL);}
    | CSYM {setCurrentDirection(VERTICAL);}
    ;

planeOps: 
      SUM {setPlaneOp(SUM_OP);}
    | AVG {setPlaneOp(AVG_OP);}
    | MIN {setPlaneOp(MIN_OP);}
    | MAX {setPlaneOp(MAX_OP);}
    ;

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


