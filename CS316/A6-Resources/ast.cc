#include "ast.hh"
#include "symbol-table.hh"
#include "procedure.hh"
#include "program.hh"

template class Number_Ast<double>;
template class Number_Ast<int>;

int Ast::labelCounter=0;

Ast::Ast(){

}

Ast::~Ast(){

}

void general_print(ostream &file_buffer, Ast* lhs, Ast* rhs,string space)
{
    file_buffer << "\n" << space << "LHS (";
    lhs->print(file_buffer);
    file_buffer << ")";
    file_buffer << "\n" << space << "RHS (";
    rhs->print(file_buffer);
    file_buffer << ")";
}

Data_Type Ast::get_data_type(){
    return node_data_type;
}

void Ast::set_data_type(Data_Type dt){
    node_data_type = dt;
}

bool Ast::is_value_zero(){}
bool Ast::check_ast(){}
Symbol_Table_Entry & Ast::get_symbol_entry(){}

void Ast::print(ostream &file_buffer){}


// Code_For_Ast & Ast::compile(){}
// Code_For_Ast & Ast::compile_and_optimize_ast(Lra_Outcome & lra){}
// Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register){}


Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line)
{
	lhs = temp_lhs;
	rhs = temp_rhs;
    node_data_type = void_data_type;
	ast_num_child = binary_arity;
	lineno = line;
}

Assignment_Ast::~Assignment_Ast()
{
	delete lhs;
	delete rhs;
}

bool Assignment_Ast::check_ast(){
    if (lhs->get_data_type() == rhs->get_data_type())
	{
		set_data_type(lhs->get_data_type());
		return true;
	}
    printf("cs316: Error : Data type not compatible for assignment\n");
    exit(0);
    return false;
}

void Assignment_Ast::print(ostream & file_buffer)
{
    file_buffer << "\n" << AST_SPACE << "Asgn:";
    general_print(file_buffer,lhs,rhs,AST_NODE_SPACE);
}


Name_Ast::Name_Ast(string & name, Symbol_Table_Entry & var_entry, int line){
    variable_symbol_entry = &var_entry;
    ast_num_child = zero_arity;
    node_data_type = var_entry.get_data_type();
    lineno=line;
}

Symbol_Table_Entry & Name_Ast::get_symbol_entry(){
    return *variable_symbol_entry;
}

Data_Type Name_Ast::get_data_type(){
    return node_data_type;
}

void Name_Ast::set_data_type(Data_Type dt){
    node_data_type = dt;
}

void Name_Ast::print(ostream & file_buffer){
    file_buffer << "Name : " << variable_symbol_entry->get_variable_name();
}

template <class DATA_TYPE> 
Number_Ast<DATA_TYPE> :: Number_Ast(DATA_TYPE number, Data_Type constant_data_type, int line){
    constant=number;
    node_data_type=constant_data_type;
    lineno=line;
    ast_num_child=zero_arity;
}

template <class DATA_TYPE>
Number_Ast<DATA_TYPE>::~Number_Ast(){}

template <class DATA_TYPE>
void Number_Ast<DATA_TYPE>::print(ostream & file_buffer)
{
    file_buffer << "Num : " << constant;
}

template <class DATA_TYPE>
Data_Type Number_Ast<DATA_TYPE>::get_data_type(){
    return node_data_type;
}

template <class DATA_TYPE>
void Number_Ast<DATA_TYPE>::set_data_type(Data_Type dt){
    node_data_type = dt;
}

template <class DATA_TYPE>
bool Number_Ast<DATA_TYPE>::is_value_zero(){}


bool Arithmetic_Expr_Ast::check_ast(){
    if (lhs->get_data_type() == rhs->get_data_type())
    {
        set_data_type(lhs->get_data_type());
        return true;
    }
    printf("cs316: Error : Data type not compatible for arithmetic expression\n");
    exit(0);
    return false;
}

Data_Type Arithmetic_Expr_Ast::get_data_type(){
    return node_data_type;
}

void Arithmetic_Expr_Ast::set_data_type(Data_Type dt){
    node_data_type = dt;
}

void Arithmetic_Expr_Ast::print(ostream & file_buffer){}

Plus_Ast::Plus_Ast(Ast * l, Ast * r, int line){
    lhs=l;
    rhs=r;
    lineno=line;
    ast_num_child = binary_arity;
}

