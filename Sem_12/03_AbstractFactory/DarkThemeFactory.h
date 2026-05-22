#pragma once
#include "UIFactory.h"

class DarkThemeFactory : public UIFactory
{
public:
	Button* createButton() const override;
	Checkbox* createCheckbox() const override;
};
