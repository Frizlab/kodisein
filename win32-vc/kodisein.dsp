# Microsoft Developer Studio Project File - Name="kodisein" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=kodisein - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "kodisein.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "kodisein.mak" CFG="kodisein - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "kodisein - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "kodisein - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "kodisein - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "kodisein - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MD /Gm /GX /ZI /Od /I "../lib/tools" /I "../lib/types" /I "../lib/handler" /I "../lib/values" /I "../lib/widgets" /I "../lib/windows" /I "../src" /I "../src/connectors" /I "../src/handles" /I "../src/objects" /I "../src/modules" /I "../src/modules/object" /I "../src/modules/attribute" /I "../src/modules/matrix" /I "../src/modules/value" /I "./SDL/include" /I "./SDL_image/include" /I "." /I "./STLport/stlport" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib SDL.lib SDL_image.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"./GLUT" /libpath:"./SDL/lib" /libpath:"./SDL_image/lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\SDL\lib\SDL.dll Debug	copy .\SDL_image\lib\*.dll Debug	copy .\GLUT\*.dll Debug
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "kodisein - Win32 Release"
# Name "kodisein - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "handler"

# PROP Default_Filter ""
# Begin Group "handler_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\handler\KEventHandler.h
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KFileHandler.h
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KKeyActionHandler.h
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KKeyHandler.h
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KKeyRecorder.h
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KPickable.h
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KPickHandler.h
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KSelectable.h
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KSelectionHandler.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\lib\handler\KEventHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KFileHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KKeyActionHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KKeyHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KKeyRecorder.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KPickable.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KPickHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KSelectable.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\handler\KSelectionHandler.cpp
# End Source File
# End Group
# Begin Group "tools"

# PROP Default_Filter ""
# Begin Group "tools_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\tools\KFileTools.h
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KIntrospection.h
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KKeySymbols.h
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KKeyTools.h
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KNotificationObject.h
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KStringTools.h
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KTools.h
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KXMLTools.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\lib\tools\KFileTools.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KIntrospection.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KKeyTools.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KNotificationObject.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KStringTools.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KTools.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\tools\KXMLTools.cpp
# End Source File
# End Group
# Begin Group "types"

# PROP Default_Filter ""
# Begin Group "types_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\types\KColor.h
# End Source File
# Begin Source File

SOURCE=..\lib\types\KKey.h
# End Source File
# Begin Source File

SOURCE=..\lib\types\KLightingProjection.h
# End Source File
# Begin Source File

SOURCE=..\lib\types\KMatrix.h
# End Source File
# Begin Source File

SOURCE=..\lib\types\KOrthographicProjection.h
# End Source File
# Begin Source File

SOURCE=..\lib\types\KPerspectiveProjection.h
# End Source File
# Begin Source File

SOURCE=..\lib\types\KProjection.h
# End Source File
# Begin Source File

SOURCE=..\lib\types\KSeparatedMatrix.h
# End Source File
# Begin Source File

SOURCE=..\lib\types\KTexture.h
# End Source File
# Begin Source File

SOURCE=..\lib\types\KTrash.h
# End Source File
# Begin Source File

SOURCE=..\lib\types\KVector.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\lib\types\KColor.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\types\KKey.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\types\KLightingProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\types\KMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\types\KOrthographicProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\types\KPerspectiveProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\types\KProjection.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\types\KSeparatedMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\types\KTexture.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\types\KTrash.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\types\KVector.cpp
# End Source File
# End Group
# Begin Group "values"

# PROP Default_Filter ""
# Begin Group "values_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\values\KBoolValueObject.h
# End Source File
# Begin Source File

SOURCE=..\lib\values\KDiscreteValueObject.h
# End Source File
# Begin Source File

SOURCE=..\lib\values\KFileNameValueObject.h
# End Source File
# Begin Source File

SOURCE=..\lib\values\KFloatValueObject.h
# End Source File
# Begin Source File

SOURCE=..\lib\values\KKeyValueObject.h
# End Source File
# Begin Source File

SOURCE=..\lib\values\KSizeValueObject.h
# End Source File
# Begin Source File

SOURCE=..\lib\values\KStringValueObject.h
# End Source File
# Begin Source File

SOURCE=..\lib\values\KValueObject.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\lib\values\KBoolValueObject.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\values\KFileNameValueObject.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\values\KFloatValueObject.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\values\KKeyValueObject.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\values\KSizeValueObject.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\values\KStringValueObject.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\values\KValueObject.cpp
# End Source File
# End Group
# Begin Group "widgets"

# PROP Default_Filter ""
# Begin Group "widgets_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\widgets\KButton.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KButtonBox.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KButtonSymbols.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileNameField.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeDir.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeDirCurrent.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeDirUp.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeFile.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeNode.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeWidget.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KIconButton.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KKeySequenceField.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KLabel.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KMenu.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KMenuItem.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KNumberField.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KProjectionWidget.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KStatusMenuItem.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KSubMenuItem.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KTextField.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KTextWidget.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KToggleButton.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KWidget.h
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KWidgetArray.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\lib\widgets\KButton.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KButtonBox.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileNameField.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeDir.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeDirCurrent.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeDirUp.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeFile.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeNode.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KFileTreeWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KIconButton.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KKeySequenceField.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KLabel.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KMenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KNumberField.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KProjectionWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KStatusMenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KSubMenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KTextField.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KTextWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KToggleButton.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KWidget.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\widgets\KWidgetArray.cpp
# End Source File
# End Group
# Begin Group "windows"

