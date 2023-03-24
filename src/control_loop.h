#include <iostream>
#include "boost/thread.hpp"
#include <random>
#include <thread>
#include <chrono>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <mutex>
#include <condition_variable>


using namespace std;

class CONTROLLER {
    public:
    
    CONTROLLER(double kp, double ki, double kd, double ts)
      : kp_(kp), ki_(ki), kd_(kd), ts_(ts), prev_error_(0), error_integral_(0), error_derivative_(), output_(0){}

    double loop(double state);                //Main loop function        
    double getoutputcontroll();
    void setsetpoint(double setpoint);
    void setstatus(double status);

    private:
  // PID guadagni
    double kp_; //proportional constant
    double ki_; //integral constant
    double kd_; // derivative constant
    double ts_; // Sample Timeb // a better way is to get the time with getclock (real time system)
    double output_;// action control
    double prev_error_;
    double error_integral_;
    double error_derivative_;
    double setpoint_;
};

int rand_status();

void mainloop(CONTROLLER &controllo, double &state, double &input, double time_constant, double sampling_time, std::chrono::milliseconds timespan);

void detect_keyboard_input(CONTROLLER &controllo);

int rand_status();