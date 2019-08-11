%{
#include <stdio.h>
#include <list>
#include "program.hh"
#include "procedure.hh"
#include "ast.hh"
#include "symbol-table.hh"
extern "C" void yyerror(char *s);
extern int yylex(void);
extern int yylineno;	
list<pair<string,int> > vars;
Symbol_Table *gtab;
Procedure *curProc;
int isGlob=1;
%}

%union { 
    int integer_value;
	double double_value;
	std::string * string_value;
	list<Ast *> * ast_list;
	Ast * ast;
	Symbol_Table * symbol_table;
	Symbol_Table_Entry * symbol_entry;
	Basic_Block * basic_block;
	Procedure * procedure;
};


%token <integer_value>INTEGER_NUMBER 
%token <double_value>DOUBLE_NUMBER 
%token INTEGER FLOAT RETURN VOID ASSIGN IF ELSE DO WHILE EQ NEQ LT LTE GT GTE AND OR NOT PRINT
%token <string_value>NAME 
%type <integer_value> INTEGER FLOAT data_type less_greater equal_not_equal
%type <ast> variable FunCall
%type <ast> expression assignment_statement relational_expression cond_expression statement if_else_stmt body else
%type <ast> do_while_stmt while_stmt
%type <ast_list> statement_list exprList
%type <symbol_table> variable_declaration optional_variable_declaration_list proc_declaration 
%type <symbol_table>  var_proc_decl_list argument_list variable_declaration_list var_proc_decl type_list
%type <symbol_entry> argument
%type <procedure> procedure_name

%right '?' ':'
%left OR
%left AND
%left GT GTE LT LTE
%left NEQ EQ
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS NOT

%%

program			:	var_proc_decl_list 
					procedure_definition_list
					
				|	procedure_definition_list
					
			    ;


/*
{
	$1->set_table_scope(global);
	gtab=$1;
	program_object.set_global_table(*$1);
}	
*/
var_proc_decl_list 		:  	var_proc_decl 
							{
								$$=$1; 
								$$->set_table_scope(global);
								gtab=$$;
								program_object.set_global_table(*$$);
							}
						|	var_proc_decl_list  var_proc_decl
							{
								$1->append_list(*$2,yylineno);
								$$=$1;
								$$->set_table_scope(global);
								gtab=$$;
								program_object.set_global_table(*$$);
							}
						;

var_proc_decl			:	variable_declaration {$$=$1;}
						|	proc_declaration {$$=$1;}
						;

proc_declaration		:	data_type NAME '(' ')' ';'	
							{
								$$ = new Symbol_Table();
								Data_Type varType;
								if($1==263)
									varType=int_data_type;
								else if($1==264)
									varType=double_data_type;
								else if($1==265)
									varType=void_data_type;
								if(program_object.variable_in_symbol_list_check(*$2))
									yyerror("proc name cant be same to global var");
								
								Procedure *proc = new Procedure(varType,*$2,yylineno);
								program_object.set_proc_to_map(*$2,proc);
							}
						|	data_type NAME '(' argument_list ')' ';'	
							{
								$$ = new Symbol_Table();
								Data_Type varType;
								if($1==263)
									varType=int_data_type;
								else if($1==264)
									varType=double_data_type;
								else if($1==265)
									varType=void_data_type;
								if(program_object.variable_in_symbol_list_check(*$2))
									yyerror("proc name cant be same to global var");
								
								Procedure *proc = new Procedure(varType,*$2,yylineno);
								$4->set_table_scope(formal);
								proc->set_formal_param_list(*$4);
								program_object.set_proc_to_map(*$2,proc);
							}
						|	data_type NAME '(' type_list ')' ';'	
							{
								$$ = new Symbol_Table();
								Data_Type varType;
								if($1==263)
									varType=int_data_type;
								else if($1==264)
									varType=double_data_type;
								else if($1==265)
									varType=void_data_type;
								if(program_object.variable_in_symbol_list_check(*$2))
									yyerror("proc name cant be same to global var");
								
								Procedure *proc = new Procedure(varType,*$2,yylineno);
								$4->set_table_scope(formal);
								proc->set_formal_param_list(*$4);
								program_object.set_proc_to_map(*$2,proc);
							}
						;

type_list 				: 	type_list ',' data_type	
							{	
								if($3==265) yyerror("void variable type not allowed");
								Data_Type varType;
								if($3==263)
									varType=int_data_type;
								else
									varType=double_data_type;
								string s="";
								Symbol_Table_Entry *e= new Symbol_Table_Entry(s,varType,yylineno);
								$1->push_symbol(e);
								$$=$1;
							}
						|	data_type   
							{
								if($1==265) yyerror("void variable type not allowed");
								Symbol_Table *symtab = new Symbol_Table();
								Data_Type varType;
								if($1==263)
									varType=int_data_type;
								else
									varType=double_data_type;
								string s="";
								Symbol_Table_Entry *e= new Symbol_Table_Entry(s,varType,yylineno);
								symtab->push_symbol(e);
								$$ = symtab;
							}
						;

