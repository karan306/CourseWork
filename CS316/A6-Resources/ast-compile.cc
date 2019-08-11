#include "ast.hh"
#include "symbol-table.hh"
#include "procedure.hh"
#include "program.hh"
#include "local-environment.hh"
#include "icode.hh"
#include "reg-alloc.hh"

template class Number_Ast<double>;
template class Number_Ast<int>;

int count =0;

void error_print(string s){
    // printf("hi %d\n",count); count++;
    // count++;
	printf("cs316: Error : %s\n", s);
}

Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register){}


/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/



Code_For_Ast & Assignment_Ast::compile() {
    // printf("assignment %d\n",count); count++;
	if(lhs == NULL) printf("cs316: Error: Lhs cannot be null\n");
	if(rhs == NULL) printf("cs316: Error: Rhs cannot be null\n");

	Code_For_Ast & loadStmt = rhs->compile();
	
	Register_Descriptor * loadReg = loadStmt.get_reg();

	Code_For_Ast store_stmt = lhs->create_store_stmt(loadReg);

	// Store the statement in icList

	list<Icode_Stmt *> & icList = loadStmt.get_icode_list();

	icList.merge(store_stmt.get_icode_list());

	Code_For_Ast * assign_stmt = new Code_For_Ast(icList, loadReg);

	return *assign_stmt;
} 

Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}



/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/



Code_For_Ast & Name_Ast::compile() {
    // printf("name %d\n",count); count++;
	Ics_Opd * opd = new Mem_Addr_Opd(*variable_symbol_entry);
	Register_Descriptor * resultReg = NULL;
	Tgt_Op opr ;
	if (node_data_type == int_data_type) {
		resultReg = machine_desc_object.get_new_register<int_reg>();
		opr = load ;
	}
	else {
		resultReg = machine_desc_object.get_new_register<float_reg>();
		opr = load_d ;
	}

	resultReg->update_symbol_information(*variable_symbol_entry);
	Ics_Opd * register_opd = new Register_Addr_Opd(resultReg);
	
	Icode_Stmt * loadStmt = new Move_IC_Stmt(opr, opd, register_opd);
	
	list<Icode_Stmt *> icList;
	icList.push_back(loadStmt);

	Code_For_Ast & load_code = *new Code_For_Ast(icList, resultReg);

	return load_code;
} 

Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}

Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register){
    // printf("create store %d\n",count); count++;

	if (store_register == NULL) cout<<"cs316: Error : Store register must not be null\n";

	Ics_Opd * opd = new Mem_Addr_Opd(*variable_symbol_entry);
	Ics_Opd * reg = new Register_Addr_Opd(store_register);
	Icode_Stmt * store_stmt = NULL ;


	if (store_register->get_use_category() == int_reg)
		store_stmt = new Move_IC_Stmt(store, reg, opd);
	else if (store_register->get_use_category() == float_reg)
		store_stmt = new Move_IC_Stmt(store_d, reg, opd);
	else cout<<"cs316: Error : Wrong store type\n";

	// if (command_options.is_do_lra_selected() == false) 
	//   {
    variable_symbol_entry->free_register(store_register);
    store_register->clear_lra_symbol_list();
    store_register->reset_use_for_expr_result();
	//   }
	// else {
	//   variable_symbol_entry->free_register(variable_symbol_entry->get_register());
	//   variable_symbol_entry->update_register(store_register);
	// }
	list<Icode_Stmt *> & icList = *new list<Icode_Stmt *>;
	icList.push_back(store_stmt);

	Code_For_Ast & name_code = *new Code_For_Ast(icList, store_register);

	return name_code;
}



/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/



template <class T>
Code_For_Ast & Number_Ast<T>::compile(){
    // printf("no %d\n",count); count++;
	Register_Descriptor * resultReg = NULL;
	Tgt_Op opr ;
    Ics_Opd * opd;
	if (node_data_type == int_data_type) {
		resultReg = machine_desc_object.get_new_register<int_reg>();
		opr = imm_load ;
        opd = new Const_Opd<int>(constant);
	}
	else {
		resultReg = machine_desc_object.get_new_register<float_reg>();
		opr = imm_load_d ;
        opd = new Const_Opd<double>(constant);
	}
	resultReg->set_use_for_expr_result();
	Ics_Opd * loadRegister = new Register_Addr_Opd(resultReg);
	

	Icode_Stmt * loadStmt = new Move_IC_Stmt(opr, opd, loadRegister);

	list<Icode_Stmt *> & icList = *new list<Icode_Stmt *>;
	icList.push_back(loadStmt);

	Code_For_Ast & num_code = *new Code_For_Ast(icList, resultReg);

	return num_code;
}

template <class T>
Code_For_Ast & Number_Ast<T>::compile_and_optimize_ast(Lra_Outcome & lra){}



/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/



