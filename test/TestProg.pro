QT		+= core
QT		+= gui

TARGET 	= TestProg
CONFIG	+= console
CONFIG	-= app_bundle

TEMPLATE	= app

SOURCES += \
	../UART/UART.cpp \
	../SPI/SensorsSPI.cpp \
	../Joystick/Joystick.cpp \
	../Protocol/Protocol.cpp \
	joysticktest.cpp

HEADERS += \
	../UART/UART.h \
	../Joystick/Joystick.h \
	../SPI/SensorsSPI.h \
	../Protocol/Protocol.h

LIBS += \
	-lwiringPi
