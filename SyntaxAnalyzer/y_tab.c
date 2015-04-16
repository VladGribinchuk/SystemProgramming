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
#line 53 "y.tab.c"

#if ! defined(YYSTYPE) && ! defined(YYSTYPE_IS_DECLARED)
/* Default: YYSTYPE is the semantic value type. */
typedef int YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
#endif

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

#define _VAR 257
#define _CONST 258
#define _PROC 259
#define _CALL 260
#define _BEGIN 261
#define _END 262
#define _DO 263
#define _IF 264
#define _THEN 265
#define _UNKN_SYM 266
#define _LPAREN 267
#define _RPAREN 268
#define _WHILE 269
#define _ASSIGN 270
#define _SEMICOLON 271
#define _COMMA 272
#define _MATH_OPER 273
#define _LOGIC_OPER 274
#define _NUM 275
#define _ID 276
#define _DOT 277
#define _EQ 278
#define _NEQ 279
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    2,    1,    1,    1,    1,    4,    4,    5,    5,
    6,    3,    3,    7,    7,    7,    7,    7,    9,    9,
    9,   10,   10,    8,   12,   12,   11,   11,   11,
};
static const YYINT yylen[] = {                            2,
    2,    4,    0,    4,    4,    4,    5,    3,    3,    1,
    5,    0,    2,    1,    3,    2,    4,    4,    3,    3,
    3,    1,    4,    3,    3,    1,    1,    1,    3,
};
static const YYINT yydefred[] = {                         3,
    0,    0,    0,    0,    0,   12,    1,   10,    0,    0,
    0,    0,    0,    0,    5,    0,    0,    4,    0,    0,
    6,    0,    0,    0,    0,   14,    0,   13,    0,    9,
    8,    0,   12,    0,    2,    0,   28,   27,    0,    0,
    0,    0,   16,    0,    0,   15,   26,    0,    0,    0,
    0,    0,    0,    0,    7,   11,   29,    0,   12,   22,
   17,   19,   20,   21,   18,    0,    0,    0,   23,
};
static const YYINT yydgoto[] = {                          1,
    2,    7,   14,   11,    9,   13,   28,   29,   39,   61,
   47,   48,
};
static const YYINT yysindex[] = {                         0,
    0, -210, -261, -253, -244,    0,    0,    0, -219, -236,
 -216, -214, -213, -258,    0, -217, -215,    0, -212, -200,
    0, -211, -209, -232, -232,    0, -208,    0, -205,    0,
    0, -207,    0, -204,    0, -232,    0,    0, -202, -241,
 -194, -232,    0, -203, -255,    0,    0, -228, -230, -232,
 -232, -232, -230, -199,    0,    0,    0, -232,    0,    0,
    0,    0,    0,    0,    0, -199, -252, -201,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -198,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -246,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,    0,  -30,    0,    0,    0,    1,    0,   50,   23,
  -24,  -22,
};
#define YYTABLESIZE 76
static const YYINT yytable[] = {                         40,
   40,   22,   45,   23,   22,   24,   56,   22,   24,   68,
   25,   24,   26,   25,    8,   26,   25,   27,   26,   54,
   27,   25,   10,   27,   25,   62,   63,   64,   67,   22,
   59,   12,   50,   24,   36,   66,   51,   52,   25,   57,
   26,   17,   37,   38,   58,   27,    3,    4,    5,   60,
    6,   15,   16,   60,   18,   19,   20,   21,   30,   31,
   33,   42,   49,   32,   34,   43,   46,   35,   53,   69,
   44,   55,   24,   58,   41,   65,
};
static const YYINT yycheck[] = {                         24,
   25,  260,   33,  262,  260,  264,  262,  260,  264,  262,
  269,  264,  271,  269,  276,  271,  269,  276,  271,   42,
  276,  268,  276,  276,  271,   50,   51,   52,   59,  260,
  261,  276,  274,  264,  267,   58,  278,  279,  269,  268,
  271,  278,  275,  276,  273,  276,  257,  258,  259,   49,
  261,  271,  272,   53,  271,  272,  271,  271,  276,  275,
  261,  270,  265,  276,  276,  271,  271,  277,  263,  271,
  278,  275,  271,  273,   25,   53,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 279
#define YYUNDFTOKEN 294
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"_VAR","_CONST","_PROC","_CALL",
"_BEGIN","_END","_DO","_IF","_THEN","_UNKN_SYM","_LPAREN","_RPAREN","_WHILE",
"_ASSIGN","_SEMICOLON","_COMMA","_MATH_OPER","_LOGIC_OPER","_NUM","_ID","_DOT",
"_EQ","_NEQ",0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program_stuct",
"program_stuct : optional_expressions program_body",
"program_body : _BEGIN statements _END _DOT",
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
"condition_expression : atom _LOGIC_OPER atom",
"condition_expression : atom _EQ atom",
"condition_expression : atom _NEQ atom",
"_body : statement",
"_body : _BEGIN statements _END _SEMICOLON",
"assign_expression : _ID _ASSIGN value",
"value : value _MATH_OPER value",
"value : atom",
"atom : _ID",
"atom : _NUM",
"atom : _LPAREN value _RPAREN",

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
