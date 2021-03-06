PROJECT(BlueBerryPluginGenerator)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
MARK_AS_ADVANCED(
CMAKE_BACKWARDS_COMPATIBILITY CMAKE_INSTALL_PREFIX CMAKE_BUILD_TYPE)

FIND_FILE(PLUGIN_TEMPLATE BundleTemplate
          ${PROJECT_SOURCE_DIR}/../../CMake
          DOC "Path to the plugin templates")

IF(BUNDLE_DEFAULTS_FILE)
  IF(EXISTS "${BUNDLE_DEFAULTS_FILE}")
    INCLUDE(${BUNDLE_DEFAULTS_FILE})
  ELSE(EXISTS "${BUNDLE_DEFAULTS_FILE}")
    MESSAGE(SEND_ERROR "cannot find supplied defaults file: ${BUNDLE_DEFAULTS_FILE}")
  ENDIF(EXISTS "${BUNDLE_DEFAULTS_FILE}")
ELSE(BUNDLE_DEFAULTS_FILE)
  INCLUDE(${PLUGIN_TEMPLATE}/BundleDefaults.cmake)
ENDIF(BUNDLE_DEFAULTS_FILE)

SET(PLUGIN_ID "${DEFAULT_PLUGIN_ID}" CACHE STRING "unique plugin id (i.e. your.domain.pluginid) (required)")
SET(PLUGIN_NAME "" CACHE STRING "a human-readable description of your plugin (required)")
SET(CUSTOM_PROJECT_NAME "" CACHE STRING "Your project name (optional)")
OPTION(GUI_SUPPORT "enable this if your plugin contributes to the UI" ON)

STRING(REPLACE " " "" CUSTOM_PROJECT_NAME_NOWS "${CUSTOM_PROJECT_NAME}")
SET(CUSTOM_PROJECT_NAME "${CUSTOM_PROJECT_NAME_NOWS}" CACHE STRING "Your project name (optional)" FORCE)


IF(PLUGIN_ID AND PLUGIN_NAME)

SET(PLUGIN_VERSION "${DEFAULT_PLUGIN_VERSION}" CACHE STRING "plugin version (required)")
SET(PLUGIN_VENDOR "${DEFAULT_PLUGIN_VENDOR}" CACHE STRING "plugin vendor (optional)")

SET(ACTIVATOR_CLASS "" CACHE STRING "class name for your plugin activator (optional)")

IF(GUI_SUPPORT)

  STRING(REGEX REPLACE "[^a-zA-Z_]" "" _view_baseid "${PLUGIN_NAME}")
  STRING(TOLOWER ${_view_baseid} _lview_baseid)

  SET(_default_view_class_name "${DEFAULT_VIEW_CLASS_BEGIN}${_view_baseid}View")

  SET(VIEW_NAME "${PLUGIN_NAME}" CACHE STRING "a human-readable name of your view (required)")
  SET(VIEW_CLASS "${_default_view_class_name}" CACHE STRING "class name of the view")
  IF(VIEW_CLASS)
    STRING(TOUPPER ${VIEW_CLASS} UVIEW_CLASS)
  ENDIF(VIEW_CLASS)
  SET(VIEW_BASE_CLASS ${DEFAULT_VIEW_BASE_CLASS} CACHE STRING "base class of your new view class (required)")
  SET(VIEW_BASE_CLASS_H ${DEFAULT_VIEW_BASE_CLASS_H} CACHE STRING "base class header (required)")

  SET(VIEW_ID "${DEFAULT_VIEW_BASEID}${_lview_baseid}" CACHE STRING "unique view id (i.e. your.domain.viewid) (required)")

  #SET(EDITOR_CLASS "" CACHE STRING "")
  #SET(EDITOR_TYPE "" CACHE STRING "")
ENDIF(GUI_SUPPORT)

#SET(GENERATE_SERVICE "" CACHE STRING "")
#SET(GENERATE_SERVICE_CLASS "" CACHE STRING "")

SET(_required_bundles ${DEFAULT_REQUIRED_BUNDLES})
IF(GUI_SUPPORT)
  SET(_required_bundles ${DEFAULT_REQUIRED_BUNDLES_FOR_GUI})
ENDIF(GUI_SUPPORT)
SET(REQUIRED_PLUGINS ${_required_bundles} CACHE STRING "a semicolon-separated list of required plugins (optional)")

