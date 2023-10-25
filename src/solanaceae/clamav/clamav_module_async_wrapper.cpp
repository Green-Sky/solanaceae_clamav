#include "./clamav_module_async_wrapper.hpp"

#include <cstdlib>

ClamAVModuleAsyncWrapper::ClamAVModuleAsyncWrapper(ClamAVModuleInterface& cavmi) : _cavmi(cavmi) {
}

std::future<ClamAVModuleAsyncWrapper::ScanResult> ClamAVModuleAsyncWrapper::scanFilePath(std::string_view path) {
	return std::async(
		std::launch::async,
		[this](std::string inner_path) {
			std::srand(5693);
			// TODO: optimize, clamav supports multi threading
			std::lock_guard lock_guard{_cavmi_mutex};
			return _cavmi.scanFilePath(inner_path);
		},
		std::string{path} // copy
	);
}

