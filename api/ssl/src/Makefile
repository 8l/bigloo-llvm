#*=====================================================================*/
#*    serrano/prgm/project/bigloo/api/ssl/src/Makefile                 */
#*    -------------------------------------------------------------    */
#*    Author      :  Manuel Serrano                                    */
#*    Creation    :  Wed Apr  1 18:45:46 1998                          */
#*    Last change :  Fri Aug  6 08:11:24 2010 (serrano)                */
#*    -------------------------------------------------------------    */
#*    The makefile to build the library.                               */
#*=====================================================================*/

#*---------------------------------------------------------------------*/
#*    Standard Ssl configuration                                       */
#*---------------------------------------------------------------------*/
include ../../../Makefile.config
include ../../../Makefile.misc

#*---------------------------------------------------------------------*/
#*    Compilers, Tools and Destinations                                */
#*---------------------------------------------------------------------*/
# the library name
API		= ssl
# Directories
BIGLOO_SRC_DIR 	= Llib
DOTNET_SRC_DIR 	= DotNet
JAVA_SRC_DIR 	= Java
C_SRC_DIR 	= C
MISC_SRC_DIR 	= Misc
WIN32_SRC_DIR 	= Win32
# Where to store the library class files
CLASS_DIR	= objs/class_s/bigloo/$(API)
CLASS_EDIR	= objs/class_es/bigloo/$(API)
DOTNET_OBJ_DIR	= objs/dotnet_s
DOTNET_OBJ_EDIR	= objs/dotnet_es
# The Bigloo compiler
BIGLOO		= $(BGLBUILDBIGLOO)
AFILE		= $(BGLBUILDBINDIR)/$(AFILE_EXE)
JFILE		= $(BGLBUILDBINDIR)/$(JFILE_EXE)
DEPEND		= $(BGLBUILDBINDIR)/$(BDEPEND_EXE)
BTAGS		= $(BGLBUILDBINDIR)/$(BTAGS_EXE)
# Bigloo compilation options
BAPIFLAGS	= $(BFLAGS) -I Llib -lib-dir $(BOOTLIBDIR) -unsafe -safee
# Flags to build a heap
BHEAPFLAGS	= -unsafe -q -mkaddheap -mkaddlib -L $(BOOTLIBDIR) -I Llib \
                   -heap-library $(API)
BJVMFLAGS       := $(BJVMFLAGS)

# Additional SSL lib for C
EXTRALIBS	= $(OPENSSLLIBS)
# Additional SSL lib for java
SSL_ZIP		= commons-ssl.zip
JVMAPIBOOTPATH  := $(JVMAPIBOOTPATH):$(BOOTLIBDIR)/$(SSL_ZIP)

#*---------------------------------------------------------------------*/
#*    Scheme extended objects                                          */
#*---------------------------------------------------------------------*/
_BGL_OBJECTS	= ssl

_C_OBJECTS	= bglssl
_JAVA_CLASSES	= certificate private_key
_JAVA_ECLASSES	= ssl_client_socket ssl_server_socket 
_DOTNET_OBJ	= # bglssl

_OBJECTS	= $(_C_OBJECTS) $(_BGL_OBJECTS)
OBJECTS		= $(_OBJECTS:%=objs/%.o)

EOBJECTS	= objs/make_lib.o

BGL_CLASSES	= $(_BGL_OBJECTS:%=$(CLASS_DIR)/%.class)
BGL_ECLASSES	= $(CLASS_EDIR)/make_lib.class

JAVA_CLASSES	= $(_JAVA_CLASSES:%=$(CLASS_DIR)/%.class) \
                  $(_JAVA_ECLASSES:%=$(CLASS_DIR)/%.class)
JAVA_CLASSES_SRC= $(_JAVA_CLASSES:%=$(CLASS_DIR)/%.java)

BGL_DOTNET_OBJ	= $(_BGL_OBJECTS:%=$(DOTNET_OBJ_DIR)/%.obj)
DOTNET_OBJ	= $(_DOTNET_OBJ:%=$(DOTNET_OBJ_DIR)/%.obj)
BGL_DOTNET_EOBJ	= $(DOTNET_OBJ_EDIR)/make_lib.obj

DOTNET_OBJ_SRC	= # $(_DOTNET_OBJ:%=$(DOTNET_OBJ_DIR)/%.cs)

_WIN32_SRC	= 

_BGL_SOURCES	= $(_BGL_OBJECTS:%=$(BIGLOO_SRC_DIR)/%.scm)
_C_SOURCES	= $(_C_OBJECTS:%=$(C_SRC_DIR)/%.c)
_JAVA_SOURCES	= $(_JAVA_CLASSES:%=$(JAVA_SRC_DIR)/%.java)
_DOTNET_SOURCES	= $(_DOTNET_OBJ:%=$(DOTNET_SRC_DIR)/%.cs)
_WIN32_SOURCES	= $(_WIN32_SRC:%=$(WIN32_SRC_DIR)/%)

