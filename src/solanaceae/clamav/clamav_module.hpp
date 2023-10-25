#pragma once

#include "./clamav_module_interface.hpp"

extern "C" {
	struct cl_engine;
}
struct ConfigModelI;

// blocking
class ClamAVModule : public ClamAVModuleInterface {
	ConfigModelI& _conf;
	cl_engine* _clamav_engine {nullptr};

	bool startEngine(void);

	public:
		ClamAVModule(ConfigModelI& conf);
		~ClamAVModule(void);

		ScanResult scanFilePath(std::string_view path) override;

};

