
#include "Application.hpp"
#include "Logger.h"


int WinMain()
{
	Logger l;
	try
	{
		Application app;
		app.run();
	}
	catch (std::exception& e)
	{
		l.LogData(Logger::Sys, "Error: " + std::string(e.what()));
		//std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
	l.WriteLog();
	l.CloseLogger();
}
