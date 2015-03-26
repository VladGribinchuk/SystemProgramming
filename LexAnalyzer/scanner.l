%option noyywrap
%{
  #include <stdio.h>
  #include <math.h>
  #include "scan_header.h"
  
  int num_lines = 1;
%}

DIGIT [0-9]
LETTER [a-zA-Z]
IDENTIFIER [a-z][a-zA-Z0-9]*


     
%%

var|VAR 		return _VAR_STAT;
const|CONST 		return _CONST_STAT;
procedure|PROCEDURE 	return _PROC_STAT;
call|CALL		return _CALL_STAT;
begin|BEGIN		return _BEG_STAT;
"end"|"END"			return _END_STAT;
do|DO			return _DO_STAT;
if|IF			return _IF_STAT;
then|THEN		return _THEN_STAT;
while|WHILE		return _WHILE_STAT;

\+		return _PLUS;
\-		return _MINUS;
\/		return _DIRECT_SLASH;
\*		return _TIMES;
":="		return _ASSIGN;
\(		return _LPAREN;
\)		return _RPAREN;

\=		return _EQ;
\#		return _NEQ;
\>		return _GT;
\<		return _LT;
">="		return _GE;
"<="		return _LE;

\;		return _SEMICOLON;
\:		return _COLON;
\,		return _COMMA;
\.		return _DOT;

{LETTER}({LETTER}|{DIGIT})*	return _ID;
{DIGIT}				return _NUM;

\n				{num_lines++;}
[\t\f' '] 			;
.				return _UNKNOWN_SYMBOL;

