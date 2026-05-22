#pragma once
#include "Button.h"
#include "Checkbox.h"

class UIFactory
{
public:
	virtual Button* createButton() const = 0;
	virtual Checkbox* createCheckbox() const = 0;
	virtual ~UIFactory() = default;
};