# PROP Default_Filter ""
# Begin Group "windows_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\windows\KConsole.h
# End Source File
# Begin Source File

SOURCE=..\lib\windows\KFileTreeWindow.h
# End Source File
# Begin Source File

SOURCE=..\lib\windows\KMenuWindow.h
# End Source File
# Begin Source File

SOURCE=..\lib\windows\KMessagePanel.h
# End Source File
# Begin Source File

SOURCE=..\lib\windows\KPopupMenu.h
# End Source File
# Begin Source File

SOURCE=..\lib\windows\KWindow.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\lib\windows\KConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\windows\KFileTreeWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\windows\KMenuWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\windows\KMessagePanel.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\windows\KPopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\lib\windows\KWindow.cpp
# End Source File
# End Group
# Begin Group "main"

# PROP Default_Filter ""
# Begin Group "main_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\KCameraHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\KController.h
# End Source File
# Begin Source File

SOURCE=..\src\KMain.h
# End Source File
# Begin Source File

SOURCE=..\src\KMainMenu.h
# End Source File
# Begin Source File

SOURCE=..\src\KModules.h
# End Source File
# Begin Source File

SOURCE=..\src\KObjects.h
# End Source File
# Begin Source File

SOURCE=..\src\KPreferences.h
# End Source File
# Begin Source File

SOURCE=..\src\KTextureSets.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\KCameraHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\KController.cpp
# End Source File
# Begin Source File

SOURCE=..\src\KMain.cpp
# End Source File
# Begin Source File

SOURCE=..\src\KMainMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\KModules.cpp
# End Source File
# Begin Source File

SOURCE=..\src\KObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\kodisein.cpp
# End Source File
# Begin Source File

SOURCE=..\src\KPreferences.cpp
# End Source File
# Begin Source File

SOURCE=..\src\KTextureSets.cpp
# End Source File
# End Group
# Begin Group "connectors"

# PROP Default_Filter ""
# Begin Group "connectors_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\connectors\KConnector.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorAttributeIn.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorAttributeOut.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorDiscreteValueInOut.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorMatrixIn.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorMatrixOut.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorModulatorIn.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorModulatorOut.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorParticleIn.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorParticleOut.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorSceneIn.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorSceneOut.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureBatchIn.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureBatchOut.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureFileIn.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureFileOut.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureVersionIn.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureVersionOut.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorValueIn.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorValueInOut.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorValueOut.h
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KValueConnector.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\connectors\KConnector.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorAttributeIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorAttributeOut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorIntValueInOut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorMatrixIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorMatrixOut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorModulatorIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorModulatorOut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorParticleIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorParticleOut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorSceneIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorSceneOut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureBatchIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureBatchOut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureFileIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureFileOut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureVersionIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorTextureVersionOut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorValueIn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorValueInOut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KConnectorValueOut.cpp
# End Source File
# Begin Source File

SOURCE=..\src\connectors\KValueConnector.cpp
# End Source File
# End Group
# Begin Group "handles"

# PROP Default_Filter ""
# Begin Group "handles_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\handles\KHandle.h
# End Source File
# Begin Source File

SOURCE=..\src\handles\KHandlesObject.h
# End Source File
# Begin Source File

SOURCE=..\src\handles\KMatrixHandle.h
# End Source File
# Begin Source File

SOURCE=..\src\handles\KMatrixHandleRotate.h
# End Source File
# Begin Source File

SOURCE=..\src\handles\KMatrixHandleScale.h
# End Source File
# Begin Source File

SOURCE=..\src\handles\KMatrixHandleTranslate.h
# End Source File
# Begin Source File

SOURCE=..\src\handles\KMoveHandle.h
# End Source File
# Begin Source File

SOURCE=..\src\handles\KOneDirectionHandle.h
# End Source File
# Begin Source File

SOURCE=..\src\handles\KRotationHandle.h
# End Source File
# Begin Source File

SOURCE=..\src\handles\KScaleHandle.h
# End Source File
# Begin Source File

SOURCE=..\src\handles\KTwoDirectionHandle.h
# End Source File
# Begin Source File

SOURCE=..\src\handles\KVertexHandle.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\handles\KHandle.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handles\KHandlesObject.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handles\KMatrixHandle.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handles\KMatrixHandleRotate.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handles\KMatrixHandleScale.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handles\KMatrixHandleTranslate.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handles\KMoveHandle.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handles\KOneDirectionHandle.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handles\KRotationHandle.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handles\KScaleHandle.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handles\KTwoDirectionHandle.cpp
# End Source File
# Begin Source File

