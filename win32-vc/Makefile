
SDL_INCLUDES  = -I ./SDL/include -I ./SDL_image/include
STL_INCLUDES  = -I /usr/include/c++/3.3.1

# /usr/include/c++/3.3.1/ext

LIB = ../lib
LIB_HANDLER = ${LIB}/handler
LIB_TOOLS = ${LIB}/tools
LIB_TYPES = ${LIB}/types
LIB_VALUES = ${LIB}/values
LIB_WIDGETS = ${LIB}/widgets
LIB_WINDOWS = ${LIB}/windows

KDS = ../src
KDS_MAIN = ${KDS}
KDS_CONNECTORS = ${KDS}/connectors
KDS_HANDLES = ${KDS}/handles
KDS_OBJECTS = ${KDS}/objects
KDS_MODULES = ${KDS}/modules
KDS_MODULES_ATTRIBUTE = ${KDS_MODULES}/attribute
KDS_MODULES_MATRIX = ${KDS_MODULES}/matrix
KDS_MODULES_OBJECT = ${KDS_MODULES}/object
KDS_MODULES_VALUE = ${KDS_MODULES}/value

LIB_INCLUDES = -I ${LIB_HANDLER} -I ${LIB_TOOLS} -I ${LIB_TYPES} -I ${LIB_VALUES} -I ${LIB_WIDGETS} -I ${LIB_WINDOWS}
KDS_INCLUDES = -I ${KDS_MAIN} -I ${KDS_CONNECTORS} -I ${KDS_HANDLES} -I ${KDS_OBJECTS} -I ${KDS_MODULES} -I ${KDS_MODULES_ATTRIBUTE} -I ${KDS_MODULES_MATRIX} -I ${KDS_MODULES_OBJECT} -I ${KDS_MODULES_VALUE}

CXX_FLAGS = -w -D_REENTRANT -Dmain=SDL_main -DNO_HASH_MAP  -DWIN32 ${LIB_INCLUDES} ${KDS_INCLUDES} ${SDL_INCLUDES} ${STL_INCLUDES} ${GLUT_INCLUDES}

LIBS = -L./SDL/lib -L./SDL_image/lib -l SDL -l SDL_image -lSDLmain -l opengl32 -l glu32 -l glut -l kernel32 -l user32 -l gdi32 -l comdlg32 -l advapi32 -l shell32 -l ole32 -l oleaut32 -l uuid -l imm32 -l winmm -l wsock32 -mwindows

#-l kernel32 -l user32 -l gdi32 -l comdlg32 -l advapi32 -l shell32 -l ole32 -l oleaut32 -l uuid -l imm32 -l winmm -l wsock32

SRC_LIB_HANDLER = \
		${LIB_HANDLER}/KEventHandler.cpp \
		${LIB_HANDLER}/KFileHandler.cpp \
		${LIB_HANDLER}/KKeyActionHandler.cpp \
		${LIB_HANDLER}/KKeyHandler.cpp \
		${LIB_HANDLER}/KKeyRecorder.cpp \
		${LIB_HANDLER}/KPickable.cpp \
		${LIB_HANDLER}/KPickHandler.cpp \
		${LIB_HANDLER}/KSelectable.cpp \
		${LIB_HANDLER}/KSelectionHandler.cpp
OBJ_LIB_HANDLER = $(SRC_LIB_HANDLER:.cpp=.o)

SRC_LIB_TOOLS =	${LIB_TOOLS}/KFileTools.cpp \
		${LIB_TOOLS}/KIntrospection.cpp \
		${LIB_TOOLS}/KKeyTools.cpp \
		${LIB_TOOLS}/KNotificationObject.cpp \
		${LIB_TOOLS}/KStringTools.cpp \
		${LIB_TOOLS}/KTools.cpp \
		${LIB_TOOLS}/KXMLTools.cpp
OBJ_LIB_TOOLS = $(SRC_LIB_TOOLS:.cpp=.o)