IF(ACTIVATOR_CLASS)
  SET(FULLY_QUALIFIED_ACTIVATOR "${BUNDLE_NAMESPACE}::${ACTIVATOR_CLASS}")
    STRING(TOUPPER ${ACTIVATOR_CLASS} UACTIVATOR_CLASS)
    IF(GUI_SUPPORT)
      SET(ACTIVATOR_BASE_CLASS "berry::AbstractUIPlugin")
      SET(ACTIVATOR_BASE_CLASS_H "berryAbstractUIPlugin.h")
    ELSE()
      SET(ACTIVATOR_BASE_CLASS "berry::Plugin")
      SET(ACTIVATOR_BASE_CLASS_H "berryPlugin.h")
    ENDIF()
ELSE(ACTIVATOR_CLASS)
  SET(FULLY_QUALIFIED_ACTIVATOR "")
ENDIF(ACTIVATOR_CLASS)

SET(PROJECT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CUSTOM_PROJECT_NAME}")
IF(CUSTOM_PROJECT_NAME)
  SET(PLUGIN_DIR "${PROJECT_DIR}/Bundles/${PLUGIN_ID}")
ELSE(CUSTOM_PROJECT_NAME)
  SET(PLUGIN_DIR "${PROJECT_DIR}/${PLUGIN_ID}")
ENDIF(CUSTOM_PROJECT_NAME)

IF(NOT EXISTS "${PLUGIN_TEMPLATE}/META-INF/MANIFEST_TEMPLATE.MF")
  MESSAGE(FATAL_ERROR "Could not find ${PLUGIN_TEMPLATE}/META-INF/MANIFEST_TEMPLATE.MF!")
ENDIF(NOT EXISTS "${PLUGIN_TEMPLATE}/META-INF/MANIFEST_TEMPLATE.MF")

# ====================== PROJECT FILES ===============================

IF(CUSTOM_PROJECT_NAME AND EXISTS "${PLUGIN_TEMPLATE}/project/CMakeListsTemplate.txt")

    SET(CUSTOM_PROJECT_EXECUTABLE ${CUSTOM_PROJECT_NAME} CACHE STRING "the name of your project's executable")

    IF(GUI_SUPPORT)
      SET(FIND_PACKAGE_QT4 "FIND_PACKAGE(Qt4 REQUIRED)")
    ENDIF(GUI_SUPPORT)

    SET(BLUEBERRY_BINARY_DIR "@BLUEBERRY_BINARY_DIR@")
    SET(BLUEBERRY_PLUGINS_OUTPUT_DIR "@BLUEBERRY_PLUGINS_OUTPUT_DIR@")
    SET(PLUGIN_CACHE_DIR "@PLUGIN_CACHE_DIR@")
    SET(PLUGIN_BINARY_DIRS "@PLUGIN_BINARY_DIRS@")
    SET(MITK_PLUGIN_BINARY_DIRS "@MITK_PLUGIN_BINARY_DIRS@")

    SET(BATCH_FILE_PATH "@MITK_RUNTIME_PATH@;@CMAKE_RUNTIME_OUTPUT_DIRECTORY@/@VS_BUILD_TYPE@")
    SET(BATCH_FILE_VS_PATH ${BATCH_FILE_PATH})
    SET(BATCH_FILE_EXEC_CMD "@APP_BUILD_TYPE@\\${CUSTOM_PROJECT_EXECUTABLE}.exe")
    SET(BATCH_FILE_VS_EXEC_CMD "\@PROJECT_BINARY_DIR\@/${CUSTOM_PROJECT_NAME}.sln")

    CONFIGURE_FILE("${PLUGIN_TEMPLATE}/project/CMakeListsTemplate.txt"
                   "${PROJECT_DIR}/CMakeLists.txt" @ONLY)
                   
    CONFIGURE_FILE("${PLUGIN_TEMPLATE}/project/Bundles/CMakeListsTemplate.txt"
                   "${PROJECT_DIR}/Bundles/CMakeLists.txt" @ONLY)

    CONFIGURE_FILE("${PLUGIN_TEMPLATE}/project/AppTemplate.cpp"
                   "${PROJECT_DIR}/${CUSTOM_PROJECT_EXECUTABLE}.cpp" @ONLY)

    CONFIGURE_FILE("${PLUGIN_TEMPLATE}/project/AppTemplate.ini"
                   "${PROJECT_DIR}/${CUSTOM_PROJECT_EXECUTABLE}.ini" COPYONLY)

    CONFIGURE_FILE("${PLUGIN_TEMPLATE}/project/startAppTemplate.bat"
                   "${PROJECT_DIR}/start${CUSTOM_PROJECT_EXECUTABLE}.bat.in" @ONLY)
                   
    CONFIGURE_FILE("${PLUGIN_TEMPLATE}/project/startVS2008Template.bat"
                   "${PROJECT_DIR}/startVS2008.bat.in" @ONLY)

