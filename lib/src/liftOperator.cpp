#include<iostream>
#include"liftOperator.h"

void liftOperator::handleInput(int ucf, int utf) {
	std::unique_ptr<userInput> uiptr = std::make_unique <userInput>();
	uiptr->setData(ucf, utf);
	{
		std::unique_lock<std::mutex> guard(m_queue_lock);
		ui_queue.push(std::move(uiptr));
	}
	cv.notify_all();
}

liftOperator::liftOperator() {
	lifts.reserve(4);
	for (auto i = 0; i < 4; i++) {

		std::cout << "lift here:" << std::endl;

		lifts.push_back(std::thread([this] {
			while (true) {
				std::unique_ptr<userInput> uiptr{ nullptr };
				{
					std::unique_lock<std::mutex> guard(m_queue_lock);

					std::cout << "lift waiting here" << std::endl;

					cv.wait(guard, [&]() {return !ui_queue.empty(); });
					uiptr = std::move(ui_queue.front());
					ui_queue.pop();
				}
				if (!uiptr) {
					break;
				}
				//(*uiptr)();

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
		t.join();
}