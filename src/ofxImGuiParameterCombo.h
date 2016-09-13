#pragma once
#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxImGuiUtils.h"

class ofxImGuiParameterCombo : public ofParameter<int>
{

public:
	ofxImGuiParameterCombo(ofxImGuiParameterCombo& copy)
		: stringRef(copy.getStringRef())
	{
	};

	ofxImGuiParameterCombo(ofParameter<string> & opt)
		: stringRef(opt)
	{
	};


	ofParameter<int> & setCombo(const int & val) {
		return setCombo(this->getName(), val, this->getMin(), this->getMax());
	};
	ofParameter<int> & setCombo(const string& name, const int & val) {
		return setCombo(name, val, this->getMin(), this->getMax());
	};
	ofParameter<int> & setCombo(const string& name, const int & val, const int & min, const int & max)
	{
		options = stringRef.get();
		value = val;

		//		OFXIMGUIPARAM_VERBOSE << "2 " << ofToString(options) << "]";
		int maximum = parseOptions(options);
		setName(name);
		set(value);
		setMin(0);
		setMax(maximum);

		OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
		OFXIMGUIPARAM_VERBOSE << "getValue [" << this->get() << "]";
		OFXIMGUIPARAM_VERBOSE << "getMin   [" << this->getMin() << "]";
		OFXIMGUIPARAM_VERBOSE << "getMax   [" << this->getMax() << "]";
		OFXIMGUIPARAM_VERBOSE << "getStringRef [" << this->getStringRef() << "]";
		OFXIMGUIPARAM_VERBOSE << "options  [" << options << "]";

		return *this;
	};

	//-----------
	void drawCombo()
	{
		getOfParameter();


		ImGui::PushID(this->getName().c_str());
		ImGui::PushItemWidth(sliderWidth);
		ImGui::Text(this->getName().c_str());
		// use vectors as const char *
		// https://github.com/ocornut/imgui/issues/673
		ImGui::Combo("##Combo", &value,
			[](void* vec, int idx, const char** out_text) {
			std::vector<std::string>* vector = reinterpret_cast<std::vector<std::string>*>(vec);
			if (idx < 0 || idx >= vector->size())return false;
			*out_text = vector->at(idx).c_str();
			return true;
		}, reinterpret_cast<void*>(&comboItems), comboItems.size());
		ImGui::PopItemWidth();
		ImGui::PopID();

		setOfParameter();
	}

	ofParameter<string>& getStringRef() {
		return stringRef;
	}

private:
	int	value;
	bool didChange = false;
	string options;
	ofParameter<string>& stringRef;
	vector<string> comboItems;
	int sliderWidth = 180;
	int inputIntWidth = 80;


	//-----------
	int parseOptions(string incoming_str) {
		if (incoming_str == "") {
			OFXIMGUIPARAM_VERBOSE << "string is empty!";
			return 0;
		}

		size_t pos = 0;
		size_t index = -1;
		std::string token;
		//		OFXIMGUIPARAM_VERBOSE << "3 " << ofToString(options) << "]";
		comboItems.clear();
		while (incoming_str.length() > 0) {
			if ((pos = incoming_str.find(OFXIMGUIPARAM_DELIMITER)) != std::string::npos) {
				token = incoming_str.substr(0, pos);
				OFXIMGUIPARAM_VERBOSE << "token " << token;
				comboItems.push_back(token);
				incoming_str.erase(0, pos + ((string)OFXIMGUIPARAM_DELIMITER).length());
				index++;
			}
			//get the last element if there is no delimiter at the end
			else {
				OFXIMGUIPARAM_VERBOSE << "token " << incoming_str;
				comboItems.push_back(incoming_str);
				incoming_str.clear();
				index++;
			}
		}

		return index;
	}

	//-----------
	bool getOfParameter()
	{
		didChange = false;
		if (this->get() != this->value)
		{
			value = this->get();
			OFXIMGUIPARAM_VERBOSE << "get Value [" << value << "]";
			didChange = true;
		}
		if (stringRef.get() != this->options)
		{
			options = stringRef;
			OFXIMGUIPARAM_VERBOSE << "get String [" << options << "]";
			// update
			setMax(parseOptions(options));

			OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "getValue [" << this->get() << "]";
			OFXIMGUIPARAM_VERBOSE << "getMin   [" << this->getMin() << "]";
			OFXIMGUIPARAM_VERBOSE << "getMax   [" << this->getMax() << "]";
			OFXIMGUIPARAM_VERBOSE << "getStringRef [" << this->getStringRef() << "]";

			didChange = true;
		}
		return didChange;
	}

	//-----------
	bool setOfParameter()
	{
		didChange = false;
		if (this->get() != this->value)
		{
			this->set(value);
			OFXIMGUIPARAM_VERBOSE << "getName  [" << this->getName() << "]";
			OFXIMGUIPARAM_VERBOSE << "[" << value << "]";
			didChange = true;
		}
		return didChange;
	}

};

