#ifndef LIFT
#define LIFT

#include<set>
#include<mutex>
#include<thread>
#include<chrono>
#include<vector>
#include<condition_variable>

class lift {
public:
	std::vector<std::mutex> lift_mutex{ 4 };
	std::vector<std::set<int>> lift_stoppages{ 4 };
	std::vector<std::condition_variable> lift_cv{ 4 };
	std::vector<std::thread> lifts;

	std::vector<int> lifts_current_floor{ 0, 0, 0, 0 };

	std::vector<bool> lift_up{true, true, true, true };  

	lift();
	
	void add_stopages(int floor, int i);

	~lift();

};

#endif // LIFT