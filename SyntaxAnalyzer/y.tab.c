/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "yacc_pass.y"
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
#line 127 "yacc_pass.y"
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
#line 157 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

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
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    0,    3,    2,    2,    2,    2,    5,    5,
    6,    6,    7,    4,    4,    8,    8,    8,    8,    8,
   10,   10,   10,   11,   11,    9,    1,    1,    1,    1,
    1,    1,    1,
};
static const YYINT yylen[] = {                            2,
    0,    2,    2,    4,    0,    4,    4,    4,    5,    3,
    3,    1,    5,    0,    2,    1,    3,    2,    4,    4,
    3,    3,    3,    1,    4,    3,    3,    3,    3,    3,
    3,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    3,    0,    0,    0,   14,    2,   12,    0,
    0,    0,    0,    0,    0,    7,    0,    0,    6,    0,
    0,    8,    0,    0,    0,    0,    0,   16,   15,    0,
   11,   10,    0,   14,    0,    0,    4,   33,   32,    0,
    0,    0,    0,   18,    0,    0,    0,   17,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    9,   13,
   27,    0,    0,   30,   31,    0,    0,    0,   14,   24,
   19,   20,    0,    0,   25,
};
static const YYINT yydgoto[] = {                          1,
   41,    2,    8,   15,   12,   10,   14,   29,   30,   42,
   71,
};
static const YYINT yysindex[] = {                         0,
 -250, -191,    0, -234, -208, -204,    0,    0,    0, -196,
 -216, -193, -189, -188, -239,    0, -182, -195,    0, -175,
 -179,    0, -184, -172,   41,  -37,  -37,    0,    0, -181,
    0,    0, -185,    0,  -37, -180,    0,    0,    0,  -37,
  -27, -176, -173,    0, -164, -219,   -1,    0,  -34,  -37,
  -37,  -37,  -37,  -37,  -37,  -37, -210, -210,    0,    0,
    0,  -21,  -21,    0,    0,   -1,   -1,   -1,    0,    0,
    0,    0, -203, -174,    0,
};
static const YYINT yyrindex[] = {                         1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -171,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -41,  -31,    0,    0, -237, -201, -194,    0,    0,
    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  -18,    0,    0,  -29,    0,    0,    0,   22,    0,   67,
   37,
};
#define YYTABLESIZE 264
static const YYINT yytable[] = {                         28,
    1,   28,   40,   28,   46,    3,   61,   52,   50,   29,
   51,   29,   53,   29,   52,   50,   47,   51,   23,   53,
   52,   49,   24,    9,   25,   53,   26,   21,   27,   21,
   28,   62,   63,   64,   65,   66,   67,   68,   23,   73,
   52,   50,   24,   51,   60,   53,   26,   23,   27,   11,
   28,   24,   69,   13,   23,   26,   18,   27,   24,   28,
   74,   32,   26,   22,   27,   22,   28,    4,    5,    6,
   23,    7,   23,   16,   17,   31,   19,   20,   70,   70,
   21,   22,   33,   34,   35,   36,   37,   45,   44,   48,
   57,   58,   59,   43,   72,   75,    0,    0,   26,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   38,
   39,    0,    0,   28,    0,   28,    0,    0,   28,    0,
   28,   28,   28,   29,    0,   29,    0,    0,   29,    0,
   29,   29,   29,    0,   54,   55,   56,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    1,    0,    0,    5,
    5,    5,    0,    5,
};
static const YYINT yycheck[] = {                         41,
    0,   43,   40,   45,   34,  256,   41,   42,   43,   41,
   45,   43,   47,   45,   42,   43,   35,   45,  258,   47,
   42,   40,  262,  258,  264,   47,  266,  265,  268,  267,
  270,   50,   51,   52,   53,   54,   55,   56,  258,   69,
   42,   43,  262,   45,  264,   47,  266,  258,  268,  258,
  270,  262,  263,  258,  258,  266,  273,  268,  262,  270,
  264,  257,  266,  265,  268,  267,  270,  259,  260,  261,
  265,  263,  267,  270,  271,  258,  270,  271,   57,   58,
  270,  270,  258,  263,  269,  258,   46,  273,  270,  270,
  267,  265,  257,   27,   58,  270,   -1,   -1,  270,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,
  258,   -1,   -1,  265,   -1,  267,   -1,   -1,  270,   -1,
  272,  273,  274,  265,   -1,  267,   -1,   -1,  270,   -1,
  272,  273,  274,   -1,  272,  273,  274,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  256,   -1,   -1,  259,
  260,  261,   -1,  263,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 274
#define YYUNDFTOKEN 288
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'",0,"'-'","'.'","'/'",0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"_NUM","_ID","_VAR","_CONST","_PROC","_CALL","_BEGIN","_END","_DO","_IF",
"_THEN","_WHILE","_ASSIGN","_SEMICOLON","_COMMA","_LOGIC_OPER","_EQ","_NEQ",0,0,
0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program_struct",
"program_struct :",
"program_struct : optional_expressions program_body",
"program_struct : program_struct error",
"program_body : _BEGIN statements _END '.'",
"optional_expressions :",
"optional_expressions : optional_expressions _CONST constant_declare _SEMICOLON",
"optional_expressions : optional_expressions _VAR variable_declare _SEMICOLON",
"optional_expressions : optional_expressions _PROC procedure_declare _SEMICOLON",
"constant_declare : constant_declare _COMMA _ID _EQ _NUM",
"constant_declare : _ID _EQ _NUM",
"variable_declare : variable_declare _COMMA _ID",
"variable_declare : _ID",
"procedure_declare : _ID _SEMICOLON _BEGIN statements _END",
"statements :",
"statements : statements statement",
"statement : _SEMICOLON",
"statement : _CALL _ID _SEMICOLON",
"statement : assign_expression _SEMICOLON",
"statement : _IF condition_expression _THEN _body",
"statement : _WHILE condition_expression _DO _body",
"condition_expression : value_expression _LOGIC_OPER value_expression",
"condition_expression : value_expression _EQ value_expression",
"condition_expression : value_expression _NEQ value_expression",
"_body : statement",
"_body : _BEGIN statements _END _SEMICOLON",
"assign_expression : _ID _ASSIGN value_expression",
"value_expression : '(' value_expression ')'",
"value_expression : value_expression '+' value_expression",
"value_expression : value_expression '-' value_expression",
"value_expression : value_expression '*' value_expression",
"value_expression : value_expression '/' value_expression",
"value_expression : _ID",
"value_expression : _NUM",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 3:
#line 147 "yacc_pass.y"
	{ yyerrok; yyclearin; }
break;
case 9:
#line 162 "yacc_pass.y"
	{
      addToTable("constantID",yystack.l_mark[-2].str,yystack.l_mark[0].value);
    }
break;
case 10:
#line 166 "yacc_pass.y"
	{
      addToTable("constantID",yystack.l_mark[-2].str,yystack.l_mark[0].value);
    }
break;
case 11:
#line 173 "yacc_pass.y"
	{
      addToTable("variabletID",yystack.l_mark[0].str,0);
    }
break;
case 12:
#line 177 "yacc_pass.y"
	{
      addToTable("variabletID",yystack.l_mark[0].str,0);
    }
break;
case 13:
#line 184 "yacc_pass.y"
	{
      addToTable("procedureID",yystack.l_mark[-4].str,NULL);
    }
break;
case 26:
#line 214 "yacc_pass.y"
	{
      setValue(yystack.l_mark[-2].str, yystack.l_mark[0].value);
      printf("%s = %d", yystack.l_mark[-2].str,yystack.l_mark[0].value);
    }
break;
case 27:
#line 222 "yacc_pass.y"
	{ yyval.value = yystack.l_mark[-1].value; }
break;
case 28:
#line 224 "yacc_pass.y"
	{ yyval.value = yystack.l_mark[-2].value + yystack.l_mark[0].value; }
break;
case 29:
#line 226 "yacc_pass.y"
	{ yyval.value = yystack.l_mark[-2].value - yystack.l_mark[0].value; }
break;
case 30:
#line 228 "yacc_pass.y"
	{ yyval.value = yystack.l_mark[-2].value * yystack.l_mark[0].value; }
break;
case 31:
#line 230 "yacc_pass.y"
	{ yyval.value = yystack.l_mark[-2].value / yystack.l_mark[0].value; }
break;
case 32:
#line 232 "yacc_pass.y"
	{ 
    yyval.value = getValue(yystack.l_mark[0].str);
    /*$$ = 2;*/
    }
break;
#line 681 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
