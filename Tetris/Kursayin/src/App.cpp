#include "App.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Scores.h"
#include "Game.h"
#include <ctime>
#include <cmath>


void showHighScores(Scores& scores, sf::Font& font) {

		sf::RenderWindow scoresWindow(
    sf::VideoMode(300, 400),
    "High Scores",
    sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize
);



    sf::Text hsTitle("HIGH SCORES", font, 28);
    hsTitle.setFillColor(sf::Color(120, 180, 250));
    hsTitle.setPosition(60, 10);

    sf::RectangleShape panel;
    panel.setSize(sf::Vector2f(260, 320));
    panel.setPosition(20, 60);
    panel.setFillColor(sf::Color(28, 40, 90, 220));

    sf::Text closeHint("ESC - Close", font, 14);
    closeHint.setFillColor(sf::Color(170, 170, 190));
    closeHint.setPosition(90, 360);

    auto topScores = scores.getTopScores();

    while (scoresWindow.isOpen()) {
        sf::Event ev;
        while (scoresWindow.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                scoresWindow.close();

            if (ev.type == sf::Event::KeyPressed &&
                ev.key.code == sf::Keyboard::Escape)
                scoresWindow.close();
        }

        scoresWindow.clear(sf::Color(18, 24, 48));
        scoresWindow.draw(panel);
        scoresWindow.draw(hsTitle);

        int y = 80;
        int rank = 1;

        for (int s : topScores) {
            sf::Text t(std::to_string(s), font, 20);
            sf::FloatRect b = t.getLocalBounds();
            t.setOrigin(b.width / 2.f, 0);
            t.setPosition(150, y);

            if (rank == 1)       t.setFillColor(sf::Color::Yellow);
            else if (rank == 2)  t.setFillColor(sf::Color(200,200,200));
            else if (rank == 3)  t.setFillColor(sf::Color(205,127,50));
            else                 t.setFillColor(sf::Color::Green);

            scoresWindow.draw(t);
            y += 25;
            rank++;
        }

        scoresWindow.draw(closeHint);
        scoresWindow.display();
    }
}


// ================= GAME STATE =================
enum class GameState {
    MENU,
    PLAYING
};

// ================= FALL SPEED =================
static float getFallDelay(int level) {
    float baseDelay = 0.8f;
    float factor    = 0.9f;
    float minDelay  = 0.05f;

    float d = baseDelay * std::pow(factor, level);
    return (d < minDelay) ? minDelay : d;
}

