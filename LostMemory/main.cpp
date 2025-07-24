#pragma warning(disable:4244)
#pragma warning(disable:4267)

#include <iostream>

#include "parser.h"
#include "map.h"
#include "populace.h"

using namespace std;

int main() {
	Map* map = new Map();
	Populace* populace = new Populace();

	string cmd;

	CMD_TYPE type = CMD_UNKOWN;
	do {
		string input;
		getline(cin, input);

		Parser parser;
		parser.AddOption("--help", 'h', "Show help.");
		
		auto cmd = parser.ExtractCmd(input);
		auto type = parser.GetAction(cmd[0]);

		try {
			switch (type) {
			case CMD_INIT:
				parser.AddOption("--block", 'b', "Block num both horizontally and vertically.", true, "4");
				parser.ParseCmd(cmd);
				populace->Init(map->Init(4, 4));
				break;
			case CMD_PASS:
				parser.AddOption("--tick", 't', "Tick num to pass.", true, "1");
				parser.ParseCmd(cmd);
				break;
			case CMD_PRINT:
				parser.AddOption("--map", 'm', "Whether to print the map.", false);
				parser.AddOption("--populace", 'p', "Whether to print the populace.", false);
				parser.ParseCmd(cmd);
				break;
			default:
				parser.ParseCmd(cmd);
				break;
			}

			if (parser.HasOption("--help")) {
				parser.PrintHelp(type);
			}
		}
		catch (exception e) {
			cout << e.what() << endl;
		}

	} while (type != CMD_EXIT);

	return 0;
}