void Plus_Ast::print(ostream &file_buffer){
    file_buffer << "\n" << AST_NODE_SPACE << "Arith: PLUS";
    general_print(file_buffer,lhs,rhs,AST_SUB_NODE_SPACE);
}

Minus_Ast::Minus_Ast(Ast * l, Ast * r, int line){
    lhs=l;
    rhs=r;
    lineno=line;
    ast_num_child = binary_arity;
}
void Minus_Ast::print(ostream &file_buffer){
    file_buffer << "\n" << AST_NODE_SPACE << "Arith: MINUS";
    general_print(file_buffer,lhs,rhs,AST_SUB_NODE_SPACE);
}


Divide_Ast::Divide_Ast(Ast * l, Ast * r, int line){
    lhs=l;
    rhs=r;
    lineno=line;
    ast_num_child = binary_arity;
}

void Divide_Ast::print(ostream &file_buffer){
    file_buffer << "\n" << AST_NODE_SPACE << "Arith: DIV";
    general_print(file_buffer,lhs,rhs,AST_SUB_NODE_SPACE);
}


Mult_Ast::Mult_Ast(Ast * l, Ast * r, int line){
    lhs=l;
    rhs=r;
    lineno=line;
    ast_num_child = binary_arity;
}

void Mult_Ast::print(ostream &file_buffer){
    file_buffer << "\n" << AST_NODE_SPACE << "Arith: MULT";
    general_print(file_buffer,lhs,rhs,AST_SUB_NODE_SPACE);
}

UMinus_Ast::UMinus_Ast(Ast * l, Ast * r, int line){
    // cout<<"4"<<endl;
    lhs=l;
    rhs=r;
    lineno=line;
    ast_num_child = unary_arity;
    node_data_type=l->get_data_type();
    // cout<<"5"<<endl;
}
void UMinus_Ast::print(ostream &file_buffer){
    file_buffer << "\n" << AST_NODE_SPACE << "Arith: UMINUS";
    file_buffer << "\n" << AST_SUB_NODE_SPACE << "LHS (";
    lhs->print(file_buffer);
    file_buffer << ")";
    // general_print(file_buffer,lhs,rhs,AST_SUB_NODE_SPACE);
}

Conditional_Expression_Ast::Conditional_Expression_Ast(Ast* c, Ast* l, Ast* r, int line){
    cond=c;
    lhs=l;
    rhs=r;
    lineno=line;
    node_data_type=l->get_data_type();
    ast_num_child=ternary_arity;
    get_new_label();
}

Conditional_Expression_Ast::~Conditional_Expression_Ast(){}

void Conditional_Expression_Ast::print(ostream & file_buffer){
    file_buffer << "\n" << AST_SPACE << "Cond:";
    file_buffer<< "\n" <<AST_NODE_SPACE<< "IF_ELSE";
    cond->print(file_buffer);
    general_print(file_buffer,lhs,rhs,AST_NODE_SPACE);
}

Relational_Expr_Ast::Relational_Expr_Ast(Ast * lhs, Relational_Op rop, Ast * rhs, int line)
{
    lhs_condition=lhs;
    rel_op=rop;
    rhs_condition=rhs;
    lineno=line;
    node_data_type=lhs->get_data_type();
    ast_num_child=binary_arity;
}

Relational_Expr_Ast::~Relational_Expr_Ast(){}

Data_Type Relational_Expr_Ast::get_data_type(){
    return node_data_type;
}
void Relational_Expr_Ast::set_data_type(Data_Type dt){
    node_data_type=dt;
}

bool Relational_Expr_Ast::check_ast(){
    if (lhs_condition->get_data_type() == rhs_condition->get_data_type())
    {
        set_data_type(lhs_condition->get_data_type());
        // cerr<<"hey there"<<endl;
        return true;
    }
    printf("cs316: Error : Data type not compatible for Relational expression\n");
    exit(0);
    return false;
}

void Relational_Expr_Ast::print(ostream & file_buffer){
    string s;
    if(rel_op==less_equalto) s="LE";
    else if(rel_op==greater_than) s="GT";
    else if(rel_op==greater_equalto) s="GE";
    else if(rel_op==less_than) s="LT";
    else if(rel_op==equalto) s="EQ";
    else if(rel_op==not_equalto) s="NE";
    file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: "<<s;
    general_print(file_buffer,lhs_condition,rhs_condition,AST_SUB_NODE_SPACE);
}

