######################################################################
# Automatically generated by qmake (2.01a) lun. nov. 14 12:14:21 2011
######################################################################

TEMPLATE = app
TARGET = bin/GBW
DEPENDPATH +=   . \
                include \
                include/graphics \
                include/emulator \
                include/debugger \
                src \
                src/graphics \
                src/emulator \
                src/debugger \

INCLUDEPATH +=  . \
                include \
                include/graphics \
                include/emulator \
                include/debugger

LIBS += -lsfml-system -lsfml-graphics
OBJECTS_DIR = ./obj
MOC_DIR = ./obj

# Input
HEADERS +=      include/MainWindow.hpp \
                include/App.hpp \
                include/graphics/QSFMLCanvas.hpp \
                include/graphics/GraphicsEngine.hpp \
                include/emulator/Emulator.hpp \
                include/debugger/Debugger.hpp \
                include/debugger/MemWatcher.hpp \
                include/debugger/RegWatcher.hpp

SOURCES +=      src/main.cpp \
                src/MainWindow.cpp \
                src/App.cpp \
                src/graphics/QSFMLCanvas.cpp \
                src/graphics/GraphicsEngine.cpp \
                src/emulator/Emulator.cpp \
                src/emulator/Init.cpp \
                src/debugger/Debugger.cpp \
                src/debugger/MemWatcher.cpp \
                src/debugger/RegWatcher.cpp