Code_For_Ast & Plus_Ast::compile() {
    // printf("+ %d\n",count); count++;
	if(lhs == NULL) printf("cs316: Error: LHS cannot be null\n");
	if(rhs == NULL) printf("cs316: Error: RHS cannot be null\n");
	Code_For_Ast & lhs_stmt = lhs->compile();
	Register_Descriptor * lreg = lhs_stmt.get_reg();
	Code_For_Ast & rhs_stmt = rhs->compile();
	Register_Descriptor * rreg = rhs_stmt.get_reg();

	if(lreg->get_use_category()!=rreg->get_use_category())
		printf("cs316: Error: LHS and RHS are incompatible data types\n");

	list<Icode_Stmt *> & icList = *new list<Icode_Stmt *>;

	Ics_Opd * lhs_reg = new Register_Addr_Opd(lreg);
	Ics_Opd * rhs_reg = new Register_Addr_Opd(rreg);

	if (!lhs_stmt.get_icode_list().empty())
		icList = lhs_stmt.get_icode_list();
	if (!rhs_stmt.get_icode_list().empty())
		icList.merge(rhs_stmt.get_icode_list());

	Register_Descriptor * result_reg ;
	Tgt_Op opr ;
	if (lreg->get_use_category() == int_reg) {
		result_reg = machine_desc_object.get_new_register<int_reg>();
		opr = add ;
	}
	if (lreg->get_use_category() == float_reg) {
		result_reg = machine_desc_object.get_new_register<float_reg>();
		opr = add_d ;
	}
	result_reg->set_use_for_expr_result();
	Ics_Opd * register_result = new Register_Addr_Opd(result_reg);

	icList.push_back(new Compute_IC_Stmt(opr, lhs_reg, rhs_reg,register_result)) ;

	lreg->reset_use_for_expr_result();
	lreg->clear_lra_symbol_list();
	rreg->reset_use_for_expr_result();
	rreg->clear_lra_symbol_list();
	Code_For_Ast & plus_code = *new Code_For_Ast(icList, result_reg);
	return plus_code;
} 

Code_For_Ast & Plus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {}



/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/



Code_For_Ast & Minus_Ast::compile() {
	// printf("- %d\n",count); count++;
	if(lhs == NULL) printf("cs316: Error: LHS cannot be null\n");
	if(rhs == NULL) printf("cs316: Error: RHS cannot be null\n");
	Code_For_Ast & lhs_stmt = lhs->compile();
	Register_Descriptor * lreg = lhs_stmt.get_reg();
	Code_For_Ast & rhs_stmt = rhs->compile();
	Register_Descriptor * rreg = rhs_stmt.get_reg();

	if(lreg->get_use_category()!=rreg->get_use_category())
		printf("cs316: Error: LHS and RHS are incompatible data types\n");

	list<Icode_Stmt *> & icList = *new list<Icode_Stmt *>;

	Ics_Opd * lhs_reg = new Register_Addr_Opd(lreg);
	Ics_Opd * rhs_reg = new Register_Addr_Opd(rreg);

	if (!lhs_stmt.get_icode_list().empty())
		icList = lhs_stmt.get_icode_list();
	if (!rhs_stmt.get_icode_list().empty())
		icList.merge(rhs_stmt.get_icode_list());

	Register_Descriptor * result_reg ;
	Tgt_Op opr ;
	if (lreg->get_use_category() == int_reg) {
		result_reg = machine_desc_object.get_new_register<int_reg>();
		opr = sub ;
	}
	if (lreg->get_use_category() == float_reg) {
		result_reg = machine_desc_object.get_new_register<float_reg>();
		opr = sub_d ;
	}
	result_reg->set_use_for_expr_result();
	Ics_Opd * register_result = new Register_Addr_Opd(result_reg);

	icList.push_back(new Compute_IC_Stmt(opr, lhs_reg, rhs_reg,register_result)) ;

	lreg->reset_use_for_expr_result();
	lreg->clear_lra_symbol_list();
	rreg->reset_use_for_expr_result();
	rreg->clear_lra_symbol_list();
	Code_For_Ast & minus_code = *new Code_For_Ast(icList, result_reg);
	return minus_code;
} 
Code_For_Ast & Minus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {}



/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/



Code_For_Ast & Mult_Ast::compile() {
	// printf("* %d\n",count); count++;
    if(lhs == NULL) printf("cs316: Error: LHS cannot be null\n");
	if(rhs == NULL) printf("cs316: Error: RHS cannot be null\n");
	Code_For_Ast & lhs_stmt = lhs->compile();
	Register_Descriptor * lreg = lhs_stmt.get_reg();
	Code_For_Ast & rhs_stmt = rhs->compile();
	Register_Descriptor * rreg = rhs_stmt.get_reg();

	if(lreg->get_use_category()!=rreg->get_use_category())
		printf("cs316: Error: LHS and RHS are incompatible data types\n");

	list<Icode_Stmt *> & icList = *new list<Icode_Stmt *>;

	Ics_Opd * lhs_reg = new Register_Addr_Opd(lreg);
	Ics_Opd * rhs_reg = new Register_Addr_Opd(rreg);

	if (!lhs_stmt.get_icode_list().empty())
		icList = lhs_stmt.get_icode_list();
	if (!rhs_stmt.get_icode_list().empty())
		icList.merge(rhs_stmt.get_icode_list());

	Register_Descriptor * result_reg ;
	Tgt_Op opr ;
	if (lreg->get_use_category() == int_reg) {
		result_reg = machine_desc_object.get_new_register<int_reg>();
		opr = mult ;
	}
	if (lreg->get_use_category() == float_reg) {
		result_reg = machine_desc_object.get_new_register<float_reg>();
		opr = mult_d ;
	}
	result_reg->set_use_for_expr_result();
	Ics_Opd * register_result = new Register_Addr_Opd(result_reg);

	icList.push_back(new Compute_IC_Stmt(opr, lhs_reg, rhs_reg,register_result)) ;

	lreg->reset_use_for_expr_result();
	lreg->clear_lra_symbol_list();
	rreg->reset_use_for_expr_result();
	rreg->clear_lra_symbol_list();
	Code_For_Ast & mult_code = *new Code_For_Ast(icList, result_reg);
	return mult_code;
} 
Code_For_Ast & Mult_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {}



/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/



