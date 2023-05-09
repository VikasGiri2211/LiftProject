#include<iostream>
#include"liftOperator.h"
#include"lift.h"
#include<functional>


//void liftOperator::handleInput(int ucf, int utf) {
//	std::unique_ptr<userInput> ui_ptr = std::make_unique <userInput>();
//	ui_ptr->setData(ucf, utf);
//	{
//		std::unique_lock<std::mutex> guard(m_queue_lock);
//		ui_queue.push(std::move(ui_ptr));
//	}
//	cv.notify_all();
//}

void liftOperator::handleInput(std::function<void()> task) {

	{
		std::unique_lock
	}
}







liftOperator::liftOperator() {
	std::string keys[] = { "A", "B", "C", "D" };
	  
	for (auto i = 0; i < 4; i++) {     

		lifts.emplace(keys[i], std::thread([this] { 

			//std::unique_ptr<lift> lift_ptr(new lift());

			std::cout << "lift created:" << std::endl;

			while (true) {
				//std::unique_ptr<userInput> ui_ptr{ nullptr };
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> guard(m_queue_lock);

					std::cout << "lift waiting here" << std::endl;

					cv.wait(guard, [&]() {
						return !tasks.empty() || stop;});

						/*return ((!ui_queue.empty() && (ui_queue.front()->distance_up
							    && lift_ptr->lift_up && ui_queue.front()->user_calling_floor >= lift_ptr->lift_current_floor))
							|| (!ui_queue.empty() && (!ui_queue.front()->distance_up
								&& !lift_ptr->lift_up && ui_queue.front()->user_calling_floor <= lift_ptr->lift_current_floor)));
						});*/
					task = std::move(tasks.front());
					//ui_queue.pop();
					tasks.pop();
				}                                   
				/*lift_ptr->add_stopages(ui_ptr->user_calling_floor);
				lift_ptr->add_stopages(ui_ptr->user_target_floor);*/
				std::cerr << "New stopages added" << std::endl;
			}

			}));
	}
}

liftOperator::~liftOperator() {
	{                                       // this is scope for unique_lock to unlock mutex at its end.
		std::unique_lock<std::mutex>(m_queue_lock);
		for (auto& t : lifts)
			ui_queue.push(std::unique_ptr<userInput>{nullptr});  // making all threads one by one point to nullptr so that they can exit the infinite loop in constructor.
		stop = true;
	}
	for (auto& t : lifts)
		t.second.join();
}