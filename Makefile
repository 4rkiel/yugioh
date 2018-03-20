#############################################################################
# Makefile for building: yugioh
# Generated by qmake (2.01a) (Qt 4.8.7) on: mar. mars 20 18:32:11 2018
# Project:  yugioh.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -o Makefile yugioh.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -std=c++0x -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Iobj
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = src/buildtab.cpp \
		src/choice.cpp \
		src/field.cpp \
		src/generique.cpp \
		src/genProgress.cpp \
		src/helptab.cpp \
		src/intro.cpp \
		src/main.cpp \
		src/optab.cpp \
		src/ruletab.cpp \
		src/shadowButt.cpp \
		src/shadowLab.cpp \
		src/duplica.cpp \
		src/slotCard.cpp \
		src/editeur_de_carte.cpp obj/moc_buildtab.cpp \
		obj/moc_choice.cpp \
		obj/moc_field.cpp \
		obj/moc_generique.cpp \
		obj/moc_genProgress.cpp \
		obj/moc_helptab.cpp \
		obj/moc_intro.cpp \
		obj/moc_main.cpp \
		obj/moc_optab.cpp \
		obj/moc_ruletab.cpp \
		obj/moc_shadowButt.cpp \
		obj/moc_shadowLab.cpp \
		obj/moc_duplica.cpp \
		obj/moc_slotCard.cpp \
		obj/moc_editeur_de_carte.cpp
OBJECTS       = obj/buildtab.o \
		obj/choice.o \
		obj/field.o \
		obj/generique.o \
		obj/genProgress.o \
		obj/helptab.o \
		obj/intro.o \
		obj/main.o \
		obj/optab.o \
		obj/ruletab.o \
		obj/shadowButt.o \
		obj/shadowLab.o \
		obj/duplica.o \
		obj/slotCard.o \
		obj/editeur_de_carte.o \
		obj/moc_buildtab.o \
		obj/moc_choice.o \
		obj/moc_field.o \
		obj/moc_generique.o \
		obj/moc_genProgress.o \
		obj/moc_helptab.o \
		obj/moc_intro.o \
		obj/moc_main.o \
		obj/moc_optab.o \
		obj/moc_ruletab.o \
		obj/moc_shadowButt.o \
		obj/moc_shadowLab.o \
		obj/moc_duplica.o \
		obj/moc_slotCard.o \
		obj/moc_editeur_de_carte.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		yugioh.pro
QMAKE_TARGET  = yugioh
DESTDIR       = 
TARGET        = yugioh

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: yugioh.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile yugioh.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile yugioh.pro

dist: 
	@$(CHK_DIR_EXISTS) obj/yugioh1.0.0 || $(MKDIR) obj/yugioh1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/yugioh1.0.0/ && $(COPY_FILE) --parents inc/buildtab.h inc/choice.h inc/field.h inc/generique.h inc/genProgress.h inc/helptab.h inc/intro.h inc/main.h inc/optab.h inc/ruletab.h inc/shadowButt.h inc/shadowLab.h inc/duplica.h inc/sleeper.h inc/slotCard.h inc/editeur_de_carte.h obj/yugioh1.0.0/ && $(COPY_FILE) --parents src/buildtab.cpp src/choice.cpp src/field.cpp src/generique.cpp src/genProgress.cpp src/helptab.cpp src/intro.cpp src/main.cpp src/optab.cpp src/ruletab.cpp src/shadowButt.cpp src/shadowLab.cpp src/duplica.cpp src/slotCard.cpp src/editeur_de_carte.cpp obj/yugioh1.0.0/ && (cd `dirname obj/yugioh1.0.0` && $(TAR) yugioh1.0.0.tar yugioh1.0.0 && $(COMPRESS) yugioh1.0.0.tar) && $(MOVE) `dirname obj/yugioh1.0.0`/yugioh1.0.0.tar.gz . && $(DEL_FILE) -r obj/yugioh1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: obj/moc_buildtab.cpp obj/moc_choice.cpp obj/moc_field.cpp obj/moc_generique.cpp obj/moc_genProgress.cpp obj/moc_helptab.cpp obj/moc_intro.cpp obj/moc_main.cpp obj/moc_optab.cpp obj/moc_ruletab.cpp obj/moc_shadowButt.cpp obj/moc_shadowLab.cpp obj/moc_duplica.cpp obj/moc_slotCard.cpp obj/moc_editeur_de_carte.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) obj/moc_buildtab.cpp obj/moc_choice.cpp obj/moc_field.cpp obj/moc_generique.cpp obj/moc_genProgress.cpp obj/moc_helptab.cpp obj/moc_intro.cpp obj/moc_main.cpp obj/moc_optab.cpp obj/moc_ruletab.cpp obj/moc_shadowButt.cpp obj/moc_shadowLab.cpp obj/moc_duplica.cpp obj/moc_slotCard.cpp obj/moc_editeur_de_carte.cpp
