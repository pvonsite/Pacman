#pragma once

#ifndef _LOGSTATUS_H_
#define _LOGSTATUS_H_

#include <iostream>
#include <string>


class LogStatus {
    private:
        std::string area = "";
    public:
        LogStatus() {

        }

        LogStatus(std::string area) {
            this->area = area;
        }

        void Status(const std::string msg) {
            std::cout << area << ": " << msg << std::endl;
        }
};

#endif // _LOGSTATUS_H_
