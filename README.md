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

## Core Loop 

## Feature Summary 


 


