%{
  #include <stdio.h>
  
  extern FILE *yyin;
  extern int num_line;
  
  void yyerror(const char *str)
  {
    fprintf(stderr, "error: %s\n", str);
  }
  
  int yywrap()
  {
    return 1;
  }
  
  main(int argc, char* argv[])
  {
     if (argc == 2) 
      yyin = fopen( argv[1], "r" );
     else {
      printf("found no input parameter!\n");
      return 1;
     }
      
     if(yyparse() == 0)
      printf("success parsing!\n");
     else
      printf("error in line: %d\n", num_line);
     
     fclose(yyin); 
  }
%}

%token	_VAR _CONST _PROC _CALL _BEGIN _END _DO _IF _THEN _UNKN_SYM _LPAREN _RPAREN
%token	_WHILE _ASSIGN _SEMICOLON _COMMA _MATH_OPER _LOGIC_OPER _NUM _ID _DOT _EQ _NEQ

%%

program_stuct:
    optional_expressions program_body 
    ;
   
program_body:
    _BEGIN statements _END _DOT
    ;
   
optional_expressions: /*empty*/
    | optional_expressions _CONST constant_declare _SEMICOLON
    | optional_expressions _VAR variable_declare _SEMICOLON
    | optional_expressions _PROC procedure_declare _SEMICOLON
    ;
   
constant_declare:
    constant_declare _COMMA _ID _EQ _NUM
    | _ID _EQ _NUM
    ;
   
variable_declare:
    variable_declare _COMMA _ID
    | _ID
    ;
   
procedure_declare:
    _ID _SEMICOLON _BEGIN statements _END
    ;
   
statements: /*empty*/
    | statements statement
    ;
  
statement: 
     _SEMICOLON
    | _CALL _ID _SEMICOLON
    | assign_expression _SEMICOLON
    | _IF condition_expression _THEN _body 
    | _WHILE condition_expression _DO _body 
    ;
   
condition_expression:
    atom _LOGIC_OPER atom 
    | atom _EQ atom
    | atom _NEQ atom
    ;
  
_body:
    statement 
    | _BEGIN statements _END _SEMICOLON
    ;
  
assign_expression:
    _ID _ASSIGN value
    ;
  
value:
    value _MATH_OPER value
    | atom
    ;
   
atom:
    _ID
    | _NUM
    | _LPAREN value _RPAREN
    ;
    

%%
