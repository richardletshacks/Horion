#include "Glide.h"

Glide::Glide() : IModule(0, Category::MOVEMENT, "Float down") {
	registerBoolSetting("Selfhurt", &this->selfhurt, this->selfhurt);
	registerFloatSetting("value", &this->glideMod, this->glideMod, -2, 1);
}

Glide::~Glide() {
}

void Glide::onEnable() {
	if (selfhurt) {
		g_Data.getLocalPlayer()->swing();
		g_Data.getCGameMode()->attack(g_Data.getLocalPlayer());
	}
}

const char* Glide::getModuleName() {
	if (isEnabled()) {
		static char modName[30];  // This is kinda ghetto rn, there should be a better way to make this...
		sprintf_s(modName, 30, "Glide [%.2f]", glideModEffective);
		return modName;
	} else
		return ("Glide");
}

void Glide::onTick(C_GameMode* gm) {
	glideModEffective = glideMod;
	C_GameSettingsInput* input = g_Data.getClientInstance()->getGameSettingsInput();

	if (g_Data.canUseMoveKeys()) {
		if (GameData::isKeyDown(*input->spaceBarKey))
			glideModEffective += 0.2f;
		if (GameData::isKeyDown(*input->sneakKey))
			glideModEffective -= 0.2f;
	}
	gm->player->velocity.y = glideModEffective;
}

const char* Glide::getRawModuleName() {
	return "Glide";
}
