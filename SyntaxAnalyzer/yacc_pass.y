%{
#include <stdio.h>


FILE* itable;
extern FILE *yyin;
extern int num_line;

typedef struct node {
  int value;
  char* type;
  char* id;
  struct node* next;
} _node;

_node *HEAD, *CURPOS;

void yyerror(const char *str)
{
  fprintf(stderr, "error: %s\n", str);
}

int yywrap()
{
  return 1;
}


void createTable()
{
  HEAD = (_node*)malloc(sizeof(_node));
  HEAD->next = NULL;
  CURPOS = HEAD;
}

void addToTable(char* _type, char* _id, int _value)
{
  CURPOS->next = (_node*)malloc(sizeof(_node));
  CURPOS = CURPOS->next;
  
  CURPOS->type = strdup(_type);
  CURPOS->id = strdup(_id);
  CURPOS->value = _value;
  CURPOS->next = NULL;
}


void setValue(char* _id, int _value)
{
  _node *pNode;
  pNode = HEAD->next;
  while(pNode != NULL){
    
    if(strcmp(pNode->id, _id) == 0){
      pNode->value = _value;
      break;
    }
    
    pNode = pNode->next;
  }
}

int getValue(char* _id)
{
  _node *pNode;
  pNode = HEAD->next;
  while(pNode != NULL){
      
    if(strcmp(pNode->id, _id) == 0)
      return pNode->value;
    
    pNode = pNode->next;
  }
}

void dumpTable()
{
  itable = fopen("itable.txt", "w");
   
  _node* pNode;
  pNode = HEAD->next;
  while(pNode != NULL){
    if(strcmp(pNode->type,"procedureID") != 0)
      fprintf(itable, "%s: %s = %d\n", pNode->type, pNode->id, pNode->value);
    else
      fprintf(itable, "%s: %s\n", pNode->type, pNode->id);
    pNode = pNode->next;
  }
  
  fclose(itable);
}

void freeTable()
{
  _node* pNode;
  do {
    pNode = HEAD->next;
    free(HEAD);
    HEAD = pNode;
  } while(pNode != NULL);
  
}

main(int argc, char* argv[])
{
    if (argc == 2) 
      yyin = fopen( argv[1], "r" );
    else {
      printf("found no input parameter!\n");
      return;
    }
    
    createTable();
    
    if(yyparse() == 0)
      printf("success parsing!\n");
    else
      printf("error in line: %d\n", num_line);
    
    dumpTable();
    freeTable();
    
    fclose(yyin); 
}
%}

%union{
  int value;
  char* str;
}


%left '+' '-'
%left '*' '/'

%token <value> _NUM
%token <str> _ID

%token	_VAR _CONST _PROC _CALL _BEGIN _END _DO _IF _THEN
%token	_WHILE _ASSIGN _SEMICOLON _COMMA _LOGIC_OPER _EQ _NEQ
%type <value> value_expression

%%

program_struct:
    | optional_expressions program_body
    | program_struct error { yyerrok; yyclearin; }
    ;
   
program_body:
    _BEGIN statements _END '.'
    ;
   
optional_expressions: /*empty*/
    | optional_expressions _CONST constant_declare _SEMICOLON
    | optional_expressions _VAR variable_declare _SEMICOLON
    | optional_expressions _PROC procedure_declare _SEMICOLON
    ;
   
constant_declare:
    constant_declare _COMMA _ID _EQ _NUM
    {
      addToTable("constantID",$3,$5);
    }
    | _ID _EQ _NUM
    {
      addToTable("constantID",$1,$3);
    }
    ;
   
variable_declare:
    variable_declare _COMMA _ID
    {
      addToTable("variabletID",$3,0);
    }
    | _ID
    {
      addToTable("variabletID",$1,0);
    }
    ;
   
procedure_declare:
    _ID _SEMICOLON _BEGIN statements _END
    {
      addToTable("procedureID",$1,NULL);
    }
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
    value_expression _LOGIC_OPER value_expression
    | value_expression _EQ value_expression
    | value_expression _NEQ value_expression
    ;
  
_body:
    statement 
    | _BEGIN statements _END _SEMICOLON
    ;
  
assign_expression:
    _ID _ASSIGN value_expression
    {
      setValue($1, $3);
    }
    ;
  
value_expression:
    '(' value_expression ')'
    { $$ = $2; }
    | value_expression '+' value_expression
    { $$ = $1 + $3; }
    | value_expression '-' value_expression
    { $$ = $1 - $3; }
    | value_expression '*' value_expression
    { $$ = $1 * $3; }
    | value_expression '/' value_expression
    { $$ = $1 / $3; }
    | _ID
    { 
    $$ = getValue($1);
    //$$ = 2;
    }
    | _NUM
    ;
 

%%
