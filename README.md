<p align="center">
 <img src="https://github.com/victorcas04/PartyRush/blob/main/Content/Splash/Splash.png?raw=true"/>
</p>

<p align="center">
# PartyRush

<br></br><br></br>
<p align="center">
### DESCRIPTION
</p>

The objective is to reach the exit without colliding with the enemy lines.

<br></br><br></br>
<p align="center">
### CONDITIONS
</p>

**Win**
<br>The main character must reach the exit square.

**Game Over**
<br>If the main character touches one of the congas, it's game over.

**Movement**
<br>You can select and control the different congas. Once a conga is selected you can move the first person in the conga horizontally, vertically, or in any of the 4 directions, and the rest of the people in the conga will follow the same path.

**Merge**
<br>If the start/end of a conga touches the start/end of another conga, they will merge and become a single conga.

<br></br><br></br>
<p align="center">
### CONTROLS
</p>

**INGAME**

Move cursor -> Arrows/WASD
<br>Select/deselect conga/player -> Enter
<br>Move conga/player when selected -> Arrows/WASD

**MENUS**

Menu open/close -> Escape / P
<br>Select option on menu -> Mouse left button

<br></br><br></br>
<p align="center">
### TODO LIST
</p>

Bugfixing:
 - Win and gameover screens wont work with popup (remove from parent wont work)
 - Some materials not loading on standalone/build
 - Make a build and do git release

Feedback:
 - New: Camera shakes and rumbles on death and merge
 - New: Add bg music, sfx when moving, dying, merging, and completing the level
 - Make a build and do git release

 Gameplay:
 - New: Add some kind of stats (number of moves, time, deaths, number of merges, etc) so we can add a score or something
 
 Settings:
 - New: Add settings for audio
 - New: Add settings for camera shake and rumble
 - New: Add colorblind support (shapes)

 Improvements:
 - Enhanced inputs
 - Support for cursor mode
 - Map creation enhancement (read through file or similar)

 Content:
 - New maps
 - New hazard: non mergeable obstacle
 - New hazard: moving conga
