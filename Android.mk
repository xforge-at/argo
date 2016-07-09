LOCAL_PATH := $(call my-dir)
HERE_DIR := $(LOCAL_PATH)

LOCAL_PATH := $(HERE_DIR)

include $(HERE_DIR)/dependencies/blocksruntime/Android.mk
include $(HERE_DIR)/dependencies/libdispatch/Android.mk
include $(HERE_DIR)/dependencies/libkqueue/Android.mk
include $(HERE_DIR)/dependencies/libpthread_workqueue/Android.mk


include $(HERE_DIR)/GypAndroid.mk

include $(CLEAR_VARS)

LOCAL_LDLIBS += -latomic
LOCAL_MODULE    := Argo_android
LOCAL_WHOLE_STATIC_LIBRARIES := blocksruntime \
			libpthread_workqueue \
			libkqueue \
			libdispatch \
			dependencies_djinni_support_lib_djinni_jni_gyp \
			libArgo_gyp \
			libArgo_android_static

include $(BUILD_SHARED_LIBRARY)
