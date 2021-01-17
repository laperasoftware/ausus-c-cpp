#include <iostream>
#include <vector>

#include "peripherals/Aes.h"
#include "kernel/Processes.h"

#include "threads/SyncPoint.h"

void processes () {
    std::vector<float> values;
    values.reserve(4);

    //random values
    for (int i = 0; i < 4; ++i) {
        values.push_back(i*rand()%128-(i*5000-rand())%5);
    }

    int result = run();
    printf("\ncompleted: status=%d", result);
}

//-------------------- THREADS ----------------------//
void creator (SyncPoint<float>& points) {
    for (int i = 0; i<30; i++) {
        std::this_thread::sleep_for (std::chrono::milliseconds (rand()%128));
        points.addData((rand()/159.43)/2048);
    }
}

void reader (SyncPoint<float>& points) {
    for (int i = 0; i<10; i++) {
        std::this_thread::sleep_for (std::chrono::milliseconds (rand()%256));
        auto data = points.getData();
        data.clear();
    }
}
void threads() {

    SyncPoint<float> syncPointQueue;
    std::thread t1 (creator, std::ref(syncPointQueue));
    std::thread t2 (reader, std::ref(syncPointQueue));
    t1.join();
    t2.join();
}

//--------------------- MAIN -------------------------//
int main() {
    std::cout << "Hello, World!" << std::endl;

    int choice = -1;
    printf("Choose a software\n1. processes 2. threads\n");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            processes();
            break;
        case 2:
            std::cout << "threads!" <<std::endl;
            threads();
            break;
        default:
            break;
    }

    return 0;
}
