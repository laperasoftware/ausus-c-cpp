#include <iostream>
#include <vector>

#include "peripherals/Aes.h"
#include "kernel/Processes.h"
int main() {
    std::cout << "Hello, World!" << std::endl;

    std::vector<float> values;
    values.reserve(4);

    //random values
    for (int i = 0; i < 4; ++i) {
        values.push_back(i*rand()%128-(i*5000-rand())%5);
    }

    int result = run();
    printf("\ncompleted: status=%d", result);
    return 0;
}
