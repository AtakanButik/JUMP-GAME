# Jump Game
![](https://cdn.serverbutik.com.tr/vQtKr5.png)

## What is the purpose of the game?
Our character tries to jump through the random boxes he encounters. Earns 1 point for each box it passes. The aim of our character is to complete the game by reaching the highest score.
## How to Play?
When we start the game, boxes begin to come across our character in random sizes and intervals. Our character tries to jump over these boxes by jumping. For each box it passes, our character will earn 1 point. If it hits any of the boxes, our character will die and the game will be over.
## Game Controls
| KEY | EVENT |
|--|--|
| **UP / W / SPACE** | JUMP |
| **DOWN / S** | DOWN |
| **R** | PLAY AGAIN |
| **ESC** | CLOSE THE GAME |
## Game Settings
It can be played with many settings within the game. We included these settings in the code.
The speed of the boxes can be changed
```c
Con.BLOCK_SPEED = 3.4;
```
Jumping speed of the character can be changed
```c
Con.JUMP_SPEED = 4.7;
```
The upward limit of the character can be changed
```c
Con.JUMP_LIMIT = 30;
```
Boxes creation time can be changed
```c
BLOCKS_DELAY DELAY = { 60, 110 }; // Blocks created per random from first/FPS to second/FPS second
```
Maximum and Minimum heights and widths of the boxes can be changed
```c
CONFIG_BLOCKS BLOCKS = { 75, 50, 20, 10, DELAY }; // { MAXIMUM WIDTH, MAXIMUM HEIGHT, MINIMUM WIDTH, MINIMUM HEIGHT, DELAY }
```
Character's ability to go down can be turned on / off
```c
Con.FASTEST_MAN_ALIVE = 1; // allow to stop jumping with key S or DOWN
```
## Screen Size Sensivity
Our game opens with size of 800 x 400 pixels originally. However, the game can support almost all sizes of screens. Our game also has support for mobile screens.
![](https://cdn.serverbutik.com.tr/YnvsKt.png)
1920x1080p
![](https://cdn.serverbutik.com.tr/bWqSx3.png)
550x800p (Mobile)

Screen sizes can also be changed in the settings section.
```c
CONFIG_DISPLAY DISPLAY = { 800, 600 };
```
## Game Screens
There are 3 main screens you can encounter in the game.

 1. Start Screen
 2. Gamplay
 3. Game Over

#### 1. Start Screen
![](https://cdn.serverbutik.com.tr/bSeCYJ.png)
On this screen, we can display the name of our game and instructions to start the game in the blue framed part. Just press any key to start the game.
#### 2. Gameplay
![](https://cdn.serverbutik.com.tr/tgPDdE.png)
On this screen, we can display our character in the blue-framed part, our instant score in the green-framed parts and the score we have achieved the most, and our moving boxes in the orange-framed parts. We can jump with the up arrow, W or SPACE keys, while jumping, we can go down directly with the down arrow or S keys, and end the game directly with the ESC key.
#### Game Over
![](https://cdn.serverbutik.com.tr/CtuXME.png)
If our character touches any box at the time of gameplay, our game ends with the ending screen. If we wish, we can restart our game by pressing the R button, and if we wish, we can close our game by pressing the ESC button. If our score is higher than the highest score at the end of the game, the highest score is automatically updated. When we restart our game, while our score is reset, no change is observed in our highest score.
<![endif]-->

## REFERENCES
Allegro (Game Programing Library) - [https://liballeg.org/](https://liballeg.org/)
Character Animation Images - [https://www.youtube.com/watch?v=rmORvPK5gpg](https://www.youtube.com/watch?v=rmORvPK5gpg)