%%         
int main( int argc, char **argv )
{
  ++argv;--argc;
  if ( argc > 0 ) yyin = fopen( argv[0], "r" );
  else yyin = stdin;
  
  int extra_lexeme,
      num_id;
  char id_lexeme[20];
  int token_lexeme = yylex();
  while(token_lexeme){
    switch(token_lexeme){
    
    case _BEG_STAT:
      printf("_BEG_STATEMENT\n");
      break;
    case _END_STAT:
      printf("_END_STATEMENT\n");
      break;
    case _PROC_STAT:
      printf("_PROC_STATEMENT(procedure declaration): ");
      extra_lexeme = yylex();
      if (extra_lexeme != _ID ){
	printf("Error in line: %d, expected an identifier procedure, but found: \'%s\'\n", num_lines, yytext);
	return 1;
      } 
      else
	printf("_ID(%s)", yytext);
      break;
    case _CALL_STAT:
      printf("_CALL_STATEMENT: ");
      extra_lexeme = yylex();
      if (extra_lexeme != _ID ){
	printf("Error in line: %d, expected an identifier procedure which has called, but found: \'%s\'\n", num_lines, yytext);
	return 1;
      } 
      else
	printf("_ID(%s)", yytext);
      break;
    case _DO_STAT:
      printf("_DO_STATEMENT:\n");
      break;
    case _THEN_STAT:
      printf("_THEN_STATEMENT:\n");
      break;
    
    case _CONST_STAT:
      printf("_CONST_STATEMENT(constant declaration unit):\n");
      extra_lexeme = yylex();
      while( extra_lexeme != _SEMICOLON){
	strcpy(id_lexeme, yytext);
	if (extra_lexeme != _ID ){
	  printf("Error in line: %d, expected an identifier, but found: \'%s\'\n", num_lines, yytext);
	  return 1;
	} 
	else {
	  extra_lexeme = yylex();
	    if (extra_lexeme != _EQ ){
	      printf("Error in line: %d, constant value undefined, expected \'=\'\n", num_lines);
	      return 1;
	    } 
	    else {
	      extra_lexeme = yylex();
	      num_id = atoi(yytext);
	      if (extra_lexeme != _NUM ){
		printf("Error in line: %d, expected class _NUM, but found \'%s\'\n", num_lines, yytext);
		return 1;
	      }
	    }
	  printf("_ID(%s) set to _NUM(%d)\n", id_lexeme, num_id);
	}
	
	extra_lexeme = yylex();
	if (extra_lexeme == _COMMA){
	  extra_lexeme = yylex();
	  if (extra_lexeme != _ID ){
	    printf("Error in line: %d, expected an identifier, but found: \'%s\'\n", num_lines, yytext);
	    return 1;
	  } 
	}
      }
      break;
    
    case _VAR_STAT:
      printf("_VAR_STATEMENT(var declaration unit):\n");
      extra_lexeme = yylex();
      while( extra_lexeme != _SEMICOLON){
	if (extra_lexeme != _ID ){
	  printf("Error in line: %d, expected an identifier, but found: \'%s\'\n", num_lines, yytext);
	  return 1;
	} 
	else {
	  printf("_ID(%s) has been declared\n", yytext);
	}
	
	extra_lexeme = yylex();
	if (extra_lexeme == _COMMA){
	  extra_lexeme = yylex();
	  if (extra_lexeme != _ID ){
	    printf("Error in line: %d, expected an identifier, but found: \'%s\'\n", num_lines, yytext);
	    return 1;
	  } 
	}	  
      }
      break;
      
      case _IF_STAT:
	printf("_IF_STATEMENT(condition): ");
	extra_lexeme = yylex();
	if(extra_lexeme!=_ID && extra_lexeme!=_NUM){
	  printf("Error in line: %d, expected _NUM or _ID for condition\n", num_lines);
	  return 1;
	} 
	else {
	  token_lexeme = extra_lexeme;
	  continue;
	}
	break;
      
      case _WHILE_STAT:
	printf("_WHILE_STATEMENT(condition): ");
	extra_lexeme = yylex();
	if(extra_lexeme!=_ID && extra_lexeme!=_NUM){
	  printf("Error in line: %d, expected _NUM or _ID for condition\n", num_lines);
	  return 1;
	} 
	else {
	  token_lexeme = extra_lexeme;
	  continue;
	}
      break;
      
      case _ID:
	printf("_ID(%s) ", yytext);
	extra_lexeme = yylex();
	if(extra_lexeme == _ASSIGN){
	  extra_lexeme = yylex();
	  if(extra_lexeme!=_ID && extra_lexeme!=_NUM){
	    printf("Error in line: %d, bad assign operation\n", num_lines);
	    return 1;
	  } 
	  else {
	    printf("assign to ");
	    if (extra_lexeme == _NUM)
	      printf("_NUM(%s) ", atoi(yytext));
	    else
	      printf("_ID(%s) ", yytext);
	  }
	}
	else {
	 token_lexeme = extra_lexeme;
	 continue;
	}
	break;
      case _NUM:
	printf("_NUM(%s) ", yytext);
	break;
      case _PLUS:
	printf("_PLUS(%s) ", yytext);
	break;
      case _MINUS:
	printf("_MINUS(%s) ", yytext);
	break;
      case _DIRECT_SLASH:
	printf("_SLASH(%s) ", yytext);
	break;
      case _TIMES:
	printf("_TIMES(%s) ", yytext);
	break;
      case _EQ:
	printf("_EQ(=) ", yytext);
	break;
      case _NEQ:
	printf("_NEQ(#) ", yytext);
	break;
      case _GT:
	printf("_GT(>) ", yytext);
	break;
      case _LT:
	printf("_LT(<) ", yytext);
	break;
      case _GE:
	printf("_GE(>=) ", yytext);
	break;
      case _LE:
	printf("_LE(<=) ", yytext);
	break;
      case _SEMICOLON:
	printf("\n");
	break;
      case _LPAREN:
	printf("_LPAREN\'(\' ");
	break;
      case _RPAREN:
	printf("_RPAREN\')\' ");
	break;
      case _DOT:
	printf("<<EOF>>, errors not found\n");
	break;
      
      case _UNKNOWN_SYMBOL:
	printf("Error in line: %d, _UNKNOWN_SYMBOL(%s)\n", num_lines, yytext);
	return 1;
      default:
	break;
    }  // end switch
    token_lexeme = yylex();
  } // end while
}






