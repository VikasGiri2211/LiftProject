#ifndef USERINPUT
#define USERINPUT

class userInput {
public:
	int user_calling_floor;
	int user_target_floor;
	int distance;
	bool upwards;
	void setData(int ucf, int utf) {
		user_calling_floor = ucf;
		user_target_floor = utf;
		distance = utf - ucf;
		if (distance > 0) {
			upwards = true;
		}
		else {
			upwards = false;
		}
		std::cerr << "upwards set value: " << upwards << std::endl;
	}

};

#endif // USERINPUT