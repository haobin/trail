APP_NAME = trail

CONFIG += qt warn_on cascades10

LIBS += -lQtLocationSubset
LIBS += -lbbcascadesmaps 
LIBS += -lGLESv1_CM
LIBS += -lbbsystem

include(config.pri)
