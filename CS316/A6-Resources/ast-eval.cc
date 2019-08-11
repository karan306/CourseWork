#include "ast.hh"
#include "symbol-table.hh"
#include "procedure.hh"
#include "program.hh"
#include "local-environment.hh"


template class Number_Ast<double>;
template class Number_Ast<int>;


void Symbol_Table::create(Local_Environment & local_global_variables_table)
{
	list<Symbol_Table_Entry *>::iterator it;

	for (it = variable_table.begin(); it != variable_table.end(); it++)
	{
		string s = (*it)->get_variable_name();
		if((*it)->get_data_type()==int_data_type){
			Eval_Result_Value_Int * result = new Eval_Result_Value_Int();
			if (scope == global)
			{
				result->set_variable_status(false);
				result->set_value(0);
			}
			local_global_variables_table.put_variable_value(*result, s);
		}
		else{
			Eval_Result_Value_Double * result = new Eval_Result_Value_Double();
			if (scope == global)
			{
				result->set_variable_status(false);
				result->set_value(0);
			}
			local_global_variables_table.put_variable_value(*result, s);
		}
	}
}


void Ast::print_value(Local_Environment & eval_env, ostream & file_buffer){

}

Eval_Result & Ast::get_value_of_evaluation(Local_Environment & eval_env){

}
void Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result){

}
Eval_Result & Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){

}


Eval_Result & Assignment_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	//  printf("hey\n");
  Eval_Result & result = rhs->evaluate(eval_env, file_buffer);
    // printf("hi\n");
    if(result.is_variable_defined() ==false)
        printf("cs316: Error : Variable should be defined to be on rhs\n");

	lhs->set_value_of_evaluation(eval_env, result);
  // printf("1\n");
	print(file_buffer);
  // printf("2\n");
	lhs->print_value(eval_env, file_buffer);
  // printf("3\n");
	return result;
}




void Name_Ast::print_value(Local_Environment & eval_env, ostream & file_buffer)
{
	string varName = variable_symbol_entry->get_variable_name();

	Eval_Result * loc_var_val = eval_env.get_variable_value(varName);
	Eval_Result * glob_var_val = interpreter_global_table.get_variable_value(varName);

	file_buffer << "\n" << AST_SPACE << varName << " : ";

	if (!eval_env.is_variable_defined(varName) && !interpreter_global_table.is_variable_defined(varName))
		file_buffer << "undefined";

	else if (eval_env.is_variable_defined(varName) && loc_var_val != NULL)
	{
		if(loc_var_val->get_result_enum() == int_result)
		    file_buffer << loc_var_val->get_int_value() << "\n";
    else if(loc_var_val->get_result_enum() == double_result)
        file_buffer << loc_var_val->get_double_value() << "\n";
    else
        printf("cs316: Error: type can be int or float\n");
	}

	else
	{
		if (glob_var_val == NULL)
			file_buffer << "0\n";
		else if(glob_var_val->get_result_enum() == int_result)
			file_buffer << glob_var_val->get_int_value() << "\n";
    else if(glob_var_val->get_result_enum() == double_result)
        file_buffer << glob_var_val->get_double_value() << "\n";
    else
        printf("cs316: Error: type can be int or float\n");            
	}
	file_buffer << "\n";
}

Eval_Result & Name_Ast::get_value_of_evaluation(Local_Environment & eval_env)
{
	string varName = variable_symbol_entry->get_variable_name();

	if (eval_env.does_variable_exist(varName))
	{
		if(eval_env.is_variable_defined(varName) == false){
			printf("cs316: Error  : Variable should be defined before its use\n");
      exit(0);
    }

		Eval_Result * result = eval_env.get_variable_value(varName);
		return *result;
	}

	if(interpreter_global_table.is_variable_defined(varName) == false){
		printf("cs316: Error : Variable should be defined before its use\n");
    exit(0);
  }

	Eval_Result * result = interpreter_global_table.get_variable_value(varName);
	return *result;
}

void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result)
{
	Eval_Result * i;
	string varName = variable_symbol_entry->get_variable_name();

	if (variable_symbol_entry->get_data_type() == int_data_type){
		i = new Eval_Result_Value_Int();
        if (result.get_result_enum() == int_result)
	 	    i->set_value(result.get_int_value());
        else
            printf("cs316: Error : Type Mismatch\n");
    }
	else{
        i = new Eval_Result_Value_Double();
        if (result.get_result_enum() == double_result)
	 	    i->set_value(result.get_double_value());
        else
            printf("cs316: Error : Type Mismatch\n");
    }
	if (eval_env.does_variable_exist(varName))
	  eval_env.put_variable_value(*((Eval_Result_Value *) i), varName);
	else
		interpreter_global_table.put_variable_value(*((Eval_Result_Value *) i), varName);
}

Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
  // cout<<variable_symbol_entry->get_variable_name()<<endl;
	return get_value_of_evaluation(eval_env);
}

