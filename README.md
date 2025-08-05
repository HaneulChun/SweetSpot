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

### High Concept 
Sweet Spot is a 3D, First Person, Puzzle Solving game with Horror Elements. You play as a concierge working in a remote hotel known for its classical aesthetics, things get weird when the Elevator breaks down and its Control Panel pieces go missing. The environment progressively gets more unsettling driving you mad, manage your Madness Meter and stay in the Sweet Spot to see the incomprehensible and find the missing Elevator Pieces to escape.

### Pillars

### Nothing is at it Seems

	Reality in this hallway is very loose and strange, thanks to the eldritch presence. Things are not as it appears.  Thus in order to solve the puzzles, players must use the sweet spot to change their perception. They will see things previously unseen in the sane state, such as symbols that give hints to the solution or items that only appear when in the sweet spot. While they may be able to solve the puzzles without the sweet spot, it will be immensely difficult to do so. 
	
### The Hotel is the Enemy

 Some say insanity is doing the same thing over and over and expecting different results. With the environment having a loop effect there will be no progression until the Player does something different to break the loop. This process is another way psychosis can occur which will start the “hallucinations” of the Eldritch Horror which in the end may be real after all. You are fighting against the environment and the environment fights back, albeit indirectly. 

### Reward Precise Management 

	Individuals who are in the early stages of psychosis could recognize their diminishing mental condition. Having the Player also experience the process of going mad they too will be able to recognize things are wrong and use this to their advantage by precisely managing their Madness Meter to stay in the Sweet Spot, which is vital for solving puzzles. The more they stay in the sweet spot, the faster they are able to solve puzzles.

### Documentation  
Google Drive: https://drive.google.com/drive/folders/1iGh71J26g5hfqgEvMaGSsHmyDN9VofN6?usp=sharing

Sweet Spot Task Tracker: https://docs.google.com/spreadsheets/d/1rfIm30ryMnFfzlmCgfppY8QS98akgqSs-voqU7PmRqI/edit?gid=0#gid=0

Level Design Document: https://drive.google.com/drive/folders/1zEFb_PUugLA4ELfhpR0h1WceM5O-Wrrp?usp=drive_link

Playtest Form Spreadsheet: https://docs.google.com/forms/d/e/1FAIpQLSdc2rJ5N8a37Deaw4-MCjRGVXiiEhhr8v1HuZLbbJzC3YxDmA/viewform?usp=sharing&ouid=113901013285546762999

PitchnPlay Final Build: https://drive.vfs.com/index.php/apps/files/?dir=/VFSSTORAGE10%20Dropbox%20GDPGSD/Builds/Final%20Project/GD76PG27/Sweet_Spot/MBeta_Pitch_and_Play_Build&fileid=132902754

### Gameplay Controls  
Action               | Keyboard Control  | Gamepad Control
---                  |---                |---
Move                 | WASD            
look                 | Mouse Look       
Interact             | E / LMB   
Focus                | RMB  


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

### Collaborators
Adam Yassine - 3D Modeller

Jonah Byron - Concept Artist

Ciara - Concept Artist

Stitch - Concept Artist

Alec - Concept Artist

Juan De Stefano - Sound Designer

Andres Ortiz Trejo - Sound Designer

Estefania Briones Escalera - Technical Sound Designer

Santiago Hernandez Guerra - Technical Sound Designer


