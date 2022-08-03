#include "./Headers/timer.h"

void Timer::Config()
{
	short Attempts = 0;
	while (true)
	{
		std::ifstream cFile("settings.cfg");	//	Ifstream for reading
		if (cFile.is_open()) //	Check if the file "server.cfg" is exists
		{
			std::string line;
			while (std::getline(cFile, line))
			{
				//line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end()); | Remove all whitespaces on line
				if (line[0] == '#' || line.empty()) continue; // Ignore lines start with '#' or empty lines

				auto delimiterPos = line.find("=");
				auto name = line.substr(0, delimiterPos);
				auto value = line.substr(delimiterPos + 1);
				if (value[0] == ' ') value = line.substr(delimiterPos + 2);

				//	Scan and read data from file
				if (name == "Language" || name == "Language ") { if (value == "vi" || value == "vn" || value == "vie") this->Language = "vi"; }
				else if (name == "FasterLoad" || name == "FasterLoad ") { if (value == "1" || value == "true" || value == "on" || value == "yes") this->FasterLoad = true; }
				else if (name == "EnableConsoleSelection" || name == "EnableConsoleSelection ") { if (value == "1" || value == "true" || value == "on" || value == "yes") this->EnableConsoleSelection = true; }
				else if (name == "EnableResize" || name == "EnableResize ") { if (value == "1" || value == "true" || value == "on" || value == "yes") this->EnableResize = true; }
			}
			cFile.close(); // Close file
			break;
		}
		else {
			std::ofstream gFile("settings.cfg");	//	Ofstream for writing
			std::cout << "[*] Default configuration file not found, generating 'settings.cfg'..\n";
			gFile << "# Available settings: Language, FasterLoad, EnableConsoleSelection, EnableResize\n# Available Languages: en, vi\n# Set to \"0\" to disable and \"1\" to enable\n# Example on enabling faster load feature:\n# FasterLoad = 1\n\n# Settings\nLanguage = en\nFasterLoad = 0\nEnableConsoleSelection = 0\nEnableResize = 0" << std::endl;	//	Writing default config file
			std::cout << "[*] 'settings.cfg' file generated.\n";
			gFile.close();	// Close file
			Sleep(5000);
			if (Attempts == 3) { std::cout << "[!] Error occurred, lacking permission?\n"; exit(1); }
			Attempts++;
		}
	}
}

void Timer::Loading()
{
	short loading_percentage = GetRand();

	while (true)
	{
		if (loading_percentage > 100) break;
		system("cls");
		if (this->Language == "en") std::cout << "Loading (" << loading_percentage << "%)\n";
		else if (this->Language == "vi") std::cout << "Đang tải (" << loading_percentage << "%)\n";
		loading_percentage += (GetRand() + 7);
		Sleep(10);
	}

	system("cls");
}

void Timer::ShowMenu()
{
	SetColor(0, 14);
	if (this->Language == "en") std::cout << "Shutdown Timer v2.0\n";
	else if (this->Language == "vi") std::cout << "Bộ Hẹn Giờ v2.0\n";
	std::cout << "--------------------\n\n";
	SetColor(0, 15);

	if (this->Language == "en") std::cout << "1. Shutdown windows in 1 hour\n";
	else if (this->Language == "vi") std::cout << "1. Tắt máy tính sau 1 tiếng\n";
	if (this->Language == "en") std::cout << "2. Shutdown windows in 2 hour\n";
	else if (this->Language == "vi") std::cout << "2. Tắt máy tính sau 2 tiếng\n";
	if (this->Language == "en") std::cout << "3. Shutdown windows in 4 hour\n";
	else if (this->Language == "vi") std::cout << "3. Tắt máy tính sau 4 tiếng\n";
	if (this->Language == "en") std::cout << "4. Shutdown windows (Specific)\n";
	else if (this->Language == "vi") std::cout << "4. Tắt máy tính (Thời gian tuỳ chọn)\n";
	if (this->Language == "en") std::cout << "5. Cancel current shutdown schedule\n";
	else if (this->Language == "vi") std::cout << "5. Huỷ lịch tắt máy hiện tại (Nếu có)\n";
	if (this->Language == "en") std::cout << "6. Exit Program\n\n";
	else if (this->Language == "vi") std::cout << "6. Thoát chương trình\n\n";
}