SRC_LIB_TYPES = \
${LIB_TYPES}/KColor.cpp                   ${LIB_TYPES}/KProjection.cpp \
${LIB_TYPES}/KKey.cpp                     ${LIB_TYPES}/KSeparatedMatrix.cpp \
${LIB_TYPES}/KLightingProjection.cpp      ${LIB_TYPES}/KTexture.cpp \
${LIB_TYPES}/KMatrix.cpp                  ${LIB_TYPES}/KTrash.cpp \
${LIB_TYPES}/KOrthographicProjection.cpp  ${LIB_TYPES}/KVector.cpp \
${LIB_TYPES}/KPerspectiveProjection.cpp
OBJ_LIB_TYPES = $(SRC_LIB_TYPES:.cpp=.o)

SRC_LIB_VALUES = \
${LIB_VALUES}/KBoolValueObject.cpp      ${LIB_VALUES}/KSizeValueObject.cpp \
${LIB_VALUES}/KFileNameValueObject.cpp  ${LIB_VALUES}/KStringValueObject.cpp \
${LIB_VALUES}/KFloatValueObject.cpp     ${LIB_VALUES}/KValueObject.cpp \
${LIB_VALUES}/KKeyValueObject.cpp
OBJ_LIB_VALUES = $(SRC_LIB_VALUES:.cpp=.o)

SRC_LIB_WIDGETS = \
${LIB_WIDGETS}/KButton.cpp              ${LIB_WIDGETS}/KMenu.cpp \
${LIB_WIDGETS}/KButtonBox.cpp           ${LIB_WIDGETS}/KMenuItem.cpp \
${LIB_WIDGETS}/KFileNameField.cpp       ${LIB_WIDGETS}/KNumberField.cpp \
${LIB_WIDGETS}/KFileTreeDir.cpp         ${LIB_WIDGETS}/KProjectionWidget.cpp \
${LIB_WIDGETS}/KFileTreeDirCurrent.cpp  ${LIB_WIDGETS}/KStatusMenuItem.cpp \
${LIB_WIDGETS}/KFileTreeDirUp.cpp       ${LIB_WIDGETS}/KSubMenuItem.cpp \
${LIB_WIDGETS}/KFileTreeFile.cpp        ${LIB_WIDGETS}/KTextField.cpp \
${LIB_WIDGETS}/KFileTreeNode.cpp        ${LIB_WIDGETS}/KTextWidget.cpp \
${LIB_WIDGETS}/KFileTreeWidget.cpp      ${LIB_WIDGETS}/KToggleButton.cpp \
${LIB_WIDGETS}/KIconButton.cpp          ${LIB_WIDGETS}/KWidget.cpp \
${LIB_WIDGETS}/KKeySequenceField.cpp    ${LIB_WIDGETS}/KWidgetArray.cpp \
${LIB_WIDGETS}/KLabel.cpp
OBJ_LIB_WIDGETS = $(SRC_LIB_WIDGETS:.cpp=.o)

SRC_LIB_WINDOWS = \
${LIB_WINDOWS}/KConsole.cpp         ${LIB_WINDOWS}/KMessagePanel.cpp \
${LIB_WINDOWS}/KFileTreeWindow.cpp  ${LIB_WINDOWS}/KPopupMenu.cpp \
${LIB_WINDOWS}/KMenuWindow.cpp      ${LIB_WINDOWS}/KWindow.cpp
OBJ_LIB_WINDOWS = $(SRC_LIB_WINDOWS:.cpp=.o)

SRC_KDS_MAIN = \
../src/KCameraHandler.cpp  ../src/KMainMenu.cpp  ../src/KPreferences.cpp \
../src/KController.cpp     ../src/KModules.cpp   ../src/KTextureSets.cpp \
../src/KMain.cpp           ../src/KObjects.cpp
OBJ_KDS_MAIN = $(SRC_KDS_MAIN:.cpp=.o)