void runGame() {
    srand(time(0));
    Scores scores("scores.txt");
    scores.load();
    Game game;
    GameState state = GameState::MENU;
    int menuIndex = 0;

    sf::RenderWindow window(
        sf::VideoMode(Board::WIDTH * 30 + 120, Board::HEIGHT * 30),
        "Tetris SFML",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize
    );
    window.setFramerateLimit(60);

    sf::RectangleShape cell(sf::Vector2f(29, 29));

    sf::Color pieceColors[8] = {
        sf::Color::Black,   // 0 unused
        sf::Color::Cyan,    // I
        sf::Color::Yellow,  // O
        sf::Color::Magenta, // T
        sf::Color(255, 165, 0), // L (orange)
        sf::Color::Blue,    // J
        sf::Color::Green,   // S
        sf::Color::Red      // Z
    };

    float timer = 0;
    float delay = 0;
    sf::Clock clock;
		
    // ================= FONT =================
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf");

    // ================= MENU TEXT =================
    sf::Text titleText("TETRIS", font, 40);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setPosition(130, 80);

    sf::Text playText("Play", font, 24);
    playText.setPosition(170, 160);

    sf::Text highScoresText("High Scores", font, 24);
    highScoresText.setPosition(170, 200);
    highScoresText.setFillColor(sf::Color::White);

    sf::Text exitText("Exit", font, 24);
    exitText.setPosition(170, 240);


    auto isMouseOver = [&](sf::Text &text) {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return text.getGlobalBounds().contains(mouse);
    };

    // ================= GAME TEXT =================
    sf::Text scoreText("Score: 0", font, 14);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(14, 16);

    sf::Text nextText("Next:", font, 16);
    nextText.setFillColor(sf::Color::White);
    nextText.setPosition(Board::WIDTH * 30 + 20, 20);

    // ================= BORDERS =================
//    sf::RectangleShape leftBorder;
  //  leftBorder.setSize(sf::Vector2f(4.f, Board::HEIGHT * 30.f));
   // leftBorder.setPosition(0.f, 0.f);
    //leftBorder.setFillColor(sf::Color(160, 160, 160));

    sf::RectangleShape rightBorder;
    rightBorder.setSize(sf::Vector2f(4.f, Board::HEIGHT * 30.f));
    rightBorder.setPosition(Board::WIDTH * 30.f, 0.f);
    rightBorder.setFillColor(sf::Color(100, 200, 255));


    while (window.isOpen()) {
        float frametime = clock.restart().asSeconds();
        timer += frametime;

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, Board::WIDTH * 30 + 120, Board::HEIGHT * 30);
                window.setView(sf::View(visibleArea));
            }

            if (e.type == sf::Event::KeyPressed) {
                if (state == GameState::MENU) {
                    if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::Down)
                        menuIndex = (menuIndex + 1) % 3;

                    if (e.key.code == sf::Keyboard::Enter) {
                        if (menuIndex == 0) { 
                            game = Game();
                            timer = 0;
														game.score = 0;
                            state = GameState::PLAYING;
                        } 
												else if (menuIndex == 1) {
														showHighScores(scores, font);		
                        } 
												else { 
                            	window.close();
                        }
                    }
                } 
								else {
                    if (e.key.code == sf::Keyboard::Left)  game.moveLeft();
                    if (e.key.code == sf::Keyboard::Right) game.moveRight();
                    if (e.key.code == sf::Keyboard::Up)    game.rotate();
                    if (e.key.code == sf::Keyboard::Down)  game.moveDown();
                    if (e.key.code == sf::Keyboard::Space) game.moveInstantlyDown();
                    if (e.key.code == sf::Keyboard::Escape) state = GameState::MENU;
                }
            }

            if (e.type == sf::Event::MouseButtonPressed &&
                e.mouseButton.button == sf::Mouse::Left &&
                state == GameState::MENU) {

                if (isMouseOver(playText)) {
                    game = Game();
                    timer = 0;
                    state = GameState::PLAYING;
                }
                if (isMouseOver(highScoresText)) {
											showHighScores(scores, font);
                }
                if (isMouseOver(exitText)) {
                    window.close();
                }
            }
        }

        if (state == GameState::PLAYING) {
            if (game.isGameOver()) {
                scores.addScore(game.score);   
                game = Game();                 
                timer = 0;
                state = GameState::MENU;
                continue;                    
            }

            delay = getFallDelay(game.level);

            if (timer > delay) {
                timer = 0;
                if (!game.board.checkCollides(game.curX, game.curY + 1, game.curRot, game.pieces[game.curPiece])) {
                    game.curY++;
                } 
								else {
                    game.moveInstantlyDown();
                }
            }
        }

        scoreText.setString("Score: " + std::to_string(game.score));

        window.clear(sf::Color(25, 25, 35));

        if (state == GameState::MENU) {
            playText.setFillColor(isMouseOver(playText) || menuIndex == 0 ? sf::Color::Yellow : sf::Color::White);
            highScoresText.setFillColor(isMouseOver(highScoresText) || menuIndex == 1 ? sf::Color::Yellow : sf::Color::White);
            exitText.setFillColor(isMouseOver(exitText) || menuIndex == 2 ? sf::Color::Yellow : sf::Color::White);

            window.draw(titleText);
            window.draw(playText);
            window.draw(highScoresText);
            window.draw(exitText);
        } 
				else {  
//          window.draw(leftBorder);
            window.draw(rightBorder);

            for (int r = 0; r < Board::HEIGHT; r++)
                for (int c = 0; c < Board::WIDTH; c++)
                    if (game.board.grid[r][c]) {
                        cell.setFillColor(pieceColors[game.board.grid[r][c]]);
                        cell.setPosition(c * 30, r * 30);
                        window.draw(cell);
                    }

            Piece &p = game.pieces[game.curPiece];
            for (int r = 0; r < 4; ++r)
                for (int c = 0; c < 4; ++c)
                    if (p.rotations[game.curRot][r][c]) {
                        cell.setFillColor(pieceColors[p.color]);
                        cell.setPosition((game.curX + c) * 30, (game.curY + r) * 30);
                        window.draw(cell);
                    }

            Piece &next = game.pieces[game.nextPiece];
            cell.setSize(sf::Vector2f(20, 20));
            for (int r = 0; r < 4; ++r)
                for (int c = 0; c < 4; ++c)
                    if (next.rotations[0][r][c]) {
                        cell.setFillColor(pieceColors[next.color]);
                        cell.setPosition(Board::WIDTH * 30 + 20 + c * 22, 60 + r * 22);
                        window.draw(cell);
                    }
            cell.setSize(sf::Vector2f(29, 29));

            window.draw(scoreText);
            window.draw(nextText);
        }

        window.display();
    }

}

