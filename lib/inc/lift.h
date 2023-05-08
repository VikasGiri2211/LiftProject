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

	std::thread lift_thread;

public:
	int lift_current_floor;
	bool lift_up;

	lift():lift_current_floor(0), lift_up(true) {

		lift_thread = std::thread([this] {
			while (!stoppages_set.empty()) {
				auto it = stoppages_set.begin();
				int target_floor = *it;
				while (lift_current_floor < target_floor) {
					std::this_thread::sleep_for(std::chrono::seconds(1));
					lift_current_floor++;
					std::cout << "Lift is at floor " << lift_current_floor << std::endl;
				}
				std::unique_lock<std::mutex> guard(m_set_lock);
				stoppages_set.erase(it);
				std::cout << "Lift has arrived at floor " << target_floor << std::endl;
			}});

	}

	void add_stopages(int floor) {
		std::unique_lock<std::mutex> guard(m_set_lock);
		stoppages_set.insert(floor);
	};

	void move(int lift_target_floor) {
		for (int i = lift_current_floor; i <= lift_target_floor; i++) {
			std::cout << "Lift on floor : " << i << std::endl;
			lift_current_floor++;
		}
	}

	~lift() {
		if (lift_thread.joinable()) {
			lift_thread.join();
		}
		std::cerr << "lift destroyed" << std::endl;
	}

};

#endif // LIFT