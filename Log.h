#pragma once

#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>

using namespace std;

class Log {
    private:
        string area;
    public:
        Log() {

        }

        ~Log() {
            area = "";
        }

        Log(string area) {
            this->area = area;
        }

        void Status(const string log) {
            cout << area << " " << log << endl;
        }
};

#endif // _LOG_H_