template <class DATA_TYPE>
Eval_Result & Number_Ast<DATA_TYPE>::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	// cout<<constant<<endl;
  if (node_data_type == int_data_type)
	{
		Eval_Result & result = *new Eval_Result_Value_Int();
		result.set_value(constant);
		return result;
	}
    else{
        Eval_Result & result = *new Eval_Result_Value_Double();
		result.set_value(constant);
		return result;
    }
}

Eval_Result & Plus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
  Eval_Result & lhs_result = lhs->evaluate(eval_env, file_buffer);
  Eval_Result & rhs_result = rhs->evaluate(eval_env, file_buffer);
 
  if(node_data_type == int_data_type) {
    Eval_Result * result = new Eval_Result_Value_Int(); 
    result->set_value( lhs_result.get_int_value() + rhs_result.get_int_value());
    return * result;
  }
  
  else {
    Eval_Result * result = new Eval_Result_Value_Double(); 
    result->set_value( lhs_result.get_double_value() + rhs_result.get_double_value());
    return * result;
  }
}

Eval_Result & Minus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
  Eval_Result & lhs_result = lhs->evaluate(eval_env, file_buffer);
  Eval_Result & rhs_result = rhs->evaluate(eval_env, file_buffer);
 
  if(node_data_type == int_data_type) {
    Eval_Result * result = new Eval_Result_Value_Int(); 
    result->set_value( lhs_result.get_int_value() - rhs_result.get_int_value());
    return * result;
  }
  
  else {
    Eval_Result * result = new Eval_Result_Value_Double(); 
    result->set_value( lhs_result.get_double_value() - rhs_result.get_double_value());
    return * result;
  }
}

Eval_Result & Mult_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
  Eval_Result & lhs_result = lhs->evaluate(eval_env, file_buffer);
  Eval_Result & rhs_result = rhs->evaluate(eval_env, file_buffer);
 
  if(node_data_type == int_data_type) {
    Eval_Result * result = new Eval_Result_Value_Int(); 
    result->set_value( lhs_result.get_int_value() * rhs_result.get_int_value());
    return * result;
  }
  
  else {
    Eval_Result * result = new Eval_Result_Value_Double(); 
    result->set_value( lhs_result.get_double_value() * rhs_result.get_double_value());
    return * result;
  }
}

Eval_Result & Divide_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
  Eval_Result & lhs_result = lhs->evaluate(eval_env, file_buffer);
  Eval_Result & rhs_result = rhs->evaluate(eval_env, file_buffer);
 
  if(node_data_type == int_data_type) {
    if(rhs_result.get_int_value() == 0) {
        printf("cs316: Error : Divide by 0\n");
        exit(0);
    }
    
    Eval_Result * result = new Eval_Result_Value_Int(); 
    result->set_value( lhs_result.get_int_value() / rhs_result.get_int_value());
    return * result;
  }
  
  else {
    if(rhs_result.get_double_value() == 0.0) {
        printf("cs316: Error : Divide by 0\n");
        exit(0);
    }
    Eval_Result * result = new Eval_Result_Value_Double(); 
    result->set_value( lhs_result.get_double_value() / rhs_result.get_double_value());
    return * result;
  }
}

Eval_Result & UMinus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer) {
  Eval_Result & lhs_result = lhs->evaluate(eval_env, file_buffer);
 
  if(node_data_type == int_data_type) {
    Eval_Result * result = new Eval_Result_Value_Int(); 
    result->set_value( -1 * lhs_result.get_int_value());
    return * result;
  }
  
  else {
    Eval_Result * result = new Eval_Result_Value_Double(); 
    result->set_value( -1.0 * lhs_result.get_double_value());
    return * result;
  }
}

Eval_Result & Conditional_Expression_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    Eval_Result & cond_result = cond->evaluate(eval_env, file_buffer);
    
    if(cond_result.get_int_value() == 1){
        Eval_Result & lhs_result = lhs->evaluate(eval_env, file_buffer);
        if(lhs_result.get_result_enum()==int_result){
            Eval_Result & result = *new Eval_Result_Value_Int();
            result.set_value(lhs_result.get_int_value());
            return result;
        }
        else{
            Eval_Result & result = *new Eval_Result_Value_Double();
            result.set_value(lhs_result.get_double_value());
            return result;
        }
    }
    else{
        Eval_Result & rhs_result = rhs->evaluate(eval_env, file_buffer);
        if(rhs_result.get_result_enum()==int_result){
            Eval_Result & result = *new Eval_Result_Value_Int();
            result.set_value(rhs_result.get_int_value());
            return result;
        }
        else{
            Eval_Result & result = *new Eval_Result_Value_Double();
            result.set_value(rhs_result.get_double_value());
            return result;
        }
    }
}

Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){}


