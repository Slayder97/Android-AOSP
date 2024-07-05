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
Location: your-android-root-directory/
    Add folder mgpio
        mkdir -p hardware/libhardware/modules/mgpio/

    Add new file mgpio.h
        touch hardware/libhardware/include/hardware/mgpio.h

    Add new file mgpio.cpp
        touch hardware/libhardware/modules/mgpio/mgpio.cpp

    Edit Android.mk in hardware/libhardware/module
        hardware_modules := \
                    camera \
                    gralloc \
                    sensors \
                    mgpio

Note: Defined module ID in header file should be same as the name of the file
Ex: file name: mgpio.c
Should be defined: #define MGPIO_HARDWARE_MODULE_ID "mgpio"

Build: mmm hardware/libhardware/modules/mgpio/
Obtain mgpio.default.so

## JNI
Location: frameworks/base/services/core/jni/
    Add new file com_android_server_mgpio_MgpioService.cpp
    Call the register function from frameworks/base/services/core/jni/onload.cpp
    Build new JNI wrapper frameworks/base/services/core/jni/Android.bp


    Declare API frameworks/base/api/current.txt
        ...
        package android.hardware.mgpio {
            public final class MgpioManager {
                method public void turnOnLED(int);
                method public void turnOffLED(int);
            }
        }
        ...

Build: mmm frameworks/base/services/core/jni/
Obtain: libservices.core.a

## Service and Manager
Location: frameworks/base/core/java/android/content/
    Define a name for new Service Context.java
        /** @hide */
        @StringDef(suffix = { "_SERVICE" }, value = {
            ...
            MGPIO_SERVICE,
        })
        ...
        public static final String MGPIO_SERVICE = "mgpio";

Location: frameworks/base/core/java/android/hardware/mgpio/
    Define the Service Interface IMgpioManager.aidl
        mkdir -p frameworks/base/core/java/android/hardware/mgpio/
        touch frameworks/base/core/java/android/hardware/mgpio/IMgpioManager.aidl
            package android.hardware.mgpio;

            /**
            * Mgpio Manager interface
            *
            * {@hide}
            */
            interface IMgpioManager {
                void turnOnLED(int32_t pin);
                void turnOffLED(int32_t pin);
            }

Location: frameworks/base
    Build AIDL Android.bp
        ...
        java_defaults {
            name: "framework-defaults",
            installable: true,

            srcs: [
                "core/java/android/hardware/invcase/IInvcaseManager.aidl",
            ],

            ...
        }
        ...



            
	           
