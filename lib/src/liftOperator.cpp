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
	cv.notify_all();
}

liftOperator::liftOperator() {
	std::string keys[] = { "A", "B", "C", "D" };
	for (auto i = 0; i < 4; i++) {

		lifts.emplace(keys[i], std::thread([this, keys, i] {
			std::unique_ptr<lift> lift_ptr(new lift(keys[i]));
			std::cout << "lift created:" << keys[i] << std::endl;
			while (true) {
				std::unique_ptr<userInput> ui_ptr{ nullptr };
				{
					std::unique_lock<std::mutex> guard(m_queue_lock);

					std::cout << "lift waiting here" << std::endl;

					cv.wait(guard, [&]() { 
						if (!ui_queue.empty()) {
							if (ui_queue.front()->upwards) {
								if (lift_ptr->lift_up && ui_queue.front()->user_calling_floor > lift_ptr->lift_current_floor) {
									return true;
								}
							}
							else if (!ui_queue.front()->upwards) {
								if (!lift_ptr->lift_up && ui_queue.front()->user_calling_floor < lift_ptr->lift_current_floor) {
									return true;
								}
							}
							else {
								std::this_thread::sleep_for(std::chrono::seconds(4));
								return true;
							}
						}
						return false;

						});
					ui_ptr = std::move(ui_queue.front());
					ui_queue.pop();
				}
				if (!ui_ptr) {
					break;
				}
				if (ui_ptr->upwards) {
					lift_ptr->lift_up = true;
					std::cerr << "ui_ptr->upwards: " << ui_ptr->upwards << std::endl;
				}
				else {
					lift_ptr->lift_up = false;
				}
				lift_ptr->add_stopages(ui_ptr->user_calling_floor);
				lift_ptr->add_stopages(ui_ptr->user_target_floor);
				std::cerr << "New stopages added to lift: " << keys[i] << std::endl;
			}

			}));
	}
}

liftOperator::~liftOperator() {
	{                                       // this is scope for unique_lock to unlock mutex at its end.
		std::unique_lock<std::mutex>(m_queue_lock);
		for (auto& t : lifts)
			ui_queue.push(std::unique_ptr<userInput>{nullptr});  // making all threads one by one point to nullptr so that they can exit the infinite loop in constructor.
	}
	for (auto& t : lifts)
		t.second.join();
}