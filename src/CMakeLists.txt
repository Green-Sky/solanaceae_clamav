cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

add_library(solanaceae_clamav
	# TODO: seperate interface lib
	./solanaceae/clamav/clamav_module_interface.hpp
	./solanaceae/clamav/clamav_module.hpp
	./solanaceae/clamav/clamav_module.cpp
)
target_include_directories(solanaceae_clamav PUBLIC .)
target_compile_features(solanaceae_clamav PUBLIC cxx_std_17)
target_link_libraries(solanaceae_clamav PUBLIC
	EXT_SOL::libclamav
	solanaceae_util
)

add_executable(solanaceae_clamav_test
	./solanaceae/clamav/test_exe.cpp
)
target_include_directories(solanaceae_clamav_test PUBLIC .)
target_compile_features(solanaceae_clamav_test PUBLIC cxx_std_17)
target_link_libraries(solanaceae_clamav_test PUBLIC
	solanaceae_clamav
	#solanaceae_util
)

