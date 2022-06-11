#include <string>
#include <iostream>
#include "arithmetic_expr.hpp"

int main()
{
	std::string expression;
	/*
	std::cout << "input an arithmetic expression" << std::endl;
	getline(std::cin, expression);
	*/

	//expression = "(1.1+(-7.5))-4*(-3)*(6-2)";
	//expression = "((1.1+(-7.5))*4*(-3)+(6-2))";
	expression = "(1.1+(+7.5))*4*(-3)+(6-2)";
	//expression = "1.1+(7.5*4)+(6-2)";
	//expression = "1.1+7.5*4+6-2333";
	
	
	// the below for loop is for testing the performance of the code
	/*
	for(int i = 0; i < 1000000; ++i) {
		arithmetic_expr my_expr(expression);
		my_expr.solve();
	}
	*/
	
	/*  
	   uncomment next commented code lines and see the 
	   result of the solution but comment the for loop above
	*/

	arithmetic_expr my_expr(expression); 
	std::cout << expression << " = ";
	std::cout << my_expr.solve() << std::endl;
	/*
	*/

	/* 
	   the method call below prints the expression in any parsed stage. 
	   It's possible manipulate with stages commenting or uncommenting the member function calls in class constructor 
	   not touching first two lines
	*/
	//std::cout << expression << std::endl;
	//my_expr.just_print(); 
	std::cout << "everything went ok" << std::endl;
}
