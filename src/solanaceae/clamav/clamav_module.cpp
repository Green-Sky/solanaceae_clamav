#include "./clamav_module.hpp"

#include <clamav.h>

#include <iostream>
#include <stdexcept>

extern "C" {
	void sol_cl_msg_cb(enum cl_msg severity, const char *fullmsg, const char *msg, void *context);
};

ClamAVModule::ClamAVModule(void) {
	if (cl_init(CL_INIT_DEFAULT) != CL_SUCCESS) {
		throw std::domain_error("clamav cl_init() failed");
	}

	cl_set_clcb_msg(sol_cl_msg_cb);
}

ClamAVModule::~ClamAVModule(void) {
	if (_clamav_engine != nullptr) {
		cl_engine_free(_clamav_engine);
		_clamav_engine = nullptr;
	}
}

bool ClamAVModule::startEngine(void) {
	if (_clamav_engine != nullptr) {
		// already loaded
		return true;
	}

	_clamav_engine = cl_engine_new();
	if (_clamav_engine == nullptr) {
		return false;
	}

	std::string db_dir;
	// TODO: load from config

	unsigned int signo = 0;

	if (db_dir.empty()) {
		std::cout << "default db dir: " << cl_retdbdir() << "\n";
		if (cl_load(cl_retdbdir(), _clamav_engine, &signo, CL_DB_STDOPT) != CL_SUCCESS) {
			std::cerr << "default db dir load failed, falling back to '/var/lib/clamav'\n";
			if (cl_load("/var/lib/clamav", _clamav_engine, &signo, CL_DB_STDOPT) != CL_SUCCESS) {
				std::cerr << "db dir load failed, exiting\n";
				cl_engine_free(_clamav_engine);
				_clamav_engine = nullptr;
				return false;
			} else {
				db_dir = "/var/lib/clamav";
			}
		} else {
			db_dir = cl_retdbdir();
		}
		// if db_dir changed, save to config?
	} else {
		if (cl_load(db_dir.c_str(), _clamav_engine, &signo, CL_DB_STDOPT) != CL_SUCCESS) {
			std::cerr << "config db dir load failed, exiting (" << db_dir << ")\n";
			cl_engine_free(_clamav_engine);
			_clamav_engine = nullptr;
			return false;
		}
	}

	std::cout << "signatures loaded: " << signo << "\n";

	if (cl_engine_compile(_clamav_engine) != CL_SUCCESS) {
		cl_engine_free(_clamav_engine);
		_clamav_engine = nullptr;
		return false;
	}

	return true;
}

ClamAVModule::ScanResult ClamAVModule::scanFilePath(std::string_view path) {
	// makeing sure engine is running
	if (!startEngine()) {
		return ScanResult{};
	}

	const char* virname = nullptr;
	unsigned long int scanned = 0;

	struct cl_scan_options scan_opts {
		/*CL_SCAN_GENERAL_ALLMATCHES |*/ CL_SCAN_GENERAL_HEURISTICS | CL_SCAN_GENERAL_HEURISTIC_PRECEDENCE,
		~0u,
		~0u,
		0u,
		0u
	};

	std::string path_cpy {path};
	if (
		auto ret = cl_scanfile(
			path_cpy.c_str(),
			&virname,
			&scanned,
			_clamav_engine,
			&scan_opts
		)
		;
		ret != CL_CLEAN && ret != CL_VIRUS) {
		// error
		return ScanResult{false, std::string{"error: "} + cl_strerror(ret)};
	} else if (ret == CL_VIRUS) {
		std::cout << "file virus\n";
		return ScanResult{true, virname};
	} else { // clean
		std::cout << "file clean\n";
		return ScanResult{false, "no virus detected"};
	}
}

void sol_cl_msg_cb(enum cl_msg severity, const char *fullmsg, const char *msg, void *context) {
	(void)msg;
	(void)context;
	std::cout << severity << " " << fullmsg << "\n";
}