short Timer::SelectOption()
{
	short option = 0;
	while (true)
	{
		system("cls");
		ShowMenu();
		SetColor(0, 14);
		if (this->Language == "en") std::cout << "Select option: ";
		else if (this->Language == "vi") std::cout << "Nhập lựa chọn: ";
		SetColor(0, 15);
		std::cin >> option;
		ClearCinBuffer();
		std::cout << "\n";

		if (option >= 1 && option <= 6)	break;

		else 
		{ 
			SetColor(0, 14);
			std::cout << "> ";
			SetColor(0, 12);
			if (this->Language == "en") std::cout << "Invalid option\n";
			else if (this->Language == "vi") std::cout << "Lựa chọn không hợp lệ\n";
			SetColor(0, 15);
			system("pause");
		}
	}

	return option;
}

bool Timer::ProcessOption(short option)
{
	bool EXIT_PROGRAM = 0;

	switch (option)
	{
		case 1:
		{
			{
				system("cls");
				
				system("shutdown -a");
				system("cls");
				system("shutdown -s -t 3600");
				if (this->Language == "en") std::cout << "The windows will be shutdown in 1 hour\n";
				else if (this->Language == "vi") std::cout << "Máy tính sẽ được tự động tắt sau 1 tiếng\n";
				std::cout << "> "; SetColor(0, 11); DotAnimation(3, 1200);
				SetColor(0, 15);
				system("cls");
			}
			break;
		}

		case 2:
		{
			{
				system("cls");

				system("shutdown -a");
				system("cls");
				system("shutdown -s -t 7200");
				if (this->Language == "en") std::cout << "The windows will be shutdown in 2 hour\n";
				else if (this->Language == "vi") std::cout << "Máy tính sẽ được tự động tắt sau 2 tiếng\n";
				std::cout << "> "; SetColor(0, 11); DotAnimation(3, 1200);
				SetColor(0, 15);
				system("cls");
			}
			break;
		}

		case 3:
		{
			{
				system("cls");

				system("shutdown -a");
				system("cls");
				system("shutdown -s -t 14400");
				if (this->Language == "en") std::cout << "The windows will be shutdown in 4 hour\n";
				else if (this->Language == "vi") std::cout << "Máy tính sẽ được tự động tắt sau 4 tiếng\n";
				std::cout << "> "; SetColor(0, 11); DotAnimation(3, 1200);
				SetColor(0, 15);
				system("cls");
			}
			break;
		}

		case 4:
		{
			{
				system("cls");

				short time = 0;
				while (true)
				{
					system("cls");
					if (this->Language == "en") std::cout << "Enter the desired amount of time (in hour): ";
					else if (this->Language == "vi") std::cout << "Nhập số tiếng: ";
					std::cin >> time;
					ClearCinBuffer();
					if (time > 0 && time <= 24) break;
					else
					{
						SetColor(0, 12);
						if (this->Language == "en") std::cout << "Must be at least 1+ hour and no more than 24 hours\n";
						else if (this->Language == "vi") std::cout << "Tối thiểu 1 tiếng và tối đa 24 tiếng\n";
						SetColor(0, 15);
						system("pause");
					}
				}
				system("cls");


				system("shutdown -a");
				system("cls");
				system(("shutdown -s -t " + std::to_string(time * 3600)).c_str());
				if (this->Language == "en") std::cout << "The windows will be shutdown in " << time << " hour(s)\n";
				else if (this->Language == "vi") std::cout << "Máy tính sẽ được tự động tắt sau " << time << " tiếng\n";
				std::cout << "> "; SetColor(0, 11); DotAnimation(3, 1200);
				SetColor(0, 15);
				system("cls");
			}
			break;
		}

		case 5:
		{
			{
				system("cls");

				system("shutdown -a");
				system("cls");
				if (this->Language == "en") std::cout << "All current shutdown schedules have been cancelled\n";
				else if (this->Language == "vi") std::cout << "Các lịch tắt máy tự động đã được huỷ (Nếu có)\n";
				std::cout << "> "; SetColor(0, 11); DotAnimation(3, 1200);
				SetColor(0, 15);
				system("cls");
			}
			break;
		}

		case 6:
		{
			{
				SetColor(0, 15);
				std::cout << "> "; SetColor(0, 11); DotAnimation();
				SetColor(0, 15);
				system("cls");
				EXIT_PROGRAM = 1;
			}
			break;
		}

		default:
		{
			break;
		}
	}

	return EXIT_PROGRAM;
}