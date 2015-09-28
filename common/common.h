/*
solution:	glib
project:	common
file:		common.h
author:		cj
*/

#pragma once

#include <fstream>

#define COM_assert(expr) \
	if(!(expr)) { \
		COM::log << "assertion failed: " << #expr << " in " \
				 << __FILE__ << ", " << __LINE__ << std::endl; \
		throw COM::AssertionException(); \
	}

#define MAX_TOKEN 512

typedef struct ctoken_s {
	struct ctoken_s* next;
	char string[MAX_TOKEN];
	float f;
	int i;
} ctoken_t;

int COM_Tokenize(ctoken_t** tokens, const char* string);
void COM_FreeTokens(ctoken_t* tokens);

#define MAX_HASH 1024

static int COM_Hash(const char* str) {
	int len = strlen(str);
	int hash = 0;
	int i;

	for(i = 0; i < len; ++i) {
		hash = ((hash << 8) + str[i]) % MAX_HASH;
	}
	return hash;
}

namespace COM {

	// exceptions
	struct FileNotFoundException : std::exception { };
	struct IOException : std::exception { };
	struct UnknownFormatException : std::exception { };
	struct InvalidFormatException : std::exception { };
	struct AssertionException : std::exception { };
	struct GLException : std::exception { };
 
	// types
	typedef unsigned char	uchar_t;
	typedef unsigned char	byte_t;
	typedef int				size_t;

	// logging
	struct LogStream : std::ofstream { 
		LogStream(void) {
			open("logfile.txt");
		}
	};

	extern LogStream log;

} // namespace COM