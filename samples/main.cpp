#include<iostream> 
#include"liftOperator.h" 

int main() {

	std::cout << "Hey! I'm your lift." << std::endl;
	int ucf, utf;
	liftOperator lop;
	while (true) {
		try {
			std::cin >> ucf >> utf;
			bool floorsInRange = (ucf >= 0 && ucf <= 16) && (utf >= 0 && utf <= 16);
			if (!floorsInRange)
				throw - 1; 
			lop.handleInput(ucf, utf);
		}
		catch (int value) {
			std::cout << "Venus is a 16 floors building!!" << std::endl;
		}
	}
	return 0;
}