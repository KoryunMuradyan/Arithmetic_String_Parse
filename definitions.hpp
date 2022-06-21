#ifndef __DEFINITIONS_CPP__
#define __DEFINITIONS_CPP__

#include "arithmetic_expr.hpp"
#include <cassert>
#include <math.h>

arithmetic_expr::arithmetic_expr(const std::string& arg_str)
{
	resolve_str(arg_str);
	current = first;
}

arithmetic_expr::arithmetic_expr(const node*& arg_first, const node*& arg_last)
{
	const node* tmp_current = arg_first;
	while(tmp_current != arg_last->next)
	{
		node *new_node = new node;
		new_node->op = tmp_current->op;
		new_node->math_f_expr = tmp_current->math_f_expr;
		new_node->val = tmp_current->val;
		bind_node(new_node);
		tmp_current = tmp_current->next;
	}
	current = first;
}

arithmetic_expr::arithmetic_expr(const node*&& arg_first, const node*&& arg_last)
{
	const node* tmp_current = arg_first;
	while(tmp_current != arg_last->next)
	{
		node *new_node = new node;
		new_node->op = tmp_current->op;
		new_node->math_f_expr = tmp_current->math_f_expr;
		new_node->val = tmp_current->val;
		bind_node(new_node);
		tmp_current = tmp_current->next;
	}
	current = first;
}

void arithmetic_expr::resolve_str(const std::string& arg_str)
{
	int counter = 0;
	std::string tmp_numer_str = "", to_pass = "", math_f_expr = "";
	for(auto i: arg_str) {
		++counter;
		if(i == ' ') {continue;}
		if((int(i) >= 48 && int(i) <= 57) || i == '.') {
			tmp_numer_str += i;
			if(counter == arg_str.size()) {
				insert_num(tmp_numer_str);
			}
			to_pass = i;
			continue;
		} else if('-' == i && "(" == to_pass) {
			to_pass = "";
			tmp_numer_str += i;
			continue;
		} else if(int(i) >= 97 && int(i) <= 122) {
			math_f_expr += i;
			continue;
		}
		if(tmp_numer_str.size() > 0) {
			insert_num(tmp_numer_str);
		} else if(0 < math_f_expr.size()) {
			insert_math_f_expr(math_f_expr);
		}
		to_pass = "";
		to_pass+=i;
		insert_symbol(to_pass);
	}
}

void arithmetic_expr::insert_symbol(const std::string& arg_symbol)
{
	assert("+" == arg_symbol || "-" == arg_symbol || "*" == arg_symbol ||
		"/" == arg_symbol || "(" == arg_symbol || ")" == arg_symbol ||
		"," == arg_symbol
		);
	node *new_node = new node;
	new_node->op = arg_symbol;
	bind_node(new_node);
}

void arithmetic_expr::insert_num(std::string& arg_numer_str)
{
	node *new_node = new node;
	new_node->val = std::stof(arg_numer_str);
	arg_numer_str = "";
	bind_node(new_node);
}

void arithmetic_expr::insert_math_f_expr(std::string& arg_math_f_expr)
{
	assert("sin" == arg_math_f_expr || "cos" == arg_math_f_expr || 
		"tan" == arg_math_f_expr || "acos" == arg_math_f_expr ||
		"asin" == arg_math_f_expr || "atan" == arg_math_f_expr ||
		"cosh" == arg_math_f_expr || "tanh" == arg_math_f_expr ||
		"log" == arg_math_f_expr || "pow" == arg_math_f_expr
	);
	node *new_node = new node;
	new_node->math_f_expr = arg_math_f_expr;
	arg_math_f_expr = "";
	bind_node(new_node);
}

void arithmetic_expr::bind_node(node*& arg_node)
{
	if(nullptr == first){
		first = arg_node;
		last = first;
	} else {
		arg_node->next = nullptr;
		last->next = arg_node;
		arg_node->prev = last;
		last = arg_node;
	}
}

bool arithmetic_expr::is_sin(node*& arg_node)
{
	return ("sin" == arg_node->math_f_expr);
}

