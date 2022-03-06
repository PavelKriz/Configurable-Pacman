Semester work on Pac-Man {#mainpage}
============

## School assignment from Progtest


Implement the classic Pacman game against the computer (you can implement other variants as well).

The game must have the following functionalities:

1. Adherence to basic rules, collecting bonuses, mints (dots), cherries, teleports, etc.
    Several types of AI ghosts are implemented (working at the same time - eg ghosts differ in color, character).
2. Maps can be loaded from a file (maze + bonus and ghost positions).
3. Configurable difficulty of the game from the file (speed of ghosts, duration of individual game modes, probability of adding a new bonus to the map, ...)
4. Scalable ghost difficulty (multiple ghost strategies by difficulty, by different behavior)

Where can polymorphism be used? (recommended)

    Distribution of players: player, spirit (different types of artificial intelligence)
    Game mode: classic (ghosts walk according to their strategies), furious (ghosts chase players), invulnerable (ghosts are slower, they can be killed)
    Game field: ground, wall, point, bonus (change mode), cherry (more points), teleport
    User interface: console, ncurses, SDL, OpenGL (various variants), ...

More information

    https://cs.wikipedia.org/wiki/Pac-Man
    http://programujte.com/clanek/2011010500-chovani-duchu-ve-hre-pac-man-cast-1/
    http://programujte.com/clanek/2011010900-chovani-duchu-ve-hre-pac-man-cast-2/
    
    
## Detailed specification of the assignment


(designation [1] - [4] refers to individual mandatory points from the assignment)

The behavior of the game and its appearance will be similar to the classic game Pac-Man (as a reference to the game Pac-Man is taken a description of the rules of the game available through the links in the school assignment) [1]. The game will allow at least two game modes. However, the non-basic mode may differ in form from the classic game. The game will be implemented using a graphical interface.

The game will take place on a predetermined map on which the game objects will be located. The map will load from file [2]. It will also be possible to set other properties using a configuration file (it will be possible to modify all parameters from the school assignment) [3]. It will also be possible to set the game mode using this configuration file. The mode of play will determine the behavior of ghosts and thus their difficulty [4]. Both files will have a predefined valid format.

#### Description of moving game objects [1]:
Player (Pac-Man, movement controlled by the player)
Four different ghosts (behaving according to classic rules, moves)
Moving bonus (if the player picks it up, it adds a score to the player, in the classic game the cherry moves)

#### Bonuses that can be collected by the player [1]:
Small bonus (if the player picks it up, it adds a score to the player, it doesn't move)
Bigger bonus (if the player picks it up, it allows the player to capture ghosts for a while, it doesn't move)
Moving bonus ...

#### Game field on the map:
Wall (object that cannot be passed)
Gate (an object through which only ghosts can pass)
Empty box (normal object free to move moving objects)

Teleporting to the other side of the map will also be possible [1] (in cases where the classic rules of the game allow it).


## Implementation and design already done


During the implementation of the game, the intention is mainly to implement the necessary basic skeleton of the game. Later, other functionalities will be extended to the specified range. For example, some elements may be missing (for example, it could be an extra class for special ghost behavior outside the basic ghosts of Pac-man). Since the game is far from complete, the existing implementation, if any, is in the prototype state. Some parts of the implementation are purely to allow compilation of the completed part of the prototype. Additionally, methods that are in the header files are marked with a TEST comment.


## Polymorphism


Polymorphism will be used in different ghost behavior. This applies to the CGhost class and its other descendants (CRedGhost, CTurqoiseGhost, CSienaGhost, CPurpleGhost). A simple design of classes using polymorphism was attached as an illustration.

#### Methods where polymorphism will be used in ghosts:

##### Move method
Design method declaration: \
virtual SCoordinates move (const CMap & map, const SCoordinates & playerCoords, const CGameInfo & gameInfo) = 0;

The method starts moving the ghost on the map and returns the new position of the ghost after the move. This will allow each ghost to behave exactly according to its characteristics. It's so easy to implement different types of ghosts.

##### getObjectInfo method
Design method declaration: \
virtual SGameObjectInfo getObjectInfo () const = 0;

The method returns basic game information about the game object (in this case, the ghost). SGameObjectInfo is a structure through which data is passed in the application. For example, such a structure is passed to the CView class, which takes care of the GUI.

##### Rationale for polymorphism location
The main purpose of multiple game modes is to allow for a greater variety of behaviors or ghost types. That's why the polymorphism will be used by ghosts.
Despite the similarity, the Moving Bonus (CMovingBonus) and the Player (CPlayer) are not included in this polymorphism because theirmethods with the same functionality require fewer arguments. In addition, their occurrence is always only a maximum of one.

## Game controls

### Key inputs
Pacman (player) moves with the arrow keys. When selecting a new direction, this direction is memorized and used as a new direction of movement in the nearest possible place, so it is possible to schedule a turn forward.

When losing, you can start a new game by pressing the enter key.

### Starting the game

Game call method: \
[program name] [path to configuration file] [path to map file]
The folder from which the game is started must contain a valid directory of textured images, otherwise the game will not start.

##### Map from file
The map always needs to be loaded from a text file.

Sample map:

\ - \ - \ - \ - \ - \ - \ - <br/>
| ##. ## | <br/>
| # ... # | <br/>
| #. # G # | <br/>
| # P # X # | <br/>
| #. # G # | <br/>
| # ... # | <br/>
| ## @ ## | <br/>
\ - \ - \ - \ - \ - \ - \ - <br/>

Each map must be delimited by characters (- and |) as shown in the example. The inner field of this "pen" must be filled with characters from the following set of characters:

 '' for an empty field (0 to more) <br/>
 '#' for wall (0 to more) <br/>
 'X' for a gate through which only ghosts pass (0 to more) <br/>
 'P' for players (just 1) <br/>
 'G' for ghost (at least 1!) <br/>
 '.' for a basic bonus (at least 1!) <br/>
 '@' for a bonus allowing players to kill ghosts (0 to more) <br/>
 
The minimum map size is 3x3.

If the above rules are followed, there is no problem with loading the game. However, loading maps is tolerant and it is possible to create, for example, a file where the maps are counted one after the other and only the first one is used. It is important to have the individual elements behind you and not to use the signs of the pen outside the use in the pen.

\ - \ - \ - \ - \ - \ - \ - Any ascii characters can be outside the fence <br/>
| ##. ## | <br/>
| # ... # | <br/>
| #. # G # | <br/>
| # P # X # | also here <br/>
| #. # G # | <br/>
even here there may be characters, this is not a map interruption <br/>
| # ... # | <br/>
| ## @ ## | <br/>
\ - \ - \ - \ - \ - \ - \ -

\ - \ - \ - \ - \ - \ - \ - | ##. ## || # ... # || #. # G # | this is how you can create a map <br/>
| # P # X # || #. # G # | <br/>
| # ... # || ## @ ## | \ - \ - \ - \ - \ - \ - \ -

##### File inputs
The configuration file always needs to be loaded from a text file.

Configuration file format (example)


0 // game mode 0 for normal, 1 for hard, 2 for random
50 // ghost speed percentage, possible values ​​= 50 - 200
15 // default neutral time length, possible values ​​= 1 - 60
15 // default hunt on ghosts time length, possible values ​​= 1 - 60
15 // default hunt on player time length, possible values ​​= 1 - 60
60 // probability of moving bonus spawn, possible values ​​= 0 - 100 (0 makes bigger probability then 100)


There can be any ascii characters in the file, except that the individual parameters must be specified at the beginning of the lines, as shown in the example (lines with parameters must follow each other and start on the first line)
