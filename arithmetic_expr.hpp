#ifndef __DEFINITIONS_CPP__
#define __DEFINITIONS_CPP__

#include "declarations.hpp"
#include <cassert>
#include <iostream>

// constructor getting an arithmetical string as an argument
arithmetic_expr::arithmetic_expr(const std::string& arg_str)
{
	resolve_str(arg_str);
	current = first;
	mult_dive_resolve();
	brace_resolve();
}

// purpose of the below function is technical it can be deleted
void arithmetic_expr::just_print()
{
	if(nullptr == current){
		current = first;
		return;
	}
	std::cout << current->val << "  " << current->op << std::endl;
	current = current->next;
	just_print();
}

void arithmetic_expr::mult_dive_resolve()
{
	node *tmp = current;
	current = first;
	while(current){
		if("*" == current->op || "/" == current->op){
			mult_div_sum_sub();
		}
		current = current->next;
	}
	current = tmp;
}

void arithmetic_expr::brace_resolve()
{
	if(nullptr == current){
		current = first;
		mult_dive_resolve();
		return;
	} else if(")" == current->op) {
		current = current->prev;
		if("(" == current->prev->op){
			cut_dummy_nodes();
			mult_dive_resolve();
			current->op = "";
			current = current->next;
			brace_resolve();
		} else {
			current = current->prev;
			mult_dive_resolve();
			mult_div_sum_sub();
			current->op = "";
			current = current->next;
			brace_resolve();
		}
	} else {
		current = current->next;
		brace_resolve();
	}
}

float arithmetic_expr::solve()
{
	std::string tmp = current->op;
	if(nullptr == current->next && nullptr == current->prev) {
		return current->val;
	} else if("-" == current->op || "+" == current->op) {
		mult_div_sum_sub();
		if(nullptr != current->next )
			current = current->next;
		return solve();
	} else if("" == current->op) {
		current = current->next;
		return solve();
	}
}

void arithmetic_expr::mult_div_sum_sub()
{
	if("" == current->prev->op && "" == current->next->op) {
		float operand1 = current->prev->val;
		float operand2 = current->next->val;
		switch(current->op[0])
		{
			case '/': current->val = divide(operand1, operand2);
				  break;
			case '*': current->val = operand1*operand2; break;
			case '+': current->val = operand1+operand2; break;
			case '-': current->val = operand1-operand2; break;
		}
		current->op = "";
		cut_dummy_nodes();
	}
}

// below are string parsing and supporting the parsing process functions
void arithmetic_expr::resolve_str(const std::string& arg_str)
{
	int counter = 0;
	std::string tmp_numer_str = "";
	std::string to_pass = "";
	for(auto i: arg_str) {
		++counter;
		//check_chars(i);
		if(i == ' ') {continue;}
		if((int(i) >= int('0') && int(i) <= int('9')) || i == '.') {
			tmp_numer_str += i;
			if(counter == arg_str.size()) {
				insert_num(tmp_numer_str);
			}
			to_pass = i;
			continue;
		} else if(('-' == i || '+' == i) && "(" == to_pass) {
			to_pass = "";
			tmp_numer_str += i;
			continue;
		}
		if(tmp_numer_str.size() > 0) {
			insert_num(tmp_numer_str);
			tmp_numer_str = "";
		}
		to_pass = "";
		to_pass+=i;
		insert_symbol(to_pass);
	}
}

void arithmetic_expr::insert_symbol(const std::string& arg_symbol)
{
	node *new_node = new node;
	new_node->op = arg_symbol;
	bind_node(new_node);
}

void arithmetic_expr::insert_num(const std::string& arg_numer_str)
{
	node *new_node = new node;
	new_node->val = std::stof(arg_numer_str);
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

void arithmetic_expr::cut_dummy_nodes()
{
	if(nullptr != current->prev->prev) {
		current->prev->prev->next = current;
	}
	if(nullptr != current->next->next) {
		current->next->next->prev = current;
	}
	node *tmp_prev = current->prev->prev;
	node *tmp_next = current->next->next;
	delete current->prev;
	delete current->next;
	current->prev = tmp_prev;
	if(nullptr == tmp_prev) {
		first = current;
	}
	current->next = tmp_next;
}

void check_chars(const char ch)
{
	assert(ch == '+' || ch == '-' || ch == '/' || ch == '*' ||
			ch == '(' || ch == ')' || ch == ' ' || ch == '.' ||
			((int(ch) >= int('0'))&&(int(ch) <= int(9))));
}

#endif // __DEFINITIONS_CPP__
