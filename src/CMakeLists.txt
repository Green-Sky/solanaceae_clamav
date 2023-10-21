cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

add_library(solanaceae_clamav
	./solanaceae/clamav/test_lib.cpp
)
target_include_directories(solanaceae_clamav PUBLIC .)
target_compile_features(solanaceae_clamav PUBLIC cxx_std_17)
target_link_libraries(solanaceae_clamav PUBLIC
	libclamav
	#solanaceae_util
)

