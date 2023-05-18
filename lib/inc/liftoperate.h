#ifndef LIFTOPERATE 
#define LIFTOPERATE  
 
#include<map> 
#include<queue> 
#include"lift2.h" 
#include<string> 
#include<queue> 
#include"input.h" 
#include<mutex> 
#include<condition_variable> 
#include<thread> 
#include<memory> 
#include <liftOperator.h> 
#include <functional> 
 
//class liftOperator { 
//	 
//	std::map <std::string, std::thread> lifts; 
//	std::queue<std::unique_ptr<userInput>> ui_queue; 
//	std::mutex m_queue_lock; 
//	std::condition_variable cv;
//
//public: 
//	 
//	liftOperator(); 
//	 
//	~liftOperator(); 
//	 
//	void handleInput(int ucf, int utf);  
//	 
// 	// deleting the copy/move constructors and copy/move assignment operators because liftOperator object must be non copiable and non movable to avoid race condition or exceptional behaviour.
// 	liftOperator(const liftOperator&) = delete;
// 	liftOperator(liftOperator&&) = delete;
// 	liftOperator& operator = (const liftOperator&) = delete;
// 	liftOperator& operator = (liftOperator&&) = delete;
// 
//}; 
 
class liftOperator { 
private: 

	std::map<std::string, std::thread> lifts; 
	std::queue<std::unique_ptr<userInput>> ui_queue; 
	std::mutex m_queue_lock; 
	std::condition_variable cv;

public: 
  	 
	liftOperator();
	~liftOperator();
 
 	void handleInput(int ucf, int utf);

	liftOperator(const liftOperator&) = delete;
	liftOperator(liftOperator&&) = delete;
	liftOperator& operator = (const liftOperator&) = delete;
	liftOperator& operator = (liftOperator&&) = delete;

};

#endif // LIFTOPERATE 