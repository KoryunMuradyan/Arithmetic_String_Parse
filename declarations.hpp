#ifndef __ARITHMETIC_EXPR_CPP__
#define __ARITHMETIC_EXPR_CPP__

#include <cassert>

int divide(const float& a, const float& b)
{
	assert(b != 0);
	return a/b;
}

struct node
{
	float val = 0;
	std::string op = "";
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

		~arithmetic_expr()
		{
			node *tmp_node = first;
			while(first){
				tmp_node = first->next;
				delete first;
				first = tmp_node;
			}
		}
		float solve();
		void just_print();
	private:
		void resolve_str(const std::string&);
		void bind_node(node*&);
		void mult_div_sum_sub();
		void cut_dummy_nodes();
		void insert_num(const std::string&);
		void insert_symbol(const std::string&);
		void mult_dive_resolve();
		void brace_resolve();
};

#endif // __ARITHMETIC_EXPR_CPP__
