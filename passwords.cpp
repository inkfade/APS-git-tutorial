#include "passwords.h"
/*
	md5crack ~ md5 password recovery tool 'built for educational purposes' and society demos ;)
	available at: github.com/AR-Calder/md5crack
    Writen By Andrew R. Calder 
*/

//get dictionary file
void passwords::get_passwords(std::string filename){
	//add extension
	filename += +".txt";
	std::ifstream input(filename);

	//password currently being read in
	std::string current_password = "";

	int current_line = 0;
	try {
		// loop until pattern count is reached or no more lines in file - whichever comes first
		for(;getline(input, current_password); current_line++){
			#ifdef DEBUGWORD
			std::cout << "Line " << current_line+1 << ": " << line << std::endl;
			#endif

			// Add password from each line to password vector
			password_vec.emplace_back(current_password);
		}
    	if (!current_line){
			// The file either didn't exist or was empty!
      		throw 1;
    	}
	}
	catch (int exc) {
		msg->add_task(new MessageTask("Unable to read file :S\n"));
		exit(1);
	}
	msg->add_task(new MessageTask("Successfully read dictionary!\n"));
}

//perform dictionary attack
void passwords::compare_hash(std::vector<std::string> & password, size_t next, size_t last, std::string & hash) {
	md5_hash md5h;
	// for given range of items in dictionary... && No other threads have already completed the task
	for (auto i = last; i < next && !task_complete; ++i) {		
		//if match found notify other threads then print out password that matches
		if (md5h.hash(password[i]) == hash) {
			msg->add_task(new MessageTask("\npassword: " + password[i] + "\n\npassword hash: \n" + md5h.hash(password[i]) + "\n\nMatches entered hash: \n" + hash + "\n\n"));
			task_complete = true;
			return;
		}
	}
}

//subdivide dictionary task
void passwords::split_dictionary(std::vector<std::string> & tasks, std::string & hash) {
	int threads = global_threads;
	//if we only have few passwords to test no point in making loads of threads
	threads = (tasks.size() < threads) ? tasks.size() : threads;

	//wee bit of math to help evenly split tasks
	const int base = floor(tasks.size() / float(threads));
	float offset_counter = static_cast<int>(tasks.size()) % threads;
	const float c_offset = ceil(offset_counter / threads);

	//keep track of tasks
	int offset = 0,
		last_task = 0,
		next_task = 0;

	//create workers
	Tasker dict_farm(threads);

	//subdivide tasks
	for (auto i = 0; i < threads; ++i) {
		//ensure threads get an ~even load
		offset = 0;
		if (offset_counter) {
			--offset_counter;
			offset = c_offset;
		}

		//update last task
		last_task = (((i)*base) + (i)*offset);
		//update next task
		next_task = ((i + 1)*base) + (i + 1)*offset;

		dict_farm.add_task([this, &tasks, next_task, last_task, &hash]() {compare_hash(tasks, next_task, last_task, hash); });
	}
	dict_farm.wait();
}
void passwords::crack() {
	auto start = std::chrono::high_resolution_clock::now();

	split_dictionary(password_vec, hash);

	auto finish = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << "ms\n";
}

//constructor
passwords::passwords(std::string & file_dictionary, std::string & password_hash, int threads)
{	
	task_complete = false;

	//initialize msg
	msg = new Messages;
	msg->run();

	filename = file_dictionary;
	hash = password_hash;
	global_threads = threads;

	//get dictionary file
	get_passwords(filename);
}

//destructor
passwords::~passwords()
{
	msg->exit();
	delete msg;
}