Code_For_Ast & Divide_Ast::compile() {
	// printf("/ %d\n",count); count++;
	if(lhs == NULL) printf("cs316: Error: LHS cannot be null\n");
	if(rhs == NULL) printf("cs316: Error: RHS cannot be null\n");
	Code_For_Ast & lhs_stmt = lhs->compile();
	Register_Descriptor * lreg = lhs_stmt.get_reg();
	Code_For_Ast & rhs_stmt = rhs->compile();
	Register_Descriptor * rreg = rhs_stmt.get_reg();

	if(lreg->get_use_category()!=rreg->get_use_category())
		printf("cs316: Error: LHS and RHS are incompatible data types\n");

	list<Icode_Stmt *> & icList = *new list<Icode_Stmt *>;

	Ics_Opd * lhs_reg = new Register_Addr_Opd(lreg);
	Ics_Opd * rhs_reg = new Register_Addr_Opd(rreg);

	if (!lhs_stmt.get_icode_list().empty())
		icList = lhs_stmt.get_icode_list();
	if (!rhs_stmt.get_icode_list().empty())
		icList.merge(rhs_stmt.get_icode_list());

	Register_Descriptor * result_reg ;
	Tgt_Op opr ;
	if (lreg->get_use_category() == int_reg) {
		result_reg = machine_desc_object.get_new_register<int_reg>();
		opr = divd ;
	}
	if (lreg->get_use_category() == float_reg) {
		result_reg = machine_desc_object.get_new_register<float_reg>();
		opr = div_d ;
	}
	result_reg->set_use_for_expr_result();
	Ics_Opd * register_result = new Register_Addr_Opd(result_reg);

	icList.push_back(new Compute_IC_Stmt(opr, lhs_reg, rhs_reg,register_result)) ;

	lreg->reset_use_for_expr_result();
	lreg->clear_lra_symbol_list();
	rreg->reset_use_for_expr_result();
	rreg->clear_lra_symbol_list();
	Code_For_Ast & div_code = *new Code_For_Ast(icList, result_reg);
	return div_code;
} 
Code_For_Ast & Divide_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}



/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/



Code_For_Ast & UMinus_Ast::compile() {
	// printf("u- %d\n",count); count++;
	if(lhs == NULL) printf("cs316: Error: LHS cannot be null\n");
	Code_For_Ast & lhs_stmt = lhs->compile();
	Register_Descriptor * lreg = lhs_stmt.get_reg();

	list<Icode_Stmt *> & icList = *new list<Icode_Stmt *>;

	Ics_Opd * lhs_reg = new Register_Addr_Opd(lreg);

	if (!lhs_stmt.get_icode_list().empty())
		icList = lhs_stmt.get_icode_list();

	Register_Descriptor * result_reg ;
	Tgt_Op opr ;
	if (lreg->get_use_category() == int_reg) {
		result_reg = machine_desc_object.get_new_register<int_reg>();
		opr = uminus ;
	}
	if (lreg->get_use_category() == float_reg) {
		result_reg = machine_desc_object.get_new_register<float_reg>();
		opr = uminus_d ;
	}
	result_reg->set_use_for_expr_result();
	Ics_Opd * register_result = new Register_Addr_Opd(result_reg);

	icList.push_back(new Compute_IC_Stmt(opr,  lhs_reg, NULL,register_result)) ;

	lreg->reset_use_for_expr_result();
	lreg->clear_lra_symbol_list();
	Code_For_Ast & uminus_code = *new Code_For_Ast(icList, result_reg);
	return uminus_code;
} 
Code_For_Ast & UMinus_Ast::compile_and_optimize_ast(Lra_Outcome & lra) {}



/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/



Code_For_Ast & Conditional_Expression_Ast::compile() {
	// printf("cond %d\n",count); count++;
	if(cond->get_data_type()!=int_data_type) cout<<"cs316: Error: Float comparisons not allowed in ternary\n";
    Code_For_Ast Cond = cond->compile();
	Register_Descriptor *  condReg = Cond.get_reg();
	list<Icode_Stmt *> condIC = Cond.get_icode_list();
	Register_Addr_Opd * condOpd = new Register_Addr_Opd(condReg);	
	string lab1 = "label" + to_string(labelCounter);	
	Control_Flow_IC_Stmt* jump = new Control_Flow_IC_Stmt(beq,condOpd,NULL,lab1);
	condIC.push_back(jump);
	labelCounter++;

	Code_For_Ast thenBody = lhs->compile();
	Register_Descriptor *  thenReg = thenBody.get_reg();
	Register_Addr_Opd * thenOpd = new Register_Addr_Opd(thenReg);
	list<Icode_Stmt *> thenIC = thenBody.get_icode_list();
	condIC.merge(thenIC);



	Register_Descriptor * res;
	if(lhs->get_data_type() == double_data_type){
		res = machine_desc_object.get_new_register<float_reg>();
	}
	else{
		res = machine_desc_object.get_new_register<int_reg>();
	}
	res->set_use_for_expr_result();

	Register_Addr_Opd * result = new Register_Addr_Opd(res);
	Register_Descriptor * ZeroReg = machine_desc_object.spim_register_table[zero];
	ZeroReg->reset_use_for_expr_result();
	Register_Addr_Opd * zeroOpd = new Register_Addr_Opd(ZeroReg);

	Compute_IC_Stmt * temp = new Compute_IC_Stmt(or_t,thenOpd,zeroOpd,result);

	string lab2 = "label" + to_string(labelCounter);	
	Label_IC_Stmt *labelStmt = new Label_IC_Stmt(j,lab2);

	condIC.push_back(temp);
	condIC.push_back(labelStmt);

	Label_IC_Stmt * printLabelStmt = new Label_IC_Stmt(label,lab1);
	condIC.push_back(printLabelStmt);
	labelCounter++;

	Code_For_Ast elseBody = rhs->compile();
	Register_Descriptor *  elseReg = elseBody.get_reg();
	Register_Addr_Opd * elseOpd = new Register_Addr_Opd(elseReg);
	list<Icode_Stmt *> elseIC = elseBody.get_icode_list();
	condIC.merge(elseIC);

	temp = new Compute_IC_Stmt(or_t,elseOpd,zeroOpd,result);
	condIC.push_back(temp);

	printLabelStmt = new Label_IC_Stmt(label,lab2);
	condIC.push_back(printLabelStmt);

	Code_For_Ast *c = new Code_For_Ast(condIC,res);
	condReg->reset_use_for_expr_result();
	thenReg->reset_use_for_expr_result();
	elseReg->reset_use_for_expr_result();	
	return *c;
}



