#pragma once

#include "./clamav_module_interface.hpp"

#include <future>

// non-blocking
struct ClamAVModuleAsyncInterface {
	using ScanResult = ClamAVModuleInterface::ScanResult;

	virtual std::future<ScanResult> scanFilePath(std::string_view path) = 0;

};

