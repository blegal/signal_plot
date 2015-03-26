TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS +=-m32 --stdlib=libc++ -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

QMAKE_CXXFLAGS +=--stdlib=libc++ -m32 -O2 -msse -msse2 -mtune=native -march=native -pipe -fomit-frame-pointer -fprefetch-loop-arrays -I/usr/local/include

SOURCES += \
    src/CTimer/CTimer.cpp \
    src/filters/band_pass/Filter_Fp_1500Hz_2500Hz.cpp \
    src/filters/band_stop/Filter_Fs_1500Hz_2500Hz.cpp \
    src/filters/channels/Mono2Stereo_fx1.cpp \
    src/filters/channels/Mono2Stereo_fx2.cpp \
    src/filters/channels/Stereo2Mono_fx1.cpp \
    src/filters/channels/Stereo2Mono_fx2.cpp \
    src/filters/Copy.cpp \
    src/filters/Filter_FIR.cpp \
    src/filters/Filter.cpp \
    src/filters/FilterLibrary.cpp \
    src/filters/high_pass/HighPass_2taps.cpp \
    src/filters/high_pass/HP_Filter_Fc_2kHz.cpp \
    src/filters/high_pass/HP_Filter_Fc_8kHz.cpp \
    src/filters/high_pass/HP_Filter_Fc_12kHz.cpp \
    src/filters/high_pass/HP_Filter_Fc_100Hz.cpp \
    src/filters/high_pass/HP_Filter_Fc_500Hz.cpp \
    src/filters/low_pass/Filter_Fc_2kHz.cpp \
    src/filters/low_pass/Filter_Fc_8kHz.cpp \
    src/filters/low_pass/Filter_Fc_10.cpp \
    src/filters/low_pass/Filter_Fc_12kHz.cpp \
    src/filters/low_pass/Filter_Fc_100Hz.cpp \
    src/filters/low_pass/Filter_Fc_500Hz.cpp \
    src/filters/low_pass/Filter_Fs_10.cpp \
    src/filters/low_pass/LowPass_2taps.cpp \
    src/filters/noise/Denoise_3taps.cpp \
    src/filters/noise/Denoise_Gaussian.cpp \
    src/filters/noise/NoiseAWNG.cpp \
    src/GL_Button.cpp \
    src/main.cpp \
    src/RawSound.cpp \
    src/SoundSystem.cpp \
    src/SoundView.cpp \
    src/filters/effects/BassBooster.cpp \
    src/filters/effects/Echo_500ms.cpp \
    src/filters/effects/Equalization.cpp \
    src/filters/effects/Modulation_1kHz_lut.cpp \
    src/filters/effects/Modulation_1kHz.cpp

HEADERS += \
    src/CTimer/CTimer.h \
    src/filters/band_pass/Filter_Fp_1500Hz_2500Hz.h \
    src/filters/band_stop/Filter_Fs_1500Hz_2500Hz.h \
    src/filters/channels/Mono2Stereo_fx1.h \
    src/filters/channels/Mono2Stereo_fx2.h \
    src/filters/channels/Stereo2Mono_fx1.h \
    src/filters/channels/Stereo2Mono_fx2.h \
    src/filters/Copy.h \
    src/filters/Filter_FIR.h \
    src/filters/Filter.h \
    src/filters/FilterLibrary.h \
    src/filters/high_pass/HighPass_2taps.h \
    src/filters/high_pass/HP_Filter_Fc_2kHz.h \
    src/filters/high_pass/HP_Filter_Fc_8kHz.h \
    src/filters/high_pass/HP_Filter_Fc_12kHz.h \
    src/filters/high_pass/HP_Filter_Fc_100Hz.h \
    src/filters/high_pass/HP_Filter_Fc_500Hz.h \
    src/filters/low_pass/Filter_Fc_2kHz.h \
    src/filters/low_pass/Filter_Fc_8kHz.h \
    src/filters/low_pass/Filter_Fc_10.h \
    src/filters/low_pass/Filter_Fc_12kHz.h \
    src/filters/low_pass/Filter_Fc_100Hz.h \
    src/filters/low_pass/Filter_Fc_500Hz.h \
    src/filters/low_pass/Filter_Fs_10.h \
    src/filters/low_pass/LowPass_2taps.h \
    src/filters/noise/Denoise_3taps.h \
    src/filters/noise/Denoise_Gaussian.h \
    src/filters/noise/NoiseAWNG.h \
    src/GL_Button.h \
    src/RawSound.h \
    src/SoundSystem.h \
    src/SoundView.h \
    src/filters/effects/BassBooster.h \
    src/filters/effects/Echo_500ms.h \
    src/filters/effects/Equalization.h \
    src/filters/effects/Modulation_1kHz_lut.h \
    src/filters/effects/Modulation_1kHz.h

