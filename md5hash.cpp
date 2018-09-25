#include "md5hash.h"

/*
	md5crack ~ md5 password recovery tool 'built for educational purposes' and society demos ;)
	available at: github.com/AR-Calder/md5crack
    Writen By Andrew R. Calder 
*/

std::string md5_hash::hash(std::string & password) {
//initialize
 MD5_Init(&context);
 //get c equiv string
 cstring = password.c_str();
 //get md5 of string
 MD5_Update(&context, cstring, strlen(cstring));
 MD5_Final(digest, &context);

 //format
 for (int i = 0; i < 16; i++)
	 sprintf(&md5String[i * 2], "%02x", static_cast<unsigned int>(digest[i]));
 //return hashed word
 return md5String;
}

//constructor
md5_hash::md5_hash(){}
//destuctor
md5_hash::~md5_hash(){}
