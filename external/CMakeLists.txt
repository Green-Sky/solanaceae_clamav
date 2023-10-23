cmake_minimum_required(VERSION 3.24 FATAL_ERROR)


add_subdirectory(./solanaceae_util)
#add_subdirectory(./solanaceae_plugin)

add_subdirectory(./entt)

add_subdirectory(./solanaceae_contact)
add_subdirectory(./solanaceae_message3)

# TODO: move to clamav.cmake
find_package(PkgConfig QUIET)
if (PKG_CONFIG_FOUND)
	pkg_check_modules(PKGC_CLAMAV QUIET IMPORTED_TARGET libclamav)

	if (PKGC_CLAMAV_FOUND)
		add_library(libclamav ALIAS PkgConfig::PKGC_CLAMAV)
		message("II libclamav found using pkg-config")
	endif()
endif()

if (NOT TARGET libclamav)
	find_package(clamav)
	if (TARGET clamav)
		message("------ find_package(clamav) found")
	else()
		find_package(libclamav)
		if (TARGET libclamav)
			message("------ find_package(libclamav) found")
		else()
			find_package(clamav CONFIG)
			if (TARGET clamav)
				message("------ find_package(clamav CONFIG) found")
			else()
				find_package(libclamav CONFIG REQUIRED)
			endif()
		endif()
	endif()

	#set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE ALWAYS)
	#include(FetchContent)
	#set(ENABLE_LIBCLAMAV_ONLY ON)
	#set(ENABLE_APP OFF)
	#set(ENABLE_TESTS OFF)
	#FetchContent_Declare(clamav
		#GIT_REPOSITORY https://github.com/Cisco-Talos/clamav.git
		#GIT_TAG clamav-1.2.0

		## find_package is tried first
		#FIND_PACKAGE_ARGS
	#)

	#FetchContent_MakeAvailable(clamav)
endif()

