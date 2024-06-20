// FIXME: your file license if you have one

#pragma once

#include <android/hardware/mgpio/1.0/IMgpio.h>
#include <android/hardware/mgpio/1.0/types.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

#define BUFFER_MAX 		(4)
#define DIRECTION_MAX 	(35)
#define VALUE_MAX 		(30)

namespace android::hardware::mgpio::V1_0::implementation {

using ::android::hardware::mgpio::V1_0::Status;
using ::android::hardware::mgpio::V1_0::Direction;
using ::android::hardware::mgpio::V1_0::Voltage;

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Mgpio : public IMgpio {
    // Methods from ::android::hardware::mgpio::V1_0::IMgpio follow.
    Return<Status> exportGpio(int32_t pin) override;
    Return<Status> unexportGpio(int32_t pin) override;
    Return<int32_t> readValue(int32_t pin) override;
    Return<Status> wirteValue(int32_t pin, int32_t value) override;
    Return<Status> setDirection(int32_t pin, int32_t dir) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
extern "C" IMgpio* HIDL_FETCH_IMgpio(const char* name);

}  // namespace android::hardware::mgpio:V1_0::implementation