argument_list			:	argument_list ',' argument
							{
								if(!$1->variable_in_symbol_list_check($3->get_variable_name()))
									$1->push_symbol($3);
								else
									yyerror("Variable is declared twice");
								$$=$1;
							}
						|	argument
							{
								Symbol_Table *symtab = new Symbol_Table();
								symtab->push_symbol($1);
								$$ = symtab;
							}
						;

argument 				:	data_type NAME
							{
								if($1==265) yyerror("void variable type not allowed");
								Data_Type varType;
								if($1==263)
									varType=int_data_type;
								else
									varType=double_data_type;
								$$ = new Symbol_Table_Entry(*$2, varType, yylineno);
							}
						;

procedure_definition_list :	procedure_definition
						| 	procedure_definition_list procedure_definition
						;

procedure_definition	:   procedure_name
							'{'
									optional_variable_declaration_list
									statement_list
							'}'	
							{
								$1->set_ast_list(*$4);
							}
                        ;

procedure_name 			:	data_type NAME '(' ')' 
							{
								Data_Type varType;
								if($1==263)
									varType=int_data_type;
								else if($1==264)
									varType=double_data_type;
								else if($1==265)
									varType=void_data_type;
								if(program_object.variable_in_symbol_list_check(*$2))
									yyerror("proc name cant be same to global var");
								
								if(program_object.variable_in_proc_map_check(*$2)){
									Procedure *temp = program_object.get_procedure_prototype(*$2);
									if(temp->is_proc_defined())
										yyerror("multiple proc definition");
								}
		
								Procedure *proc = new Procedure(varType,*$2,yylineno);
								// proc->set_formal_param_list(*$4);
								proc->set_proc_is_defined();
								program_object.set_proc_to_map(*$2,proc);
								curProc = proc;
								$$ = proc;
							}
						|	data_type NAME '(' argument_list ')' 
							{
								Data_Type varType;
								if($1==263)
									varType=int_data_type;
								else if($1==264)
									varType=double_data_type;
								else if($1==265)
									varType=void_data_type;
								if(program_object.variable_in_symbol_list_check(*$2))
									yyerror("proc name cant be same to global var");
								
								if(program_object.variable_in_proc_map_check(*$2)){
									Procedure *temp = program_object.get_procedure_prototype(*$2);
									if(temp->is_proc_defined())
										yyerror("multiple proc definition");
								}
								Procedure *proc = new Procedure(varType,*$2,yylineno);
								proc->set_formal_param_list(*$4);
								proc->set_proc_is_defined();
								program_object.set_proc_to_map(*$2,proc);
								curProc = proc;
								$$ = proc;
							}
						;

optional_variable_declaration_list	:	/* empty */ 
							{
								$$ = new Symbol_Table();
								$$->set_table_scope(local);
								curProc->set_local_list(*$$);
							}
						|	variable_declaration_list 
							{
								$1->set_table_scope(local);
								curProc->set_local_list(*$1);
								$$ = $1;
							}
						;

variable_declaration_list	:	variable_declaration
							{
								$$=$1;
							}
						|	variable_declaration_list 
							variable_declaration
							{
								$1->append_list(*$2,yylineno);
								$$=$1;
							}
						;

variable_declaration	:	data_type variable_list ';'
							{
								if($1==265) yyerror("void variable type not allowed");
								Symbol_Table *symtab = new Symbol_Table();
								while(!vars.empty()){
									pair<string,int> var=vars.front();
									vars.pop_front();
									Data_Type varType;
									if($1==263)
										varType=int_data_type;
									else
										varType=double_data_type;
									
									Symbol_Table_Entry *e= new Symbol_Table_Entry(var.first,varType,var.second);

									if(!symtab->variable_in_symbol_list_check(var.first))
										symtab->push_symbol(e);
									else
										yyerror("Variable is declared twice");
								}	
								$$ = symtab;							
							}
                        ;

data_type               :   INTEGER
							{
								$<integer_value>$=263;
							}
                        |   FLOAT
							{
								$<integer_value>$=264;
							}
						|	VOID 
							{
								$<integer_value>$=265;
							}
						;
                        
variable_list           :   variable_list ',' NAME
							{
								vars.push_back(make_pair(*($3),yylineno));
							}
						| 	NAME
							{
								vars.push_back(make_pair(*($1),yylineno));
							}
						;

