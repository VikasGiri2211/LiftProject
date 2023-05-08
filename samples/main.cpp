#include<iostream>

#include"liftOperator.h"


int main() {

	std::cout << "Hey! I'm your lift. Enter floor (0 to 16) " << std::endl;

<<<<<<< HEAD
 
=======
	int ucf, utf;
	liftOperator lop;
	while (true) {
		std::cerr << "Inside main while loop" << std::endl;
		std::cin >> ucf >> utf;
		lop.handleInput(ucf, utf);
	}

>>>>>>> 556a28aa28ba7601361f91a6807b0aad54df2c3f
	return 0;
}