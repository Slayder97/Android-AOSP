#include <stdio.h>
#include <hardware/rpi4_gpio.h>

int main()
{
	int err;
	struct gpio_module_t *module;
	struct gpio_device_t *device = NULL;

	err =  hw_get_module(GPIO_HARDWARE_MODULE_ID, (struct hw_module_t const**)&module);
	if (err != 0) 
		printf("hw_get_module() failed (%s)\n", strerror(-err));
	else {
		if (module->common.methods->open((struct hw_module_t *)module, "", ((hw_device_t **)&device)) != 0) {
			printf("Failed : HAL open (%s)\n",strerror(-err));
			return 0;
		}
	}

	device->gpio_export(181);
	device->gpio_direction(181, 1);
	device->gpio_write(1);

	printf("PHONGLT turn led on\n");
	
	return 0;	
}