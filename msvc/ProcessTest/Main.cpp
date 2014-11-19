// ProcessTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <chrono>

int _tmain(int argc, _TCHAR* argv[])
{
    int exit = EXIT_SUCCESS;
    int seconds = 1;

    _tprintf_s(_T("ARGS: "));
    for (int i = 0; i < argc; i++) {
        _tprintf_s(_T("%s "), argv[i]);
    }
    _tprintf_s(_T("\n"));

    if (argc > 1) {
        if (_stscanf_s(argv[0], _T("%d"), &seconds) != 1) {
            _tprintf_s(_T("OMEGA-ERROR-HAPPENED\n"));
            seconds = 1;
        } else {
            _tprintf_s(_T("CONVERTED VALUE: %d"), seconds);
        }

        if (argc >= 2 && _stscanf_s(argv[1], _T("%d"), &exit) != 1) {
            exit = EXIT_SUCCESS;
        }
    }

    _tprintf_s(_T("\nWait for %d seconds ... \n"), seconds);
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
	return exit;
}

