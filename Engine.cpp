#include <cstdlib>
#include <iostream>
// g++ -o eng Engine.cpp
void head(std::string task){
	std::string header = "";
	header += ",--------.------------------.\n";
	header += "| ENGINE | TYPE h FOR HELP  | [" + task + "]\n";
	header += "`--------'------------------'\n\n";
	system("cls");
	std::cout << header;
}

int main(){
	bool run = true;
	std::string command;
	std::string help = "";
	help += " cmp  : compiles project in current directory\n";
	help += " run  : runs compuled project in currect directory\n";
	help += " exit : exits the engine program and returns to cmd\n";
	head("");
	while(run){
		std::cout << "\n > ";
		std::getline(std::cin, command);
		head("");
		for (int i = 0; i < command.length(); ++i){
  			command[i] = tolower(command[i]);
  		}
		if (command == "h"){
			std::cout << help;
		}
		else if (command == "cmp"){
			head("COMPILING");
			std::cout << " CHECK OUTPUT WINDOW FOR ERRORS/WARNINGS\n";
			system("start /wait cmd /c \"cmp.bat\"");
			head("");
			std::cout << " COMPILE SEQUENCE TERMINATED\n";
		}
		else if (command == "run"){
			head("RUNNING PROCESS");
			std::cout << " DEBUG OUTPUT:\n";
			system("run");
			head("");
			std::cout << " PROCESS TERMINATED\n";
		}
		else if (command == "exit"){
			run=false;
		}
		else{
			std::cout << "COMMAND NOT RECOGNIZED\n";
		}
	}
	system("cls");
	return 0;
}
