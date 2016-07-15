all: ios android

clean:
	-xcodebuild -workspace ios/ArgoLib.xcworkspace -scheme ArgoLib clean
	-cd android/app && ndk-build clean
	-rm -r **/generated/	
	-rm -r **/build/
	-rm -r build
	-rm -r obj
	-rm *.target.mk
	-rm GypAndroid.mk
	-rm compile_commands.json

ios/build/libArgo.xcodeproj: ./records/libArgo.djinni ./libArgo.gyp ./src/ common.gypi ./dependencies/json11.gyp
	./generate.sh
	PYTHONPATH=dependencies/gyp/pylib dependencies/gyp/gyp libArgo.gyp -DOS=ios --depth=. -f xcode --generator-output=./ios/build/ -Icommon.gypi

GypAndroid.mk: records/libArgo.djinni ./libArgo.gyp ./src/ ./dependencies/json11.gyp
	./generate.sh
	ANDROID_BUILD_TOP=$(shell which ndk-build) PYTHONPATH=dependencies/gyp/pylib dependencies/gyp/gyp --depth=. -f android -DOS=android -Icommon.gypi --root-target=libArgo_android_static libArgo.gyp 

ios: ios/build/libArgo.xcodeproj 

android: GypAndroid.mk

compile_commands.json: ios
	xctool build -dry-run -reporter json-compilation-database:compile_commands.json -workspace ./ios/ArgoLib.xcworkspace -scheme ArgoLib -sdk iphonesimulator -jobs 8

.PHONY: ios android clean all
