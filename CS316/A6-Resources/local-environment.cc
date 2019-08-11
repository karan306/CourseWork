#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#include "local-environment.hh"

int Eval_Result::get_int_value(){

}

void Eval_Result::set_value(int value){

}

double Eval_Result::get_double_value(){

}

void Eval_Result::set_value(double value){

}

bool Eval_Result::is_variable_defined(){

}

void Eval_Result::set_variable_status(bool def){

}

void Eval_Result_Value::set_value(int number){

}
void Eval_Result_Value::set_value(double number){

}
int Eval_Result_Value::get_int_value(){

}
double Eval_Result_Value::get_double_value(){

}

Eval_Result_Value_Int::Eval_Result_Value_Int()
{
	value = 0;
	defined = false;
	result_type = int_result;
}

Eval_Result_Value_Int::~Eval_Result_Value_Int()
{ }

void Eval_Result_Value_Int::set_value(int number)
{
	value = number;
	defined = true;
}
void Eval_Result_Value_Int::set_value(double number)
{
	value = (int)number;
	defined = true;
}

int Eval_Result_Value_Int::get_int_value()
{
	return value;
}

void Eval_Result_Value_Int::set_variable_status(bool def)
{
	defined = def;
}

bool Eval_Result_Value_Int::is_variable_defined()
{
	return defined;
}

void Eval_Result_Value_Int::set_result_enum(Result_Enum res)
{
	result_type = res;
}

Result_Enum Eval_Result_Value_Int::get_result_enum()
{
	return result_type;
}





Eval_Result_Value_Double::Eval_Result_Value_Double()
{
	value = 0.0;
	defined = false;
	result_type = double_result;
}

Eval_Result_Value_Double::~Eval_Result_Value_Double()
{ }

void Eval_Result_Value_Double::set_value(double number)
{
	value = number;
	defined = true;
}
void Eval_Result_Value_Double::set_value(int number)
{
	value = (double)number;
	defined = true;
}
double Eval_Result_Value_Double::get_double_value()
{
	return value;
}

void Eval_Result_Value_Double::set_variable_status(bool def)
{
	defined = def;
}

bool Eval_Result_Value_Double::is_variable_defined()
{
	return defined;
}

void Eval_Result_Value_Double::set_result_enum(Result_Enum res)
{
	result_type = res;
}

Result_Enum Eval_Result_Value_Double::get_result_enum()
{
	return result_type;
}




Local_Environment::Local_Environment()
{}

Local_Environment::~Local_Environment()
{}

void Local_Environment::print(ostream & file_buffer)
{
	map<string, Eval_Result *>::iterator i;
	for (i = variable_table.begin(); i != variable_table.end(); i++)
	{
		Eval_Result * vi = i->second;
		if (vi != NULL)
		{
			if (vi->is_variable_defined() == false)
				file_buffer << VAR_SPACE << (*i).first << " : undefined" << "\n";
		
			else if(vi->get_result_enum() == int_result) 
				file_buffer << VAR_SPACE << (*i).first << " : " << vi->get_int_value() << "\n";
			
			else if(vi->get_result_enum() == double_result) 
			  file_buffer << VAR_SPACE << (*i).first << " : " << std::fixed << std::setprecision(2) << vi->get_double_value() << "\n";
		}
	}
}

bool Local_Environment::is_variable_defined(string name)
{
	Eval_Result * i = variable_table[name];
	if (i != NULL) {
		return i->is_variable_defined();
	}
	else
		return false;
}

Eval_Result * Local_Environment::get_variable_value(string name)
{
	Eval_Result * i = variable_table[name];
	return i;
}

void Local_Environment::put_variable_value(Eval_Result & i, string name)
{
	variable_table[name] = &i; 
}

bool Local_Environment::does_variable_exist(string name)
{
	if (variable_table[name] == NULL)
		return false;
	else
		return true;
}
