PROJECT(MbiLogExample)
FIND_PACKAGE(MITK)
INCLUDE_DIRECTORIES(${MITK_INCLUDE_DIRS})
LINK_DIRECTORIES(${MITK_LINK_DIRECTORIES})
ADD_EXECUTABLE(MitkLogExample MitkLogExample.cpp)
TARGET_LINK_LIBRARIES(MitkLogExample ${MITK_LIBRARIES})

