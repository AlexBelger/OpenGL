
!include <win32.mak>

LINK_DIR = "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin"
DIR_BIN = bin
DIR_BIN_FREEGLUT = $(DIR_BIN)\freeglut
DIR_BIN_MFC = $(DIR_BIN)\MFC
DIR_INTERMEDIATE = intermediate
OBJ_FILES_FREEGLUT = \
	$(DIR_INTERMEDIATE)\main.obj \
	$(DIR_INTERMEDIATE)\GLProgram.obj \
	$(DIR_INTERMEDIATE)\GLRenderer.obj \
	$(DIR_INTERMEDIATE)\GLShader.obj \
	$(DIR_INTERMEDIATE)\ShapeGenerator.obj 

all : clean create_dirs cube_freeglut cube_mfc

cube_freeglut : $(OBJ_FILES_FREEGLUT)
	$(LINK_DIR)/$(link) $(ldebug) $(conflags) -out:$(DIR_BIN_FREEGLUT)\cube.exe $** $(conlibs) freeglut.lib glew32.lib opengl32.lib

cube_mfc : 
	msbuild.exe SystemSpecific/MFC/OpenGL.sln /p:Configuration=Debug /p:Platform="x86"

{OpenGL\Shapes}.cpp{$(DIR_INTERMEDIATE)}.obj:	; $(cc) /EHsc /Fo$(DIR_INTERMEDIATE)\ $(cdebug) $(cflags) $(cvars) $<
{OpenGL}.cpp{$(DIR_INTERMEDIATE)}.obj:		; $(cc) /EHsc /Fo$(DIR_INTERMEDIATE)\ $(cdebug) $(cflags) $(cvars) $<
{SystemSpecific\freeglut}.cpp{$(DIR_INTERMEDIATE)}.obj:		; $(cc) /EHsc /Fo$(DIR_INTERMEDIATE)\ $(cdebug) $(cflags) $(cvars) $<

create_dirs:
 @if not exist $(DIR_BIN) mkdir $(DIR_BIN)
 @if not exist $(DIR_BIN_FREEGLUT) mkdir $(DIR_BIN_FREEGLUT)
 @if not exist $(DIR_BIN_MFC) mkdir $(DIR_BIN_MFC)
 @if not exist $(DIR_INTERMEDIATE) mkdir $(DIR_INTERMEDIATE)

clean:
 @if exist $(DIR_BIN) rmdir /S /Q $(DIR_BIN)
 @if exist $(DIR_BIN_FREEGLUT) rmdir /S /Q $(DIR_BIN_FREEGLUT)
 @if exist $(DIR_BIN_MFC) rmdir /S /Q $(DIR_BIN_MFC)
 @if exist $(DIR_INTERMEDIATE) rmdir /S /Q $(DIR_INTERMEDIATE)

