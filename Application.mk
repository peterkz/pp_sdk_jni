APP_OPTIM := release
APP_PLATFORM := android-15
APP_STL := stlport_static
APP_CPPFLAGS += -frtti 
APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS += -DANDROID
APP_ABI := armeabi armeabi-v7a
#APP_CXXFLAGS += -std=gnu++11