Logical_Expr_Ast::Logical_Expr_Ast(Ast * lhs, Logical_Op bop, Ast * rhs, int line){
    lhs_op=lhs;
    rhs_op=rhs;
    bool_op=bop;
    lineno=line;
    node_data_type=int_data_type;
    if(bop==_logical_not)
        ast_num_child=unary_arity;
    else ast_num_child=binary_arity;
}

Logical_Expr_Ast::~Logical_Expr_Ast(){}

Data_Type Logical_Expr_Ast::get_data_type(){
    return node_data_type;
}
void Logical_Expr_Ast::set_data_type(Data_Type dt){
    node_data_type=dt;
}

bool Logical_Expr_Ast::check_ast(){
    // cerr<<4<<endl;
    if(bool_op==_logical_not){
        // cerr<<5<<endl;
        if(rhs_op->get_data_type()==int_data_type)
        {
            // cerr<<6<<endl;
            set_data_type(int_data_type);
            return true;
        }
        else{
            printf("cs316: Error : Logical operation not allowed on float comparisons\n");
            exit(0);
        }
        // cerr<<7<<endl;
    }
    else if (lhs_op->get_data_type() == rhs_op->get_data_type()==int_data_type)
    {
        set_data_type(int_data_type);
        return true;
    }
    printf("cs316: Error : Data type not compatible for logical expression\n");
    exit(0);
    return false;
}

void Logical_Expr_Ast::print(ostream &file_buffer){
    if (ast_num_child==unary_arity){
        file_buffer << "\n" << AST_NODE_SPACE << "Condition: NOT";
        // cerr<<"hi"<<endl;
        file_buffer << "\n" << AST_SUB_NODE_SPACE << "RHS (";
        rhs_op->print(file_buffer);
        file_buffer << ")";
        return;
    }
    string s;
    if (bool_op==_logical_or) s="OR";
    else s="AND";
    file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: "<<s;
    general_print(file_buffer,lhs_op,rhs_op,AST_SUB_NODE_SPACE);
}

Selection_Statement_Ast::Selection_Statement_Ast(Ast * c,Ast* t, Ast* e, int line)
{
    cond=c;
    then_part=t;
    else_part=e;
    lineno=line;
    node_data_type=int_data_type;
    ast_num_child=binary_arity;
}

Selection_Statement_Ast::~Selection_Statement_Ast(){}

Data_Type Selection_Statement_Ast::get_data_type(){
    return node_data_type;
}

void Selection_Statement_Ast::set_data_type(Data_Type dt){
    node_data_type=dt;
}

bool Selection_Statement_Ast::check_ast(){}

void Selection_Statement_Ast::print(ostream &file_buffer){
    file_buffer << "\n" << AST_SPACE << "IF : ";
    file_buffer << "\n" << AST_SPACE << "CONDITION (";
    cond->print(file_buffer);
    file_buffer<<")";
    file_buffer << "\n" << AST_SPACE << "THEN (";
    then_part->print(file_buffer);
    file_buffer<<")";
    if(else_part!=NULL)
    {
        file_buffer<< "\n"<<AST_SPACE<< "ELSE (";
        else_part->print(file_buffer);
        file_buffer<<")";
    }
}

Iteration_Statement_Ast::Iteration_Statement_Ast(Ast * c, Ast* b, int line, bool do_form){
    cond=c;
    body=b;
    is_do_form=do_form;
    lineno=line;
    node_data_type=int_data_type;
    // ast_num_child=binary_arity;
}

Iteration_Statement_Ast::~Iteration_Statement_Ast(){}

Data_Type Iteration_Statement_Ast::get_data_type(){
    return node_data_type;
}

void Iteration_Statement_Ast::set_data_type(Data_Type dt){
    node_data_type=dt;
}

bool Iteration_Statement_Ast::check_ast(){}

