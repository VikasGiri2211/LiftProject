#ifndef LIFTOPERATOR
#define LIFTOPERATOR

//#include<map>
#include<string>
#include<queue>
#include"userInput.h"
#include<mutex>
#include<condition_variable>
#include<thread>
#include<memory> // to be able to smart_pointers.
#include"lift.h"

class liftOperator {
	//std::map<std::string, std::thread> lifts;
	std::queue<std::unique_ptr<userInput>> ui_queue;
	std::mutex m_queue_lock;
	std::condition_variable queue_cv;
	std::thread liftOp_thread;
	//std::unique_ptr<lift> lift_ptr = std::make_unique<lift>(lift());


public:
	liftOperator();

	~liftOperator();

	void handleInput(int ucf, int utf);

	//bool assign_lift(std::unique_ptr<lift> lift_ptr, );

	// deleting the copy/move constructors and copy/move assignment operators because liftOperator object must be non copiable and non movable to avoid race condition or exceptional behaviour.
	liftOperator(const liftOperator&) = delete;
	liftOperator(liftOperator&&) = delete;
	liftOperator& operator = (const liftOperator&) = delete;
	liftOperator& operator = (liftOperator&&) = delete;

};

#endif // LIFTOPERATOR