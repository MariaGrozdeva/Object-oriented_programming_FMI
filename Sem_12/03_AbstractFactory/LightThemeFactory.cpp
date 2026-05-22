#include "LightThemeFactory.h"
#include "LightButton.h"
#include "LightCheckbox.h"

Button* LightThemeFactory::createButton() const
{
	return new LightButton();
}

Checkbox* LightThemeFactory::createCheckbox() const
{
	return new LightCheckbox();
}
