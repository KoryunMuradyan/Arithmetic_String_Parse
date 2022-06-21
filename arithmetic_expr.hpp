#ifndef __ARITHMETIC_EXPR_CPP__
#define __ARITHMETIC_EXPR_CPP__

#include <math.h>
#include <cassert>

void check_chars(const char ch)
{
	assert(ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == ',' ||
			ch == '(' || ch == ')' || ch == ' ' || ch == '.' ||
			((int(ch) >= int('0'))&&(int(ch) <= int(9))));
}

float divide(const float& a, const float& b)
{
	assert(b != 0);
	return a/b;
}


float solve_log(const float& argbase, const float& arg)
{
	return std::move(log(arg)/log(argbase));
}


struct node
{
	float val = 0;
	std::string op = "";
	std::string math_f_expr = "";
	node* next = nullptr;
	node* prev = nullptr;
};

class arithmetic_expr
{
	private:
		node *first = nullptr;
		node *last  = nullptr;
		node *current = nullptr;
	public:
		arithmetic_expr()
		{}

		arithmetic_expr(const std::string&);
		arithmetic_expr(const node*&, const node*&);
		arithmetic_expr(const node*&&, const node*&&);

		~arithmetic_expr()
		{
			node *tmp_node = first;
			while(first){
				tmp_node = first->next;
				delete first;
				//first = nullptr;
				first = tmp_node;
			}
		}
		float solve();
		void just_print();
	private:
		void resolve_str(const std::string&);
		void bind_node(node*&);
		void insert_num(std::string&);
		void insert_symbol(const std::string&);
		void insert_math_f_expr(const std::string&);
		void insert_math_f_expr(std::string&);
		void cut_dummy_range(node*, node*);
		node* find_pow_log_comma(node*&);
		std::pair<float, float> resolve_log_pow_brace(node*&);
		float solve_math_f_expr(node*&);
		node* find_cobrace(node*);
		float resolve_brace(node*&);
		void resolve_and_swap_the_math_f_expr(node*&);
		void resolve_and_swap_the_braced_expr(node*&);
		void solve_operator(node*&);

		void solve_plus(node*&);
		void solve_minus(node*&);
		void solve_mult(node*&);
		void solve_div(node*&);
		float solve_sin(node*&);
		float solve_cos(node*&);
		float solve_tan(node*&);
		float solve_asin(node*&);
		float solve_acos(node*&);
		float solve_atan(node*&);
		float solve_cosh(node*&);
		float solve_tanh(node*&);
		float solve_log(node*&);
		float solve_power(node*&);

		bool is_sin(node*&);
		bool is_cos(node*&);
		bool is_tan(node*&);
		bool is_asin(node*&);
		bool is_acos(node*&);
		bool is_atan(node*&);
		bool is_tanh(node*&);
		bool is_cosh(node*&);
		bool is_log(node*&);
		bool is_power(node*&);
		bool is_minus(node*&);
		bool is_plus(node*&);
		bool is_mult(node*&);
		bool is_div(node*&);
		bool is_open_brace(node*&);
		bool is_close_brace(node*&);
		bool is_comma(node*&);
		bool is_number(node*&);
		bool is_math_f_expr(node*&);
		bool is_operator(node*&);
};

#endif // __ARITHMETIC_EXPR_CPP__
