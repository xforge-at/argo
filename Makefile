SRC_FILES := $(shell python glob.py src "*.cpp" "*.hpp")
TEST_FILES := $(shell python glob.py test "*.cpp")
DJINNI_FILES := $(shell find records -name "*.djinni")
GYP_FILES := $(shell find . -name "*.gyp" -or -name "*.gypi" -maxdepth 2)

all: ios android test/build/Makefile

clean:
	-xcodebuild -project ios/ArgoLib.xcodeproj -scheme Argo clean
	-cd android/app && ndk-build clean
	-rm -r **/generated/	
	-rm -r **/build/
	-rm -r build
	-rm -r obj
	-rm *.target.mk
	-rm Argo.yaml
	-rm GypAndroid.mk
	-rm compile_commands.json

# This file changes whenever the djinni files change -> good target for the rest to depend on
Argo.yaml: $(DJINNI_FILES)
	./generate.sh

ios/build/libArgo.xcodeproj: Argo.yaml $(SRC_FILES) $(GYP_FILES)
	PYTHONPATH=dependencies/gyp/pylib dependencies/gyp/gyp libArgo.gyp -DOS=ios --depth=. -f xcode --generator-output=./ios/build/ --root-target=libArgo_objc -Icommon.gypi

GypAndroid.mk: Argo.yaml $(SRC_FILES) $(GYP_FILES)
	ANDROID_BUILD_TOP=$(ANDROID_NDK) PYTHONPATH=dependencies/gyp/pylib dependencies/gyp/gyp --depth=. -f android -DOS=android -Icommon.gypi --root-target=libArgo_android_static libArgo.gyp 

test/build/Makefile: Argo.yaml $(SRC_FILES) $(TEST_FILES)
	PYTHONPATH=dependencies/gyp/pylib dependencies/gyp/gyp libArgo.gyp -f make -D OS=mac --depth=. --generator-output=./test//build/ --root-target=test -Icommon.gypi &> /dev/null

ios: ios/build/libArgo.xcodeproj 

android: GypAndroid.mk

compile_commands.json: ios
	xctool build -dry-run -reporter json-compilation-database:compile_commands.json -project ./ios/ArgoLib.xcodeproj -scheme Argo -sdk iphonesimulator -jobs 8

./test/build/out/Debug/test: test/build/Makefile
	chmod +x ./test/build/gyp-mac-tool
	make -C ./test/build/ > /dev/null

build_tests: ./test/build/out/Debug/test

test: Argo.yaml ./test/build/out/Debug/test
	./test/build/out/Debug/test 

print_vars:
	@echo "src: " $(SRC_FILES)
	@echo "test: " $(TEST_FILES)
	@echo "gyp: " $(GYP_FILES)
	@echo "djinni: " $(DJINNI_FILES)

.PHONY: ios android clean all test build_tests print_vars 
