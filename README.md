Saurabh Chand Ramola
20161106
Graphics Assignment 2 : Legend of Zelda




* TO START THE GAME, GO THE BUILD DIRECTORY AND RUN ./graphics_asgn1 ON YOUR TERMINAL.

* THE SCORING OF THE GAME WILL BE:
+100 - IF YOU DESTROY THE OBSTACLES OR KILL THE MONSTERS
-10 - IF YOU COME IN CONTACT WITH A MONSTER OR COLLIDE WITH AN OBSTACLE
IF YOU GO IN THE AREA OCCUPIED BY THE MONSTER WHEN THE MONSTER IS PRESENT, YOUR SCORE WILL DECREASE.

IF YOU KILL 5 MONSTERS, THE BOSS MONSTER WILL COME INTO PLAY

IF YOU COME IN CONTACT WITH THE MONSTER'S FIRE POWER, YOU DIE.

IF YOUR SCORE GOES LESS THEN 0 AT ANY POINT IN THE GAME, YOUR GAME GETS OVER.


How to run:
1. Make sure you are in the directory 20161106_Assignment2
2. Run the command mkdir build
3. Run the command cd build
4. Run the command cmake ..
5. Run the command make
6. Run the command ./graphics_asgn1


Controls:
● The boat floats in water and can move and jump on it.
● To move up, press up key, to move right - right key and to move left - left key.
● To jump use the spacebar.
● Camera key 1 : Follow Cam
  Camera key 2 : Top View Cam
  Camera key 3 : Boat Cam
  Camera key 4 : Tower view Cam
  Camera key 5 : Helicopter view Cam
● In heli-cam use the scroll wheel or + and - to zoom in or out
* Fire using 'f' key.
● Score and Health is displayed in the window title bar.
● The game starts with the health and score = 0.
● In the game after that if the score again gets 0 at any point in time, game gets over and Game over is displayed on the screen for two seconds before the screen is closed.
● The game is infinitely and the player can move anywhere horizontally on the ground.


Things I have implemented:
Version 1.0: A static world (Water, boat, rocks)
Version 2.0: Movement of the boat, wind, collisions with rocks
Version 3.0: Cannon, Monsters (including boss)
Version 3.5: Barrels, booster, gifts, health points
Version 4.0: Textures