void Iteration_Statement_Ast::print(ostream &file_buffer)
{
    if(is_do_form){
       file_buffer << "\n"<<AST_SPACE<<"DO (";
       body->print(file_buffer);
       file_buffer<<")";
       file_buffer<< "\n" <<AST_SPACE<<"WHILE CONDITION (";
       cond->print(file_buffer);
       file_buffer<<")";
       return;
    }   
    file_buffer<< "\n" <<AST_SPACE<<"WHILE : \n"<<AST_SPACE<<"CONDITION (";
    cond->print(file_buffer);
    file_buffer<<")";
    file_buffer << "\n"<<AST_SPACE<< "BODY (";
    body->print(file_buffer);    
    file_buffer<<")";
}

Sequence_Ast::Sequence_Ast(int line)
{
    lineno=line;
    get_new_label();
}

Sequence_Ast::~Sequence_Ast(){}

void Sequence_Ast::ast_push_back(Ast *ast)
{
    statement_list.push_back(ast);
}

void Sequence_Ast::print(ostream &file_buffer)
{
    list<Ast*>::iterator it;
    for(it=statement_list.begin();it!=statement_list.end();++it)
    {
        file_buffer<<"\n"<<AST_NODE_SPACE;
        (*it)->print(file_buffer);
    }
}

void Sequence_Ast::print_assembly(ostream &file_buffer)
{
    list<Icode_Stmt *>::iterator it;
    for(it=sa_icode_list.begin();it!=sa_icode_list.end();++it)
    {
        file_buffer<<"\n"<<AST_NODE_SPACE;
        (*it)->print_assembly(file_buffer);
    }
}

void Sequence_Ast::print_icode(ostream &file_buffer)
{
    list<Icode_Stmt *>::iterator it;
    for(it=sa_icode_list.begin();it!=sa_icode_list.end();++it)
    {
        file_buffer<<"\n"<<AST_NODE_SPACE;
        (*it)->print_icode(file_buffer);
    }
}

Print_Ast::Print_Ast(Ast *v,int line){
    var = v;
    ast_num_child = unary_arity;
    lineno = line;
    node_data_type = v->get_data_type();
}

Print_Ast::~Print_Ast(){}

void Print_Ast::print(ostream & file_buffer){
    file_buffer<<"\n"<<AST_SPACE<<"Print :";
    file_buffer<<"\n"<<AST_SUB_NODE_SPACE;
    var->print(file_buffer);
}

Return_Ast::Return_Ast(Ast * ret_val, string name, int line){
    return_value= ret_val;
    proc_name=name;
    lineno = line;
    ast_num_child = zero_arity;
    if(ret_val==NULL) node_data_type=void_data_type;
    else node_data_type=ret_val->get_data_type();
}

Return_Ast::~Return_Ast(){}

void Return_Ast::print(ostream & file_buffer)
{
    file_buffer << "\n" << AST_SPACE << "Return <NOTHING>\n";
}

Data_Type Return_Ast::get_data_type(){
    return node_data_type;
}
 
Call_Ast::Call_Ast(string name, int line){
    procedure_name=name;
    lineno=line;
    Procedure *proc=program_object.get_procedure_prototype(procedure_name);
    node_data_type = proc->get_return_type();
}

Call_Ast::~Call_Ast(){}

Data_Type Call_Ast::get_data_type(){
    return node_data_type;
}

void Call_Ast::check_actual_formal_param(Symbol_Table & formal_param_list){
    Procedure *proc=program_object.get_procedure_prototype(procedure_name);
    list<Symbol_Table_Entry *> formalParam = formal_param_list.get_table();
    if (formalParam.size()!=actual_param_list.size()){
        cout<<"cs316: Error : wrong number of arguments"<<endl;
        exit(0);
    }
    // cout<<"hi"<<endl;
    list<Symbol_Table_Entry*>::iterator i1;
    list<Ast*>::iterator i2;
    i1=formalParam.begin();
    // int size=0;
    for(i2=actual_param_list.begin();i2!=actual_param_list.end()&&i1!=formalParam.end();++i2)
    {
        // cout<<"hi"<<endl;
        if((*i2)->get_data_type()!=(*i1)->get_data_type())
        {
            cout<<"cs316: Error : type mismatch between formal and actual arguments"<<endl;
            exit(0);
        }
        i1++;
    }
}

void Call_Ast::set_actual_param_list(list<Ast *> & param_list){
    actual_param_list=param_list;
}

void Call_Ast::set_register(Register_Descriptor * reg){
    return_value_reg=reg;
}

void Call_Ast::print(ostream & file_buffer){}
    
Eval_Result & Call_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){}
