#include <iostream>
#include <stypox/argparser.hpp>

#include "app/application.hpp"
#include "app/no_ui_application.hpp"
#include "game/game.hpp"

int main(int argc, char const* argv[]) {
	bool help = false;
	bool usage = false;
	bool noUi = false;

	stypox::ArgParser argParser{
		std::make_tuple(
			stypox::HelpSection{"\nHelp options:"},
			stypox::SwitchOption{"help", help, stypox::args("-h", "--help"), "show help screen"},
			stypox::SwitchOption{"usage", usage, stypox::args("-u", "--usage"), "show usage screen"},
			stypox::HelpSection{"\nGame options:"},
			stypox::SwitchOption{"no ui", noUi, stypox::args("-n", "--no-ui"), "do not start an sfml application but just run the game and print out the results"}
		),
		"1010! AI by Stypox"
	};

	argParser.parse(argc, argv);

	// check for help before validating
	if (help) {
		std::cout << argParser.help();
		return 0;
	}
	if (usage) {
		std::cout << argParser.usage();
		return 0;
	}

	argParser.validate();

    if (noUi) {
		app::NoUiApplication{game::Game{}}.run();
    } else {
        app::Application{game::Game{}}.run();
    }
}
