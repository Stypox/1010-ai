#include "no_ui_application.hpp"

#include <iostream>
#include <iomanip>

namespace app {

NoUiApplication::NoUiApplication(const game::Game& theGame)
    	: game{theGame} {
	if (!game.getUseAi()) {
		game.toggleUseAi();
	}
}


void NoUiApplication::run() {
	int gameCount = 0;
	int scoresSum = 0;

	while (1) {
        game.tick();
        if (game.getHasLost()) {
			++gameCount;
			scoresSum += game.getScore();
            std::cout << "#" << gameCount << " - Score:" << std::setw(6) << game.getScore() << " - Average:" << std::setw(6) << scoresSum / gameCount << "\n";

            game.reset();
        }
    }
}

} // namespace app