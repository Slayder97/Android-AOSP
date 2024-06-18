#include <hardware/hardware.h>
#include <hardware/gpio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

static int gpio_device_open(const struct hw_module_t *module, const char *name, struct hw_device_t **device);

static struct hw_module_methods_t gpio_module_methods = {
    .open = gpio_device_open,
};

struct gpio_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = 1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = GPIO_HARDWARE_MODULE_ID,
        .name = "GPIO HAL Module FOR RASPBERRY PI4",
        .author = "phonglt17",
        .methods = &gpio_module_methods,
    },
};

int gpio_export(int32_t pin)
{
    char buffer[BUFFER_MAX];
    ssize_t numb_written;
    int32_t fd;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open export for gpio\n");
        return FAILURE;
    }

    numb_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, numb_written);

    close(fd);
    return SUCCESS;
}

int gpio_unexport(int32_t pin)
{
    char buffer[BUFFER_MAX];
    ssize_t numb_written;
    int32_t fd;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open export for gpio\n");
        return FAILURE;
    }

    numb_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, numb_written);

    close(fd);
    return SUCCESS;
}

int gpio_direction(int32_t pin, int32_t dir)
{
    static const char s_directions_str[]  = "in\0out";
    char path[DIRECTION_MAX];
    int32_t fd;

    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open gpio direction for gpio\n");
        return FAILURE;
    }

    if (-1 == write(fd, &s_directions_str[IN == dir_ ? 0 : 3], IN == dir_ ? 2 : 3)) {
        fprintf(stderr, "Failed to set direction!\n");
        return FAILURE;
    }

    close(fd);
    return SUCCESS;
}

int gpio_read(int32_t pin)
{
    static char r_values;
    char path[VALUE_MAX];
    int32_t fd;

    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_RDONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open gpio value for gpio\n");
        return FAILURE;
    }

    if (1 != read(fd, &r_values, 1)) {
        fprintf(stderr, "Failed to read value!\n");
        return FAILURE;
    }

    close(fd);
    return (r_values - 48);
}

int gpio_write(int32_t pin)
{
    static const char s_values_str[] = "01";
    char path[VALUE_MAX];
    int32_t fd;

    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd) {
        fprintf(stderr, "Failed to open gpio value for gpio\n");
        return FAILURE;
    }

    if (1 != write(fd, &s_values_str[LOW == value_ ? 0 : 1], 1)) {
        fprintf(stderr, "Failed to write value!\n");
        return FAILURE;
    }

    close(fd);
    return SUCCESS;
}

static int device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device) 
{
	struct gpio_device_t* dev;

	dev = (struct gpio_device_t *)malloc(sizeof(struct gpio_device_t));
	if(dev == NULL) {
		ALOGE("Unable to reserve memory for rpi4 gpio hal: %s, ID: %s\n", strerror(errno), name);
		return -ENOMEM;
	}

    memset(dev, 0, sizeof(struct gpio_device_t));

	/* Initialize common fields */
	dev->common.tag = HARDWARE_DEVICE_TAG;
	dev->common.version = 1;
	dev->common.module = (struct hw_module_t *)module;
	dev->common.close = gpio_device_close;
    dev->gpio_export = gpio_export;
    dev->gpio_unexport = gpio_unexport;
    dev->gpio_direction = gpio_direction;
    dev->gpio_read = gpio_read;
    dev->gpio_write = gpio_write;

    *device = &dev->common;
	ALOGD("Gpio device initialize successfully\n");

	return 0;
}
