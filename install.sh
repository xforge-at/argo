#!/bin/bash

case "$BUILD_TARGET" in 
   "ios")
      bundle install
      make ios
      ;;
   "android")
      mkdir -p $ANDROID_NDK
      wget https://dl.google.com/android/repository/android-ndk-r12b-linux-x86_64.zip -O ndk.zip
      unzip ndk.zip -d $ANDROID_NDK
      make android
      ;;
   "cpp")
      make test/build/Makefile
      ;;
esac
