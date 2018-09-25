#include "Messages.h"

/*
	Messages ~ threaded cerr output for time-critical testing
    Writen By Andrew R. Calder  - Based on work by Dr Adam Sampson
*/


Messages::Messages() {
	// Intentionally blank
}

Messages::~Messages() {
	T->join();
	delete T;
}

void Messages::add_task(Task * task) {
	std::unique_lock<std::mutex> lock(message_mutex);
	tasks.push(task);
}

void Messages::run() {
	// Create our threads
	T = new std::thread(std::mem_fun(&Messages::worker), this);
}

void Messages::exit() {
	exit_messages = true;
	// Join our thread
}

void Messages::worker()
{
	//run until no tasks left
	while (!exit_messages)
	{
		if (!tasks.empty()) {
			Task * next;
			{
				std::unique_lock<std::mutex> lock(message_mutex);
				next = tasks.front();
				tasks.pop();
			}
			next->run();
		}
	}
}

