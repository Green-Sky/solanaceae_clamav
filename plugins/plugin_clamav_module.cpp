#include <solanaceae/plugin/solana_plugin_v1.h>

#include <solanaceae/clamav/clamav_module.hpp>
#include <solanaceae/util/config_model.hpp>

#include <memory>
#include <iostream>

#define RESOLVE_INSTANCE(x) static_cast<x*>(solana_api->resolveInstance(#x))
#define PROVIDE_INSTANCE(x, p, v) solana_api->provideInstance(#x, p, static_cast<x*>(v))

static std::unique_ptr<ClamAVModule> g_cavm = nullptr;

extern "C" {

SOLANA_PLUGIN_EXPORT const char* solana_plugin_get_name(void) {
	return "ClamAVModule";
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_get_version(void) {
	return SOLANA_PLUGIN_VERSION;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_start(struct SolanaAPI* solana_api) {
	std::cout << "PLUGIN CAVM START()\n";

	if (solana_api == nullptr) {
		return 1;
	}

	ConfigModelI* conf = nullptr;

	{ // make sure required types are loaded
		conf = RESOLVE_INSTANCE(ConfigModelI);

		if (conf == nullptr) {
			std::cerr << "PLUGIN CAVM missing ConfigModelI\n";
			return 2;
		}
	}

	// static store, could be anywhere tho
	// construct with fetched dependencies
	g_cavm = std::make_unique<ClamAVModule>(*conf);

	// register types
	PROVIDE_INSTANCE(ClamAVModule, "ClamAVModule", g_cavm.get());

	return 0;
}

SOLANA_PLUGIN_EXPORT void solana_plugin_stop(void) {
	std::cout << "PLUGIN CAVM STOP()\n";

	g_cavm.reset();
}

SOLANA_PLUGIN_EXPORT void solana_plugin_tick(float delta) {
	(void)delta;
	//std::cout << "PLUGIN CAVM TICK()\n";
	//g_cavm->iterate();
}

} // extern C

