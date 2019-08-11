#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "icode.hh"
#include "reg-alloc.hh"
#include "symbol-table.hh"

using namespace std;


template class Const_Opd<int>;
template class Const_Opd<double>;

void error_prnt(string s){
	// printf("%s\n",s);
	// printf("cs316: Error : %s\n", s);
	cout<<"cs316: Error : "<<s<<endl;
}

/************************ class Instruction_Descriptor ********************************/

Tgt_Op Instruction_Descriptor::get_op(){
	return inst_op; 
}
string Instruction_Descriptor::get_name(){
	return name; 
}
string Instruction_Descriptor::get_mnemonic(){ 
	return mnemonic; 
}
string Instruction_Descriptor::get_ic_symbol(){ 
	return ic_symbol; 
}
Icode_Format Instruction_Descriptor::get_ic_format(){ 
	return ic_format; 
}
Assembly_Format Instruction_Descriptor::get_assembly_format(){ 
	return assem_format; 
}

Instruction_Descriptor::Instruction_Descriptor (Tgt_Op op, string temp_name, string temp_mnemonic, 
						string ic_sym, Icode_Format ic_form, Assembly_Format as_form)
{
	inst_op = op;
	name = temp_name; 
	mnemonic = temp_mnemonic;
	ic_symbol = ic_sym;
	ic_format = ic_form;
	assem_format = as_form;
}

Instruction_Descriptor::Instruction_Descriptor()
{
	inst_op = nop;
	name = "";
	mnemonic = "";
	ic_symbol = "";
	ic_format = i_nsy;
	assem_format = a_nsy;
}


/************************ class Ics_Opd ********************************/

Register_Descriptor * Ics_Opd::get_reg()
{
	error_prnt("Control should not reach here");
}

/****************************** Class Mem_Addr_Opd *****************************/

Mem_Addr_Opd::Mem_Addr_Opd(Symbol_Table_Entry & se) 
{
	symbol_entry = &se;
}

Mem_Addr_Opd & Mem_Addr_Opd::operator=(const Mem_Addr_Opd & rhs)
{
	symbol_entry = rhs.symbol_entry;
	return *this;
}

void Mem_Addr_Opd::print_ics_opd(ostream & file_buffer) 
{
	file_buffer << symbol_entry->get_variable_name();
}

void Mem_Addr_Opd::print_asm_opd(ostream & file_buffer) 
{
	Table_Scope symbol_scope = symbol_entry->get_symbol_scope();

	if(symbol_scope != global && symbol_scope != local && symbol_scope != formal)
		error_prnt("Wrong scope");
	if(symbol_scope == global){
		file_buffer << symbol_entry->get_variable_name();
	}
	else if(symbol_entry->get_ref_offset()==fp_ref)
	{
		int offset = symbol_entry->get_start_offset();
		file_buffer << offset << "($fp)";
	}
	else if(symbol_entry->get_ref_offset()==sp_ref)
	{
		int offset = symbol_entry->get_start_offset();
		file_buffer << offset << "($sp)";
	}
	// if (symbol_scope == local )
	// {
	// 	int offset = symbol_entry->get_start_offset();
	// 	file_buffer << offset << "($fp)";
	// }
	// else if (symbol_scope == formal )
	// {
	// 	int offset = symbol_entry->get_start_offset();
	// 	file_buffer << offset << "($sp)";
	// }
	// else
	// 	file_buffer << symbol_entry->get_variable_name();
}

/****************************** Class Register_Addr_Opd *****************************/

Register_Addr_Opd::Register_Addr_Opd(Register_Descriptor * reg) 
{
	register_description = reg;
}

Register_Descriptor * Register_Addr_Opd::get_reg(){ 
	return register_description; 
}

Register_Addr_Opd& Register_Addr_Opd::operator=(const Register_Addr_Opd& rhs)
{
	register_description = rhs.register_description ;
	return *this;
}