ENDIF()


# ====================== END PROJECT FILES ===========================


STRING(REPLACE . _ NormalizedPluginID ${PLUGIN_ID})
STRING(TOUPPER ${NormalizedPluginID} UNormalizedPluginID)

# ----- START cut plugin_ID from last '.' till end ------------
SET(LAST_PART_PLUGIN_ID ${PLUGIN_ID})
STRING(REGEX MATCH "\\.[^\\.]*$" LAST_PART_PLUGIN_ID ${LAST_PART_PLUGIN_ID})
STRING(LENGTH ${LAST_PART_PLUGIN_ID} LengthStr)
MATH(EXPR LengthStr "${LengthStr}-1")
STRING(SUBSTRING ${LAST_PART_PLUGIN_ID} 1 ${LengthStr} LAST_PART_PLUGIN_ID)
MATH(EXPR LengthStr "${LengthStr}-1")
STRING(SUBSTRING ${LAST_PART_PLUGIN_ID} 0 1 LAST_PART_PLUGIN_ID_FIRST_LETTER)
STRING(TOUPPER ${LAST_PART_PLUGIN_ID_FIRST_LETTER} LAST_PART_PLUGIN_ID_FIRST_LETTER)
STRING(SUBSTRING ${LAST_PART_PLUGIN_ID} 1 ${LengthStr} LAST_PART_PLUGIN_ID_REST)
SET(LAST_PART_PLUGIN_ID ${LAST_PART_PLUGIN_ID_FIRST_LETTER}${LAST_PART_PLUGIN_ID_REST})
STRING(TOUPPER ${LAST_PART_PLUGIN_ID} ULAST_PART_PLUGIN_ID)
# ------ END --------------------------------------------------


# --------------------- META-INF/MANIFEST_TEMPLATE.MF ---------------------
SET(REQUIRED_PLUGINS_MF "${REQUIRED_PLUGINS}")
STRING(REPLACE ";" "," REQUIRED_PLUGINS_MF "${REQUIRED_PLUGINS_MF}" )
CONFIGURE_FILE(${PLUGIN_TEMPLATE}/META-INF/MANIFEST_TEMPLATE.MF ${PLUGIN_DIR}/META-INF/MANIFEST.MF @ONLY)

# ----------------- documentation/doxygen/modulesTemplate.dox ------------
IF(DOXYGEN_INGROUP)
  SET(DOXYGEN_INGROUP_CMD "\\ingroup ${DOXYGEN_INGROUP}")
ENDIF(DOXYGEN_INGROUP)
CONFIGURE_FILE(${PLUGIN_TEMPLATE}/documentation/doxygen/modulesTemplate.dox
               ${PLUGIN_DIR}/documentation/doxygen/modules.dox @ONLY)

# ----------------- documentation/Manual/Manual.dox ------------
CONFIGURE_FILE(${PLUGIN_TEMPLATE}/documentation/Manual/Manual.dox
               ${PLUGIN_DIR}/documentation/Manual/Manual.dox @ONLY)
CONFIGURE_FILE(${PLUGIN_TEMPLATE}/documentation/Manual/icon.png 
               ${PLUGIN_DIR}/documentation/Manual/icon.png @ONLY)

# ----------------- resources directory ---------------------------------
IF(GUI_SUPPORT)
  FILE(MAKE_DIRECTORY ${PLUGIN_DIR}/resources)
  IF(EXISTS ${PLUGIN_TEMPLATE}/resources/qtresources.qrc)
    CONFIGURE_FILE(${PLUGIN_TEMPLATE}/resources/qtresources.qrc ${PLUGIN_DIR}/resources/${VIEW_CLASS}.qrc @ONLY)
  ENDIF(EXISTS ${PLUGIN_TEMPLATE}/resources/qtresources.qrc)

  IF(EXISTS ${PLUGIN_TEMPLATE}/resources/icon.xpm)
    CONFIGURE_FILE(${PLUGIN_TEMPLATE}/resources/icon.xpm ${PLUGIN_DIR}/resources/icon.xpm @ONLY)
  ENDIF(EXISTS ${PLUGIN_TEMPLATE}/resources/icon.xpm)
