# **PACMAN** 

Hi everyone, my name is Tung. This is my first project. In this project, I will make Pacman using [C++](https://en.wikipedia.org/wiki/C++) and [SDL 2.0](https://www.libsdl.org/download-2.0.php).

If you want to study SDL 2.0 you can visit this [website](https://lazyfoo.net/tutorials/SDL/index.php).

All the codes in my project is coded by myself.

.More information is in Readme.md(Vietnamese version).

## Table of Content
1. [How to Download and Install the game](#how-to-download-and-install-the-game)
2. [How to Play the game](#how-to-play-the-game)
3. [Game Detail](#game-detail)
4. [Game algorithm](#game-algorithm) 
5. [Image and Sound source](#image-and-sound-source)


### Contents
1. ### How to Download and Install the game

    First you will need to install [Code::Blocks](https://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/codeblocks-20.03mingw-setup.exe/download) to run C++, follow the instruction on these links to install:  
        - [SDL 2.0](https://www.libsdl.org/download-2.0.php)  
        - [SDL_image](https://www.libsdl.org/projects/SDL_image/)  
        - [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/)  
        - [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)  

    After installing, download as zip my project on github and then extract them.  

    Then open `Code::Blocks` then click `Open an existing project`. Move to the file where you extract the zip, open `Pacman.cbp`.

2. ### How to Play the game   
 
    You control a character named `Pacman` ![](Source/Assets/Entity%20Image/pacman%20icon.png). Your mission is eating all the `dot` ![](Source/Assets/Entity%20Image/dot.png) (or `coin`) in the maze. You will go to the next level after that.
    
    Using WASD or navigation arrows to control Pacman.
    
    Prevent you from eating is 6 Ghosts: `Blinky`, `Pinky`, `Clyde`, `Inky`, `Greendy`, `Friendy`.
    
    In the original game, there are only the first 4 ghosts, I add 2 more, make the game harder.

    Eating the bigger dot ![](Source/Assets/Entity%20Image/power%20dot.png) (normally called `power dot`) you will have a small time to hunt the ghosts. Eatting the scared ghosts gives you lots of
    scores, also make them return to the cage.
3. ### Game Detail

    The game is a maze with 28x31 tiles. 
    There are total 244 dots. 240 normal and 4 power dots.   

    In the original, there are 256 level due to game mechanic. In my game, the limit are 2^31-1 levels.
    
    Yes, that is the  `int` limit. I don't think anyone can play to that level. 

    About the ghosts, each one of them has their own AI. That means that each ghost behaves differently.

    ##### `Chase`
    - [`Blinky`]() ![](Source/Assets/Entity%20Image/blinky%20icon.png): chasing `Pacman`.   
    - [`Pinky`]() ![](Source/Assets/Entity%20Image/pinky%20icon.png): go to the 4 tiles in front of `Pacman`'s direction.
    - [`Inky`]() ![](Source/Assets/Entity%20Image/inky%20icon.png): go to the location created by `Blinky` ![Blinky](Source/Assets/Entity%20Image/blinky%20icon.png) symmetry across the Pacman.
    - [`Clyde`]() ![](Source/Assets/Entity%20Image/clyde%20icon.png): chase Pacman if the distance between him and `Pacman` is greater than 8 tiles.  
    ##### `Scatter`
    In scatter mode, the first 4 ghosts, each one has its own corner. They will go around that corner for a few seconds.

    ##### `Frighten`    
    In frighten mode, except `Friendy`, the ghosts will turn blue ![](Source/Assets/Entity%20Image/frighten%20ghost%20icon.png) and `Pacman` will able to eat them for a few seconds.

    If you eat a ghost in this mode, it will turn into `ghost's eyes` ![](Source/Assets/Entity%20Image/ghost%20eye.png), find way and get back to the in front of the cage then respawn.

    The three modes above change alternately.
    More information: https://pacman.fandom.com/wiki/Maze_Ghost_AI_Behaviors  

    About 2 ghosts I created:

    - `Greendy` ![](Source/Assets/Entity%20Image/greendy%20icon.png): Like his name, his skin is green and he like green apple. In my game, from level 3, a green apple is spawn randomly at 1 of 4 corner. If greendy is out of cage, he will go finding the apple. After eating, he will gain 2x speed in 2s, start hunting Pacman. You should becareful with him. Greendy can be scared and eaten.

    - `Friendy` ![](Source/Assets/Entity%20Image/friendy%20icon.png): This one is special. Her skin is yellow, like Pacman but darker. She is someone who cares about friends (of course, friend here is ghost). From level 5 she will appear. She will go randomly in the maze. But if you eat a `power dot`, she will not be effect. Instead, she will start hunting `Pacman` in 3s. 
4. ### Game algorithm
    -------------------------------
    Let me talk about the algorithm that helps ghosts chase `Pacman`.

    In the original game, they use [Euclidean distance](https://en.wikipedia.org/wiki/Euclidean_distance) to help the ghost decide which way to go. This will sometimes cause the ghosts to fail to reach the optimal path to their destination.
    
    In my game, objects are moved on the tiles. There are 28x31 `tiles`. Each ghost has:    
    - `tileX`: Current tile pos along the horizontal axis
    - `tileY`: Current tile pos along the vertical axis
    - `scrPosX`: Current screen pos along the horizontal axis
    - `scrPosY`: Current screen pos along the vertical axis
    - `nextTile (X, Y)`: destination tile     
    
    
    While the game loads the map, I use BFS to calculate how long it will take a ghost to go from one tile to the rest, provided that the ghost only chooses one of three directions: `in front of it`, `90 degrees clockwise`, or `90 degrees counter-clockwise`. 

    When a ghost moves into a new tile, i will get the minimum `distance` between the `distance` from one of the three directions above to the ghost's destination (if not a wall). If the destination is a wall or outside of the maze, the distance will calculte by `Euclidean distance`. 
    
    After taking the best direction, the ghost will go in that direction.
    
    This process is repeated every time the ghost enters a new `tile`. 

5. ### Image and Sound source

    Almost of images from my project is drew and edited by myself with Adobe Photoshop. I still have PSD file of each image incase you want edit it. 

    - green-apple: http://pixelartmaker.com/art/5adcfa718020edf
    - arrow-wasd: adobe (I can't find the link)
    - youlose: https://www.vectorstock.com/royalty-free-vector/you-lose-rubber-stamp-vector-17695736  
    - pacman-dead: https://www.deviantart.com/friendbeard/art/Dead-Heroes-Pacman-511878694  

    Sound: I found sounds in [apple music](https://music.apple.com/us/album/pac-man-game-sound-effect/328036461). If you have money you can pay for them. If you not, open chrome extension storage, searching a Audio Capture and use [Cut Mp3 Online](https://mp3cut.net/vi/).

    




