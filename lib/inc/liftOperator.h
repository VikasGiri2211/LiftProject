#ifndef LIFTOPERATOR
#define LIFTOPERATOR

#include<vector>
#include<queue>
#include"lift.h"
#include"userInput.h"
#include<mutex>
#include<condition_variable>
#include<thread>

class liftOperator {
	std::vector <lift> lifts;
	std::queue<userInput> ui_queue;
	std::mutex m_queue_lock;
	std::condition_variable cv;

public:
	liftOperator() {
		lifts.reserve(4);
		for (auto i = 0; i < 4; i++) {
			lifts.push_back(std::thread([this] {
				while (true) {
					std::unique_ptr<userInput> work{ nullptr };
				{
					std::unique_lock<std::mutex> guard(m_queue_lock);
					cv.wait(guard, [&]() {return !ui_queue.empty(); });
					work = std::move(ui_queue.front());
					ui_queue.pop();
				}
				if (!work) {
					break;
				}
				(*work)();

				}

				}));
		}
	}

	void handleInput(int ucf , int utf) {
		std::unique_ptr<userInput> work_item = std::make_unique <userInput>();
		{
			std::unique_lock<std::mutex> guard(m_queue_lock);
			ui_queue.push(*work_item);
		}
	}

};

#endif // LIFTOPERATOR