obj/moc_buildtab.cpp: inc/shadowButt.h \
		inc/sleeper.h \
		inc/buildtab.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/buildtab.h -o obj/moc_buildtab.cpp

obj/moc_choice.cpp: inc/shadowButt.h \
		inc/sleeper.h \
		inc/choice.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/choice.h -o obj/moc_choice.cpp

obj/moc_field.cpp: inc/shadowButt.h \
		inc/sleeper.h \
		inc/shadowLab.h \
		inc/slotCard.h \
		inc/duplica.h \
		inc/field.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/field.h -o obj/moc_field.cpp

obj/moc_generique.cpp: inc/genProgress.h \
		inc/sleeper.h \
		inc/generique.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/generique.h -o obj/moc_generique.cpp

obj/moc_genProgress.cpp: inc/sleeper.h \
		inc/genProgress.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/genProgress.h -o obj/moc_genProgress.cpp

obj/moc_helptab.cpp: inc/shadowButt.h \
		inc/sleeper.h \
		inc/helptab.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/helptab.h -o obj/moc_helptab.cpp

obj/moc_intro.cpp: inc/shadowButt.h \
		inc/sleeper.h \
		inc/intro.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/intro.h -o obj/moc_intro.cpp

obj/moc_main.cpp: inc/field.h \
		inc/shadowButt.h \
		inc/sleeper.h \
		inc/shadowLab.h \
		inc/slotCard.h \
		inc/duplica.h \
		inc/intro.h \
		inc/choice.h \
		inc/generique.h \
		inc/genProgress.h \
		inc/buildtab.h \
		inc/optab.h \
		inc/ruletab.h \
		inc/helptab.h \
		inc/main.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/main.h -o obj/moc_main.cpp

obj/moc_optab.cpp: inc/shadowButt.h \
		inc/sleeper.h \
		inc/optab.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/optab.h -o obj/moc_optab.cpp

obj/moc_ruletab.cpp: inc/shadowButt.h \
		inc/sleeper.h \
		inc/ruletab.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/ruletab.h -o obj/moc_ruletab.cpp

obj/moc_shadowButt.cpp: inc/sleeper.h \
		inc/shadowButt.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/shadowButt.h -o obj/moc_shadowButt.cpp

obj/moc_shadowLab.cpp: inc/shadowLab.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/shadowLab.h -o obj/moc_shadowLab.cpp

obj/moc_duplica.cpp: inc/duplica.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/duplica.h -o obj/moc_duplica.cpp

obj/moc_slotCard.cpp: inc/slotCard.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/slotCard.h -o obj/moc_slotCard.cpp

obj/moc_editeur_de_carte.cpp: inc/editeur_de_carte.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) inc/editeur_de_carte.h -o obj/moc_editeur_de_carte.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

obj/buildtab.o: src/buildtab.cpp inc/buildtab.h \
		inc/shadowButt.h \
		inc/sleeper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/buildtab.o src/buildtab.cpp

obj/choice.o: src/choice.cpp inc/choice.h \
		inc/shadowButt.h \
		inc/sleeper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/choice.o src/choice.cpp