/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/


// Code_For_Ast & Conditional_Expression_Ast::compile_and_optimize_ast(Lra_Outcome & lra)  {}

Code_For_Ast & Return_Ast::compile() {
	// printf("ret %d\n",count); count++;
	// if(return_value==NULL) cout<<"hi"<<endl;
	// else cout<<"hey"<<endl;
	list<Icode_Stmt *> & icList = *new list<Icode_Stmt *>;
	Register_Descriptor * resultReg = NULL;

	if (return_value != NULL) {
		Code_For_Ast & return_exp_stmt = return_value->compile();
		Register_Descriptor * rreg = return_exp_stmt.get_reg();

		Ics_Opd * return_exp_reg = new Register_Addr_Opd(rreg);

		if (return_exp_stmt.get_icode_list().empty() == false)
			icList = return_exp_stmt.get_icode_list();

		Tgt_Op opr ;
		if (return_value->get_data_type() == int_data_type) {
			resultReg = (machine_desc_object.spim_register_table[v1]);
			opr = mov ;
		}
		if (return_value->get_data_type() == double_data_type) {
			resultReg = (machine_desc_object.spim_register_table[f0]);
			opr = move_d ;
		}
		resultReg->set_use_for_expr_result();
		Ics_Opd * register_result = new Register_Addr_Opd(resultReg);

		icList.push_back(new Move_IC_Stmt(opr, return_exp_reg, register_result)) ;


		rreg->reset_use_for_expr_result();
		rreg->clear_lra_symbol_list();
	}

	icList.push_back(new Label_IC_Stmt(j, "epilogue_"+proc_name));
	Code_For_Ast & rel_expr_code = *new Code_For_Ast(icList, resultReg);
	return rel_expr_code;
}

Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra)  {}



/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/



Code_For_Ast & Relational_Expr_Ast::compile() {
	// printf("rel %d\n",count); count++;
	if(lhs_condition == NULL) printf("cs316: Error: LHS cannot be null");
	if(rhs_condition == NULL) printf("cs316: Error: RHS cannot be null");
	Code_For_Ast & lhs_stmt = lhs_condition->compile();
	Register_Descriptor * lreg = lhs_stmt.get_reg();
	Code_For_Ast & rhs_stmt = rhs_condition->compile();
	Register_Descriptor * rreg = rhs_stmt.get_reg();
	list<Icode_Stmt *> & icList = *new list<Icode_Stmt *>;

	Ics_Opd * lhs_reg = new Register_Addr_Opd(lreg);
	Ics_Opd * rhs_reg = new Register_Addr_Opd(rreg);
	
	if (lhs_stmt.get_icode_list().empty() == false)
		icList = lhs_stmt.get_icode_list();
	if (rhs_stmt.get_icode_list().empty() == false)
		icList.splice(icList.end(), rhs_stmt.get_icode_list());
		
	
	Register_Descriptor * result_reg = machine_desc_object.get_new_register<int_reg>();
	result_reg->set_use_for_expr_result();
	Ics_Opd * register_result = new Register_Addr_Opd(result_reg);

	if(node_data_type==int_data_type){
		if(rel_op==equalto)       
			icList.push_back(new Compute_IC_Stmt(seq, lhs_reg, rhs_reg,register_result)) ;
		else if(rel_op==not_equalto) 
			icList.push_back(new Compute_IC_Stmt(sne, lhs_reg, rhs_reg,register_result)) ;
		else if(rel_op==greater_than)
			icList.push_back(new Compute_IC_Stmt(sgt, lhs_reg, rhs_reg,register_result)) ;
		else if(rel_op==greater_equalto) 
			icList.push_back(new Compute_IC_Stmt(sge, lhs_reg, rhs_reg,register_result)) ;
		else if(rel_op==less_than)
			icList.push_back(new Compute_IC_Stmt(slt, lhs_reg, rhs_reg,register_result)) ;
		else if(rel_op==less_equalto)
			icList.push_back(new Compute_IC_Stmt(sle, lhs_reg, rhs_reg,register_result)) ;	
	}
	else{
		string label = "label" + to_string(labelCounter);	
		if(rel_op==equalto) {     
			icList.push_back(new Compute_IC_Stmt(seq_d, rhs_reg, NULL, lhs_reg)) ;
			icList.push_back(new Label_IC_Stmt(bc1f,label));
		}
		else if(rel_op==not_equalto) {
			icList.push_back(new Compute_IC_Stmt(sne_d, rhs_reg, NULL, lhs_reg)) ;
			icList.push_back(new Label_IC_Stmt(bc1t,label));
		}
		else if(rel_op==greater_than) {
			icList.push_back(new Compute_IC_Stmt(sgt_d, rhs_reg, NULL, lhs_reg)) ;
			icList.push_back(new Label_IC_Stmt(bc1t,label));
		}
		else if(rel_op==greater_equalto) {
			icList.push_back(new Compute_IC_Stmt(sge_d, rhs_reg, NULL, lhs_reg)) ;
			icList.push_back(new Label_IC_Stmt(bc1t,label));
		}
		else if(rel_op==less_than) {
			icList.push_back(new Compute_IC_Stmt(slt_d, rhs_reg, NULL, lhs_reg)) ;
			icList.push_back(new Label_IC_Stmt(bc1f,label));
		}
		else if(rel_op==less_equalto) {
			icList.push_back(new Compute_IC_Stmt(sle_d, rhs_reg, NULL, lhs_reg)) ;
			icList.push_back(new Label_IC_Stmt(bc1f,label));
		}
		result_reg->reset_use_for_expr_result();
	}


	lreg->reset_use_for_expr_result();
	lreg->clear_lra_symbol_list();
	rreg->reset_use_for_expr_result();
	rreg->clear_lra_symbol_list();
	Code_For_Ast & rel_expr_code = *new Code_For_Ast(icList, result_reg);
	return rel_expr_code;
}




