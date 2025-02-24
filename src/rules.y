%{
    int ruleslex(void);
    void ruleserror(const char *);
%}
%define api.prefix {rules}

%token ARROW NEWLINE  

%start line


%%
line:  ARROW

%%


