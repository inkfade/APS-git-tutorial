

#include <string>
#include <chrono>
#include <atomic>
#include <cmath>
#include <fstream>

#include <boost/iostreams/device/mapped_file.hpp> // for mmap
#include "tasker.h" //for my farmer worker thing
#include "md5hash.h" //for openssl md5 hash
#include "Messages.h"

/*
	md5crack ~ md5 password recovery tool 'built for educational purposes' and society demos ;)
	available at: github.com/AR-Calder/md5crack
    Writen By Andrew R. Calder 
*/

class passwords
{
public:
	// Run the application
	void crack();

	passwords(std::string & file_dictionary, std::string & password_hash, int threads);
	~passwords();	

private:
	// Get dictionary file
	void get_passwords(std::string);
	// Perform dictionary attack
	void compare_hash(std::vector<std::string> &, size_t, size_t, std::string &);
	// Subdivide dictionary task
	void split_dictionary(std::vector<std::string> & tasks, std::string & comparison);

	
	// Threads that will be used
	int global_threads = 1;
	// Required thread-safe items
	std::mutex mtx;
	std::atomic<bool> task_complete;

	std::vector<std::string> password_vec;

	//basic requirments
	std::string filename;
	std::string hash;
	std::string password;

	//output
	Messages * msg;
};