void Register_Addr_Opd::print_ics_opd(ostream & file_buffer) 
{
	if(register_description == NULL)
		error_prnt("Register cannot be null");
	file_buffer << register_description->get_name();
}

void Register_Addr_Opd::print_asm_opd(ostream & file_buffer) 
{
	if(register_description == NULL)
		error_prnt("Register cannot be null");
	file_buffer << "$" << register_description->get_name();
}

/****************************** Class Const_Opd *****************************/

template <class DATA_TYPE>
Const_Opd<DATA_TYPE>::Const_Opd(DATA_TYPE n) 
{
	num = n;
}

template <class DATA_TYPE>
Const_Opd<DATA_TYPE> & Const_Opd<DATA_TYPE>::operator=(const Const_Opd<DATA_TYPE> & rhs)
{
	num = rhs.num;
	return *this;
}

template <class DATA_TYPE>
void Const_Opd<DATA_TYPE>::print_ics_opd(ostream & file_buffer) 
{
	file_buffer << num ;
}

template <class DATA_TYPE>
void Const_Opd<DATA_TYPE>::print_asm_opd(ostream & file_buffer) 
{
	file_buffer << num ;
}

/****************************** Class Icode_Stmt *****************************/

Instruction_Descriptor & Icode_Stmt::get_op()
{ 
	return op_desc; 
}

Ics_Opd * Icode_Stmt::get_opd1()
{
	error_prnt("Control should not reach here");
}

Ics_Opd * Icode_Stmt::get_opd2()
{
	error_prnt("Control should not reach here");
}

Ics_Opd * Icode_Stmt::get_result()
{
	error_prnt("Control should not reach here");
}

void Icode_Stmt::set_opd1(Ics_Opd * ics_opd)
{
	error_prnt("Control should not reach here");
}

void Icode_Stmt::set_opd2(Ics_Opd * ics_opd)
{
	error_prnt("Control should not reach here");
}

void Icode_Stmt::set_result(Ics_Opd * ics_opd)
{
	error_prnt("Control should not reach here");
}

/*************************** Class Move_IC_Stmt *****************************/

Move_IC_Stmt::Move_IC_Stmt(Tgt_Op op, Ics_Opd * o1, Ics_Opd * res)
{
	if(machine_desc_object.spim_instruction_table[op] == NULL)
		error_prnt("Instruction description in spim table cannot be null");

	op_desc = *(machine_desc_object.spim_instruction_table[op]);
	opd1 = o1;   
	result = res; 
}

Ics_Opd * Move_IC_Stmt::get_opd1()          { return opd1; }
Ics_Opd * Move_IC_Stmt::get_result()        { return result; }

void Move_IC_Stmt::set_opd1(Ics_Opd * io)   { opd1 = io; }
void Move_IC_Stmt::set_result(Ics_Opd * io) { result = io; }

Move_IC_Stmt& Move_IC_Stmt::operator=(const Move_IC_Stmt& rhs)
{
	op_desc = rhs.op_desc;
	opd1 = rhs.opd1;
	result = rhs.result; 
	return *this;
}

void Move_IC_Stmt::print_icode(ostream & file_buffer)
{
	if(opd1==NULL)
		error_prnt("Opd1 cannot be NULL for a move IC Stmt");
	if(result==NULL)
		error_prnt("Result cannot be NULL for a move IC Stmt");

	string op_name = op_desc.get_name();
	
	file_buffer << "\t" << op_name<<":    \t";
	result->print_ics_opd(file_buffer);
	file_buffer << " <- ";
	opd1->print_ics_opd(file_buffer);
	file_buffer << "\n";
}

