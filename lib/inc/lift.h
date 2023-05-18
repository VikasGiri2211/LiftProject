//#ifndef LIFT
//#define LIFT
//
////#include<set>
////#include<mutex>
////#include<thread>
////#include<chrono>
////#include<vector>
////#include <iostream>
////
////const int floors = 16;
////const int lifts = 4;
////
////std::vector<int> current_lift_floors (lifts,0);
////std::vector<bool> lift_assigned(lifts, false);
////
////std::mutex lift_mutex;
////
////
////    void move_lift(int lift, int destination) {
////        int lift_floor = current_lift_floors[lift];
////
////        if (lift_floor < destination) {
////            std::cout << "Lift " << lift + 1 << " is moving up from floor " << lift_floor << " to floor " << destination << "." << std::endl;
////            for (int floor = lift_floor + 1; floor <= destination; floor++) {
////                std::this_thread::sleep_for(std::chrono::seconds(1));
////                current_lift_floors[lift] = floor;
////            }
////        }
////        else if (lift_floor > destination) {
////            std::cout << "Lift " << lift + 1 << " is moving down from floor " << lift_floor << " to floor " << destination << "." << std::endl;
////            for (int floor = lift_floor - 1; floor >= destination; floor--) {
////                std::this_thread::sleep_for(std::chrono::seconds(1));
////                current_lift_floors[lift] = floor;
////            }
////        }
////
////        std::cout << "Lift " << lift + 1 << " has arrived at floor " << destination << "." << std::endl;
////    }
////
////    void assign_lift(int user_floor, int user_destination) {
////        // Find the available lift with the minimum distance and assign it to the user
////        int assigned_lift = -1;
////        int min_distance = floors;
////
////        for (int j = 0; j < lifts; j++) {
////            // Check if the lift is not assigned and is moving in the correct direction
////            bool available = false;
////            int direction = 0;
////            lift_mutex.lock();
////
////            if (!lift_assigned[j]) {
////                if (current_lift_floors[j] < user_floor && user_floor < user_destination) {
////                    available = true;
////                    direction = 1;
////                }
////                else if (current_lift_floors[j] > user_floor && user_floor > user_destination) {
////                    available = true;
////                    direction = -1;
////                }
////                else if (current_lift_floors[j] == user_floor) {
////                    available = true;
////                    direction = 0;
////                }
////            }
////            lift_mutex.unlock();
////
////            if (available) {
////                int distance = abs(user_floor - current_lift_floors[j]);
////                if (distance < min_distance) {
////                    assigned_lift = j;
////                    min_distance = distance;
////                }
////                else if (distance == min_distance) {
////                    // If the distances are the same, choose the lift that is moving in the correct direction
////                    int lift_direction = current_lift_floors[j] < user_floor ? 1 : -1;
////                    if (direction == lift_direction) {
////                        assigned_lift = j;
////                    }
////                }
////            }
////        }
////
////        if (assigned_lift == -1) {
////            std::cout << "No available lift to the user's destination." << std::endl;
////        }
////        else {
////            // Assign the lift to the user and move it to the user's floor and then to the destination floor
////            lift_mutex.lock();
////            lift_assigned[assigned_lift] = true;
////            lift_mutex.unlock();
////            move_lift(assigned_lift, user_floor);
////            move_lift(assigned_lift, user_destination);
////            lift_mutex.lock();
////            lift_assigned[assigned_lift] = false;
////            lift_mutex.unlock();
////        }
////    }
////
////
////
////
////
//
//
//
//#include<mutex>
//#include<thread>
//#include<chrono>
//#include<vector>
//#include <iostream>
//#include <set>
//#include <string>
//#include <condition_variable> 
//
//class lift {
//	std::mutex m_set_lock;
//	std::set<int> stoppages_set;
//	std::condition_variable sivi;
//	std::string name; 
//	std::thread lift_thread;
//
//public:
//	int lift_current_floor;
//	bool lift_up;
//
//	lift(std::string str);
//
//	void add_stopages(int floor);
//
//	~lift();
//
//
//};
//
//
//
//
//
//
//#endif // LIFT
