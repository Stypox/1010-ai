#include <iostream>
#include <stypox/argparser.hpp>

#include "app/application.hpp"
#include "app/no_ui_application.hpp"
#include "game/game.hpp"
#include "game/piece.hpp"
#include "ai/scoring_function.hpp"

void parseArguments(int argc,
					char const* argv[],
					bool& noUi,
					ai::scoring_table_t& scoringTable,
					std::pair<float, int>& connectedComponentsParams,
					float& biggestRectangleMaxScore) {
	bool help = false;
	bool usage = false;

	stypox::ArgParser argParser{
		std::make_tuple(
			stypox::HelpSection{"\nHelp options:"},
			stypox::SwitchOption{"help", help, stypox::args("-h", "--help"), "show help screen"},
			stypox::SwitchOption{"usage", usage, stypox::args("-u", "--usage"), "show usage screen"},
			stypox::HelpSection{"\nGame options:"},
			stypox::SwitchOption{"no ui", noUi, stypox::args("-n", "--no-ui"),
				"do not start an sfml application but just run the game and print out the results"},
			stypox::HelpSection{"\nAI options (only the scoring functions related to the provided arguments will be used,"
				"though if no option is selected, FittingPiecesScoringFunction with fastScoringTable will be used):"},
			stypox::ManualOption{"fitting pieces scoring table", scoringTable,
				stypox::args("-fpst=", "--fitting-pieces-scoring-table="),
				"a scoring table for FittingPiecesScoringFunction (possible values: full, fast, custom)",
				[](const std::string_view& str) {
					if (str == "full") {
						return ai::fullScoringTable;
					} else if (str == "fast") {
						return ai::fastScoringTable;
					} else if (str == "custom") {
						return ai::customScoringTable;
					} else {
						throw std::runtime_error{"Invalid scoring table: " + std::string{str}};
					}
				}},
			stypox::ManualOption{"connected components parameters", connectedComponentsParams,
				stypox::args("-ccp=", "--connected-components-parameters="),
				"the max score (>= 0) and the minimum size of non penalized groups (> 0 and <= number of"
				" squares) for ConnectedComponentsScoringFunction (format: `score:size` [`float:int`])",
				[](const std::string_view& str) {
					std::pair<float, int> result;
					try {
						size_t semicolonIndex = str.find_first_of(":");
						if (semicolonIndex == std::string::npos)
							throw std::runtime_error{""};

						std::string maxScore{str.substr(0, semicolonIndex)},
							penalizeSmallerThan{str.substr(semicolonIndex + 1, str.size() - semicolonIndex - 1)};
						result = {std::stof(maxScore), std::stoi(penalizeSmallerThan)};
					} catch (...) {
						throw std::runtime_error{"Badly formatted connected components parameters: " + std::string{str}};
					}

					if (result.first < 0) {
						throw std::runtime_error{"Max score must be >= 0 in connected components parameters: " + std::to_string(result.first)};
					} else if (result.second <= 0 || result.second > app::BOARD_SIZE * app::BOARD_SIZE) {
						throw std::runtime_error{"Penalize when smaller must be > 0 and <= number of squares in connected components parameters: " + std::to_string(result.second)};
					}
					return result;
				}},
			stypox::Option{"biggest rectangle max score", biggestRectangleMaxScore,
				stypox::args("-brms=", "--biggest-rectangle-max-score="),
				"the max score (>= 0) for BiggestRectangleScoringFunction",
				false, // option not required
				[](float value){ return value >= 0; }}
		),
		"1010! AI by Stypox"
	};

	argParser.parse(argc, argv);

	// check for help before validating
	if (help) {
		std::cout << argParser.help();
		exit(0);
	}
	if (usage) {
		std::cout << argParser.usage();
		exit(0);
	}

	argParser.validate();
}

int main(int argc, char const* argv[]) {
	bool noUi = false;
	ai::scoring_table_t scoringTable;
	std::pair<float, int> connectedComponentsParams{0.0f, 1};
	float biggestRectangleMaxScore = 0.0f;

	parseArguments(argc, argv, noUi,
		scoringTable, connectedComponentsParams, biggestRectangleMaxScore);

	ai::scoring_function_t scoringFunction;
	if (!scoringTable.empty()) {
		scoringFunction += ai::FittingPiecesScoringFunction{scoringTable};
	}
	if (connectedComponentsParams.first > 0) {
		scoringFunction += ai::ConnectedComponentsScoringFunction{
			connectedComponentsParams.first, connectedComponentsParams.second};
	}
	if (biggestRectangleMaxScore > 0) {
		scoringFunction += ai::BiggestRectangleScoringFunction{biggestRectangleMaxScore};
	}
	if (scoringFunction == nullptr) {
		// if no options were provided, default to this
		scoringFunction = ai::FittingPiecesScoringFunction{ai::fastScoringTable};
	}

	// run application
	game::Game game{scoringFunction};
    if (noUi) {
		app::NoUiApplication{game}.run();
    } else {
        app::Application{game}.run();
    }
}
