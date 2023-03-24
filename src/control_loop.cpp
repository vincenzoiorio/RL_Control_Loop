#include "control_loop.h"

//constructor is implemented inline!

std::mutex m;
std::condition_variable cv;
bool wait = false;

//Random initial value

double CONTROLLER::loop(double state) {
    double error = setpoint_ - state;
    error_integral_ += error * ts_;
    error_derivative_ = (error - prev_error_) / ts_;
    double output = kp_ * error + ki_ * error_integral_ + kd_ * error_derivative_;
    prev_error_ = error;
    return output;
      
}
double CONTROLLER::getoutputcontroll()
{
        return output_;
        cout<<output_<<"questo e il valore dell'output"<<endl;
}
void CONTROLLER::setsetpoint(double setpoint){
        setpoint_=setpoint;
}

void CONTROLLER::setstatus(double status){
        output_=status;
        cout<<"lo stato del sistema è "<<output_<<endl;
}


int rand_status(){
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(0, 99);
int rand_number = dis(gen);
cout << "Random status of plant:" << rand_number<<endl;
  return rand_number;
}
void mainloop(CONTROLLER &controllo, double &state, double &input, double time_constant, double sampling_time, std::chrono::milliseconds timespan) {

    ofstream myfile("output.txt");
    
   
    while (true) {
        // Wait for the mutex to become free
        {
            std::unique_lock<std::mutex> lock(m);
            cout << "Main loop waiting..." << endl; // Add this line for debugging
            cv.wait(lock, []{return !wait;});
        }
        
        cout << "Main loop running..." << endl; // Add this line for debugging

        // Update the state of the system
        state += (input - state) * sampling_time / time_constant;

        // Calculate the output of the PID controller
        input = controllo.loop(state);

        // Print the state and control input for debugging
        std::cout << "State: " << state << std::endl;
        std::cout << "Control input: " << input << std::endl;
        myfile<< state << "\t" << input << std::endl;
        
        // Wait for the sampling time
        std::this_thread::sleep_for(timespan);
    }
}

void detect_keyboard_input(CONTROLLER &controllo) {
    double d_state;
    
    while (true) {
        int key = getchar();
        std::cout << "Key pressed: " << key << endl; // Add this line for debugging
        if (key == ' ') {
            std::cout << "Inserire il nuovo riferimento: ";
            std::unique_lock<std::mutex> lock(m);
            cout << "Keyboard input waiting..." << endl; // Add this line for debugging
            std::cout << "Inserire il nuovo riferimento: ";
            cv.wait(lock, []{return !wait;});
            cout << "Keyboard input running..." << endl; // Add this line for debugging
            cout<<"il precedente riferimento e'"<<d_state<<endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.clear();
            cin >> d_state;
            cout<<"\n il nuovo riferimento e'"<<d_state<<endl;
            controllo.setsetpoint(d_state);
            wait = false;
            cv.notify_one();
        } 
    }
}
