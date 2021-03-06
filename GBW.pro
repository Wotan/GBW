######################################################################
# Automatically generated by qmake (2.01a) lun. nov. 14 12:14:21 2011
######################################################################

CONFIG += debug
QT += opengl
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

LIBS += 
OBJECTS_DIR = ./obj
MOC_DIR = ./obj

# Input
HEADERS +=      include/MainWindow.hpp \
                include/App.hpp \
                include/Settings.hpp \
                include/graphics/GraphicsEngine.hpp \
                include/graphics/RenderOpenGL.hpp \
                include/emulator/Emulator.hpp \
                include/debugger/Debugger.hpp \
                include/debugger/MemWatcher.hpp \
                include/debugger/InfosWatcher.hpp \
                include/debugger/AsmWatcher.hpp \
                include/debugger/TileWatcher.hpp

SOURCES +=      src/main.cpp \
                src/MainWindow.cpp \
                src/App.cpp \
                src/Settings.cpp \
                src/graphics/GraphicsEngine.cpp \
                src/graphics/RenderOpenGL.cpp \
                src/emulator/Emulator.cpp \
                src/emulator/Init.cpp \
                src/emulator/Cpu.cpp \
                src/emulator/Graphics.cpp \
                src/emulator/State.cpp \
                src/debugger/Debugger.cpp \
                src/debugger/MemWatcher.cpp \
                src/debugger/InfosWatcher.cpp \
                src/debugger/Mnemonic.cpp \
                src/debugger/AsmWatcher.cpp \
                src/debugger/TileWatcher.cpp

