your-android-root-directory/
├── hardware/
│   └── libhardware/
│       └── modules/
│           └── mgpio/
│               ├── Android.mk
│               ├── mgpio.c
│               └── mgpio.h
└── vendor/
    └── your-vendor/
        └── hardware/
            ├── Android.bp
            └── mgpio.default.rc

hw_device_t: Cấu trúc đại diện cho một thiết bị phần cứng cụ thể, cung cấp phương thức để mở, đóng và tương tác với thiết bị (hw_module_t).
hw_module_t: Cấu trúc đại diện cho một module phần cứng, cung cấp thông tin và phương thức chung của module.

# Command

mkdir -p hardware/libhardware/modules/mgpio/
touch hardware/libhardware/modules/mgpio/mgpio.h
touch hardware/libhardware/modules/mgpio/mgpio.c


            
	           