Eval_Result & Relational_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	
	Eval_Result & rhs_result = rhs_condition->evaluate(eval_env, file_buffer);
	Eval_Result & lhs_result = lhs_condition->evaluate(eval_env, file_buffer);

	if (!lhs_result.is_variable_defined())
        printf("cs316: Error : Variable should be defined on LHS of comparison\n");
    if (!rhs_result.is_variable_defined())
        printf("cs316: Error : Variable should be defined on RHS of comparison\n");

	Eval_Result & result = *new Eval_Result_Value_Int();

	double lhs_value;
	double rhs_value;

	if(lhs_result.get_result_enum()==int_result)
		lhs_value = lhs_result.get_int_value();
	else
		lhs_value = lhs_result.get_double_value();

	if(rhs_result.get_result_enum()==double_result)
		rhs_value = rhs_result.get_double_value();
	else
		rhs_value = rhs_result.get_int_value();

	if(rel_op==less_equalto)
	{
		if(lhs_value<=rhs_value)
			result.set_value(1);
		else
			result.set_value(0);
	}
	else if(rel_op==less_than)
	{
		if(lhs_value<rhs_value)
			result.set_value(1);
		else
			result.set_value(0);
	}
	else if(rel_op==greater_equalto)
	{
		if(lhs_value>=rhs_value)
			result.set_value(1);
		else
			result.set_value(0);
	}
	else if(rel_op==greater_than)
	{
		if(lhs_value>rhs_value)
			result.set_value(1);
		else
			result.set_value(0);
	}
	else if(rel_op==not_equalto)
	{
		if(lhs_value!=rhs_value)
			result.set_value(1);
		else
			result.set_value(0);
	}
	else
	{
		if(lhs_value==rhs_value)
			result.set_value(1);
		else
			result.set_value(0);
	}

  // cout<<result.get_int_value()<<endl<<endl;
	return result;
}

Eval_Result & Logical_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    if(bool_op==_logical_not){
        Eval_Result & rhs_result = rhs_op->evaluate(eval_env, file_buffer);
        Eval_Result & result = *new Eval_Result_Value_Int();
        if(rhs_result.get_int_value()==0)
            result.set_value(1);
        else
            result.set_value(0);
        return result;
    }
    else{
        Eval_Result & lhs_result = lhs_op->evaluate(eval_env, file_buffer);
        Eval_Result & rhs_result = rhs_op->evaluate(eval_env, file_buffer);
        Eval_Result & result = *new Eval_Result_Value_Int();
        if(bool_op == _logical_or){
            result.set_value(rhs_result.get_int_value() | lhs_result.get_int_value());
        }
        else{
            result.set_value(rhs_result.get_int_value() & lhs_result.get_int_value());
        }
        return result;
    }
}

Eval_Result & Selection_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    Eval_Result & cond_result = cond->evaluate(eval_env, file_buffer);
    Eval_Result & result = *new Eval_Result_Value_Int();
    if(cond_result.get_int_value() == 1){
        Eval_Result & lhs_result = then_part->evaluate(eval_env, file_buffer);
        result.set_value(1);
    }
    else{
        if(else_part!=NULL){
          Eval_Result & rhs_result = else_part->evaluate(eval_env, file_buffer);
        }
        result.set_value(0);
    }
    return result;
}

Eval_Result & Iteration_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
    Eval_Result & result = *new Eval_Result_Value_Int();
    // Eval_Result & Cond = *new Eval_Result_Value_Int();
    if(is_do_form){
      body->evaluate(eval_env,file_buffer);
      // result.set_value(1);
    }
    // Eval_Result & cond_result = cond->evaluate(eval_env, file_buffer);
    // Cond.set_value(cond_result.get_int_value());
    // cout<<cond_result.get_int_value()<<"hi"<<endl;
    while(cond->evaluate(eval_env,file_buffer).get_int_value()){
      body->evaluate(eval_env,file_buffer);
      // cond_result=cond->evaluate(eval_env,file_buffer);
      // Cond.set_value(cond_result.get_int_value());
    }
    result.set_value(0);
    return result;
}

Eval_Result & Sequence_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
  Eval_Result & result = *new Eval_Result_Value_Int();
  list<Ast *>::iterator it;
  for(it=statement_list.begin();it!=statement_list.end();it++){
    (*it)->evaluate(eval_env,file_buffer);
  }
  result.set_value(1);
  return result;
}

// Eval_Result & Print_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer){
  
// }
