#Begin Microsoft Kinect hardware
OPTION(MITK_USE_MSKINECT "Enable support for MS Kinect" OFF)
# only if PMD Camcube is enabled
IF(MITK_USE_MSKINECT)
  FIND_LIBRARY(MITK_MSKINECT_LIB CLNUIDevice DOC "Kinect access library.")
  GET_FILENAME_COMPONENT(MITK_KINECT_SDK_DIR ${MITK_MSKINECT_LIB} PATH)
  SET(MITK_KINECT_SDK_DIR ${MITK_KINECT_SDK_DIR}/..)
  FIND_PATH(MITK_KINECT_INCLUDE_DIR CLNUIDevice.h ${MITK_KINECT_SDK_DIR}/Include DOC  "Include directory of Kinect-SDK.")

  SET(INCLUDE_DIRS_INTERNAL ${INCLUDE_DIRS_INTERNAL} ${MITK_KINECT_INCLUDE_DIR})
  SET(ADDITIONAL_LIBS ${ADDITIONAL_LIBS} ${MITK_MSKINECT_LIB})
  LIST(APPEND ALL_INCLUDE_DIRECTORIES ${MITK_KINECT_INCLUDE_DIR})
  LIST(APPEND ALL_LIBRARIES ${MITK_MSKINECT_LIB})
  
  IF(WIN32) 
  MITK_INSTALL(FILES ${MITK_KINECT_SDK_DIR}/Lib/CLNUIDevice.dll CONFIGURATIONS Release)
  ENDIf(WIN32)
ENDIF(MITK_USE_MSKINECT)
#End Microsoft Kinect Hardware
