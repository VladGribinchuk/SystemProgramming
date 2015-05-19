#define _NUM 257
#define _ID 258
#define _VAR 259
#define _CONST 260
#define _PROC 261
#define _CALL 262
#define _BEGIN 263
#define _END 264
#define _DO 265
#define _IF 266
#define _THEN 267
#define _WHILE 268
#define _ASSIGN 269
#define _SEMICOLON 270
#define _COMMA 271
#define _LOGIC_OPER 272
#define _EQ 273
#define _NEQ 274
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
  int value;
  char* str;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