bool arithmetic_expr::is_cos(node*& arg_node)
{
	return ("cos" == arg_node->math_f_expr);
}

bool arithmetic_expr::is_tan(node*& arg_node)
{
	return ("tan" == arg_node->math_f_expr);
}

bool arithmetic_expr::is_cosh(node*& arg_node)
{
	return ("cosh" == arg_node->math_f_expr);
}

bool arithmetic_expr::is_tanh(node*& arg_node)
{
	return ("tanh" == arg_node->math_f_expr);
}

bool arithmetic_expr::is_asin(node*& arg_node)
{
	return ("asin" == arg_node->math_f_expr);
}

bool arithmetic_expr::is_acos(node*& arg_node)
{
	return ("acos" == arg_node->math_f_expr);
}

bool arithmetic_expr::is_atan(node*& arg_node)
{
	return ("atan" == arg_node->math_f_expr);
}

bool arithmetic_expr::is_log(node*& arg_node)
{
	return ("log" == arg_node->math_f_expr);
}

bool arithmetic_expr::is_power(node*& arg_node)
{
	return ("pow" == arg_node->math_f_expr);
}

bool arithmetic_expr::is_minus(node*& arg_node)
{
	return ("-" == arg_node->op);
}

bool arithmetic_expr::is_plus(node*& arg_node)
{
	return ("+" == arg_node->op);
}

bool arithmetic_expr::is_mult(node*& arg_node)
{
	return ("*" == arg_node->op);
}

bool arithmetic_expr::is_div(node*& arg_node)
{
	return ("/" == arg_node->op);
}

bool arithmetic_expr::is_open_brace(node*& arg_node)
{
	return ("(" == arg_node->op);
}

bool arithmetic_expr::is_close_brace(node*& arg_node)
{
	return (")" == arg_node->op);
}

bool arithmetic_expr::is_comma(node*& arg_node)
{
	return ("," == arg_node->op);
}

bool arithmetic_expr::is_number(node*& arg_node)
{
	return (0 == arg_node->math_f_expr.size() && 
			"" == arg_node->op);
}

bool arithmetic_expr::is_math_f_expr(node*& arg_node)
{
	return (0 < arg_node->math_f_expr.size());
}

bool arithmetic_expr::is_operator(node*& arg_node)
{
	auto to_compare = arg_node->op;
	return ("+" == to_compare || "-" == to_compare || "*" == to_compare ||
			"/" == to_compare);
}

float arithmetic_expr::solve()
{
	if(nullptr == this->current->next && nullptr == this->current->prev) {
		return this->current->val;
	} else if(is_operator(this->current)) {
		solve_operator(this->current);
		return solve();
	} else if(is_math_f_expr(this->current)) {
		this->resolve_and_swap_the_math_f_expr(this->current);
		return solve();
	} else if(is_open_brace(this->current)) {
		this->resolve_and_swap_the_braced_expr(this->current);
		return solve();
	} else if(is_number(this->current) && nullptr != this->current->next) {  // Conceptually both first and second conditions are optional and  most likely they should be removed
		this->current = this->current->next;
		return solve();
	}
}

void arithmetic_expr::resolve_and_swap_the_math_f_expr(node*& arg_node)
{
	node *new_node = new node;
	node *new_next = find_cobrace(arg_node->next);
	new_next = new_next->next;
	new_node->next = new_next;
	new_node->val = solve_math_f_expr(arg_node);
	cut_dummy_range(arg_node, arg_node);
	if(nullptr != new_next) {
		new_next->prev = new_node;
	}
	this->first = new_node;
	this->current = first;
}

void arithmetic_expr::resolve_and_swap_the_braced_expr(node*& arg_node)
{
	node *new_node = new node;
	node *new_next = find_cobrace(arg_node);
	new_next = new_next->next;
	new_node->next = new_next;
	new_node->val = resolve_brace(arg_node);
	if(nullptr != new_next) {
		new_next->prev = new_node;
	}
	this->current = new_node;
	this->first = new_node;
}

