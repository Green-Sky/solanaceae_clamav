cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

add_library(solanaceae_clamav_interface INTERFACE
	./solanaceae/clamav/clamav_module_interface.hpp
)
target_include_directories(solanaceae_clamav_interface INTERFACE .)
target_compile_features(solanaceae_clamav_interface INTERFACE cxx_std_17)

########################################

add_library(solanaceae_clamav
	./solanaceae/clamav/clamav_module.hpp
	./solanaceae/clamav/clamav_module.cpp
)
target_include_directories(solanaceae_clamav PUBLIC .)
target_compile_features(solanaceae_clamav PUBLIC cxx_std_17)
target_link_libraries(solanaceae_clamav PUBLIC
	solanaceae_clamav_interface
	EXT_SOL::libclamav
	solanaceae_util
)

########################################

add_library(solanaceae_clamav_async_interface INTERFACE
	./solanaceae/clamav/clamav_module_async_interface.hpp
)
target_include_directories(solanaceae_clamav_async_interface INTERFACE .)
target_compile_features(solanaceae_clamav_async_interface INTERFACE cxx_std_17)

########################################

add_library(solanaceae_clamav_async_wrapper
	./solanaceae/clamav/clamav_module_async_wrapper.hpp
	./solanaceae/clamav/clamav_module_async_wrapper.cpp
)
target_link_libraries(solanaceae_clamav_async_wrapper PUBLIC
	solanaceae_clamav_interface
	solanaceae_clamav_async_interface
)

########################################

if (SOLANACEAE_CLAMAV_STANDALONE)

	add_executable(solanaceae_clamav_test
		./solanaceae/clamav/test_exe.cpp
	)
	target_include_directories(solanaceae_clamav_test PUBLIC .)
	target_compile_features(solanaceae_clamav_test PUBLIC cxx_std_17)
	target_link_libraries(solanaceae_clamav_test PUBLIC
		solanaceae_clamav
		#solanaceae_util
	)

endif()

