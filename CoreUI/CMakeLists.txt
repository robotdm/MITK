SET(MITK_DEFAULT_SUBPROJECTS MITK-CoreUI)

IF(MITK_USE_QT AND QT4_FOUND)
  ADD_SUBDIRECTORY(Qmitk)
ENDIF()

IF(MITK_USE_BLUEBERRY)
  # BlueBerry depends on CTK which depends on Qt, so we
  # need the Qt include direcotries
  INCLUDE(${QT_USE_FILE})

  ADD_SUBDIRECTORY(Bundles)
  
  IF(MITK_ENABLE_GUI_TESTING AND BLUEBERRY_ENABLE_GUI_TESTING)
    ADD_SUBDIRECTORY(BundleTesting)
  ENDIF()
ENDIF()

