#ifndef LIFT
#define LIFT

#include<set>
#include<mutex>
#include<thread>
#include<chrono>

class lift {
	std::mutex m_set_lock;
	std::set<int> stoppages_set;
	std::condition_variable sivi;
	std::string name;
	std::thread lift_thread;
	 
public:
	int lift_current_floor;
	bool lift_up;

	lift(std::string str);
	
	void add_stopages(int floor);

	~lift();

};

#endif // LIFT