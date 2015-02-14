# The Reverend

## Intro/Backstory
The Reverend is 2 2D, open-world, sandbox survival game featuring a top-down UI (similar to old-school RPGs).
It is set in the modern day world after a global economic collapse. The population has been decimated after a 
chain of events leading to wordlwide riots, overthrown governments, destruction of power grids, lawlessness, and 
widespread panic.

You play The Reverend, a former member of a small survival community. While you were never a religious man, you 
received the "Reverend" moniker from your leadership and guideance of the community. However, as is common in the 
post-modern age, the community was attacked by a bandit group and many were killed or fled during the attack. 

You are now on your own. Build your own compound or seek out other communities for help. Whatever you can do to 
survive. How long will you last?

## Features

* ...

## Control Scheme

### Controller

* Left Stick - Movement
* Right Stick - Look Direction
* A - Action
* B - Inventory
* R Trigger - Attack/fire
* L Bumper - Equip previous item in belt
* R Bumper - Equip next item in belt


### Keyboard/Mouse

#### Movement

Use the ASWD keys to move and the mouse to look in a specific direction. If you are attacking/firing, 
the Reverend will continue to look in the direction of the mouse.

* A - Left
* D - Right
* W - Up
* S - Down
* E - Action
* I - Inventory
* 1-9 - Equip item in belt (0 key equips fists)
* [ - Equip previous item in belt
* ] - Equip next item in belt
* Mouse - Look
* LMB - Attack/fire
* RMB - Action (alternative to "E" key)

## Release Notes

* ...

## Development Roadmap (TODO)

* When not moving in direction, keep existing forward/texture showing where player is facing.
* At item ID attribute instead of comparing item/gameData type/name.
* More efficient item/gameData iterations to avoid O(n^2)? Possibly a map?

## Installation

* Run install.bat

## Developer Notes

### Terrain Generation

General Technique:   
http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/  
http://www.gamasutra.com/view/feature/3549/interview_the_making_of_dwarf_.php?page=7

Voronoi:  
http://sourceforge.net/projects/mapmanager/ (which is based on http://www.skynet.ie/~sos/mapviewer/voronoi.php)

Heightmap:  
http://libnoise.sourceforge.net/tutorials/