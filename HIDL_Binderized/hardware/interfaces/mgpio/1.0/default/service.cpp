#define LOG_TAG "android.hardware.mgpio@1.0-service"

#include <hidl/HidlSupport.h>
#include <hidl/HidlTransportSupport.h>
#include "Mgpio.h"

using android::hardware::mgpio::V1_0::IMgpio;
using android::hardware::mgpio::V1_0::implementation::Mgpio;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;
using ::android::OK;

int main(int /* argc */, char* /* argv */ []) {
    android::sp<IMgpio> mgpio = new Mgpio();
    configureRpcThreadpool(1, true /* will join */);

    ALOGI("Mgpio HIDL Binderized");

    if (mgpio->registerAsService() != OK) {
        ALOGE("Could not register mgpio 1.0 service.");
        return 1;
    }
    joinRpcThreadpool();

    ALOGE("Service exited!");
    return 0;
}