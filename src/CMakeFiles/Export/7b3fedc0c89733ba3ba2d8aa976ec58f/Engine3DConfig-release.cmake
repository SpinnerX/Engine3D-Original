#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Engine3D::Engine3D" for configuration "Release"
set_property(TARGET Engine3D::Engine3D APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Engine3D::Engine3D PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libEngine3D.a"
  )

list(APPEND _cmake_import_check_targets Engine3D::Engine3D )
list(APPEND _cmake_import_check_files_for_Engine3D::Engine3D "${_IMPORT_PREFIX}/lib/libEngine3D.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
