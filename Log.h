#pragma once

#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>

using namespace std;

class Log {
    private:
        string area;
    public:
        Log(string area) {
            this->area = area;
        }

        void Status(const char* log) {
            cout << area << " " << log << endl;
        }
};

#endif // _LOG_H_