SOURCE=..\src\handles\KVertexHandle.cpp
# End Source File
# End Group
# Begin Group "modules"

# PROP Default_Filter ""
# Begin Group "attribute"

# PROP Default_Filter ""
# Begin Group "attribute_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\modules\attribute\KAttributeModule.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleAttributeHub.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleBlend.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleColor.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleColorMask.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleFog.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleMaterial.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleTexture.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleTextureFile.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleTextureMatrix.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\modules\attribute\KAttributeModule.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleAttributeHub.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleBlend.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleColor.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleColorMask.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleFog.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleMaterial.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleTexture.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleTextureFile.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\attribute\KModuleTextureMatrix.cpp
# End Source File
# End Group
# Begin Group "matrix"

# PROP Default_Filter ""
# Begin Group "matrix_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\modules\matrix\KHubModule.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KMatrixModule.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleGoto.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleIdentity.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleLabel.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleMatrix.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleMatrixHub.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleRotate.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleScale.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleSize.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleTranslate.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\modules\matrix\KHubModule.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KMatrixModule.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleGoto.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleIdentity.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleLabel.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleMatrix.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleMatrixHub.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleRotate.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleScale.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleSize.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\matrix\KModuleTranslate.cpp
# End Source File
# End Group
# Begin Group "object"

# PROP Default_Filter ""
# Begin Group "object_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\modules\object\KModuleCamera.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleLight.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleLSystem.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectBox.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectCylinder.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectDisk.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectFace.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectLandscape.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectPoint.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectSphere.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectText.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleParticle.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleParticleEmitter.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleVertex.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KObjectModule.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\modules\object\KModuleCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleLight.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleLSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectBox.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectCylinder.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectDisk.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectFace.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectLandscape.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectSphere.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleObjectText.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleParticle.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleParticleEmitter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KModuleVertex.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\object\KObjectModule.cpp
# End Source File
# End Group
# Begin Group "value"

# PROP Default_Filter ""
# Begin Group "value_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\modules\value\KActivationValueModule.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KFilterModule.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KGlobalModulator.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModulator.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModuleAccu.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModuleRandom.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModuleSwitch.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModuleTrigger.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModuleVariable.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KOperationModule.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KSequenceGenerator.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KValueModule.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\modules\value\KActivationValueModule.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KFilterModule.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KGlobalModulator.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModulator.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModuleAccu.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModuleRandom.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModuleSwitch.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModuleTrigger.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KModuleVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KOperationModule.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KSequenceGenerator.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\value\KValueModule.cpp
# End Source File
# End Group
# Begin Group "modules_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\modules\KModule.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\KModuleInspector.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\KScene.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\KSceneSet.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\KTextureBatch.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\KTextureFile.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\KTextureModule.h
# End Source File
# Begin Source File

SOURCE=..\src\modules\KTextureSet.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\modules\KModule.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\KModuleInspector.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\KScene.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\KSceneSet.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\KTextureBatch.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\KTextureFile.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\KTextureModule.cpp
# End Source File
# Begin Source File

SOURCE=..\src\modules\KTextureSet.cpp
# End Source File
# End Group
# Begin Group "objects"

# PROP Default_Filter ""
# Begin Group "objects_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\objects\KBox.h
# End Source File
# Begin Source File

SOURCE=..\src\objects\KCamera.h
# End Source File
# Begin Source File

SOURCE=..\src\objects\KCylinder.h
# End Source File
# Begin Source File

SOURCE=..\src\objects\KDisk.h
# End Source File
# Begin Source File

SOURCE=..\src\objects\KFace.h
# End Source File
# Begin Source File

SOURCE=..\src\objects\KLandscape.h
# End Source File
# Begin Source File

SOURCE=..\src\objects\KLight.h
# End Source File
# Begin Source File

SOURCE=..\src\objects\KParticle.h
# End Source File
# Begin Source File

SOURCE=..\src\objects\KSphere.h
# End Source File
# Begin Source File

SOURCE=..\src\objects\KText.h
# End Source File
# Begin Source File

SOURCE=..\src\objects\KVertex.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\objects\KBox.cpp
# End Source File
# Begin Source File

SOURCE=..\src\objects\KCamera.cpp
# End Source File
# Begin Source File

SOURCE=..\src\objects\KCylinder.cpp
# End Source File
# Begin Source File

SOURCE=..\src\objects\KDisk.cpp
# End Source File
# Begin Source File

SOURCE=..\src\objects\KFace.cpp
# End Source File
# Begin Source File

SOURCE=..\src\objects\KLandscape.cpp
# End Source File
# Begin Source File

SOURCE=..\src\objects\KLight.cpp
# End Source File
# Begin Source File

SOURCE=..\src\objects\KParticle.cpp
# End Source File
# Begin Source File

SOURCE=..\src\objects\KSphere.cpp
# End Source File
# Begin Source File

SOURCE=..\src\objects\KText.cpp
# End Source File
# Begin Source File

SOURCE=..\src\objects\KVertex.cpp
# End Source File
# End Group
# End Group
# End Target
# End Project