void Move_IC_Stmt::print_assembly(ostream & file_buffer)
{
	if(opd1==NULL)
		error_prnt("Opd1 cannot be NULL for a move IC Stmt");
	if(result==NULL)
		error_prnt("Result cannot be NULL for a move IC Stmt");

	string op_name = op_desc.get_mnemonic();

	Assembly_Format ass_format = op_desc.get_assembly_format();
	switch (ass_format)
	{
	case a_op_r_o1: 
			file_buffer << "\t" << op_name << " ";
			result->print_asm_opd(file_buffer);
			file_buffer << ", ";
			opd1->print_asm_opd(file_buffer);
			file_buffer << "\n";

			break; 

	case a_op_o1_r: 
	 		file_buffer << "\t" << op_name << " ";
			opd1->print_asm_opd(file_buffer);
			file_buffer << ", ";
			result->print_asm_opd(file_buffer);
			file_buffer << "\n";

			break; 

	default: 
			error_prnt("Control should not reach here : Intermediate code format not supported");
			break;
	}
}
/******************************* Class Label_IC_Stmt ***************************/

Label_IC_Stmt::Label_IC_Stmt(Tgt_Op inst_op, string lbl){
	if(machine_desc_object.spim_instruction_table[inst_op] == NULL)
		error_prnt("Instruction description in spim table cannot be null");

	op_desc = *(machine_desc_object.spim_instruction_table[inst_op]);
	label = lbl;
}

Instruction_Descriptor & Label_IC_Stmt::get_inst_op_of_ics() {
	return op_desc;
}

string Label_IC_Stmt::get_label(){
	return label;
}
void Label_IC_Stmt::set_label(string lbl){
	label  = lbl;
}

Label_IC_Stmt & Label_IC_Stmt::operator=(const Label_IC_Stmt & rhs){
	op_desc = rhs.op_desc;
	label = rhs.label;
	return *this;
}

void Label_IC_Stmt::print_icode(ostream & file_buffer){
	if(op_desc.get_op()==j){
		file_buffer<<"\tgoto "<<label<<"\n";
	}
	else if(op_desc.get_op()==bc1t){
		file_buffer<<"\tbc1t "<<label<<" \n";
	}
	else if(op_desc.get_op()==bc1f){
		file_buffer<<"\tbc1f "<<label<<" \n";
	}
	else if(op_desc.get_op()==jal){
		file_buffer<<"\tjal "<<label<<" \n";
	}
	else{
		file_buffer<<"\n"<<label<<":    \t\n";
	}
}
void Label_IC_Stmt::print_assembly(ostream & file_buffer){
	if(op_desc.get_op()==j){
		file_buffer<<"\tj "<<label<<"\n";
	}
	else if(op_desc.get_op()==bc1t){
		file_buffer<<"\tbc1t "<<label<<" \n";
	}
	else if(op_desc.get_op()==bc1f){
		file_buffer<<"\tbc1f "<<label<<" \n";
	}
	else if(op_desc.get_op()==jal){
		file_buffer<<"\tjal "<<label<<" \n";
	}
	else{
		file_buffer<<"\n"<<label<<":    \t\n";
	}
}

/******************************* Class Control_Flow_IC_Stmt ***********************/

Control_Flow_IC_Stmt::Control_Flow_IC_Stmt(Tgt_Op inst_op, Ics_Opd * op1, Ics_Opd * op2, string lbl,int size){
	if(machine_desc_object.spim_instruction_table[inst_op] == NULL)
		error_prnt("Instruction description in spim table cannot be null");

	op_desc = *(machine_desc_object.spim_instruction_table[inst_op]);
	offset = lbl;
	opd1 = op1;
	opd2 = op2;
	actual_param_size = size;
}

Control_Flow_IC_Stmt & Control_Flow_IC_Stmt::operator=(const Control_Flow_IC_Stmt & rhs){
	op_desc = rhs.op_desc;
	opd1 = rhs.opd1;
	offset = rhs.offset;
	opd2 = rhs.opd2;
	actual_param_size = rhs.actual_param_size;
	return *this;
}

