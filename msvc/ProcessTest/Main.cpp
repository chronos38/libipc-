// ProcessTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <chrono>

int _tmain(int argc, _TCHAR* argv[])
{
    int exit = EXIT_SUCCESS;
    int seconds = 1;

    if (argc > 1) {
        if (argc >= 2 && _stscanf_s(argv[1], _T("%d"), &seconds) != 1) {
            seconds = 1;
        }

        if (argc >= 3 && _stscanf_s(argv[2], _T("%d"), &exit) != 1) {
            exit = EXIT_SUCCESS;
        }
    }

    _tprintf_s(_T("\nWait for %d seconds ... "), seconds);
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
	return exit;
}

