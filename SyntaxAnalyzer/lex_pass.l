%option noyywrap
%{
  #include <stdio.h>
  #include "y.tab.h"
  int num_line = 1;
%}

DIGIT [0-9]
LETTER [a-zA-Z]
  
%%
  
VAR		return _VAR;
CONST		return _CONST;
PROCEDURE	return _PROC;
CALL		return _CALL;
BEGIN		return _BEGIN;
END		return _END;
DO		return _DO;
IF		return _IF;
THEN		return _THEN;
WHILE		return _WHILE;
 
\=		return _EQ; 
\#		return _NEQ;
":="		return _ASSIGN;
\;		return _SEMICOLON;
[\,]		return _COMMA;
  
[\>\<] 		return _LOGIC_OPER;
  
{DIGIT}		yylval.value = atoi(yytext); return _NUM;
{LETTER}({LETTER}|{DIGIT})*	yylval.str = strdup(yytext); return _ID;
\n		num_line++;
[\t' ']	;
.		return (int) yytext[0];
  
%%