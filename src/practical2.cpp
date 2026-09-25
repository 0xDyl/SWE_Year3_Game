#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/VideoMode.hpp"
#include <SFML/Graphics.hpp>

const sf::Keyboard::Key controls[4] = {
  sf::Keyboard::W,      // Player1 Up
  sf::Keyboard::S,      // Player1 Down
  sf::Keyboard::Up,     // Player2 UP
  sf::Keyboard::Down    // Player2 Down
};

// Parameters 
const sf::Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float time_step = 0.017f;

sf::Vector2f ball_velocity;
bool is_player_serving{true};
const float initial_velocity_x = 100.f; // Horizontal Velo
const float initial_velocity_y = 60.f; // Vertical Velo
const float velocity_multiplier = 1.1f;

// Objects of the game 
sf::CircleShape ball;
sf::RectangleShape paddles[2];

void reset() {
  // Reset paddle position 
  paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
  paddles[1].setPosition(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f);

  ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);

  // Reset velo
  is_player_serving = !is_player_serving;
  ball_velocity = { (is_player_serving ? initial_velocity_x : -initial_velocity_x), initial_velocity_y};
}

void init() {
  // Set size and origin of paddles 
  for (sf::RectangleShape &p : paddles) {
    p.setSize(paddleSize);
    p.setOrigin(paddleSize / 2.f);
  }

  // Set size and origin of ball 
  ball.setRadius(ballRadius);
  ball.setOrigin(ballRadius, ballRadius);

  reset();

  ball_velocity = { (is_player_serving ? initial_velocity_x : -initial_velocity_x), initial_velocity_y};
}

void update(float dt) {
  float p1dir = 0.0f;
  float p2dir = 0.0f;

  if (sf::Keyboard::isKeyPressed(controls[0])) {
    p1dir--;
  }
  if (sf::Keyboard::isKeyPressed(controls[1])) {
    p1dir++;
  }

  if (sf::Keyboard::isKeyPressed(controls[2])) {
    p2dir--;
  }
  if (sf::Keyboard::isKeyPressed(controls[3])) {
    p2dir++;
  }

  paddles[0].move(sf::Vector2f(0.f, p1dir * paddleSpeed * dt));
  paddles[1].move(sf::Vector2f(0.f, p2dir * paddleSpeed * dt));

  ball.move(ball_velocity * dt);

  const float bx = ball.getPosition().x;
  const float by = ball.getPosition().y;

  if (by > gameHeight) {
    ball_velocity.x *= velocity_multiplier;
    ball_velocity.y *= -velocity_multiplier;
    ball.move(sf::Vector2f(0.f, -10.f));
  } else if (by < 0) {
    ball_velocity.x *= velocity_multiplier;
    ball_velocity.y *= -velocity_multiplier;
    ball.move(sf::Vector2f(0.f, 10.f));
  } else if (bx > gameWidth) {
    reset();
  } else if (bx < 0) {
    reset();
  } else if (
    bx < paddleSize.x + paddleOffsetWall &&
    by > paddles[0].getPosition().y - (paddleSize.y * 0.5) && 
    by < paddles[0].getPosition().y + (paddleSize.y * 0.5)) {

    ball_velocity.x = -ball_velocity.x;
  } else if (
    bx > gameWidth - (paddleSize.x + paddleOffsetWall) && 
    by > paddles[1].getPosition().y - (paddleSize.y * 0.5) && 
    by < paddles[1].getPosition().y + (paddleSize.y * 0.5)) {
    
    ball_velocity.x = -ball_velocity.x;
  }
}

void render(sf::RenderWindow &window) {
  // Draw Everything 
  window.draw(paddles[0]);
  window.draw(paddles[1]);
  window.draw(ball);
}

int main() {
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "PONG");

  init();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    static sf::Clock clock;
    const float dt = clock.restart().asSeconds();

    window.clear();
    update(dt);
    render(window);
    sf::sleep(sf::seconds(time_step));
    window.display();
  }

  // clean();
}

