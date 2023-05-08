#include<iostream>

#include"liftOperator.h"


int main() {

	std::cout << "Hey! I'm your lift. Enter floor (0 to 16) " << std::endl;

	int ucf, utf;
	liftOperator lop;
	while (true) {
		std::cerr << "Inside main while loop" << std::endl;
		std::cin >> ucf >> utf;
		lop.handleInput(ucf, utf);
	}

	return 0;
}