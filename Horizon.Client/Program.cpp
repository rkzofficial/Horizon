#define _NO_CRT_STDIO_INLINE
#include "Api/Api.h"
#include <cstdio>

using namespace Horizon::Client;

int main() {

	try {
		Api::LoadApis();
		Api::_MessageBoxW(nullptr, L"This is a Test Message", L"Title", 0);
	}
	catch (...) {
		printf("Exception Thrown");
	}
}