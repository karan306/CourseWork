%{
	#include "stdio.h"
	#include "parser.tab.h"
	//#include "storetokens.hh"
%}



PRINT print
IF if
WHILE while
DO do
ELSE else
IGNORE [ \t]
NEWLINE [\n]
META_CHAR [\{\},;\(\)\?:]
NAME [a-z_A-Z]([a-zA-Z0-9_])*
ARITHOP [/*+-]
DIGIT [0-9]
NUM {DIGIT}+
DOUB {DIGIT}*(\.{DIGIT}*)?([Ee][+-]?{DIGIT}+)?
ASSIGN_OP =
COMMENT \/\/[^\n]*
LT <
GT >
LTE <=
GTE >=
EQUAL ==
NOT_EQUAL !=
AND &&
NOT !
OR  \|\|

%%
{LTE} {
		store_token_name("LESS_THAN_EQUAL",yytext,yylineno);
		return LTE;
	}
{LT} {
		store_token_name("LESS_THAN",yytext,yylineno);
		return LT;
	}
{GTE} {
		store_token_name("GREATER_THAN_EQUAL",yytext,yylineno);
		return GTE;
	}
{GT} {
		store_token_name("GREATER_THAN",yytext,yylineno);
		return GT;
	}
{EQUAL} {
		store_token_name("EQUAL",yytext,yylineno);
		return EQ;
	}

{NOT_EQUAL} {
		store_token_name("NOT_EQUAL",yytext,yylineno);
		return NEQ;
	}
{AND} {
		store_token_name("AND",yytext,yylineno);
		return AND;
	}	
{NOT} {
		store_token_name("NOT",yytext,yylineno);
		return NOT;
	}	
{OR} {
		store_token_name("OR",yytext,yylineno);
		return OR;
	}	
{DO}     {
		store_token_name("DO",yytext,yylineno);
		return DO;
	}
{PRINT}  {
		store_token_name("PRINT",yytext,yylineno);
		return PRINT;
	}
{WHILE}  {
		store_token_name("WHILE",yytext,yylineno);
		return WHILE;
	}
{IF}     {
		store_token_name("IF",yytext,yylineno);
		return IF;
	}

{ELSE}	 {
		store_token_name("ELSE",yytext,yylineno);
		return ELSE;
	}

{NUM}    { 
		store_token_name("NUM",yytext,yylineno);
		yylval.integer_value=atoi(yytext);
		return INTEGER_NUMBER;
	 }
{DOUB}   {
		store_token_name("FNUM",yytext,yylineno);
		yylval.double_value=atof(yytext);
		return DOUBLE_NUMBER;
	 }
int      {
		store_token_name("INTEGER",yytext,yylineno);
		// printf("int is called\n"); 
		return INTEGER;
	 }
float    {
		store_token_name("FLOAT",yytext,yylineno);
		return FLOAT;
	 }
return   {
		store_token_name("RETURN",yytext,yylineno);
		return RETURN;
	 }
void     {
		store_token_name("VOID",yytext,yylineno);
		return VOID;
	 }
{ARITHOP} {
		store_token_name("ARITHOP",yytext,yylineno);
		return yytext[0];
	  }
{ASSIGN_OP} {
		store_token_name("ASSIGN_OP",yytext,yylineno);
		return ASSIGN;
	    }

{IGNORE} {}
{COMMENT} {}
{NEWLINE} {}

{NAME}  {
		string *s = new std::string(yytext);
		if(!s->compare("main")==0)
			s->append("_");
		store_token_name("NAME",yytext,yylineno);
		yylval.string_value=s;
		// printf("name is called\n"); 
		return NAME;
	}
{META_CHAR} {
		store_token_name("META CHAR",yytext,yylineno);
		// printf("meta char is called\n"); 
		return yytext[0];
	    }

. {printf("cs316: Error : no action found for ' %s '\n",yytext);}
%%