void arithmetic_expr::solve_operator(node*& arg_node)
{
	if(is_plus(this->current)) {
		solve_plus(this->current);
	} else if(is_minus(this->current)) {
		solve_minus(this->current);
	} else if(is_mult(this->current)) {
		solve_mult(this->current);
	} else if(is_div(this->current)) {
		solve_div(this->current);
	}
}

void arithmetic_expr::solve_plus(node*& arg_node)
{
	arithmetic_expr *new_obj = new arithmetic_expr(arg_node->next, this->last);
	float right_operand = new_obj->solve();
	delete new_obj;
	new_obj = nullptr;
	auto tmp = arg_node->prev;
	assert(is_number(arg_node->prev));
	cut_dummy_range(arg_node, last);
	arg_node->prev->val += right_operand;
	current = current->prev;
}

void arithmetic_expr::solve_minus(node*& arg_node)
{
	arithmetic_expr *new_obj = new arithmetic_expr(arg_node->next, this->last);
	float right_operand = new_obj->solve();
	delete new_obj;
	new_obj = nullptr;
	assert(is_number(arg_node->prev));
	cut_dummy_range(arg_node, last);
	arg_node->prev->val -= right_operand;
	current = current->prev;
}

void arithmetic_expr::solve_mult(node*& arg_node)
{
	if(is_number(arg_node->next)) {
		arg_node->prev->val *= arg_node->next->val;
		auto tmp_node = arg_node->prev;
		cut_dummy_range(arg_node, arg_node->next);
		arg_node = tmp_node;
	} else if(is_open_brace(arg_node->next)) {
		arg_node->prev->val *= resolve_brace(arg_node->next);
		auto tmp_node = arg_node->prev;
		cut_dummy_range(arg_node, arg_node);
		arg_node = tmp_node;
	} else if(is_math_f_expr(arg_node->next)) {
		arg_node->prev->val *= solve_math_f_expr(arg_node->next);
		auto tmp_node = arg_node->prev;
		cut_dummy_range(arg_node, arg_node->next);
		current = tmp_node;
	}
}

void arithmetic_expr::solve_div(node*& arg_node)
{	
	if(is_number(arg_node->next)) {
		arg_node->prev->val = divide(arg_node->prev->val, arg_node->next->val);
		auto tmp_node = arg_node->prev;
		cut_dummy_range(arg_node, arg_node->next);
		arg_node = tmp_node;
	} else if(is_open_brace(arg_node->next)) {
		arg_node->prev->val = divide(arg_node->prev->val, resolve_brace(arg_node->next));
		auto tmp_node = arg_node->prev;
		cut_dummy_range(arg_node, arg_node);
		arg_node = tmp_node;
	} else if(is_math_f_expr(arg_node->next)) {
		arg_node->prev->val = divide(arg_node->prev->val, solve_math_f_expr(arg_node->next));
		auto tmp_node = arg_node->prev;
		cut_dummy_range(arg_node, arg_node->next);
		current = tmp_node;
	}
}

float arithmetic_expr::resolve_brace(node*& arg_node)
{
	node *tmp_current = find_cobrace(arg_node);
	node *begin = arg_node->next, *end = tmp_current->prev;
	arithmetic_expr *new_obj = new arithmetic_expr(begin, end);
	cut_dummy_range(arg_node, tmp_current);
	float to_return = new_obj->solve();
	delete new_obj;
	return to_return;
}

node* arithmetic_expr::find_cobrace(node* arg_node)
{
	int counter = 1;
	node *tmp_current = arg_node;
	while(0 < counter) {
		tmp_current = tmp_current->next;
		if(")" == tmp_current->op) {
			--counter;
		} else if("(" == tmp_current->op) {
			++counter;
		}
	}
	return tmp_current;
}

