#include<iostream>
#include"liftOperator.h"
#include"lift.h"

void liftOperator::handleInput(int ucf, int utf) {
	std::unique_ptr<userInput> ui_ptr = std::make_unique <userInput>();
	ui_ptr->setData(ucf, utf);
	{
		std::unique_lock<std::mutex> guard(m_queue_lock);
		ui_queue.push(std::move(ui_ptr));
	}
	queue_cv.notify_one();
}

liftOperator::liftOperator() {
	liftOp_thread = std::thread([this] {
		std::unique_ptr<lift> lift_ptr(new lift());
		while (true) {
			std::unique_ptr<userInput> ui_ptr{ nullptr };
			{
				std::unique_lock<std::mutex> guard(m_queue_lock);
				queue_cv.wait(guard, [&]() {
					if ((!ui_queue.empty()) && (ui_queue.front()->upwards || (!ui_queue.front()->upwards))) {
						return true;
					}
					std::cout << "Waiting For Input" << std::endl;
					return false;
					});
				ui_ptr = std::move(ui_queue.front());
				ui_queue.pop();
			}
			if (!ui_ptr) {
				break;
			}
				bool one = false;
				bool two = false;
			for (int i = 0; i < 4; i++) {
				if (ui_ptr->upwards && lift_ptr->lift_up[i] && ui_ptr->user_calling_floor > lift_ptr->lifts_current_floor[i]) {
					std::cerr << "first condition: " << std::endl;
					lift_ptr->add_stopages(ui_ptr->user_calling_floor, i);
					lift_ptr->add_stopages(ui_ptr->user_target_floor, i);
					one = true;
					std::cerr << "New stopages added to lift: " << i << std::endl;
					break;
				}
				else if (!ui_ptr->upwards && !lift_ptr->lift_up[i] && ui_ptr->user_calling_floor < lift_ptr->lifts_current_floor[i]) {
					std::cerr << "second condition: " << std::endl;
					lift_ptr->add_stopages(ui_ptr->user_calling_floor, i);
					lift_ptr->add_stopages(ui_ptr->user_target_floor, i);
					two = true;
					std::cerr << "New stopages added to lift: " << i << std::endl;
					break;
				}
			}
			if (!one && !two) {
			std::mutex lift_upMutex;
			int nearest_lift = -1;
			int min_distance = std::numeric_limits<int>::max();
			for (int i = 0; i < 4; i++) {
				if (std::abs(ui_ptr->user_calling_floor - lift_ptr->lifts_current_floor[i]) < min_distance) {
					nearest_lift = i;
					min_distance = std::abs(ui_ptr->user_calling_floor - lift_ptr->lifts_current_floor[i]);
				}
				}
			if (nearest_lift != -1) {
				std::cerr << "Lift" << nearest_lift << " allocated for the nearest movement." << std::endl;
				lift_upMutex.lock();
				if (lift_ptr->lifts_current_floor[nearest_lift] < ui_ptr->user_calling_floor) {
					lift_ptr->lift_up[nearest_lift] = true;
					std::cerr << " IN there: " << std::endl;

				}
				else if (lift_ptr->lifts_current_floor[nearest_lift] > ui_ptr->user_calling_floor) {
					lift_ptr->lift_up[nearest_lift] = false;
					std::cerr << " IN 1: " << std::endl;

				}
				lift_upMutex.unlock();
				lift_ptr->add_stopages(ui_ptr->user_calling_floor, nearest_lift);
				std::this_thread::sleep_for(std::chrono::seconds(3));

				lift_upMutex.lock();
				if (lift_ptr->lifts_current_floor[nearest_lift] < ui_ptr->user_target_floor) {
					lift_ptr->lift_up[nearest_lift] = true;
					std::cerr << " IN 2: " << std::endl;

				}
				else if (lift_ptr->lifts_current_floor[nearest_lift] > ui_ptr->user_target_floor) {
					lift_ptr->lift_up[nearest_lift] = false;
					std::cerr << " IN here: " << std::endl;

				}
				lift_upMutex.unlock();
				lift_ptr->add_stopages(ui_ptr->user_target_floor, nearest_lift);
				std::cerr << "New stoppages added to Lift " << nearest_lift << std::endl;
			}
			}
		}
	});
}

liftOperator::~liftOperator() {
	{                                       // this is scope for unique_lock to unlock mutex at its end.
		std::unique_lock<std::mutex>(m_queue_lock);
	std::cerr << "liftOperator destroyed" << std::endl;
		ui_queue.push(std::unique_ptr<userInput>{nullptr});  // making all threads one by one point to nullptr so that they can exit the infinite loop in constructor.
	}
	liftOp_thread.join();
}