QT       += core gui multimedia multimediawidgets core-private gui-private multimedia-private concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += resources_big
DEFINES += QT_MESSAGELOGCONTEXT
msvc {
      QMAKE_CFLAGS += /utf-8
      QMAKE_CXXFLAGS += /utf-8
}
windows {
      RC_ICONS = player.ico
      RESOURCES += resource_common.qrc
}
linux {
RESOURCES += \
    resource_common.qrc
}
unix {
RESOURCES += \
    resource_common.qrc
}
android {
LIBS += -ljnigraphics
DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/src/com/MainActivity.java
}
CONFIG += c++17
SOURCES += \
    main.cpp \
    mediawidget.cpp \
    myfiledialog.cpp \
    playerwidget.cpp \
    settingwidget.cpp \
    widget.cpp
HEADERS += \
    api.h \
    mediawidget.h \
    myfiledialog.h \
    mytaskbarprogress.h \
    playerwidget.h \
    settingwidget.h \
    widget.h
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

DISTFILES += \
    android/res/xml/filepaths.xml
