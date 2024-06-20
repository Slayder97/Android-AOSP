#define LOG_TAG "mgpio_test"

#include <iostream>
#include <android/hardware/mgpio/1.0/IMgpio.h>

using std::atoi;
using android::sp;
using android::hardware::mgpio::V1_0::IMgpio;


int main(int argc, char** argv)
{
    android::sp<IMgpio> service = IMgpio::getService();
    if (service == nullptr) {
        printf("[%s] Cannot get service\n", LOG_TAG);
        return -1;
    }

    service->exportGpio(std::atoi(argv[1]) - 48);
    return 0;
}