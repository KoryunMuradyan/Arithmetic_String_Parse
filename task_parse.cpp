#include <iostream>
#include <string>
#include "definitions.hpp"
#include <cassert>

int main()
{
	std::string expression;
	std::cout << "input an arithmetic expression" << std::endl;
	//getline(std::cin, expression);
	//expression = "(1.1+(-7.5))-4*(-3)*(6-2)";
	//expression = "(1.1+(-7.5))*4*(-3)+(6-2)";
	//expression = "1.1+(7.5*4)+(6-2)";
	//expression = "1.1+7.5*4+6-2333";
	//expression = "1.1+7.5*4 - 7";
	//expression = "(1.1+2*(7.5*4 - 7) + 11.1) + 33";
	//expression = "(1.1+2*(7.5*4 - 7) + 11.1)";
	//expression = "1.1";
	//expression = "(4*2333)*sin(1)";
	//expression = "((1.1+2*(7.5*4 - 7) + 11.1)*sin(sin(cos(1))))";
	//expression = "sin(acos(1))";
	//expression = "cos(0)/2";
	//expression = "(5*2)/2";
	//expression = "(4*2333)*10";
	//expression = "3+(4*2333)";
	//expression = "(4+2333)/2";
	//expression = "pow(2, 10)*cos(0)";
	//expression = "acos(pow(2, 0.5)/2)";
	//expression = "(2333)+10*(-5.7)*log(2, 4*cos(-1*(-1)-1+log(2, 2)))*sin(7+11) + pow(2, 10)";
	//expression = "((2333)+10*(-5.7)*log(2, 4*cos(-1*(-1)-1+log(2, 2)))*sin(7+11) + pow(2, 10))/3";
	//expression = "(2333)+10*(-5.7)*sin(7+11)";
	//expression = "log(2, 1024*sin(1))";
	//expression = "((((((((2333)+10*(-5.7)*log(2, 4*cos(-1*(-1)-1+log(2, 2)))*sin(7+11) + pow(2, 10))/3))))))*pow(7, 2)";
	expression = "((2333)+10*(-5.7)*log(2, 4*cos(-1*(-1)-1+log(2, 2)))*sin(7+11) + pow(2, 10))/3*pow(7, 2)";
	//expression = "(((((((((((((((((((((2333)+10*(-5.7)*log(2, 4*cos(-1*(-1)-1+log(2, 2)))*sin(7+11) + pow(2, 10))/3*pow(7, 2))))))))))))))))))))";

	/*
	for(int i = 0; i < 20000; ++i) {
		arithmetic_expr my_expr(expression);
		my_expr.solve();
	}
	*/
	arithmetic_expr my_expr(expression);
	std::cout << expression << " = ";
	std::cout << my_expr.solve() << std::endl;
	std::cout << "everything ok"<<std::endl;
}
