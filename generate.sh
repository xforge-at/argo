#!/bin/bash

cd dependencies/djinni
make djinni
cd -

ANDROID_OUT=android/generated/java/djinni/
CPP_OUT=src/generated/
JNI_OUT=android/generated/jni/
OBJC_OUT=ios/generated/
YAML_OUT=.
YAML_FILE=Argo.yaml

# Run djinni
./dependencies/djinni/src/run-assume-built \
   --java-out $ANDROID_OUT \
   --java-package "djinni" \
   \
   --cpp-out $CPP_OUT \
   --cpp-namespace Argo \
   --cpp-optional-template "std::experimental::optional" \
   --cpp-optional-header "<experimental/optional>" \
   --cpp-nn-header '"util.hpp"' \
   --cpp-nn-type "nn_shared_ptr" \
   --cpp-nn-check-expression "make_not_null" \
   \
   --jni-out $JNI_OUT \
   --jni-include-cpp-prefix "generated/" \
   \
   --objc-out $OBJC_OUT \
   --objc-type-prefix "XF" \
   \
   --objcpp-out $OBJC_OUT \
   --objcpp-include-cpp-prefix "generated/" \
   \
   --yaml-out $YAML_OUT \
   --yaml-out-file $YAML_FILE \
   \
   --idl records/libArgo.djinni 

# Replace "header.hpp" with <argo/header.hpp>
sed -i '' 's/\"\(.*\.hpp\)\"/<argo\/\1>/g' $YAML_OUT/$YAML_FILE