ENDIF()


# -------------------- BundleDllTemplate.h -------------------------------
IF(EXISTS ${PLUGIN_TEMPLATE}/src/BundleDllTemplate.h)
  IF(BUNDLE_NAMESPACE)
    STRING(TOUPPER ${BUNDLE_NAMESPACE} UBUNDLE_NAMESPACE)
  ENDIF(BUNDLE_NAMESPACE)
  IF(UBUNDLE_NAMESPACE)
    SET(DLL_DEFINE "${UBUNDLE_NAMESPACE}_${ULAST_PART_PLUGIN_ID}_EXPORT")
  ELSE(UBUNDLE_NAMESPACE)
    SET(DLL_DEFINE "${ULAST_PART_PLUGIN_ID}_EXPORT")
  ENDIF(UBUNDLE_NAMESPACE)


  SET(Dll_HEADER ${BUNDLE_NAMESPACE}${LAST_PART_PLUGIN_ID}Dll.h)
  CONFIGURE_FILE(${PLUGIN_TEMPLATE}/src/BundleDllTemplate.h ${PLUGIN_DIR}/src/${Dll_HEADER} @ONLY)
ENDIF(EXISTS ${PLUGIN_TEMPLATE}/src/BundleDllTemplate.h)


# --------------------- src/internal/ViewTemplateControls.ui ----------------------------
IF (GUI_SUPPORT)
  IF(EXISTS ${PLUGIN_TEMPLATE}/src/internal/ControlsTemplate.ui)
    SET(VIEW_CONTROLS "${VIEW_CLASS}Controls")
    SET(VIEW_CONTROLS_UI "${VIEW_CONTROLS}.ui")
    SET(VIEW_CONTROLS_FILE "ui_${VIEW_CONTROLS}.h")
    SET(VIEW_CONTROLS_CLASS "${VIEW_CONTROLS}")

    CONFIGURE_FILE(${PLUGIN_TEMPLATE}/src/internal/ControlsTemplate.ui ${PLUGIN_DIR}/src/internal/${VIEW_CONTROLS_UI} @ONLY)
  ENDIF(EXISTS ${PLUGIN_TEMPLATE}/src/internal/ControlsTemplate.ui)
ENDIF()

# --------------------- src/internal/ViewTemplate[.h,.cpp] ----------------------------
IF(VIEW_CLASS)
  SET(VIEW_CLASS_H "${BUNDLE_NAMESPACE}${VIEW_CLASS}.h")
  SET(VIEW_CLASS_CPP "${BUNDLE_NAMESPACE}${VIEW_CLASS}.cpp")

  IF(BUNDLE_NAMESPACE)
    SET(BEGIN_NAMESPACE "namespace ${BUNDLE_NAMESPACE} {")
    SET(END_NAMESPACE "} //namespace ${BUNDLE_NAMESPACE}")
  ENDIF(BUNDLE_NAMESPACE)
  CONFIGURE_FILE(${PLUGIN_TEMPLATE}/src/internal/ViewTemplate.h ${PLUGIN_DIR}/src/internal/${VIEW_CLASS_H} @ONLY)
  CONFIGURE_FILE(${PLUGIN_TEMPLATE}/src/internal/ViewTemplate.cpp ${PLUGIN_DIR}/src/internal/${VIEW_CLASS_CPP} @ONLY)
ENDIF(VIEW_CLASS)

# ---------------------- pluginTemplate.xml ---------------------------------
IF(VIEW_CLASS)
  SET(XP_VIEW "  <extension point=\"org.blueberry.ui.views\">
    <view id=\"${VIEW_ID}\"
          name=\"${VIEW_NAME}\"
          class=\"${BUNDLE_NAMESPACE}::${VIEW_CLASS}\" 
          icon=\"resources/icon.xpm\" />
  </extension>"
)
ENDIF(VIEW_CLASS)
CONFIGURE_FILE(${PLUGIN_TEMPLATE}/pluginTemplate.xml ${PLUGIN_DIR}/plugin.xml @ONLY)

