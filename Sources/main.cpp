/*
 *	Shutdown Timer 
 */

#include "./Headers/func.h"

int main()
{
	Timer* App = InitializeApplication();

	bool EXIT_PROGRAM = 0;
	while (EXIT_PROGRAM == 0)
	{
		EXIT_PROGRAM = App->ProcessOption(App->SelectOption());
	}

	Terminate(App);
	return 0;
}