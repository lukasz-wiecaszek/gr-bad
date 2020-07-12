INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_BAD bad)

FIND_PATH(
    BAD_INCLUDE_DIRS
    NAMES bad/api.h
    HINTS $ENV{BAD_DIR}/include
        ${PC_BAD_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    BAD_LIBRARIES
    NAMES gnuradio-bad
    HINTS $ENV{BAD_DIR}/lib
        ${PC_BAD_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/badTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(BAD DEFAULT_MSG BAD_LIBRARIES BAD_INCLUDE_DIRS)
MARK_AS_ADVANCED(BAD_LIBRARIES BAD_INCLUDE_DIRS)
