#*=====================================================================*/
#*    serrano/prgm/project/bigloo/api/pthread/recette/Makefile         */
#*    -------------------------------------------------------------    */
#*    Author      :  Manuel Serrano                                    */
#*    Creation    :  Mon Jan  7 14:55:33 2002                          */
#*    Last change :  Thu May 24 11:57:25 2007 (serrano)                */
#*    Copyright   :  2002-07 Manuel Serrano                            */
#*    -------------------------------------------------------------    */
#*    The Makefile to build the Fair threads tests                     */
#*=====================================================================*/

#*---------------------------------------------------------------------*/
#*    Standard path                                                    */
#*---------------------------------------------------------------------*/
include ../../../Makefile.config 

#*---------------------------------------------------------------------*/
#*    Bigloo                                                           */
#*---------------------------------------------------------------------*/
BIGLOO		= $(BOOTBINDIR)/bigloo
BCFLAGS		= -call/cc 

#*---------------------------------------------------------------------*/
#*    Objects and sources                                              */
#*---------------------------------------------------------------------*/
SCM_FILE	= recette

#*---------------------------------------------------------------------*/
#*    All objects and sources                                          */
#*---------------------------------------------------------------------*/
POPULATION	= recette.scm Makefile

#*---------------------------------------------------------------------*/
#*    the goals.                                                       */
#*---------------------------------------------------------------------*/
all: c jvm dotnet

c: recette$(EXE_SUFFIX)
recette$(EXE_SUFFIX): recette.o
	$(BIGLOO) $(EFLAGS) $(BFLAGS) recette.o -o recette$(EXE_SUFFIX)

jvm: 
	@ if [ "$(JVMBACKEND)" = "yes" ]; then \
             $(MAKE) recette-jvm$(SCRIPTEXTENSION); \
	  fi

recette-jvm$(SCRIPTEXTENSION): recette.class
	$(BIGLOO) -jvm $(EFLAGS) $(BFLAGS) recette.class -o recette-jvm$(SCRIPTEXTENSION)

dotnet: 
	@ if [ "$(DOTNETBACKEND)" = "yes" ]; then \
             $(MAKE) recette-dotnet$(SCRIPTEXTENSION); \
	  fi

recette-dotnet$(SCRIPTEXTENSION): recette.obj
	$(BIGLOO) -v -dotnet -dotnet-managed $(EFLAGS) $(BFLAGS) recette.obj -o recette-dotnet$(SCRIPTEXTENSION)

pop:
	@ echo $(POPULATION:%=pthread/recette/%)

clean:
	@- $(RM) -f *~ '#*#' core
	@- $(RM) -f *.escm *.ast recette.c recette$(EXE_SUFFIX)
	@- $(RM) -f recette.o
	@- $(RM) -f JVMMAIN.class *.class recette-jvm$(SCRIPTEXTENSION) 
	@- $(RM) -f recette.obj recette.il
	@- $(RM) -f recette-dotnet.exe recette-dotnet$(SCRIPTEXTENSION)

distclean: clean

#*---------------------------------------------------------------------*/
#*    Test                                                             */
#*---------------------------------------------------------------------*/
test: test-c test-jvm test-dotnet

test-c:
	(export LD_LIBRARY_PATH=../lib:$$LD_LIBRARY_PATH; \
	 export DYLD_LIBRARY_PATH=../lib:$$DYLD_LIBRARY_PATH; \
         ./recette.out)

test-jvm:
	./recette-jvm$(SCRIPTEXTENSION)

test-dotnet:
	./recette-dotnet$(SCRIPTEXTENSION)

#*---------------------------------------------------------------------*/
#*    Suffixes                                                         */
#*---------------------------------------------------------------------*/
.SUFFIXES:
.SUFFIXES: .bgl .scm .o .class .obj

#*---------------------------------------------------------------------*/
#*    .scm -> .o/.class/.obj                                           */
#*---------------------------------------------------------------------*/
.scm.o: $*.scm
	$(BIGLOO) -c $(EFLAGS) $(BCFLAGS) $(BFLAGS) $*.scm -o $*.o

.scm.class: $*.scm
	$(BIGLOO) -c -jvm $(EFLAGS) $(BCFLAGS) $(BFLAGS) $*.scm -o $*.class

.scm.obj: $*.scm
	$(BIGLOO) -c -dotnet -dotnet-managed $(EFLAGS) $(BCFLAGS) $(BFLAGS) $*.scm -o $*.obj