statement_list	        :	/* empty */
							{
								$<ast_list>$ = new list<Ast *>();
							}
			        	|	statement_list statement
			        		{
			        			$1->push_back($2);
			        			$<ast_list>$ = $1;
			        		}
		        		;

statement 				: 	PRINT variable ';'
							{
								Ast* printAst = new Print_Ast($2,yylineno);
								$<ast>$ =  printAst;
							}
						|	assignment_statement
							{
								$<ast>$=$1;
							}
						|	if_else_stmt
							{
								$<ast>$=$1;
							}
						| 	while_stmt
							{
								$<ast>$=$1;
							}
						|	do_while_stmt
							{
								$<ast>$=$1;
							}
						|	'{' statement_list '}' 
							{
								if($2->empty()){
									yyerror("Empty block not allowed");
								}
								Ast * SeqAst = new Sequence_Ast(yylineno);
								list<Ast *>::iterator it;
								for(it=$2->begin();it!=$2->end();it++){
									((Sequence_Ast *)SeqAst)->ast_push_back(*it);
								}
								$<ast>$ = SeqAst;
							}
						|	RETURN ';' 
							{
								Ast * RetAst = new Return_Ast(NULL,curProc->get_proc_name(),yylineno);
								$<ast>$ = RetAst;
							}
						|	RETURN expression ';' 
							{
								Ast * RetAst = new Return_Ast($2,curProc->get_proc_name(),yylineno);
								$<ast>$ = RetAst;
							}
						|	FunCall ';' 
							{
								((Call_Ast*)$1)->set_register(new Register_Descriptor());
								$$=$1;
							}
						;

if_else_stmt 			:	IF '(' cond_expression ')' body else
							{
								Ast* IfAst= new Selection_Statement_Ast($3,$5,$6,yylineno);
								$<ast>$ = IfAst;
							}
						;

body					:	statement 
							{
								// Ast * SeqAst = new Sequence_Ast(yylineno);
								// ((Sequence_Ast *)SeqAst)->ast_push_back($1);
								// $<ast>$=SeqAst;
								$<ast>$=$1;
							}
						;

else 					: 	/* empty */ 
							{
								$<ast>$=NULL;
							}
						|	ELSE body 
							{
								$<ast>$=$2;
							}
						;

do_while_stmt			:	DO body WHILE '(' cond_expression ')' ';'
							{
								Ast* DoAst= new Iteration_Statement_Ast($5,$2,yylineno,1);
								$<ast>$= DoAst;
							}
						;

while_stmt 				: 	WHILE '(' cond_expression ')' body
							{
								Ast* WhiAst= new Iteration_Statement_Ast($3,$5,yylineno,0);
								$<ast>$= WhiAst;
							}
						;	

cond_expression			:	NOT cond_expression %prec NOT
							{
								// cout<<1<<endl;
								Ast * LogAst = new Logical_Expr_Ast(NULL,_logical_not,$2,yylineno);
								// cout<<2<<endl;
								LogAst->check_ast();
								// cout<<3<<endl;
								$<ast>$=LogAst;
							}
						|	cond_expression AND cond_expression
							{
								Ast * LogAst = new Logical_Expr_Ast($1,_logical_and,$3,yylineno);
								LogAst->check_ast();
								$<ast>$=LogAst;
							}
						|	cond_expression OR cond_expression
							{
								Ast * LogAst = new Logical_Expr_Ast($1,_logical_or,$3,yylineno);
								LogAst->check_ast();
								$<ast>$=LogAst;
							}
						|	relational_expression
							{
								$<ast>$=$1;
							}
						|	'(' cond_expression ')'
							{
								$<ast>$=$2;
							}
						;	

relational_expression 	:	expression less_greater expression
							{
								if($2==1)
								{	
									Ast* RelAst=new Relational_Expr_Ast($1,less_than,$3,yylineno);
									RelAst->check_ast();
									$<ast>$=RelAst;
								}
								else if($2==2)
								{	
									Ast* RelAst=new Relational_Expr_Ast($1,less_equalto,$3,yylineno);
									RelAst->check_ast();
									$<ast>$=RelAst;
								}
								else if($2==3)
								{	
									Ast* RelAst=new Relational_Expr_Ast($1,greater_than,$3,yylineno);
									RelAst->check_ast();
									$<ast>$=RelAst;
								}
								else
								{	
									Ast* RelAst=new Relational_Expr_Ast($1,greater_equalto,$3,yylineno);
									RelAst->check_ast();
									$<ast>$=RelAst;
								}

							}
						|	expression equal_not_equal expression
							{
								if($2==1)
								{	
									Ast* RelAst=new Relational_Expr_Ast($1,equalto,$3,yylineno);
									RelAst->check_ast();
									$<ast>$=RelAst;
								}
								else
								{	
									Ast* RelAst=new Relational_Expr_Ast($1,not_equalto,$3,yylineno);
									RelAst->check_ast();
									$<ast>$=RelAst;
								}
							}
						;

