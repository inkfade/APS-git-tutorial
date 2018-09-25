#include <openssl/md5.h>
#include <cstring>
#include <string>

/*
	md5crack ~ md5 password recovery tool 'built for educational purposes' and society demos ;)
	available at: github.com/AR-Calder/md5crack
    Writen By Andrew R. Calder 
*/

class md5_hash {
//Ignore warning that sprintf is outdated as no simple alternative
public:
	//get hash of password
	std::string hash(std::string & password);

	//construct md5 hasher
	md5_hash();

	//destroy md5 hasher
	~md5_hash();

private:
	unsigned char digest[16];
	const char * cstring;
	char md5String[33];
	MD5_CTX context;
};

