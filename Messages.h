#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>

/*
	Messages ~ threaded cerr output for time-critical testing
    Writen By Andrew R. Calder  - Based on work by Dr Adam Sampson
*/

class Task {
public:
	virtual ~Task() {}
	virtual void run() = 0;
};

class MessageTask : public Task {
public:
	explicit MessageTask(const std::string& message)
		: message_(message) {}
	void run() override
	{
		std::cerr << message_.c_str();
	}
private:
	const std::string message_;
};

class Messages {
public:
	
	Messages();
	~Messages();

	void add_task(Task * task);
	void run();
	void exit();
	void worker();

private:
	std::thread * T;
	std::queue<Task *> tasks;
	bool exit_messages = false;
	std::mutex message_mutex;
	std::mutex task_mutex;

};