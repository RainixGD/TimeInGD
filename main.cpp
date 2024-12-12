#include "./includes.h"

#include <extensions/cocos-ext.h>
#include <array>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <Windows.h>

using namespace cocos2d;

CCLabelBMFont* timeLabel;


void updateTimeLabel() {
	SYSTEMTIME time;
	GetLocalTime(&time);
	timeLabel->setString(
		(
			(int(time.wHour) < 10 ? "0" + std::to_string(time.wHour) : std::to_string(time.wHour)) + ":" +
			(int(time.wMinute) < 10 ? "0" + std::to_string(time.wMinute) : std::to_string(time.wMinute)) + ":" +
			(int(time.wSecond) < 10 ? "0" + std::to_string(time.wSecond) : std::to_string(time.wSecond))
		).c_str()
	);
}


class Loop {
public:
	void updateTimer(float dt) {
		if (timeLabel)
			updateTimeLabel();
	}
};



bool(__thiscall* menulayer)(CCLayer* self);
bool __fastcall menulayer_hk(CCLayer* self, void*) {
	if (!menulayer(self)) return false;
	SYSTEMTIME time;
	GetLocalTime(&time);
	timeLabel = CCLabelBMFont::create(
		(
			(int(time.wHour) < 10 ? "0" + std::to_string(time.wHour) : std::to_string(time.wHour)) + ":" + 
			(int(time.wMinute) < 10 ? "0" + std::to_string(time.wMinute) : std::to_string(time.wMinute)) + ":" +
			(int(time.wSecond) < 10 ? "0" + std::to_string(time.wSecond) : std::to_string(time.wSecond))
		).c_str(), "bigFont.fnt");
	timeLabel->setPosition({ CCDirector::sharedDirector()->getWinSize().width, CCDirector::sharedDirector()->getWinSize().height});
	timeLabel->setAnchorPoint({ 1.1,1.1 });
	timeLabel->setScale(0.5);
	self->addChild(timeLabel);
	self->schedule(schedule_selector(Loop::updateTimer), 1);
	return 1;
}




void inject() {
	#if _WIN32
	auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));
	
	MH_CreateHook(
		reinterpret_cast<void*>(base + 0x1907b0),
		reinterpret_cast<void*>(&menulayer_hk),
		reinterpret_cast<void**>(&menulayer)
	);

	MH_EnableHook(MH_ALL_HOOKS);
	#endif
}

#if _WIN32
	WIN32CAC_ENTRY(inject)
#endif
