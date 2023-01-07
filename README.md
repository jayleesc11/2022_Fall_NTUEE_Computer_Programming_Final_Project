# NTUEE Computer Programming Final Project Game Student vs NTU
This game is a tower defense game based on the university school life of the developers.<br>
Players assume control of the Student side, taking defense against the NTU side which is controlled automatically by the program.

---

## For users:
### Window Size:
This game opens up a window of size 1100*960 pixels. Please modify your display settings to accommodate the window before you run the game.

### Starting Interface:
Open "Student vs NTU.exe".<br>
The starting interface pops up once the game is started.<br>
There are three blocks on the interface.<br>
* **New Game**: start playing
* **Info on student side (player controlled)**: information on the characters you control
* **Info on NTU side (CPU controlled)**: information on the characters you will be taking defense against

### Properties of characters:
* Cost: The resources (coffee) needed to construct a character on the map. The cups of coffee you possess are displayed at the left edge of the card bar.
* Cooldown time: The minimum interval between constructing a character and selecting it the next time. The cooldown time remaining for each character is displayed over their position on the card bar in seconds.<br>Please note that cooldown time doesn't start counting until the character has been constructed on the map.
* HP: The amount of damage a character can bear before it gets demolished.

### Control:
Click on the character cards in the card bar located at the top left of the screen to select a character.<br>
The image of the character will move with your cursor once a character has been selected.<br>
Then, click on any block in the game map to place the character on the chosen block.<br>
Your character is then constructed on the map and is ready to fight!<br>
Please note that once a character has been constructed, it can no longer be moved to another position on the map.<br>
If you want to cancel a character selection before construction, simply click on the card bar once more.<br>
You will see that the image of your character no longer follows your cursor on the screen.<br>

### Battle:
Once the characters have been constructed on the map, they will start working.<br>
For the NTU side objects to cause damage on the student's side, the objects must be in direct contact with your characters.<br>
Once a character's or an object's HP is damaged to zero by the opposing side, it is killed and demolished from the map.<br>
NTU objects will move at a constant speed toward the left of the map until they meet a character of the student side. <br>
If they succeed in killing the character, they will resume movement toward the left.<br>

### Winning condition:
The game will be won once the object named FINAL on the NTU side has been demolished by the students' side.<br>

### Losing condition:
The game will be lost once an NTU object not of type "Mr.Shuiyuan" reaches the first column on the left of the map.<br>

---

## For developers:
This project is in C++ and SDL2.
* `main.cpp`
  * Initializes the objects used in the program.
  * Load the media required in the program.
  * Handles input events and calls corresponding functions of other classes.
  * Frees memory and closes the program.<br>

* `constant.h`<br>Defines the constants used in the program, including the dimensions of the screen, and map and the values assigned to each character in the program.

* `student.cpp`<br>Contains the class that handles the functions of the characters on the students' side, including getting hurt, the individual functions of certain characters, and finally rendering the image of the characters onto the screen.
* `student.h`<br>Header file for `student.cpp`.

* `ntu.cpp`<br>Contains the class that handles the functions of the objects on the NTU side, including, moving, getting shot by bullets, hurting students, and the individual functions of certain characters, and finally rendering the image of the characters onto the screen.
* `ntu.h`<br>Header file for `ntu.cpp`.

* `battlecontrol.cpp`<br>Contains the functions that handle the events during battle

* `battlecontrol.h`<br>Header file for `battlecontrol.cpp`.

* `cardbar.cpp`<br>Contains functions that handle the selection of characters from the card bar, the cooldown of characters, and the amount of COFFEE the player holds.

* `cardbar.h`<br>The header file for `cardbar.cpp`.

* `state.cpp`<br>Handles the current state of the program. (Initialize, game, end.)

* `state.h`<br>Header file for `state.cpp`.

* `texture.cpp`<br>Contains the wrapper class for loading and rendering texture using SDL.

* `texture.h`<br>Header file for `texture.cpp`.

* `timer.cpp`<br>Contains the class to access the SDL timer.

* `timer.h`<br>Header file for `timer.cpp`.
