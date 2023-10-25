cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

add_library(plugin_clamav SHARED
	./plugin_clamav_module.cpp
)
target_compile_features(plugin_clamav PUBLIC cxx_std_17)
target_link_libraries(plugin_clamav PUBLIC
	solanaceae_clamav
	solanaceae_plugin
)

