#include<iostream>

#include"liftOperator.h"


int main() {

	std::cout << "Hey! I'm your lift." << std::endl;

	int ucf, utf;
	liftOperator lop;
	while (true) {
		std::cin >> ucf >> utf;
		lop.handleInput(ucf, utf);
	}

	return 0;
}