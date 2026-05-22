#include "UIFactory.h"
#include "DarkThemeFactory.h"
#include "LightThemeFactory.h"

void renderUI(const UIFactory& factory)
{
	Button* button = factory.createButton();
	Checkbox* checkbox = factory.createCheckbox();

	button->render();
	checkbox->render();

	delete button;
	delete checkbox;
}

int main()
{
	DarkThemeFactory darkFactory;
	LightThemeFactory lightFactory;

	std::cout << "--- Dark theme ---" << std::endl;
	renderUI(darkFactory);

	std::cout << "--- Light theme ---" << std::endl;
	renderUI(lightFactory);
}
