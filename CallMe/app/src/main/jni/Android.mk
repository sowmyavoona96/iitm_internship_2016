LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := DtwLibrary
LOCAL_SRC_FILES := dtw_native.cpp
LOCAL_LDLIBS := -llog -ldl -landroid
include $(BUILD_SHARED_LIBRARY)