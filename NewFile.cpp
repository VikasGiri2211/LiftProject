#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <map>


// forward declaration of lift class
class lift;

// user input class for requesting the lift
class userInput {
public:
    int user_calling_floor;
    int user_target_floor;
    bool upwards; // direction of travel, true for up, false for down

    userInput(int calling_floor, int target_floor, bool up) :
        user_calling_floor(calling_floor), user_target_floor(target_floor), upwards(up) {}
};

// lift operator class
class liftOperator {
public:
    liftOperator();

    // method to add user request to the queue
    void add_user_request(int calling_floor, int target_floor, bool upwards);

private:
    std::map<std::string, std::unique_ptr<lift>> lifts; // map of lift instances
    std::queue<std::unique_ptr<userInput>> ui_queue; // queue of user input requests
    std::mutex m_queue_lock; // mutex for ui_queue
    std::condition_variable cv; // condition variable for ui_queue
};

// lift class
class lift {
public:
    lift(std::string id) : lift_id(id), lift_current_floor(1), lift_up(true) {
        std::cout << "lift created: " << lift_id << std::endl;
    }

    // method to add stoppage to the lift
    void add_stopages(int floor) {
        std::unique_lock<std::mutex> guard(m_lift_lock);
        lift_stops.push(floor);
        cv.notify_all(); // notify the lift thread that a new stoppage has been added
    }

private:
    std::string lift_id; // lift identifier
    int lift_current_floor; // current floor of the lift
    bool lift_up; // direction of travel, true for up, false for down
    std::queue<int> lift_stops; // queue of floor stoppages for the lift
    std::mutex m_lift_lock; // mutex for lift_stops
    std::condition_variable cv; // condition variable for lift_stops

    // method to run the lift thread
    void run() {
        while (true) {
            std::unique_ptr<userInput> ui_ptr{ nullptr };
            {
                std::unique_lock<std::mutex> guard(m_lift_lock);

                cv.wait(guard, [&]() {
                    // check if there are any stoppages on the current floor
                    if (!lift_stops.empty() && lift_stops.front() == lift_current_floor) {
                        lift_stops.pop();
                        std::cerr << "lift stopped at floor " << lift_current_floor << " (" << lift_id << ")" << std::endl;
                        return true;
                    }

                    // check if there are any stoppages in the queue in the direction of travel
                    if (!lift_stops.empty()) {
                        if ((lift_up && lift_stops.front() > lift_current_floor) ||
                            (!lift_up && lift_stops.front() < lift_current_floor)) {
                            std::cerr << "lift moving to floor " << lift_stops.front() << " (" << lift_id << ")" << std::endl;
                            lift_current_floor += (lift_up ? 1 : -1);
                            return true;
                        }
                    }

                    return false;
                    });

                // check if the lift is idle and no user is waiting for it
                if (lift_stops.empty()) {
         std::cerr << "lift idle (" << lift_id << ")" <<


             //else {
             //	std::this_thread::sleep_for(std::chrono::seconds(5));
             //	std::cerr << "first else condition: " << std::endl;
             //	return true;
             //}

                    /*						else {
                                                std::this_thread::sleep_for(std::chrono::seconds(5));
                                                std::cerr << "second else condition: " << std::endl;
                                                return true;
                                            }*/

 //if (ui_ptr->upwards) {
 //	lift_ptr->lift_up = true;
 //	std::cerr << "ui_ptr->upwards: " << ui_ptr->upwards << std::endl;
 //}
 //else {
 //	lift_ptr->lift_up = false;
 //	std::cerr << "ui_ptr->upwards: " << ui_ptr->upwards << std::endl;
 //}
 //lift_ptr->add_stopages(ui_ptr->user_calling_floor, i);
 //lift_ptr->add_stopages(ui_ptr->user_target_floor, i);
 //std::cerr << "New stopages added to lift: " << i << std::endl;