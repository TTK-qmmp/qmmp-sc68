HEADERS += decodersc68factory.h \
           decoder_sc68.h \
           sc68helper.h

SOURCES += decodersc68factory.cpp \
           decoder_sc68.cpp \
           sc68helper.cpp \
           libsc68/file68/src/gzip68.c \
           libsc68/file68/src/vfs68.c \
           libsc68/file68/src/ice68.c \
           libsc68/file68/src/vfs68_ao.c \
           libsc68/file68/src/vfs68_null.c \
           libsc68/file68/src/msg68.c \
           libsc68/file68/src/timedb68.c \
           libsc68/file68/src/init68.c \
           libsc68/file68/src/vfs68_z.c \
           libsc68/file68/src/replay68.c \
           libsc68/file68/src/registry68.c \
           libsc68/file68/src/uri68.c \
           libsc68/file68/src/rsc68.c \
           libsc68/file68/src/vfs68_fd.c \
           libsc68/file68/src/vfs68_file.c \
           libsc68/file68/src/vfs68_mem.c \
           libsc68/file68/src/file68.c \
           libsc68/file68/src/string68.c \
           libsc68/file68/src/endian68.c \
           libsc68/file68/src/vfs68_curl.c \
           libsc68/file68/src/option68.c \
           libsc68/file68/src/ferror68.c \
           libsc68/libsc68/dial68/dial68.c \
           libsc68/libsc68/dial68/dial_conf.c \
           libsc68/libsc68/dial68/dial_finf.c \
           libsc68/libsc68/dial68/dial_tsel.c \
           libsc68/unice68/unice68_unpack.c \
           libsc68/unice68/unice68_pack.c \
           libsc68/unice68/unice68_version.c \
           libsc68/libsc68/conf68.c \
           libsc68/libsc68/api68.c \
           libsc68/libsc68/mixer68.c \
           libsc68/libsc68/io68/paulaemul.c \
           libsc68/libsc68/io68/ym_envel.c \
           libsc68/libsc68/io68/ymemul.c \
           libsc68/libsc68/io68/shifter_io.c \
           libsc68/libsc68/io68/paula_io.c \
           libsc68/libsc68/io68/mw_io.c \
           libsc68/libsc68/io68/ym_dump.c \
           libsc68/libsc68/io68/mfp_io.c \
           libsc68/libsc68/io68/mwemul.c \
           libsc68/libsc68/io68/ym_io.c \
           libsc68/libsc68/io68/io68.c \
           libsc68/libsc68/io68/ym_blep.c \
           libsc68/libsc68/io68/mfpemul.c \
           libsc68/libsc68/io68/ym_puls.c \
           libsc68/libsc68/libsc68.c \
           libsc68/libsc68/emu68/lines68.c \
           libsc68/libsc68/emu68/ioplug68.c \
           libsc68/libsc68/emu68/mem68.c \
           libsc68/libsc68/emu68/getea68.c \
           libsc68/libsc68/emu68/inst68.c \
           libsc68/libsc68/emu68/emu68.c \
           libsc68/libsc68/emu68/error68.c \
           libsc68/desa68/desa68.c

INCLUDEPATH += $$PWD/libsc68 \
               $$PWD/libsc68/file68 \
               $$PWD/libsc68/file68/src \
               $$PWD/libsc68/file68/sc68 \
               $$PWD/libsc68/libsc68 \
               $$PWD/libsc68/libsc68/dial68 \
               $$PWD/libsc68/libsc68/emu68 \
               $$PWD/libsc68/libsc68/io68 \
               $$PWD/libsc68/libsc68/sc68 \
               $$PWD/libsc68/unice68 \
               $$PWD/libsc68/desa68

DEFINES += HAVE_STDLIB_H \
           HAVE_STDINT_H \
           HAVE_STRING_H \
           HAVE_LIMITS_H \
           HAVE_ASSERT_H \
           HAVE_BASENAME \
           EMU68_MONOLITIC \
           EMU68_EXPORT \
           USE_UNICE68

#CONFIG += BUILD_PLUGIN_INSIDE
contains(CONFIG, BUILD_PLUGIN_INSIDE){
    include($$PWD/../../plugins.pri)
    TARGET = $$PLUGINS_PREFIX/Input/sc68

    unix{
        target.path = $$PLUGIN_DIR/Input
        INSTALLS += target
    }
}else{
    QT += widgets
    CONFIG += warn_off plugin lib thread link_pkgconfig c++11
    TEMPLATE = lib

    unix{
        equals(QT_MAJOR_VERSION, 5){
            QMMP_PKG = qmmp-1
        }else:equals(QT_MAJOR_VERSION, 6){
            QMMP_PKG = qmmp
        }else{
            error("Unsupported Qt version: 5 or 6 is required")
        }
        
        PKGCONFIG += $${QMMP_PKG}

        PLUGIN_DIR = $$system(pkg-config $${QMMP_PKG} --variable=plugindir)/Input
        INCLUDEPATH += $$system(pkg-config $${QMMP_PKG} --variable=prefix)/include

        plugin.path = $${PLUGIN_DIR}
        plugin.files = lib$${TARGET}.so
        INSTALLS += plugin
    }
}
