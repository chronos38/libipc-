// ProcessTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <chrono>

int _tmain(int argc, _TCHAR* argv[])
{
    while (true) {
        for (int i = 0; i < argc; i++) {
            _tprintf_s(_T("%s\n"), argv[i]);
        }
        _tprintf_s(_T("\n"));
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

	return 0;
}

