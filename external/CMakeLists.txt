cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

include(FetchContent)

add_subdirectory(./solanaceae_util)

add_subdirectory(./entt)

if (NOT TARGET solanaceae_contact)
	FetchContent_Declare(solanaceae_contact
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_contact.git
		GIT_TAG master
	)
	FetchContent_MakeAvailable(solanaceae_contact)
endif()

if (NOT TARGET solanaceae_message3)
	FetchContent_Declare(solanaceae_message3
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_message3.git
		GIT_TAG master
	)
	FetchContent_MakeAvailable(solanaceae_message3)
endif()

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

# TODO: rename when plugin lib is split
if (NOT TARGET solanaceae_plugin)
	FetchContent_Declare(solanaceae_plugin
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_plugin.git
		GIT_TAG master
	)
	FetchContent_MakeAvailable(solanaceae_plugin)
endif()