SRC_KDS_CONNECTORS = \
../src/connectors/KConnector.cpp \
../src/connectors/KConnectorAttributeIn.cpp \
../src/connectors/KConnectorAttributeOut.cpp \
../src/connectors/KConnectorIntValueInOut.cpp \
../src/connectors/KConnectorMatrixIn.cpp \
../src/connectors/KConnectorMatrixOut.cpp \
../src/connectors/KConnectorModulatorIn.cpp \
../src/connectors/KConnectorModulatorOut.cpp \
../src/connectors/KConnectorParticleIn.cpp \
../src/connectors/KConnectorParticleOut.cpp \
../src/connectors/KConnectorSceneIn.cpp \
../src/connectors/KConnectorSceneOut.cpp \
../src/connectors/KConnectorTextureBatchIn.cpp \
../src/connectors/KConnectorTextureBatchOut.cpp \
../src/connectors/KConnectorTextureFileIn.cpp \
../src/connectors/KConnectorTextureFileOut.cpp \
../src/connectors/KConnectorTextureVersionIn.cpp \
../src/connectors/KConnectorTextureVersionOut.cpp \
../src/connectors/KConnectorValueIn.cpp \
../src/connectors/KConnectorValueInOut.cpp \
../src/connectors/KConnectorValueOut.cpp \
../src/connectors/KValueConnector.cpp
OBJ_KDS_CONNECTORS = $(SRC_KDS_CONNECTORS:.cpp=.o)

SRC_KDS_HANDLES = \
../src/handles/KHandle.cpp \
../src/handles/KHandlesObject.cpp \
../src/handles/KMatrixHandle.cpp \
../src/handles/KMatrixHandleRotate.cpp \
../src/handles/KMatrixHandleScale.cpp \
../src/handles/KMatrixHandleTranslate.cpp \
../src/handles/KMoveHandle.cpp \
../src/handles/KOneDirectionHandle.cpp \
../src/handles/KRotationHandle.cpp \
../src/handles/KScaleHandle.cpp \
../src/handles/KTwoDirectionHandle.cpp \
../src/handles/KVertexHandle.cpp
OBJ_KDS_HANDLES = $(SRC_KDS_HANDLES:.cpp=.o)

SRC_KDS_OBJECTS = \
../src/objects/KBox.cpp        ../src/objects/KLight.cpp \
../src/objects/KCamera.cpp     ../src/objects/KParticle.cpp \
../src/objects/KCylinder.cpp   ../src/objects/KSphere.cpp \
../src/objects/KDisk.cpp       ../src/objects/KText.cpp \
../src/objects/KFace.cpp       ../src/objects/KVertex.cpp \
../src/objects/KLandscape.cpp
OBJ_KDS_OBJECTS = $(SRC_KDS_OBJECTS:.cpp=.o)

SRC_KDS_MODULES = \
../src/modules/KModule.cpp           ../src/modules/KTextureBatch.cpp \
../src/modules/KModuleInspector.cpp  ../src/modules/KTextureFile.cpp \
../src/modules/KScene.cpp            ../src/modules/KTextureModule.cpp \
../src/modules/KSceneSet.cpp         ../src/modules/KTextureSet.cpp
OBJ_KDS_MODULES = $(SRC_KDS_MODULES:.cpp=.o)

SRC_KDS_MODULES_ATTRIBUTE = \
../src/modules/attribute/KAttributeModule.cpp \
../src/modules/attribute/KModuleAttributeHub.cpp \
../src/modules/attribute/KModuleBlend.cpp \
../src/modules/attribute/KModuleColor.cpp \
../src/modules/attribute/KModuleColorMask.cpp \
../src/modules/attribute/KModuleFog.cpp \
../src/modules/attribute/KModuleMaterial.cpp \
../src/modules/attribute/KModuleTexture.cpp \
../src/modules/attribute/KModuleTextureFile.cpp \
../src/modules/attribute/KModuleTextureMatrix.cpp
OBJ_KDS_MODULES_ATTRIBUTE = $(SRC_KDS_MODULES_ATTRIBUTE:.cpp=.o)