/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/


// Code_For_Ast & Relational_Expr_Ast::compile_and_optimize_ast(Lra_Outcome & lra)  {}

Code_For_Ast & Logical_Expr_Ast::compile() {
	// printf("log %d\n",count); count++;
	if(bool_op==_logical_not){
		if(rhs_op->get_data_type()!=int_data_type) {
			cout<<"cs316: Error: Float comparisons not allowed in Logical\n";
			exit(0);
		}
		Register_Descriptor * v0 = machine_desc_object.get_new_register<int_reg>();
		v0->set_use_for_expr_result();
		Register_Addr_Opd * V0 = new Register_Addr_Opd(v0);
		
		Const_Opd<int> * constOne = new Const_Opd<int>(1);
		Move_IC_Stmt * moveOne = new Move_IC_Stmt(imm_load , constOne, V0);
	
		Code_For_Ast rhsCode = rhs_op->compile();
		Register_Descriptor * rhs_reg = rhsCode.get_reg();
		list<Icode_Stmt *> rhsIC = rhsCode.get_icode_list();
		Register_Addr_Opd * opd1 = new Register_Addr_Opd(rhs_reg);
		// I1.merge(I2);
		rhsIC.push_front(moveOne);

		Register_Descriptor * res = machine_desc_object.get_new_register<int_reg>();
		res->set_use_for_expr_result();
		Register_Addr_Opd * result = new Register_Addr_Opd(res);

		Compute_IC_Stmt * temp = new Compute_IC_Stmt(not_t,opd1,V0,result);
		rhsIC.push_back(temp);
		Code_For_Ast *c = new Code_For_Ast(rhsIC,res);
		// l->reset_use_for_expr_result();
		rhs_reg->reset_use_for_expr_result();
		v0->reset_use_for_expr_result();
		return *c;


		// if(rhs_op == NULL) printf("cs316: Error: RHS cannot be null");
		// Code_For_Ast & rhs_stmt = rhs_op->compile();
		// Register_Descriptor * rreg = rhs_stmt.get_reg();

		// list<Icode_Stmt *> & icList = *new list<Icode_Stmt *>;

		// Ics_Opd * rhs_reg = new Register_Addr_Opd(rreg);

		// if (!rhs_stmt.get_icode_list().empty())
		// 	icList = rhs_stmt.get_icode_list();
		
		// Register_Descriptor * result_reg = machine_desc_object.get_new_register<int_reg>();
		// Tgt_Op opr =not_t;
		
		// result_reg->set_use_for_expr_result();
		// Ics_Opd * register_result = new Register_Addr_Opd(result_reg);

		// icList.push_back(new Compute_IC_Stmt(opr, NULL,rhs_reg, register_result)) ;

		

		// rreg->reset_use_for_expr_result();
		// rreg->clear_lra_symbol_list();
		// Code_For_Ast & rel_expr_code = *new Code_For_Ast(icList, result_reg);
		// return rel_expr_code;
	}
	if(rhs_op->get_data_type()!=int_data_type || lhs_op->get_data_type()!=int_data_type) {
		cout<<"cs316: Error: Float comparisons not allowed in Logical\n";
		exit(0);
	}
	if(lhs_op == NULL) printf("cs316: Error: LHS cannot be null");
	if(rhs_op == NULL) printf("cs316: Error: RHS cannot be null");
	Code_For_Ast & lhs_stmt = lhs_op->compile();
	Register_Descriptor * lreg = lhs_stmt.get_reg();
	Code_For_Ast & rhs_stmt = rhs_op->compile();
	Register_Descriptor * rreg = rhs_stmt.get_reg();

	list<Icode_Stmt *> & icList = *new list<Icode_Stmt *>;

	Ics_Opd * lhs_reg = new Register_Addr_Opd(lreg);
	Ics_Opd * rhs_reg = new Register_Addr_Opd(rreg);

	if (!lhs_stmt.get_icode_list().empty())
		icList = lhs_stmt.get_icode_list();
	if (!rhs_stmt.get_icode_list().empty())
		icList.merge(rhs_stmt.get_icode_list());

	Register_Descriptor * result_reg = machine_desc_object.get_new_register<int_reg>();
	Tgt_Op opr ;
	if(bool_op==_logical_or)
		opr=or_t;
	else if(bool_op==_logical_and)
		opr=and_t;
	
	result_reg->set_use_for_expr_result();
	Ics_Opd * register_result = new Register_Addr_Opd(result_reg);

	icList.push_back(new Compute_IC_Stmt(opr, lhs_reg, rhs_reg, register_result)) ;

	lreg->reset_use_for_expr_result();
	lreg->clear_lra_symbol_list();
	rreg->reset_use_for_expr_result();
	rreg->clear_lra_symbol_list();
	Code_For_Ast & rel_expr_code = *new Code_For_Ast(icList, result_reg);
	return rel_expr_code;
}




