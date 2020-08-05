==========================================================================
OGL_Application
==========================================================================
OGL_Application is a project of a mini tool for game development.

The project is developed by a single person in his spare time with
the only purpose of enjoying programming and computer graphics.

OGL_Application allows the user to create/delete predefined objects at 
runtime, to edit existing objects in terms of their position,orientation,
colors, sizes,behaviour (activation of physics/ai).It has a shooting system 
and a simple implementation of enemy behaviour. It has 3 kind of camera 
transformations that the user can switch at runtime. 
All of the progress made during a session can be saved and restored later.

It enbeds various functionality, most of which I developed by myself
while others I integrated from third parties :

- it has a GUI
- it has a Physics Engine (I integrated the Cyclone physics library that
  was shipped as part of the book of Ian Millington (Game Physics).
  This library provides collision resolution, while collision detection 
  is managed only for some primitives, and it does not cope with tunneling.
  Therefore I integrated some part to handle the tunneling problem and to 
  add some simple primitives.

 - it integrates Irrklang sounds library
 - it integrates SOIL2 texture library


==========================================================================
1. Directory structure overview
==========================================================================
  
  \audio        	This folder contains audio files for the engine
               
  \DEPENDENCIES 	libraries for the various functionalities like 
  			texture	loading or windows and input managing etc.
			
  \include      	Header files to include when using the engine.
  
  \log_and_savings	Now and then I use a logger that drops logs on this 
  			folder. It contains a subfolders where projects 
			savings are stored					
  \src		      	Source files
  \Textures		folder to store images to be used as textures


==========================================================================
  
  loforte.andrea8@gmail.com
