#define LOG_TAG "android.hardware.mgpio@1.0-service"

#include <android/hardware/mgpio/1.0/IMgpio.h>
#include <hidl/LegacySupport.h>

using android::hardware::mgpio::V1_0::IMgpio;
using android::hardware::defaultPassthroughServiceImplementation;

int main() {
    return defaultPassthroughServiceImplementation<IMgpio>();
}