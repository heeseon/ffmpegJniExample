LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

APP_UNIFIED_HEADERS := true

LOCAL_MODULE    := ffmpeg

LOCAL_SRC_FILES := ffmpeg.c ffmpeg_opt.c cmdutils.c ffmpeg_filter.c ffmpeg_hw.c

#LOCAL_EXPORT_C_INCLUDES :=/Users/kakao/Downloads/android-ndk-r14b/platforms/android-21/arch-arm/usr/include

LOCAL_LDLIBS := -llog

LOCAL_SHARED_LIBRARIES := libavformat libavcodec libswscale libavutil libswresample libavfilter

include $(BUILD_SHARED_LIBRARY)

$(call import-module, ffmpeg-3.4/android/arm)
