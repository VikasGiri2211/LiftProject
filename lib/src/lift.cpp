#include"lift.h"
#include<iostream>

lift::lift() {
	for (auto i = 0; i < 4; i++) {
		lifts.emplace_back(std::thread([this, i] {
					std::cout << "lift created:" << i << std::endl;
			while (true) {
				std::unique_lock<std::mutex> guard(lift_mutex[i]);
				lift_cv[i].wait(guard, [this, i] {
					bool temp = !lift_stoppages.at(i).empty();        //using  at() instead of [] to access vector elements , to avoid out of bound error, if i is invalid.
					//return !lift_stoppages[i].empty(); 
					return temp;
					});
				if (lift_up[i]) {
					auto it = lift_stoppages.at(i).begin();
					int target_floor = *it;
					while (lifts_current_floor.at(i) < target_floor) {
						std::this_thread::sleep_for(std::chrono::seconds(1));
						lifts_current_floor.at(i)++;
						if (lifts_current_floor.at(i) == target_floor) {
							std::cout << "Lift " << i << " has arrived at floor " << target_floor << std::endl;
						}
						else {
							std::cerr << "Lift " << i << " is at floor " << lifts_current_floor.at(i) << std::endl;
						}
					}
					lift_stoppages.at(i).erase(it);
				}
				else if (!lift_up[i]) {

					auto it = std::prev(lift_stoppages.at(i).end());     // very important => to access last element of a set.
					int target_floor = *it;
					while (lifts_current_floor.at(i) > target_floor) {
						std::this_thread::sleep_for(std::chrono::seconds(1));
						lifts_current_floor.at(i)--;
						if (lifts_current_floor.at(i) == target_floor) {
							std::cout << "Lift " << i << " has arrived at floor " << target_floor << std::endl;
						}
						else {
							std::cerr << "Lift " << i << " is at floor " << lifts_current_floor.at(i) << std::endl;
						}
					}
					lift_stoppages.at(i).erase(it);
					std::cerr << "reached here too: " << std::endl;
				}
			}}));
	}
}

void lift::add_stopages(int floor , int i) {
	std::unique_lock<std::mutex> guard(lift_mutex[i]);
	lift_stoppages.at(i).insert(floor);
	lift_cv[i].notify_one();
};

lift::~lift() {
	for (auto& t : lifts) {
		t.join();
	}
    std::cerr << "lift destroyed" << std::endl;
}