Instruction_Descriptor & Control_Flow_IC_Stmt::get_inst_op_of_ics(){
	return op_desc;
}
Ics_Opd * Control_Flow_IC_Stmt::get_opd1(){
	return opd1;
}
void Control_Flow_IC_Stmt::set_opd1(Ics_Opd * io){
	opd1=io;
}
Ics_Opd * Control_Flow_IC_Stmt::get_opd2(){
	return opd2;
}
void Control_Flow_IC_Stmt::set_opd2(Ics_Opd * io){
	opd2=io;
}
string Control_Flow_IC_Stmt::get_Offset(){
	return offset;
}
void Control_Flow_IC_Stmt::set_Offset(string lbl){
	offset = lbl;
}

void Control_Flow_IC_Stmt::print_icode(ostream & file_buffer){
	file_buffer<<"\t"<<op_desc.get_name()<<":    \t";
	opd1->print_ics_opd(file_buffer);
	file_buffer<<" , zero : goto "<<offset<<"\n";
}
void Control_Flow_IC_Stmt::print_assembly(ostream & file_buffer){
	file_buffer<<"\t"<<op_desc.get_mnemonic()<<" ";
	opd1->print_asm_opd(file_buffer);
	file_buffer<<", $zero, "<<offset<<" \n";
}
/********************************************************************************************/


Print_IC_Stmt::Print_IC_Stmt(){
	op_desc = *(machine_desc_object.spim_instruction_table[print]);
}

Print_IC_Stmt::~Print_IC_Stmt(){}

void Print_IC_Stmt::print_assembly(ostream & file_buffer){
	file_buffer<<"\t"<<op_desc.get_mnemonic()<<"\n";
}

void Print_IC_Stmt::print_icode(ostream & file_buffer){
	file_buffer<<"\t"<<op_desc.get_name()<<"\n";
}

/******************************Class Compute_IC_Stmt ***************************/

Compute_IC_Stmt::Compute_IC_Stmt(Tgt_Op op, Ics_Opd * op1, Ics_Opd * op2, Ics_Opd * res) {
	if(machine_desc_object.spim_instruction_table[op] == NULL)
		error_prnt("Instruction description in spim table cannot be null");

	op_desc = *(machine_desc_object.spim_instruction_table[op]);
	result = res;
	opd1 = op1;
	opd2 = op2;
}

Compute_IC_Stmt & Compute_IC_Stmt::operator=(const Compute_IC_Stmt & rhs){
	opd1 = rhs.opd1;
	opd2 = rhs.opd2;
	result = rhs.result;
	op_desc = rhs.op_desc;
	return *this;
}

Instruction_Descriptor & Compute_IC_Stmt::get_inst_op_of_ics(){ return op_desc;}

Ics_Opd * Compute_IC_Stmt::get_opd1()         { return opd1; }
void Compute_IC_Stmt::set_opd1(Ics_Opd * io)  { opd1 = io;   }

Ics_Opd * Compute_IC_Stmt::get_opd2()         { return opd2; }
void Compute_IC_Stmt::set_opd2(Ics_Opd * io)  { opd2 = io;   }

Ics_Opd * Compute_IC_Stmt::get_result()       {return result;}
void Compute_IC_Stmt::set_result(Ics_Opd * io){ result = io; }


void Compute_IC_Stmt::print_icode(ostream & file_buffer){
	if(opd1==NULL)
		error_prnt("Opd1 cannot be NULL for a Compute IC Stmt");
	if(result==NULL)
		error_prnt("Result cannot be NULL for a Compute IC Stmt");
	file_buffer<<"\t"<<op_desc.get_name()<<":    \t";
	result->print_ics_opd(file_buffer);
	file_buffer<<" <- ";
	opd1->print_ics_opd(file_buffer);
	if(opd2)
	{
		file_buffer<<" , ";
		opd2->print_ics_opd(file_buffer);
	}
	
	file_buffer<<"\n";
}

