#*=====================================================================*/
#*    serrano/prgm/project/bigloo/api/fthread/src/Makefile             */
#*    -------------------------------------------------------------    */
#*    Author      :  Manuel Serrano                                    */
#*    Creation    :  Wed Apr  1 18:45:46 1998                          */
#*    Last change :  Fri Aug  6 08:08:47 2010 (serrano)                */
#*    -------------------------------------------------------------    */
#*    The makefile to build the library.                               */
#*=====================================================================*/

#*---------------------------------------------------------------------*/
#*    Standard Fthread configuration                                   */
#*---------------------------------------------------------------------*/
include ../../../Makefile.config
include ../../../Makefile.misc

#*---------------------------------------------------------------------*/
#*    Compilers, Tools and Destinations                                */
#*---------------------------------------------------------------------*/
# the library name
API		= fthread
# Directories
BIGLOO_SRC_DIR 	= Llib
DOTNET_SRC_DIR 	= DotNet
JAVA_SRC_DIR 	= Java
C_SRC_DIR 	= Posix
MISC_SRC_DIR 	= Misc
WIN32_SRC_DIR 	= Win32
# Where to store the library class files
PBASE		= bigloo.$(API)
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
CAPIFLAGS	= $(CGCTHREADFLAGS)
# Flags to build a heap
BHEAPFLAGS	= -unsafe -q -mkaddheap -mkaddlib -L $(BOOTLIBDIR) -I Llib \
                  -heap-library $(API)

# Additional pthread lib for C
EXTRALIBS	= "$(PTHREADLIBS)"
EXTRALIBS_S	= -lbigloopthread_s-$(RELEASE)
EXTRALIBS_U	= -lbigloopthread_u-$(RELEASE)

#*---------------------------------------------------------------------*/
#*    Scheme extended objects                                          */
#*---------------------------------------------------------------------*/
_BGL_OBJECTS	= types _types thread _thread \
                  scheduler _scheduler \
                  signal env _env env2d \
                  time _pthread async

_POSIX_OBJECTS	= 
_JAVA_CLASSES	= 
_DOTNET_OBJ	= 

_OBJECTS	= $(_POSIX_OBJECTS) $(_BGL_OBJECTS)
OBJECTS		= $(_OBJECTS:%=objs/%.o)
EOBJECTS	= objs/make_lib.o

BGL_CLASSES	= $(_BGL_OBJECTS:%=$(CLASS_DIR)/%.class)
BGL_ECLASSES	= $(CLASS_EDIR)/make_lib.class
JAVA_CLASSES	= $(_JAVA_CLASSES:%=$(CLASS_DIR)/%.class)
JAVA_CLASSES_SRC= $(_JAVA_CLASSES:%=$(CLASS_DIR)/%.java)

BGL_DOTNET_OBJ	= $(_BGL_OBJECTS:%=$(DOTNET_OBJ_DIR)/%.obj)
BGL_DOTNET_EOBJ	= $(DOTNET_OBJ_EDIR)/make_lib.obj
DOTNET_OBJ	= $(_DOTNET_OBJ:%=$(DOTNET_OBJ_DIR)/%.obj)
DOTNET_OBJ_SRC	= $(_DOTNET_OBJ:%=$(DOTNET_OBJ_DIR)/%.cs)

_WIN32_SRC	= 

_BGL_SOURCES	= $(_BGL_OBJECTS:%=$(BIGLOO_SRC_DIR)/%.scm)
_POSIX_SOURCES	= $(_POSIX_OBJECTS:%=$(C_SRC_DIR)/%.c)
_JAVA_SOURCES	= $(_JAVA_CLASSES:%=$(JAVA_SRC_DIR)/%.java)
_DOTNET_SOURCES	= $(_DOTNET_OBJ:%=$(DOTNET_SRC_DIR)/%.cs)
_WIN32_SOURCES	= $(_WIN32_SRC:%=$(WIN32_SRC_DIR)/%)

SOURCES		= $(_BGL_SOURCES) $(_POSIX_SOURCES) $(_JAVA_SOURCES) $(_DOTNET_SOURCES)
INCLUDES	= 
 
#*---------------------------------------------------------------------*/
#*    Sources                                                          */
#*---------------------------------------------------------------------*/
POPULATION	= $(SOURCES) $(INCLUDES) $(_WIN32_SOURCES) \
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
build-jvm: api-jvm

dotnet: build-dotnet
build-dotnet: api-dotnet

$(MISC_SRC_DIR)/$(API).init: $(MISC_SRC_DIR)/$(API).init.in
	@ echo "*** ERROR: $@ is out of date (older than $?)"
	@ echo "You need to re-configure \"(cd ..; ./configure --bootconfig)\""
	@ exit 1

#*---------------------------------------------------------------------*/
#*    pop ...                                                          */
#*---------------------------------------------------------------------*/
pop:
	@ echo $(POPULATION:%=$(API)/src/%)

#*---------------------------------------------------------------------*/
#*    clean                                                            */
#*---------------------------------------------------------------------*/
clean: api-clean

cleanall: api-cleanall

distclean: cleanall

#*---------------------------------------------------------------------*/
#*    Common API rules                                                 */
#*---------------------------------------------------------------------*/
include ../../Makefile.api

