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

	lift(std::string str):lift_current_floor(0), lift_up(true), name(str) {

		lift_thread = std::thread([this] {
				while (true) {
                std::unique_lock<std::mutex> guard(m_set_lock);
                sivi.wait(guard, [&] { return !stoppages_set.empty(); });
				if (lift_up) {
                auto it = stoppages_set.begin();
                int target_floor = *it;
                while (lift_current_floor < target_floor) {
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    lift_current_floor++;
					if (lift_current_floor == target_floor) {
						std::cout << "Lift " << name << " has arrived at floor " << target_floor << std::endl;
					}
					else {
                    std::cerr << "Lift " <<name << " is at floor " << lift_current_floor << std::endl;
					}
				}
                stoppages_set.erase(it);
				}
				else if (!lift_up) {
					auto it = stoppages_set.rbegin();
					int target_floor = *it;
					while (lift_current_floor > target_floor) {
						std::this_thread::sleep_for(std::chrono::seconds(2));
						lift_current_floor--;
						if (lift_current_floor == target_floor) {
							std::cout << "Lift " << name << " has arrived at floor " << target_floor << std::endl;
						}
						else {
							std::cerr << "Lift " << name << " is at floor " << lift_current_floor << std::endl;
						}
					}
					stoppages_set.erase(it.base());
				}
  
            }});

	}
	
	void add_stopages(int floor) {
		std::unique_lock<std::mutex> guard(m_set_lock);
		stoppages_set.insert(floor);
		sivi.notify_all();
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