void Compute_IC_Stmt::print_assembly(ostream & file_buffer){
	if(opd1==NULL)
		error_prnt("Opd1 cannot be NULL for a Compute IC Stmt");
	if(result==NULL)
		error_prnt("Result cannot be NULL for a Compute IC Stmt");
	file_buffer<<"\t"<<op_desc.get_mnemonic()<<" ";
	result->print_asm_opd(file_buffer);
	file_buffer<<", ";
	opd1->print_asm_opd(file_buffer);
	if(opd2)
	{
		file_buffer<<", ";
		opd2->print_asm_opd(file_buffer);
	}
	
	file_buffer<<"\n";
}

// void Compute_IC_Stmt::print_icode(ostream & file_buffer) {
	
// 	if(opd1==NULL)
// 		error_prnt("Opd1 cannot be NULL for a Compute IC Stmt");
// 	if(result==NULL)
// 		error_prnt("Result cannot be NULL for a Compute IC Stmt");

// 	string op_name = op_desc.get_name();

// 	Icode_Format ic_format = op_desc.get_ic_format();
// 	cout<<op_name<<endl;
// 	switch (ic_format)
// 	{
// 	case i_r_o1_op_o2: 
// 			file_buffer << "\t" << op_name ;
// 			if (op_name.size()<7) 
// 				file_buffer << ":\t\t";
// 			else if (op_name.size()<15)
// 				file_buffer << ":\t";
// 			else
// 				file_buffer << ":";
// 			result->print_ics_opd(file_buffer);
// 			file_buffer << " <- ";
// 			opd1->print_ics_opd(file_buffer);
// 			if(opd2!=NULL){
// 				file_buffer << " , " ;
// 				opd2->print_ics_opd(file_buffer);
// 			}
// 			file_buffer << "\n";
// 			break; 

// 	default: 
// 			error_prnt("Control should not reach here : Intermediate code format not supported");
// 			break;
// 	}
// }
// void Compute_IC_Stmt::print_assembly(ostream & file_buffer) {
// 	if(opd1==NULL)
// 		error_prnt("Opd1 cannot be NULL for a Compute IC Stmt");
// 	if(result==NULL)
// 		error_prnt("Result cannot be NULL for a Compute IC Stmt");

// 	string op_name = op_desc.get_mnemonic();

// 	Assembly_Format ass_format = op_desc.get_assembly_format();
// 	cout<<op_name<<endl;
// 	switch (ass_format)
// 	{
// 	case a_op_r_o1_o2: 
// 			file_buffer << "\t" << op_name << " ";
// 			result->print_asm_opd(file_buffer);
// 			file_buffer << ", ";
// 			opd1->print_asm_opd(file_buffer);
// 			if(opd2!=NULL){
// 				file_buffer << ", " ;
// 				opd2->print_asm_opd(file_buffer);
// 			}
// 			file_buffer << "\n";
// 			break; 

// 	default: 
// 			error_prnt("Control should not reach here : Intermediate code format not supported");
// 			break;
// 	}
// }


/******************************* Class Code_For_Ast ****************************/

Code_For_Ast::Code_For_Ast()
{
	ics_list = *new list<Icode_Stmt *>;
}

Code_For_Ast::Code_For_Ast(list<Icode_Stmt *> & ic_l, Register_Descriptor * reg)
{
	ics_list = ic_l;
	result_register = reg;
}

void Code_For_Ast::append_ics(Icode_Stmt & ics)
{
	ics_list.push_back(&ics);
	Ics_Opd * result = ics.get_result();
	result_register = result->get_reg();
}

list<Icode_Stmt *> & Code_For_Ast::get_icode_list()  
{ 
	return ics_list; 
}

Register_Descriptor * Code_For_Ast::get_reg()
{
	return result_register;
}

void Code_For_Ast::set_reg(Register_Descriptor * reg)
{
	result_register = reg;
}

Code_For_Ast& Code_For_Ast::operator=(const Code_For_Ast& rhs)
{
	ics_list = rhs.ics_list;
	result_register = rhs.result_register;

	return *this;
}

