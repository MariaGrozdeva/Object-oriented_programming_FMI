#include "DarkThemeFactory.h"
#include "DarkButton.h"
#include "DarkCheckbox.h"

Button* DarkThemeFactory::createButton() const
{
	return new DarkButton();
}

Checkbox* DarkThemeFactory::createCheckbox() const
{
	return new DarkCheckbox();
}
