Textures used by both ImageGO2D, VBGO and CMO models should be placed in this directory: GED2025/Textures.

They should also be added to this project and have their "Item Type" property set to "Image Content Pipeline."
Right-click on the texture file in Solution Explorer, select Properties to open the Properties pane to set this.

When the project is built, these textures will be automatically converted to DirectX's dds (DirectDraw Surface) 
format and then moved to the GED2025/Assets directory by a post-build event.

This allows the main Game project to load and use these textures at runtime.

Note: Like the Models project, this Textures project will only build if you specifically tell Visual Studio to build it.
I.e. right click on the project in Solution Explorer and select "Build" or "Rebuild."
Do so whenever you add or modify texture files in this directory.

In both cases, this is to prevent unnecessary building of these projects when building the main Game project,
and to be more like a professional asset pipeline.