/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/




Code_For_Ast & Selection_Statement_Ast::compile() {
	// printf("sel %d\n",count); count++;
	Code_For_Ast Cond = cond->compile();
	Register_Descriptor *  condReg = Cond.get_reg();
	list<Icode_Stmt *> condIC = Cond.get_icode_list();
	Register_Addr_Opd * condOpd = new Register_Addr_Opd(condReg);	
	string lab1 = "label" + to_string(labelCounter);	

	Control_Flow_IC_Stmt* jump;
	if(cond->get_data_type()==int_data_type){
		jump = new Control_Flow_IC_Stmt(beq,condOpd,NULL,lab1);
		condIC.push_back(jump);
	}

	labelCounter++;

	Code_For_Ast thenBody = then_part->compile();
	list<Icode_Stmt *> thenIC = thenBody.get_icode_list();
	condIC.merge(thenIC);

	// Register_Descriptor * res;
	// if(lhs->get_data_type() == double_data_type){
	// 	res = machine_desc_object.get_new_register<float_reg>();
	// }
	// else{
	// 	res = machine_desc_object.get_new_register<int_reg>();
	// }
	// res->set_use_for_expr_result();

	// Register_Addr_Opd * result = new Register_Addr_Opd(res);
	// Register_Descriptor * ZeroReg = machine_desc_object.spim_register_table[zero];
	// ZeroReg->reset_use_for_expr_result();
	// Register_Addr_Opd * zeroOpd = new Register_Addr_Opd(ZeroReg);

	// Compute_IC_Stmt * temp = new Compute_IC_Stmt(or_t,thenOpd,zeroOpd,result);
	if(else_part!=NULL){
		string lab2 = "label" + to_string(labelCounter);	
		Label_IC_Stmt *labelStmt = new Label_IC_Stmt(j,lab2);

		// condIC.push_back(temp);
		condIC.push_back(labelStmt);

		Label_IC_Stmt * printLabelStmt = new Label_IC_Stmt(label,lab1);
		condIC.push_back(printLabelStmt);
		labelCounter++;

		Code_For_Ast elseBody = else_part->compile();
		list<Icode_Stmt *> elseIC = elseBody.get_icode_list();
		condIC.merge(elseIC);

		printLabelStmt = new Label_IC_Stmt(label,lab2);
		condIC.push_back(printLabelStmt);	
	}
	else{
		Label_IC_Stmt * printLabelStmt = new Label_IC_Stmt(label,lab1);
		condIC.push_back(printLabelStmt);
	}
	Code_For_Ast *c = new Code_For_Ast(condIC,condReg);
	condReg->reset_use_for_expr_result();
	return *c;
}


/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/




// Code_For_Ast & Selection_Statement_Ast::compile_and_optimize_ast(Lra_Outcome & lra)  {}

Code_For_Ast & Iteration_Statement_Ast::compile() {
	// printf("ite %d\n",count); count++;
	string label2 = "label" + to_string(labelCounter+1);	
	Label_IC_Stmt *jumpl2stmt = new Label_IC_Stmt(j,label2);

	string label1 = "label" + to_string(labelCounter);
	Label_IC_Stmt * printl1stmt = new Label_IC_Stmt(label,label1);

	labelCounter+=2;

	Code_For_Ast body_code = body->compile();
	list<Icode_Stmt *> bodyIC = body_code.get_icode_list();
	bodyIC.push_front(printl1stmt);

	if(!is_do_form)
		bodyIC.push_front(jumpl2stmt);

	Label_IC_Stmt * printl2stmt = new Label_IC_Stmt(label,label2);
	bodyIC.push_back(printl2stmt);

	Code_For_Ast Cond = cond->compile();
	Register_Descriptor *  condReg = Cond.get_reg();
	list<Icode_Stmt *> condIC = Cond.get_icode_list();
	Register_Addr_Opd * opd1 = new Register_Addr_Opd(condReg);
	bodyIC.merge(condIC);	

	Control_Flow_IC_Stmt* jump ;

	if(cond->get_data_type()==int_data_type){
		jump = new Control_Flow_IC_Stmt(bne,opd1,NULL,label1);
		bodyIC.push_back(jump);
	}
	else{
		Icode_Stmt *stmt = bodyIC.back();
		bodyIC.pop_back();
		Tgt_Op op = stmt->get_op().get_op();
		if(op==bc1t){
			bodyIC.push_back(new Label_IC_Stmt(bc1f,label1));
		}
		else{
			bodyIC.push_back(new Label_IC_Stmt(bc1t,label1));
		}
	}

	
	condReg->reset_use_for_expr_result();

	Code_For_Ast *c = new Code_For_Ast(bodyIC,condReg);

	return *c;
}




/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/


// Code_For_Ast & Iteration_Statement_Ast::compile_and_optimize_ast(Lra_Outcome & lra)  {}

Code_For_Ast & Sequence_Ast::compile()
{
	// printf("seq %d\n",count); count++;
	list <Ast *>::iterator i;
	list<Icode_Stmt *> *all_stmts = new list<Icode_Stmt *>();
	Code_For_Ast temp;
	for (i = statement_list.begin(); i != statement_list.end(); i++)
	{
		// CHECK_INVARIANT(((*i) != NULL), "Ast pointer seems to be NULL into the basic block");
		temp = (*i)->compile();
		all_stmts->merge(temp.get_icode_list());
	}
	Register_Descriptor * r=temp.get_reg();
	Code_For_Ast * c = new Code_For_Ast(*all_stmts,r);
	return *c;
}
// Code_For_Ast & Sequence_Ast::compile_and_optimize_ast(Lra_Outcome & lra)  {}


