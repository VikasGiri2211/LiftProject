
#include<iostream> 
#include"liftOperator.h" 

 

int main() {

	std::cout << "Hey! I'm your lift. Enter floor (0 to 16) " << std::endl;
	int ucf, utf;
	liftOperator lop;
	while (true) {
		std::cin >> ucf >> utf;
		std::cerr << "Inside main while loop" << std::endl;
		lop.handleInput(ucf, utf);
	}

	return 0;
}