less_greater 			: 	LT 	{
									$<integer_value>$=1;
								}
						| 	LTE {
									$<integer_value>$=2;
								}
						|	GT  {
									$<integer_value>$=3;
								}
						|   GTE {
									$<integer_value>$=4;
								}
						;

equal_not_equal         :	EQ  {
									$<integer_value>$=1;
								}
						| 	NEQ {
									$<integer_value>$=2;
								}
						;				

FunCall 				: 	NAME '(' exprList ')'
							{
								if(!program_object.variable_proc_name_check(*$1)){
									yyerror("call to unknown function");
								}
								else{
									Ast* callAst = new Call_Ast(*$1,yylineno);
									((Call_Ast*)callAst)->set_actual_param_list(*$3);
									$$=callAst;
								}
							}
						|	NAME '(' ')'
							{
								if(!program_object.variable_proc_name_check(*$1)){
									yyerror("call to unknown function");
								}
								else{
									Ast* callAst = new Call_Ast(*$1,yylineno);
									list<Ast*> * exp = new list<Ast *>();
									((Call_Ast*)callAst)->set_actual_param_list(*exp);
									$$=callAst;
								}
							}
						;

exprList				: 	exprList ',' expression
							{
								$1->push_back($3);
								$$=$1;
							}
						|	expression
							{
								list<Ast*> * exp = new list<Ast *>();
								exp->push_back($1);
								$$=exp;
							}
						;

assignment_statement	:	variable ASSIGN expression ';' 
							{
								Ast* assAst = new Assignment_Ast($1,$3,yylineno);
								assAst->check_ast();
								$<ast>$= assAst;
							}
						|	variable ASSIGN FunCall ';'
							{
								Ast* assAst = new Assignment_Ast($1,$3,yylineno);
								assAst->check_ast();
								$<ast>$= assAst;
							}
                        ;

expression              : 	'-' expression  %prec UMINUS
							{
								// cout<<"1"<<endl;
								//$2->print();
								// cout<<"2"<<endl;
								Ast *unaryAst = new UMinus_Ast($2,NULL,yylineno);
								// unaryAst->check_ast();
								// cout<<"3"<<endl;
								$<ast>$ = unaryAst;
							}
						|	expression '+' expression 
							{
								Ast *plusAst = new Plus_Ast($1,$3,yylineno);
								plusAst->check_ast();
								$<ast>$ = plusAst;
							}
						|	expression '-' expression
							{
								Ast *minAst = new Minus_Ast($1,$3,yylineno);
								minAst->check_ast();
								$<ast>$ = minAst;
							}
						| 	expression '*' expression
							{
								Ast *mulAst = new Mult_Ast($1,$3,yylineno);
								mulAst->check_ast();
								$<ast>$ = mulAst;
							}
						|	expression '/' expression
							{
								Ast *divAst = new Divide_Ast($1,$3,yylineno);
								divAst->check_ast();
								$<ast>$ = divAst;
							}
						|	cond_expression '?' expression ':' expression
							{
								Ast *CondAst= new Conditional_Expression_Ast($1,$3,$5,yylineno);
								CondAst->check_ast();
								$<ast>$ = CondAst;
							}
						| 	'(' expression ')'
							{
								$$=$2;
							}
                        |   variable
							{
								$<ast>$ = $1;
							}
                        |   INTEGER_NUMBER
							{
								Ast* intAst = new Number_Ast<int>($<integer_value>1,int_data_type,yylineno);
								$<ast>$= intAst;
							}
						|	DOUBLE_NUMBER
							{
								Ast* doubAst = new Number_Ast<double>($<double_value>1,double_data_type,yylineno);
								$<ast>$ = doubAst;
							}
                        ;

variable		        :	NAME	
						{
							Symbol_Table symtab ;
							if(curProc->get_local_list().variable_in_symbol_list_check(*$1)){
								symtab=curProc->get_local_list();
							}
							else if(curProc->get_formal_param_list().variable_in_symbol_list_check(*$1)){
								symtab=curProc->get_formal_param_list();
							}
							else if(gtab->variable_in_symbol_list_check(*$1)){
								symtab=*gtab;
							}
							else{
								yyerror("Variable has not been declared");
							}

							Ast* varAst = new Name_Ast(*$1,symtab.get_symbol_table_entry(*$1),yylineno);
							varAst->set_data_type(symtab.get_symbol_table_entry(*$1).get_data_type());
							$<ast>$= varAst;
						}
                        ;

%%
void yyerror(char* s){
    printf("cs316: Error : Line : %d: %s\n",yylineno,s);
	exit(0);
}
// void yyparse()