Code_For_Ast & Print_Ast::compile(){
	// printf("prt %d\n",count); count++;
	list<Icode_Stmt *> *icList = new list<Icode_Stmt *>();
	Register_Descriptor * vee0 = (machine_desc_object.spim_register_table[v0]);
	vee0->set_use_for_expr_result();
	Register_Addr_Opd * V0 = new Register_Addr_Opd(vee0);
	Register_Descriptor * aa0;

	Move_IC_Stmt * moveNum; 
	Mem_Addr_Opd * opd = new Mem_Addr_Opd(var->get_symbol_entry());
	Move_IC_Stmt * moveVar;

	Data_Type type = var->get_data_type();
	if(type == int_data_type){
		aa0 = (machine_desc_object.spim_register_table[a0]);
		aa0->set_use_for_expr_result();
		Register_Addr_Opd * A0 = new Register_Addr_Opd(aa0);

		Const_Opd<int> * constOne = new Const_Opd<int>(1);
		moveNum = new Move_IC_Stmt(imm_load , constOne, V0);

		moveVar = new Move_IC_Stmt(load , opd, A0);
	}
	else{
		aa0 = (machine_desc_object.spim_register_table[f12]);
		aa0->set_use_for_expr_result();
		Register_Addr_Opd * A0 = new Register_Addr_Opd(aa0);

		Const_Opd<int> * constThree = new Const_Opd<int>(3);
		moveNum = new Move_IC_Stmt(imm_load , constThree, V0);

		moveVar = new Move_IC_Stmt(load_d , opd, A0);
	}

	icList->push_back(moveNum);
	icList->push_back(moveVar);

	// Register_Descriptor * res = machine_desc_object.get_new_register<int_reg>();
	// res->set_use_for_expr_result();
	// Register_Addr_Opd * result = new Register_Addr_Opd(res);

	Print_IC_Stmt * temp = new Print_IC_Stmt();
	icList->push_back(temp);
	Code_For_Ast *c = new Code_For_Ast(*icList,aa0);
	// l->reset_use_for_expr_result();
	aa0->reset_use_for_expr_result();
	vee0->reset_use_for_expr_result();
	return *c;
}

// Code_For_Ast & Print_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}


// Code_For_Ast & Call_Ast::compile(){
// 	  printf("call %d\n",count); count++;
// 	  Procedure *proc = program_object.get_procedure_prototype(procedure_name);
// 	  // if(!proc->)
// 	  int offset = 0 ;
// 	  list<Ast *>::iterator arg_itr ;
// 	  list<Symbol_Table_Entry *>::iterator param_itr ;

// 	  Symbol_Table formalTable = proc->get_formal_param_list();

// 	  list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;
// 	  list<Symbol_Table_Entry *> * parameters = fn->get_arg_symbol_table()->get_variable_table() ;

// 	  for (arg_itr = arguments.begin(), param_itr = parameters->begin(); 
// 	      arg_itr != arguments.end() && param_itr != parameters->end(); 
// 	      ++arg_itr, ++param_itr)
// 	  {
// 	    CHECK_INVARIANT(((*arg_itr) != NULL), "Arguments cannot be null");
// 	    CHECK_INVARIANT(typeid(*(*arg_itr))!=typeid(Call_Ast), "Variable cannot be a function") ;
// 	    int step = 0;
// 	    Tgt_Op opr ;
// 	    Code_For_Ast & arg_stmt = (*arg_itr)->compile() ;
// 	    Register_Descriptor * areg = arg_stmt.get_reg() ;
// 	    if (areg->get_value_type() == int_num) {
// 	      opr = store ;
// 	      step = 4 ;
// 	    }
// 	    else if (areg->get_value_type() == float_num) {
// 	      opr = store_d ; 
// 	      step = 8 ;
// 	    }
// 	    else {
// 	      CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, "Invalid Argument Type");
// 	    }
// 	    Ics_Opd * arg_reg = new Register_Addr_Opd(areg);
// 	    Ics_Opd * res_reg = new Mem_Addr_Opd(*(*param_itr));
	  
// 	    if (arg_stmt.get_icode_list().empty() == false)
// 	      ic_list.splice(ic_list.end(), arg_stmt.get_icode_list());
// 	    ic_list.push_back(new Store_Param_IC_Stmt(opr, res_reg, arg_reg, offset)) ;
// 	    offset += step ;
// 	    areg->reset_use_for_expr_result();
// 	    areg->clear_lra_symbol_list();
// 	  }

// 	  ic_list.push_back(new Control_Flow_IC_Stmt(call, fn->get_proc_name(), offset)) ;

// 	  Register_Descriptor * result_reg = NULL;
// 	  Register_Descriptor * ret_val_reg = NULL ;
// 	  Tgt_Op opr ;

// 	  if (node_data_type==float_data_type) {
// 	    result_reg = machine_dscr_object.get_new_float_register();
// 	    ret_val_reg = machine_dscr_object.get_fn_ret_float_register() ;
// 	    opr = mv_d ;
// 	  }
// 	  else if (node_data_type==int_data_type) {
// 	    result_reg = machine_dscr_object.get_new_register();
// 	    ret_val_reg = machine_dscr_object.get_fn_ret_register() ;
// 	    opr = mv ;
// 	  }
// 	  else if (node_data_type==void_data_type) {
// 	    result_reg = NULL ;
// 	    ret_val_reg = NULL ;
// 	  }
// 	  else {
// 	    CHECK_INVARIANT(false, "Invalid return type") ;
// 	  }

