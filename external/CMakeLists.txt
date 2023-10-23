cmake_minimum_required(VERSION 3.24 FATAL_ERROR)


add_subdirectory(./solanaceae_util)
#add_subdirectory(./solanaceae_plugin)

add_subdirectory(./entt)

add_subdirectory(./solanaceae_contact)
add_subdirectory(./solanaceae_message3)

# TODO: move to clamav.cmake
find_package(PkgConfig QUIET)
if (PKG_CONFIG_FOUND)
	pkg_check_modules(PKGC_CLAMAV QUIET IMPORTED_TARGET GLOBAL libclamav)

	if (PKGC_CLAMAV_FOUND)
		add_library(EXT_SOL::libclamav ALIAS PkgConfig::PKGC_CLAMAV)
		message("II clamav found using pkg-config")
	endif()
endif()

if (NOT TARGET EXT_SOL::libclamav)
	include(FetchContent)
	set(ENABLE_LIBCLAMAV_ONLY ON)
	set(ENABLE_APP OFF)
	set(ENABLE_TESTS OFF)
	FetchContent_Declare(clamav
		GIT_REPOSITORY https://github.com/Cisco-Talos/clamav.git
		GIT_TAG clamav-1.2.0

		# find_package is tried first
		FIND_PACKAGE_ARGS NAMES clamav ClamAV libclamav libClamAV
	)

	FetchContent_MakeAvailable(clamav)

	add_library(EXT_SOL::libclamav ALIAS clamav)
endif()

