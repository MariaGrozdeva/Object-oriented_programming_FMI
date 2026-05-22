#pragma once
#include "UIFactory.h"

class LightThemeFactory : public UIFactory
{
public:
	Button* createButton() const override;
	Checkbox* createCheckbox() const override;
};