// 	  if (result_reg && ret_val_reg) {
// 	    result_reg->set_used_for_expr_result();
// 	    Ics_Opd * register_result = new Register_Addr_Opd(result_reg);
// 	    Ics_Opd * register_ret_val = new Register_Addr_Opd(ret_val_reg);

// 	    ic_list.push_back( new Move_IC_Stmt(opr, register_ret_val, register_result)) ;
// 	  }

// 	  Code_For_Ast & rel_expr_code = *new Code_For_Ast(ic_list, result_reg);
// 	  return rel_expr_code;

// }

Code_For_Ast& Call_Ast::compile(){ 
	// printf("call %d\n",count); count++;
    list<Symbol_Table_Entry*> & formal_param_list=program_object.get_procedure_prototype(procedure_name)->get_formal_param_list().get_table(); 
    list<Ast*> :: iterator it1; 
    list<Symbol_Table_Entry*> :: iterator it2; 
    formal_param_list.reverse();
    actual_param_list.reverse();
   	list<Icode_Stmt *> *icList = new list<Icode_Stmt *>();
    check_actual_formal_param(program_object.get_procedure_prototype(procedure_name)->get_formal_param_list());
    // cout<<"after check"<<endl;

    Tgt_Op op; 
    int cnt=0;
    int len=0;
    int curOffset = 0;
    Symbol_Table & copytab= *new Symbol_Table();
    int argCount=0;
    for(it2=formal_param_list.begin();it2!=formal_param_list.end();it2++){
    	// cout<<"argcnt = "<<argCount<<endl;
    	argCount++;
       	string str = (*it2)->get_variable_name();
        Symbol_Table_Entry *ste = new Symbol_Table_Entry(str,(*it2)->get_data_type(),(*it2)->get_lineno(),sp_ref);
        // cout<<"hey"<<endl;
        ste->set_start_offset(curOffset);
        // cout<<"hey"<<endl;
        copytab.push_symbol(ste);
        // cout<<"hey"<<endl;
        if((*it2)->get_data_type()==int_data_type){
        	curOffset-=4;
        	len+=4;
        }
        else if((*it2)->get_data_type()==double_data_type){
        	len+=8;
        	curOffset-=8;
        }
        // cout<<"hey"<<endl;
    }
    copytab.set_table_scope(formal);

    list<Symbol_Table_Entry*> :: iterator it3; 

    // cout<<"after symtab copy"<<endl;

    // program_object.get_procedure_prototype(procedure_name)->get_formal_param_list().set_start_offset_of_first_symbol(startOffset-len);

    for(it1=actual_param_list.begin(),it3=copytab.get_table().begin();it1!=actual_param_list.end();it1++,it3++){
    	// cout<<cnt++<<endl;
    	// (*it2)->set_start_offset(curOffset);
    	// if((*it1)->get_data_type()==int_data_type){
     //    	len+=4;
     //    	curOffset-=4;
     //    }
     //    else if((*it1)->get_data_type()==double_data_type){
     //    	len+=8;
     //    	curOffset-=8;
     //    }
        Code_For_Ast & param=(*it1)->compile(); 
        Register_Descriptor * param_reg=param.get_reg(); 
        if(param_reg->get_use_category()==int_reg){
            op=store; 
        }
        else if(param_reg->get_use_category()==float_reg){
            op=store_d; 
        }
        else {
        }
        Ics_Opd * param_opd=new Register_Addr_Opd(param_reg);  
        Ics_Opd * dest_opd=new Mem_Addr_Opd(*(*it3)); 
        icList->merge(param.get_icode_list()); 
        icList->push_back(new Move_IC_Stmt(op,param_opd,dest_opd)); 
        param_reg->reset_use_for_expr_result(); 
        param_reg->clear_lra_symbol_list(); 
    }

    // cout<<"after actual_param_list"<<endl;

    formal_param_list.reverse();
    actual_param_list.reverse();
    // TODO
    Register_Descriptor * stackReg = (machine_desc_object.spim_register_table[sp]);
    Ics_Opd * stackOpd=new Register_Addr_Opd(stackReg); 
    Ics_Opd * lenOpd = new Const_Opd<int>(len);
    icList->push_back(new Compute_IC_Stmt(sub,stackOpd,lenOpd,stackOpd));
    icList->push_back(new Label_IC_Stmt(jal,procedure_name));
    icList->push_back(new Compute_IC_Stmt(add,stackOpd,lenOpd,stackOpd));
    Register_Descriptor * ret = NULL; 
    Register_Descriptor * res = NULL; 
    if(node_data_type==double_data_type){
        op=move_d; 
        res=machine_desc_object.get_new_register<float_reg>(); 
        ret=(machine_desc_object.spim_register_table[f0]); 
    }
    else if(node_data_type==int_data_type){
        op=mov; 
        res=machine_desc_object.get_new_register<int_reg>(); 
        ret=(machine_desc_object.spim_register_table[v1]); 
    }
    // cout<<"after label stmt"<<endl;
    if(res && ret){
        res->set_use_for_expr_result(); 
        Ics_Opd * ret_opd=new Register_Addr_Opd(ret); 
        Ics_Opd * res_opd=new Register_Addr_Opd(res); 
        icList->push_back(new Move_IC_Stmt(op,ret_opd,res_opd)); 
		ret->reset_use_for_expr_result(); 
        ret->clear_lra_symbol_list(); 
    }
    if(return_value_reg!=NULL){
    	if(res && ret)
    	{
	    	ret->reset_use_for_expr_result(); 
	    	res->reset_use_for_expr_result();
    	}
    }
    Code_For_Ast & call_code=*new Code_For_Ast(*icList,res); 
    return call_code; 
}

Code_For_Ast & Call_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}
