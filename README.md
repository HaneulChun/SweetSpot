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
Sweet Spot is a 3D, First Person, Puzzle Solving game with Horror Elements. You play as a concierge working in a remote hotel known for its classical aesthetics, things get weird when the Elevator breaks down and its Control Panel pieces go missing. The environment progressively gets more unsettling driving you mad, manage your Madness Meter and stay in the Sweet Spot to see the incomprehensible and find the missing Elevator Pieces to escape.

### Documentation  
Google Drive: https://drive.google.com/drive/folders/1iGh71J26g5hfqgEvMaGSsHmyDN9VofN6?usp=sharing

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

