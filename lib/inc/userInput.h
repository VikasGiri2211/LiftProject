#ifndef USERINPUT
#define USERINPUT

class userInput {
	int user_calling_floor;
	int user_target_floor;
	bool distance_up;
public:
	void setData(int ucf, int utf) {
		user_calling_floor = ucf;
		user_target_floor = utf;
		distance_up = utf - ucf;
	}

};

#endif // USERINPUT