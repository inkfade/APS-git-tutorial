
#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <atomic>
#include <queue>
#include <functional>
#include <condition_variable>

using std::vector;
using std::list;
using std::thread;
using std::unique_lock;
using std::mutex;
using std::bind;
using std::condition_variable;
using std::atomic_bool;

/*
	Tasker ~ std::functional based farmer worker
	available at: github.com/AR-Calder/CPPTasker
    Writen By Andrew R. Calder 
*/

class Tasker
{
public:
	typedef std::function<void()> task_;
	//Constructor
	Tasker(unsigned int);

	//Destructor
	~Tasker();

	//Add new tasks to task list
	void add_task(task_);

	//have calling thread wait until tasks are completed
	void wait();

private:
	//get task, run task, remove task from list
	void Run();

	std::vector<thread*> thread_vector;
	std::condition_variable run_cv;
	std::condition_variable end_cv;
	std::queue<task_> task_list;
	std::atomic_bool exit;
	std::atomic_bool end_condition;
	std::mutex mx;

};

