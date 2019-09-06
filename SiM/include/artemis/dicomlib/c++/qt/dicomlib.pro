#-------------------------------------------------
#
# Project created by QtCreator 2014-01-03T11:35:48
#
#-------------------------------------------------

TARGET = dicomlib
TEMPLATE = lib

DEFINES += DICOMLIB_LIBRARY

INCLUDEPATH += ../../src/
INCLUDEPATH += ../../src/core/

#Includes for boost
INCLUDEPATH = ../../third-party/boost/
LIBS += "-LC:../../third-party/boost/stage/lib/"

SOURCES += ../../src/core/tokenize.cpp \
../../src/core/aaac.cpp \
../../src/core/File.cpp \
../../src/core/pdata.cpp \
../../src/core/ClientConnection.cpp \
../../src/core/ThreadSpecificServer.cpp \
../../src/core/ValueToStream.cpp \
../../src/core/aarj.cpp \
../../src/core/FileMetaInformation.cpp \
../../src/core/PresentationContexts.cpp \
../../src/core/CommandSets.cpp \
../../src/core/TransferSyntax.cpp \
../../src/core/Version.cpp \
../../src/core/aarq.cpp \
../../src/core/QueryRetrieve.cpp \
../../src/core/GroupLength.cpp \
../../src/core/ViewCodeSequence.cpp \
../../src/core/AssociationRejection.cpp \
../../src/core/DDictionary.cpp \
../../src/core/Dumper.cpp \
../../src/core/UID.cpp \
../../src/core/Buffer.cpp \
../../src/core/Decoder.cpp \
../../src/core/Encoder.cpp \
../../src/core/Server.cpp \
../../src/core/UIDs.cpp \
../../src/core/Cdimse.cpp \
../../src/core/Exceptions.cpp \
../../src/core/Ndimse.cpp \
../../src/core/ServiceBase.cpp \
../../src/core/Utility.cpp

HEADERS += ../../src/core/Base.hpp \
           ../../src/core/EnablesWinSock.hpp \
           ../../src/core/Socket.hpp \
           ../../src/core/SwitchEndian.hpp \
           ../../src/core/SystemError.hpp \
           ../../src/core/AllowableLeastDepth.hpp  \
           ../../src/core/DecodingXMLfile.hpp  \
           ../../src/core/exception.hpp \
           ../../src/core/ODBC.hpp \
           ../../src/core/ProfilingStatistics.hpp \
           ../../src/core/Switchphotometric.hpp \
           ../../src/core/tokenize.h \
           ../../src/core/copy_if.hpp \
           ../../src/core/Enforce.hpp  \
           ../../src/core/HeaderReportDlg.h \
           ../../src/core/Profiling.hpp \
           ../../src/core/ProgressDlg.h \
           ../../src/core/Singleton.hpp \
../../src/core/Tag.hpp \
../../src/core/Value.hpp \
../../src/core/aaac.hpp \
../../src/core/File.hpp \
../../src/core/pdata.hpp \
../../src/core/ClientConnection.hpp \
../../src/core/dicomlib.hpp \
../../src/core/ThreadSpecificServer.hpp \
../../src/core/ValueToStream.hpp \
../../src/core/aarj.hpp \
../../src/core/FileMetaInformation.hpp \
../../src/core/PresentationContexts.hpp \
../../src/core/CommandSets.hpp \
../../src/core/TransferSyntax.hpp \
../../src/core/Version.hpp \
../../src/core/aarq.hpp \
../../src/core/DataSet.hpp \
../../src/core/QueryRetrieve.hpp \
../../src/core/Types.hpp \
../../src/core/GroupLength.hpp \
../../src/core/ViewCodeSequence.hpp \
../../src/core/AssociationRejection.hpp \
../../src/core/DDictionary.hpp \
../../src/core/Dumper.hpp \
../../src/core/ImplementationUID.hpp \
../../src/core/UID.hpp \
../../src/core/VR.hpp \
../../src/core/Buffer.hpp \
../../src/core/Decoder.hpp \
../../src/core/Encoder.hpp \
../../src/core/Server.hpp \
../../src/core/UIDs.hpp \
../../src/core/Cdimse.hpp \
../../src/core/Exceptions.hpp \
../../src/core/Ndimse.hpp \
../../src/core/ServiceBase.hpp \
../../src/core/Utility.hpp


symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEC1B0C71
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = hermes.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
