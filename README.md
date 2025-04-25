# Snake Game in C

A simple implementation of the classic Snake game in C. The game runs in the console and allows players to control the snake using the arrow keys. The goal is to eat food and grow the snake, avoiding collisions with the walls and itself. The game also offers different difficulty levels that affect the speed of the snake.

## Features

- **Snake Movement**: The snake moves based on arrow key input.
- **Food Generation**: Randomly placed food that the snake can "eat" to grow.
- **Collision Detection**: The game ends when the snake collides with the walls or itself.
- **Game Restart**: Press 'r' to restart the game after a game over or win.
- **Difficulty Levels**: Choose between Easy, Medium, or Hard difficulty that controls the snake's speed.
- **Score Tracking**: The score increases as the snake eats food and is displayed in the top-left corner.

## How to Play

1. **Controls**:
   - **Arrow Keys**: Control the snake's movement (Up, Down, Left, Right).
   - **'r'**: Restart the game after game over or winning.
   - **'q'**: Quit the game.

2. **Difficulty Settings**:
   - **1**: Easy (slow snake speed).
   - **2**: Medium (default snake speed).
   - **3**: Hard (fast snake speed).

3. **Objective**: 
   - Eat food (represented by `#`) to grow the snake.
   - Avoid hitting the walls or the snake's own body.

## Game Over / Win

- **Game Over**: The game ends if the snake collides with the walls or itself.
- **Win**: The player wins by achieving a score of 100.

## Code Explanation

- **Snake Structure**: The snake is represented as an array of coordinates. The snake's head is `@`, and the body is represented by `O`.
- **Food Structure**: Food is randomly generated and represented by `#`.
- **Game Loop**: The game continuously updates the screen, processes input, checks for collisions, and updates the snake's position.