SOURCES		= $(_BGL_SOURCES) \
                  $(_C_SOURCES) \
                  $(_JAVA_SOURCES) \
                  $(_DOTNET_SOURCES)
INCLUDES	= $(C_SRC_DIR)/bglssl.h

#*---------------------------------------------------------------------*/
#*    Java objects                                                     */
#*---------------------------------------------------------------------*/
ifeq ($(JAVA_VERSION), 1.6)
  JAVA_CLASSES_SRC+=$(CLASS_DIR)/certificate.java $(CLASS_DIR)/private_key.java
else
 ifeq ($(JAVA_VERSION), 1.5)
   JAVA_CLASSES_SRC+=$(CLASS_DIR)/certificate.java $(CLASS_DIR)/private_key.java
 endif
endif

#*---------------------------------------------------------------------*/
#*    Sources                                                          */
#*---------------------------------------------------------------------*/
POPULATION	= $(SOURCES) $(C_SRC_DIR)/bglssl.h.in $(_WIN32_SOURCES) \
                  $(JAVA_SRC_DIR)/ssl_client_socket13.java \
                  $(JAVA_SRC_DIR)/ssl_client_socket15.java \
                  $(JAVA_SRC_DIR)/ssl_server_socket13.java \
                  $(JAVA_SRC_DIR)/ssl_server_socket15.java \
                  $(JAVA_SRC_DIR)/certificate.java \
                  $(JAVA_SRC_DIR)/private_key.java \
		  $(MISC_SRC_DIR)/make_lib.scm \
                  $(MISC_SRC_DIR)/$(API).init.in \
                  Makefile

#*---------------------------------------------------------------------*/
#*    all                                                              */
#*---------------------------------------------------------------------*/
.PHONY: c jvm dotnet build-c build-jvm build-dotnet

all: 
	@ if [ "$(NATIVEBACKEND)" = "yes" ]; then \
             $(MAKE) build-c; \
	  fi
	@ if [ "$(JVMBACKEND)" = "yes" ]; then \
             $(MAKE) build-jvm; \
	  fi
	@ if [ "$(DOTNETBACKEND)" = "yes" ]; then \
             $(MAKE) build-dotnet;  \
	  fi
c: build-c
build-c: api-c

jvm: build-jvm
build-jvm: lib-jvm

dotnet: build-dotnet
build-dotnet: api-dotnet

$(MISC_SRC_DIR)/$(API).init: $(MISC_SRC_DIR)/$(API).init.in
	@ echo "*** ERROR: $@ is out of date (older than $?)"
	@ echo "You need to re-configure \"(cd ..; ./configure --bootconfig)\""
	@ exit 1

.PHONY: lib-jvm

lib-jvm: $(JAVA_SRC_DIR)/ssl_client_socket.java \
         $(JAVA_SRC_DIR)/ssl_server_socket.java \
         $(BOOTLIBDIR)/$(SSL_ZIP)
	@ $(MAKE) api-jvm
	@ $(MAKE) jvm-extra

$(BOOTLIBDIR)/$(SSL_ZIP): ../lib/$(SSL_ZIP)
	@ echo Copying $(SSL_ZIP)
	@ cp $< $@

jvm-extra: $(JAVA_CLASSES_SRC) $(BOOTLIBDIR)/$(SSL_ZIP)
	(cd objs/class_s && \
          $(JAVAC) $(CYGWINJVMPATH) -classpath $(JVMAPIBOOTPATH) $(JAVA_CLASSES_SRC:objs/class_s/%=%))

#*---------------------------------------------------------------------*/
#*    Java auconfiguration                                             */
#*---------------------------------------------------------------------*/
ifeq ($(JAVA_VERSION), 1.6)
  JDK=15
 else
  ifeq ($(JAVA_VERSION), 1.5)
    JDK=15
  else
    JDK=13
 endif
endif

$(JAVA_SRC_DIR)/ssl_client_socket.java: \
    $(JAVA_SRC_DIR)/ssl_client_socket$(JDK).java
	echo "// Generated file, don't edit" > $@
	cat $< >> $@

$(JAVA_SRC_DIR)/ssl_server_socket.java: \
    $(JAVA_SRC_DIR)/ssl_server_socket$(JDK).java
	echo "// Generated file, don't edit" > $@
	cat $< >> $@

#*---------------------------------------------------------------------*/
#*    pop ...                                                          */
#*---------------------------------------------------------------------*/
.PHONY: pop

pop:
	@ echo $(POPULATION:%=$(API)/src/%)

#*---------------------------------------------------------------------*/
#*    extra-clean                                                      */
#*---------------------------------------------------------------------*/
clean: api-clean
	$(RM) -f $(JAVA_SRC_DIR)/ssl_client_socket.java
	$(RM) -f $(JAVA_SRC_DIR)/ssl_server_socket.java

cleanall: api-cleanall
	$(RM) $(BOOTLIBDIR)/$(SSL_ZIP)

distclean: cleanall

#*---------------------------------------------------------------------*/
#*    Common API rules                                                 */
#*---------------------------------------------------------------------*/
include ../../Makefile.api
