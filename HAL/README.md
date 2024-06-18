your-android-root-directory/
├── hardware/
│   └── libhardware/
│       └── modules/
│           └── rpi4_gpio/
│               ├── Android.mk
│               ├── rpi4_gpio.c
│               └── rpi4_gpio.h
└── vendor/
    └── your-vendor/
        └── hardware/
            ├── Android.bp
            └── rpi4_gpio.default.rc

hw_device_t: Cấu trúc đại diện cho một thiết bị phần cứng cụ thể, cung cấp phương thức để mở, đóng và tương tác với thiết bị (hw_module_t).
hw_module_t: Cấu trúc đại diện cho một module phần cứng, cung cấp thông tin và phương thức chung của module.
            
            
	           
