#include "control_loop.h"


int main(int argc, char** argv) {

    double sampling_time = 0.1;
    double d_state;
    double state=rand_status();
    CONTROLLER controllo(5,0.5,0.1,sampling_time);
    cin>>d_state;// stato desiderato
    controllo.setsetpoint(d_state);
    double input;
    double time_constant = 1.0;

    std::chrono::milliseconds timespan(100);
    
    int numThreads = 4;
    std::vector<std::thread> threads(numThreads);
        threads[0] = std::thread(mainloop, std::ref(controllo), std::ref(state), std::ref(input), time_constant, sampling_time, timespan);
        threads[1] = std::thread(detect_keyboard_input,std::ref(controllo));
      for (int i = 0; i < 2; i++) {
        threads[i].join();
    }
    return 0;
}
