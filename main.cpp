#include "passwords.h"
#include <getopt.h>

/*
	md5crack ~ md5 password recovery tool 'built for educational purposes' and society demos ;)
	available at: github.com/AR-Calder/md5crack
    Writen By Andrew R. Calder 
*/

int print_usage(){
	// Usage statement
    const char * msg = "Usage: ./crackmd5 -d <file:dictionary> -p <string:md5 hash> -t <int:threads>\nRequired switches: -d, -p\nOptional switches: -t";
    std::cout << msg << std::endl;
    return 1;
}


int main(int argc, char *argv[])
{
	// Core values for dict attack
	std::string file_dictionary = "";
	std::string string_hash = "";
	unsigned int count_threads = 4;

	// CLI handling
    int opt = -1;
    static struct option long_options[] = {
		    {"dictionary", 		required_argument, 	NULL, 	'd'},
		    {"password-hash", 	required_argument, 	NULL, 	'p'},
		    {"threads", 		optional_argument, 	NULL, 	't'},
		    {NULL,0,NULL,0}
    };

    int option_index = 0;
    bool exit_condition = true;

    try { // This isn't a be-all end-all solution, in fact, it doesn't work all that well. 
        while ((opt = getopt_long(argc, argv, "d:p:t:", long_options, &option_index)) != -1){
            // if input is unexpected or doesn't meet requirements
            exit_condition = false;

            if (optarg == "?"){
                return print_usage();
            }

            // parse options
            switch(opt){
                case 'd':
                    file_dictionary = optarg;
					std::cout << "Dictionary File = " << file_dictionary << std::endl; 
                    break;
                case 'p':
                    string_hash = optarg;
					std::cout << "MD5 Hash = " << string_hash << std::endl; 
                    break;
                case 't':
                    count_threads = (optarg) ? atoi(optarg) : count_threads;
					std::cout << "thread count = " << count_threads << std::endl; 
                    break;
            }
        }
    } catch (std::exception Ex){
        std::cout << Ex.what() << std::endl;
        return print_usage();
    }
    if (exit_condition || argc < 3){
      return print_usage();
    }

	// The bit that actually matters...
	// create a dictionary cracker with <count_threads> crack workers ;)
	passwords dictionary(file_dictionary, string_hash, count_threads);
	dictionary.crack();

	return 0;
}