SRC_KDS_MODULES_MATRIX = \
../src/modules/matrix/KHubModule.cpp \
../src/modules/matrix/KMatrixModule.cpp \
../src/modules/matrix/KModuleGoto.cpp \
../src/modules/matrix/KModuleIdentity.cpp \
../src/modules/matrix/KModuleLabel.cpp \
../src/modules/matrix/KModuleMatrix.cpp \
../src/modules/matrix/KModuleMatrixHub.cpp \
../src/modules/matrix/KModuleRotate.cpp \
../src/modules/matrix/KModuleScale.cpp \
../src/modules/matrix/KModuleSize.cpp \
../src/modules/matrix/KModuleTranslate.cpp
OBJ_KDS_MODULES_MATRIX = $(SRC_KDS_MODULES_MATRIX:.cpp=.o)

SRC_KDS_MODULES_OBJECT = \
../src/modules/object/KModuleCamera.cpp \
../src/modules/object/KModuleLSystem.cpp \
../src/modules/object/KModuleLight.cpp \
../src/modules/object/KModuleObjectBox.cpp \
../src/modules/object/KModuleObjectCylinder.cpp \
../src/modules/object/KModuleObjectDisk.cpp \
../src/modules/object/KModuleObjectFace.cpp \
../src/modules/object/KModuleObjectLandscape.cpp \
../src/modules/object/KModuleObjectPoint.cpp \
../src/modules/object/KModuleObjectSphere.cpp \
../src/modules/object/KModuleObjectText.cpp \
../src/modules/object/KModuleParticle.cpp \
../src/modules/object/KModuleParticleEmitter.cpp \
../src/modules/object/KModuleVertex.cpp \
../src/modules/object/KObjectModule.cpp
OBJ_KDS_MODULES_OBJECT = $(SRC_KDS_MODULES_OBJECT:.cpp=.o)

SRC_KDS_MODULES_VALUE = \
../src/modules/value/KActivationValueModule.cpp \
../src/modules/value/KFilterModule.cpp \
../src/modules/value/KGlobalModulator.cpp \
../src/modules/value/KModulator.cpp \
../src/modules/value/KModuleAccu.cpp \
../src/modules/value/KModuleRandom.cpp \
../src/modules/value/KModuleSwitch.cpp \
../src/modules/value/KModuleTrigger.cpp \
../src/modules/value/KModuleVariable.cpp \
../src/modules/value/KOperationModule.cpp \
../src/modules/value/KSequenceGenerator.cpp \
../src/modules/value/KValueModule.cpp
OBJ_KDS_MODULES_VALUE = $(SRC_KDS_MODULES_VALUE:.cpp=.o)

KODILIB_OBJECTS = ${OBJ_LIB_HANDLER} ${OBJ_LIB_TOOLS} ${OBJ_LIB_TYPES} ${OBJ_LIB_VALUES} ${OBJ_LIB_WIDGETS} ${OBJ_LIB_WINDOWS}
KODISEIN_OBJECTS = ${OBJ_KDS_MAIN} ${OBJ_KDS_CONNECTORS} ${OBJ_KDS_HANDLES} ${OBJ_KDS_OBJECTS} ${OBJ_KDS_MODULES} ${OBJ_KDS_MODULES_ATTRIBUTE} ${OBJ_KDS_MODULES_MATRIX} ${OBJ_KDS_MODULES_OBJECT} ${OBJ_KDS_MODULES_VALUE}

kodisein.exe: $(KODILIB_OBJECTS) ${KODISEIN_OBJECTS}
	$(CXX) -o $@ $^  ${LIBS}

kodilib.a: $(KODILIB_OBJECTS)
	$(AR) r $@ $^

clean:
	$(RM) -f  $(KODILIB_OBJECTS) ${KODISEIN_OBJECTS} kodilib.a

%.o: %.cpp
	$(CXX) -c $(CXX_FLAGS) -o $@ $<