float arithmetic_expr::solve_math_f_expr(node*& arg_node)
{
	if(is_power(arg_node)) {
		return solve_power(arg_node);
	} else if(is_sin(arg_node)) {
		return solve_sin(arg_node);
	} else if(is_cos(arg_node)) {
		return solve_cos(arg_node);
	} else if(is_tan(arg_node)) {
		return solve_tan(arg_node);
	} else if(is_asin(arg_node)) {
		return solve_asin(arg_node);
	} else if(is_acos(arg_node)) {
		return solve_acos(arg_node);
	} else if(is_atan(arg_node)) {
		return solve_atan(arg_node);
	} else if(is_cosh(arg_node)) {
		return solve_cosh(arg_node);
	} else if(is_tanh(arg_node)) {
		return solve_tanh(arg_node);
	} else if(is_log(arg_node)) {
		return solve_log(arg_node);
	}
}

float arithmetic_expr::solve_sin(node*& arg_node)
{
	return sin(resolve_brace(arg_node->next));
}

float arithmetic_expr::solve_cos(node*& arg_node)
{
	return cos(resolve_brace(arg_node->next));
}

float arithmetic_expr::solve_tan(node*& arg_node)
{
	return tan(resolve_brace(arg_node->next));
}

float arithmetic_expr::solve_asin(node*& arg_node)
{
	return asin(resolve_brace(arg_node->next));
}

float arithmetic_expr::solve_acos(node*& arg_node)
{
	return acos(resolve_brace(arg_node->next));
}

float arithmetic_expr::solve_atan(node*& arg_node)
{
	return atan(resolve_brace(arg_node->next));
}

float arithmetic_expr::solve_cosh(node*& arg_node)
{
	return cosh(resolve_brace(arg_node->next));
}

float arithmetic_expr::solve_tanh(node*& arg_node)
{
	return tanh(resolve_brace(arg_node->next));
}

float arithmetic_expr::solve_log(node*& arg_node)
{
	std::pair<float, float> base_inter = resolve_log_pow_brace(arg_node);
	return log(base_inter.second)/log(base_inter.first);
}

float arithmetic_expr::solve_power(node*& arg_node)
{
	std::pair<float, float> base_inter = resolve_log_pow_brace(arg_node);
	return pow(base_inter.first, base_inter.second);
}

std::pair<float, float> arithmetic_expr::resolve_log_pow_brace(node*& arg_node)
{
	node *open_comma = arg_node->next;
	node *comma = find_pow_log_comma(open_comma);
	node *coobrace = find_cobrace(open_comma);
	node *to_pass_1 = open_comma->next, *to_pass_2 = comma->prev;
	node *to_pass_3 = comma->next, *to_pass_4 = coobrace->prev;
	arithmetic_expr *new_obj_1 = new arithmetic_expr(to_pass_1, to_pass_2);
	arithmetic_expr *new_obj_2 = new arithmetic_expr(to_pass_3, to_pass_4);
	float base = new_obj_1->solve();
	float interest = new_obj_2->solve();
	delete new_obj_1;
	delete new_obj_2;
	cut_dummy_range(open_comma, coobrace);
	return std::move(std::pair<float, float>(base, interest));
}

void make_number_node(node*& arg_node, const float& arg_num)
{
	arg_node->op = "";
	arg_node->math_f_expr = "";
	arg_node->val = arg_num;
}

node* arithmetic_expr::find_pow_log_comma(node*& arg_node)
{
	node *tmp_current = arg_node;
	int counter = 1;
	while(0 < counter) {
		tmp_current = tmp_current->next;
		if(is_power(tmp_current) || is_log(tmp_current)) {
			++counter;
		} else if(is_comma(tmp_current)) {
			--counter;
		}
	}
	return tmp_current;
}

void arithmetic_expr::cut_dummy_range(node* arg_begin, node*  arg_end)
{
	if(nullptr != arg_begin->prev) {
		arg_begin->prev->next = arg_end->next;
	} else {
		this->first = current;
	}
	if(nullptr != arg_end->next) {
		arg_end->next->prev = arg_begin->prev;
	}
	node *tmp_current = arg_begin;
	while(tmp_current != arg_end->next) {
		arg_begin = tmp_current->next;
		delete tmp_current;
		tmp_current = arg_begin;
	}
}


#endif // __DEFINITIONS_CPP__
