#!/bin/bash

case "$BUILD_TARGET" in 
   "ios")
      make ios
      ;;
   "android")
      make android
      ;;
   "cpp")
      make test/build/Makefile
      ;;
esac
