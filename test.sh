#!/bin/bash

case "$BUILD_TARGET" in 
   "ios")
      # scan --project ios/ArgoLib.xcodeproj/ --devices "iPhone 5" "iPhone 6" "iPhone 6+" --scheme "Argo"
      ;;
   "android")
      ;;
   "cpp")
      make test
      ;;
esac
