// FIXME: your file license if you have one
# define LOG_TAG "rpi4_gpio"

#include <stdio.h>
#include <log/log.h>
#include "Mgpio.h"

namespace android::hardware::mgpio::V1_0::implementation {

// Methods from ::android::hardware::mgpio::V1_0::IMgpio follow.
Return<Status> Mgpio::exportGpio(int32_t pin) {
    ALOGD("PHONGLT exportGpio\n");
    char buffer[BUFFER_MAX];
    ssize_t numb_written;
    int32_t fd;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open export for gpio\n");
        return Status::FAILURE;
    }

    numb_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, numb_written);

    close(fd);
    return Status::SUCCESS;
}

Return<Status> Mgpio::unexportGpio(int32_t pin) {
    ALOGD("PHONGLT unexportGpio\n");
    char buffer[BUFFER_MAX];
    ssize_t numb_written;
    int32_t fd;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open export for gpio\n");
        return Status::FAILURE;
    }

    numb_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, numb_written);

    close(fd);
    return Status::SUCCESS;
}

Return<int32_t> Mgpio::readValue(int32_t pin) {
    ALOGD("PHONGLT readValue\n");
    static char r_values;
    char path[VALUE_MAX];
    int32_t fd;

    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_RDONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open gpio value for gpio\n");
        return static_cast<int32_t>(Status::FAILURE);
    }

    if (1 != read(fd, &r_values, 1)) {
        fprintf(stderr, "Failed to read value!\n");
        return static_cast<int32_t>(Status::FAILURE);
    }

    close(fd);
    return (r_values - 48);
}

Return<Status> Mgpio::wirteValue(int32_t pin, int32_t value) {
    ALOGD("PHONGLT wirteValue\n");
    static const char s_values_str[] = "01";
    char path[VALUE_MAX];
    int32_t fd;

    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open gpio value for gpio\n");
        return Status::FAILURE;
    }

    if (1 != write(fd, &s_values_str[static_cast<int>(Voltage::LOW_VOLTAGE) == value ? 0 : 1], 1)) {
        fprintf(stderr, "Failed to write value!\n");
        return Status::FAILURE;
    }

    close(fd);
    return Status::SUCCESS;
}

Return<Status> Mgpio::setDirection(int32_t pin, int32_t dir) {
    static const char s_directions_str[]  = "in\0out";
    char path[DIRECTION_MAX];
    int32_t fd;

    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open gpio direction for gpio\n");
        return Status::FAILURE;
    }

    if (-1 == write(fd, &s_directions_str[static_cast<int>(Direction::INPUT) == dir ? 0 : 3], 
                    static_cast<int>(Direction::INPUT) == dir ? 2 : 3)) {
        fprintf(stderr, "Failed to set direction!\n");
        return Status::FAILURE;
    }

    close(fd);
    return Status::SUCCESS;
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

// V1_0::IMgpio* HIDL_FETCH_IMgpio(const char* /* name */) {
//     return new Mgpio();
// }
}  // namespace android::hardware::mgpio::implementation
