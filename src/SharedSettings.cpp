#include "SharedSettings.h"

SharedSettings::SharedSettings() {

	// Asio and Squash Params
	initParams.setName("init shared settings");
	initParams.add(asioIP.set("asioIP", "127.0.0.1"));
	initParams.add(asioPort.set("asioPort", 4444));
	initParams.add(codecName.set("codecName", "copy"));
	// ParameterSync Params	
	initParams.add(paramSyncIP.set("paramSyncIP", "localhost"));
	initParams.add(paramSyncServerPort.set("paramSyncServerPort", 6667));
	initParams.add(paramSyncClientPort.set("paramSyncClientPort", 6666));

	//-----------
	// syncParams
	syncParams.setName("sync shared settings");
	syncParams.add(imageFrameRate.set("Image Transfer Rate", 1, 1, 1000));

	//-----------
	// tests
	syncParams.add(float_t.set("float test", 0.5f, 0.0f, 1.0f));
	syncParams.add(int_t.set("int test", 1, 1, 1000));
	syncParams.add(float_t1.set("float test 11111", 0.2f, 0.0f, 1.0f));
	syncParams.add(int_t1.set("int test 11111", 1234, 1, 1000));

	syncParams.add(bool_t.set("bool test", true));
	syncParams.add(OSD_string_t.set("OSD text", "lorem ipsum", "a", "aaaa"));
	syncParams.add(button_t.set("button test", false));
	syncParams.add(Input_string_t.set("Input text field", "try to edit string"));

	string items = "Aaaaaaa||bbbbbbbb||ccccccc||dddddddddd||eeeeeeee||fffffffff||gggggggggggg||hhhhhhhh";
	syncParams.add(combo_options_t.set("combo options", items));
	syncParams.add(combo_value_t.setCombo("combo value", 1));
}
/*
bool SharedSettings::addListeners(* camera) {
	bool success;

	sharedSettings.imageFrameRate.addListener(&camera, &Camera::setImageFramerate);

	return success;
}
*/