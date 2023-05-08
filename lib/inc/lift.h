<<<<<<< HEAD
#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<algorithm>

const int total_lifts = 4;
const int total_floors = 16;

std::vector<int> current_lift_floors(total_lifts, 0);
std::vector<bool> lift_Assigned(total_lifts, false);
std::mutex lift_mutex;
std::vector<int> dir{1,0,-1};


//void check_near(int current_lift_floors, int user_floor) {
//
//	int index1 = abs(current_lift_floor[0] - user_floor);
//	int index2 = abs(current_lift_floor[1] - user_floor);
//	int index3 = abs(current_lift_floor[2] - user_floor);
//	int index4 = abs(current_lift_floor[3] - user_floor);
//
//	return index1;
//	
//}


void assign_lift(int user_floor, int user_destination) {

	int assigned_lift = -1;
	int min_distance = floors;


	for (int i = 0; i < total_lifts; i++) {
        
		bool available = false;
		int direction = dir[1];

		if (!lift_Assigned[i]) {

			if (current_lift_floors[i] < user_floor && user_floor < user_destination) {
				int direction = 1;
				available = true;
			}
			if (current_lift_floors[i] > user_floor && user_floor > user_destination) {
				int direction = -1;
				available = true;
			}
			if (current_lift_floors[i] == user_floor) {
				int direction = 0;
				available = true;
			}

		}

		if (available) {
			int distance = abs(current_lift_floors[i]-user_floor)
				if (distance < min_distance) {
					assigned_lift = i;
					min_distance = distance;
			    }
			    
			    else if (distance == min_distance) {
					int lift_direction = current_lift_floors[j] < user_floor ? 1 : -1;
					if (direction == lift_direction) {
						assigned_lift = j;
					}
				}
		}
	}

	if (assigned_lift == -1) {
		std::cout << "wait" << std::endl;
	}

	else {
		// Assign the lift to the user and move it to the user's floor and then to the destination floor
		lift_mutex.lock();
		lift_assigned[assigned_lift] = true;
		lift_mutex.unlock();
		move_lift(assigned_lift, user_floor);
		move_lift(assigned_lift, user_destination);
		lift_mutex.lock();
		lift_assigned[assigned_lift] = false;
		lift_mutex.unlock();
	}
	 


}

=======
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
>>>>>>> 556a28aa28ba7601361f91a6807b0aad54df2c3f
