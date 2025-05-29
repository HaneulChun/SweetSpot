# Unreal Project Base 5.4.3

### ------------------  ESSENTIAL SETUP  ----------------------
_*All the "Essential Setup" section has been setup for you already!_ 

**Project Settings**  
Search "Virtual Textures"  
Enable Virtual Textures Support

**Plugins**  
Search "Water"  
Enable Virtual Textures Support

**DefaultEngine.ini**  
[/Script/Engine.RendererSettings]  
r.Nanite.AllowTessellation=1  
r.Nanite.Tessellation=1  

**Results Node**  
Enable Tessellation  
Use with Nanite 
 
### --------------  MATERIAL INSTANCE SETTINGS  ----------------
**_Must be adjusted for every MI!_**     
Material Property Overrides > Displacement Scaling >  
Magnitude > 2 or as needed ( is the max displacement )  
Center = 0

### --------------  TEXTURE PACKING FORMAT  ----------------

BaseColor [RGB] Opacity [A] ( BC7 )  
Metal [R] Height [G] Emissive [B] Roughness [A] ( BC7 )  
NormalDX [RGB] ( BC5 )  

### ---------------  SHADER FEATURE LIST  ---------------------

**[ 01 ]** Blend Layer Expansion ( x4 )  
**[ 02 ]** Vertex Painting or Procudural Dusting Blend Styles  
**[ 03 ]** Authored UVs or Projected UVs  
**[ 04 ]** Height Blending  
**[ 05 ]** Nanite Tesselation Displacement  
**[ 06 ]** PBR ( tweaking ) Color Recolor | Normal Intensity | etc...  


### ---------------------------------------------------------------

Sweet Spot  
Sweet Spot is a First Person Eye Level, 3D Horror, Puzzle Solving game. You play as a concierge working at a remote hotel that's being haunted by an Eldritch Horror that shows itself via Tentacles and Eyeballs. It has trapped the Player in a Looping Hallway and an Elevator with missing pieces scattered throughout the Levels. The Player has access to a Wrist Watch which checks the time left in the Level and the state of their Madness. The Madness Meter is a Resource with 3 states: Sane, The Sweet Spot and Mad. The Ideal state the Player wants to be in is The Sweet Spot, this state will cause important items key to solving puzzles to glow. Use the Madness Meter to your advantage and solve the puzzles to find the missing elevator pieces and escape the loop.

### Documentation  
https://drive.google.com/drive/folders/1iGh71J26g5hfqgEvMaGSsHmyDN9VofN6?usp=sharing

### Gameplay Controls  
Action               | Keyboard Control  | Gamepad Control
---                  |---                |---
Move                 | WASD            
look                 | Mouse Look       
interact             | e               

### Debug Controls  
Action               | Keyboard Control
---                  |---          
Debug Menu           | Z              

### Team  
Parker Mise - Project Manager  
Natalie Wong - Artist 
Harnoor Garcha- Level Design
Jason Saltenis - Programmer 
Haneul Chan - Programmer 
Jacob Tallio - Programmer 

## Collaborators

## Gameplay Pillars 
Nothing is as it seems. 
The hotel is the Horror 
Precise Management is Rewarded 

## Location of Final Build 

## Known Issues 
Door moves outwards, pushing player. 
Arm moving is slow. 

## Core Loop 

Explore - Manage Madness - Solve Puzzles

## Feature Summary 

Movement
	The Player will be able to control the Player Character and move them in any direction they’re facing, they will also be able to walk backwards along with strafing in any direction they aren’t directly facing.They will not be able to crouch, jump or run. (See Character Controls)

Camera View
	The Player will be in a 1st person eye level view, this is to add a level of immersion for the Player. This camera will also be manipulated to further emphasise the Mad State of our Madness Meter. (See Camera View for FOV Specifications.) 

Character Controls
	The Player will have access to controls all across their Keyboard & Mouse, WASD to move forwards, sideways and backwards and moving their Mouse to look, E to interact with interactable objects and G to drop any item they are holding. The Player can use any item they’re holding by RMB click and LMB to check their Smart Watch. (See Character Controls for details) 

Madness Meter
	The Eldritch Horror that has trapped you in these Loops is also causing you to go Mad. The Madness Meter will only raise when the Player does a loop in the level or while in Rooms. If the Player reaches Max Madness they reset the level. The Player is able to lower the Madness Meter by using certain Interactables. The Madness Meter has 3 stages, Sane, The Sweet Spot, Madness. (See Madness Meter)

Sound Effects & Lighting
	The Lighting in Sweet Spot will be fitting for a 1930s-Themed Hotel during late night, the Hallway will always be lit enough to see and easy to traverse while the Hotel Rooms and Bathrooms will be darker with the only lights coming with TVs or Lamps. (see Lighting)
	The Audio Sound FX in Sweet Spot will be designed to make the Player feel they aren’t alone, they will hear distant footsteps, people talking through the walls, doors closing, TVs playing, and phones ringing. The Tentacles and Eyeballs will have a squishy, slimy, macaroni-and-cheese type sound. (See Sound Effects)

Environment
	The Environment of Sweet Spot is in a remote hotel that has rooms themed around different eras of the 1900s, however the Player will only be exploring Rooms reminiscent of the 1930s. The Hallway itself will be minimal in design with emphasis on its vintage appearance. (See Environment) 

Puzzles

The main draw of our game is the 3 puzzles (See Puzzles for details). You can interact and move items within each room to solve them. Items that are not resources (elevator pieces and chocolate), will not be able to be taken out of the room. (See Items)
Types of Puzzles: 

1, Toggling Setpiece Puzzle 
	Multiple Remotes will be placed around the ‘room’, only one solves the puzzle. The Sweet Spot indicates which remote is correct.
2, Control Room Puzzle 
	3 TVs are on, and all must be turned off. 3 remotes turn tvs on and off. Sweet Spot reveals symbols on both remotes and TVs that indicate which remote toggles which TV. TVs are placed all around the room and must be observed to see if the player has reached the correct solution. 
3, Symmetry Puzzle 
	Two mirrored rooms are next to each other, barring some distinct differences. Player must make the mirrored room exactly the same as the original. These pickable items can only be seen in the Sweet Spot. They will also have symbols relating to what area they need to be placed in. 
Impending Doom Timer (IDT)
	Each Level has a set time the Player has to complete it in, they can check the time left by looking at their Watch. When the Timer hits 0 the Level resets and the Player has to start again with no Mint Candies, but this time with the new knowledge they now have. (See IDT for details)

Items
	There are small chocolates scattered around the level that the Player can pickup and use to lower their Madness Meter, along with Key Cards the Player can pick up and use to open locked doors. There will also be TV Remotes scattered around the Player that can be used to turn off TVs and the Elevator Pieces that can be used to repair the Elevator. Some props in the Mirror Puzzle (Shown above) will also be movable. (See Items for more details) 

Loops
	Each level is a Looping Hallway with Rooms you can enter to find the missing Elevator Pieces, We choose a looping hallway to keep our level scope small and further emphasise our Hotel is the Enemy pillar. (See Hotel is the Enemy) (See Loops for more detail)

Smart Watch
	The Player uses this to check the state of their Madness Meter and the IDT. (See Smart Watch)


 