# ----------------------- ActivatorTemplate[.h,.cpp] ------------------------
IF(ACTIVATOR_CLASS)
  SET(ACTIVATOR_CLASS_H "${BUNDLE_NAMESPACE}${ACTIVATOR_CLASS}.h")
  SET(ACTIVATOR_CLASS_CPP "${BUNDLE_NAMESPACE}${ACTIVATOR_CLASS}.cpp")
  
  IF(BUNDLE_NAMESPACE)
    SET(BEGIN_NAMESPACE "namespace ${BUNDLE_NAMESPACE} {")
    SET(END_NAMESPACE "} //namespace ${BUNDLE_NAMESPACE}")
  ENDIF(BUNDLE_NAMESPACE)
  CONFIGURE_FILE(${PLUGIN_TEMPLATE}/src/internal/ActivatorTemplate.h ${PLUGIN_DIR}/src/internal/${ACTIVATOR_CLASS_H} @ONLY)
  CONFIGURE_FILE(${PLUGIN_TEMPLATE}/src/internal/ActivatorTemplate.cpp ${PLUGIN_DIR}/src/internal/${ACTIVATOR_CLASS_CPP} @ONLY)
ENDIF()

# ----------------------- manifestTemplate.cpp ----------------------------
IF(VIEW_CLASS)
  SET(SET_MANIFEST_SRC "SET(CPP_FILES manifest.cpp)")
  SET(MANIFEST_VIEW_ENTRY "#include \"src/internal/${VIEW_CLASS_H}\"

POCO_BEGIN_NAMED_MANIFEST(berryIViewPart, berry::IViewPart)
  POCO_EXPORT_CLASS(${BUNDLE_NAMESPACE}::${VIEW_CLASS})
POCO_END_MANIFEST")
ENDIF(VIEW_CLASS)

IF(ACTIVATOR_CLASS)
  SET(SET_MANIFEST_SRC "SET(CPP_FILES manifest.cpp)")
  SET(MANIFEST_ACTIVATOR_ENTRY "#include \"src/internal/${ACTIVATOR_CLASS_H}\"

POCO_BEGIN_MANIFEST(berry::IBundleActivator)
  POCO_EXPORT_CLASS(${BUNDLE_NAMESPACE}::${ACTIVATOR_CLASS})
POCO_END_MANIFEST")
ENDIF()

IF(VIEW_CLASS OR ACTIVATOR_CLASS)
  CONFIGURE_FILE(${PLUGIN_TEMPLATE}/manifestTemplate.cpp ${PLUGIN_DIR}/manifest.cpp @ONLY)
ENDIF()

# ---------------------- CMakeListsTemplate.txt -----------------------------
SET(CREATE_PLUGIN_MACRO "${DEFAULT_CREATE_PLUGIN_MACRO}")
IF(GUI_SUPPORT)
  SET(CREATE_PLUGIN_MACRO "${DEFAULT_CREATE_GUI_PLUGIN_MACRO}")
ENDIF(GUI_SUPPORT)

CONFIGURE_FILE(${PLUGIN_TEMPLATE}/CMakeListsTemplate.txt ${PLUGIN_DIR}/CMakeLists.txt @ONLY)

# ---------------------- filesTemplate.cmake ------------------------------
SET(PLUGIN_SOURCES "")
SET(PLUGIN_INTERNAL_SOURCES "")
IF(VIEW_CLASS)
  SET(PLUGIN_INTERNAL_SOURCES "${PLUGIN_INTERNAL_SOURCES}${VIEW_CLASS_CPP}\n")
ENDIF(VIEW_CLASS)
IF(ACTIVATOR_CLASS)
  SET(PLUGIN_INTERNAL_SOURCES "${PLUGIN_INTERNAL_SOURCES}${ACTIVATOR_CLASS_CPP}\n")
ENDIF(ACTIVATOR_CLASS)
IF(GUI_SUPPORT AND EXISTS ${PLUGIN_TEMPLATE}/src/internal/ControlsTemplate.ui)
  SET(PLUGIN_RESOURCE_FILES "resources/icon.xpm")
  SET(PLUGIN_RES_FILES "resources/${VIEW_CLASS}.qrc")
  SET(PLUGIN_UI_FILES "src/internal/${VIEW_CONTROLS_UI}")
  SET(PLUGIN_MOC_H_FILES "src/internal/${VIEW_CLASS}.h")
ENDIF()

CONFIGURE_FILE(${PLUGIN_TEMPLATE}/filesTemplate.cmake ${PLUGIN_DIR}/files.cmake @ONLY)

ENDIF(PLUGIN_ID AND PLUGIN_NAME)