obj/field.o: src/field.cpp inc/field.h \
		inc/shadowButt.h \
		inc/sleeper.h \
		inc/shadowLab.h \
		inc/slotCard.h \
		inc/duplica.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/field.o src/field.cpp

obj/generique.o: src/generique.cpp inc/generique.h \
		inc/genProgress.h \
		inc/sleeper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/generique.o src/generique.cpp

obj/genProgress.o: src/genProgress.cpp inc/genProgress.h \
		inc/sleeper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/genProgress.o src/genProgress.cpp

obj/helptab.o: src/helptab.cpp inc/helptab.h \
		inc/shadowButt.h \
		inc/sleeper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/helptab.o src/helptab.cpp

obj/intro.o: src/intro.cpp inc/intro.h \
		inc/shadowButt.h \
		inc/sleeper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/intro.o src/intro.cpp

obj/main.o: src/main.cpp inc/main.h \
		inc/field.h \
		inc/shadowButt.h \
		inc/sleeper.h \
		inc/shadowLab.h \
		inc/slotCard.h \
		inc/duplica.h \
		inc/intro.h \
		inc/choice.h \
		inc/generique.h \
		inc/genProgress.h \
		inc/buildtab.h \
		inc/optab.h \
		inc/ruletab.h \
		inc/helptab.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o src/main.cpp

obj/optab.o: src/optab.cpp inc/optab.h \
		inc/shadowButt.h \
		inc/sleeper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/optab.o src/optab.cpp

obj/ruletab.o: src/ruletab.cpp inc/ruletab.h \
		inc/shadowButt.h \
		inc/sleeper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/ruletab.o src/ruletab.cpp

obj/shadowButt.o: src/shadowButt.cpp inc/shadowButt.h \
		inc/sleeper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/shadowButt.o src/shadowButt.cpp

obj/shadowLab.o: src/shadowLab.cpp inc/shadowLab.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/shadowLab.o src/shadowLab.cpp

obj/duplica.o: src/duplica.cpp inc/duplica.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/duplica.o src/duplica.cpp

obj/slotCard.o: src/slotCard.cpp inc/slotCard.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/slotCard.o src/slotCard.cpp

obj/editeur_de_carte.o: src/editeur_de_carte.cpp inc/editeur_de_carte.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/editeur_de_carte.o src/editeur_de_carte.cpp

obj/moc_buildtab.o: obj/moc_buildtab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_buildtab.o obj/moc_buildtab.cpp

obj/moc_choice.o: obj/moc_choice.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_choice.o obj/moc_choice.cpp

obj/moc_field.o: obj/moc_field.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_field.o obj/moc_field.cpp

obj/moc_generique.o: obj/moc_generique.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_generique.o obj/moc_generique.cpp

obj/moc_genProgress.o: obj/moc_genProgress.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_genProgress.o obj/moc_genProgress.cpp

obj/moc_helptab.o: obj/moc_helptab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_helptab.o obj/moc_helptab.cpp

obj/moc_intro.o: obj/moc_intro.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_intro.o obj/moc_intro.cpp

obj/moc_main.o: obj/moc_main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_main.o obj/moc_main.cpp

obj/moc_optab.o: obj/moc_optab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_optab.o obj/moc_optab.cpp

obj/moc_ruletab.o: obj/moc_ruletab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_ruletab.o obj/moc_ruletab.cpp

obj/moc_shadowButt.o: obj/moc_shadowButt.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_shadowButt.o obj/moc_shadowButt.cpp

obj/moc_shadowLab.o: obj/moc_shadowLab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_shadowLab.o obj/moc_shadowLab.cpp

obj/moc_duplica.o: obj/moc_duplica.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_duplica.o obj/moc_duplica.cpp

obj/moc_slotCard.o: obj/moc_slotCard.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_slotCard.o obj/moc_slotCard.cpp

obj/moc_editeur_de_carte.o: obj/moc_editeur_de_carte.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_editeur_de_carte.o obj/moc_editeur_de_carte.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

