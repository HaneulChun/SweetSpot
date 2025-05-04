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

# Game Title  
[high concept goes here]

### Documentation  
[link to google drive folder here](linkURL)

### Gameplay Controls  
Action               | Keyboard Control  | Gamepad Control
---                  |---                |---
Move                 | WASD              | Stick R
Aim                  | Mouse Look        | Stick L
Attack               | Mouse L           | Trigger R
Block                | Mouse R           | Trigger L

### Debug Controls  
Action               | Keyboard Control
---                  |---          
Debug Menu           | F1              
Invincibility        | F2               
Unlimited Ammo       | F3                
Cycle Checkpoints    | F4                
Respawn Enemies      | F5                

### Team  
<Team Member 1 - Role>  
<Team Member 2 - Role>  
<Team Member 3 - Role>  
<Team Member 4 - Role>  
<Team Member 5 - Role>  
