# File Formats

## Fonts

### .font
* File mode: binary
* File extension: `font` or `FONT`
* Use: storing sprite fonts
* Magic: `MAGEfont`
* Syntax: see [SpriteFont format](https://github.com/matt77hias/MAGE-SpriteFont)

## Materials

### .mtl
* File mode: ANSI
* File extension: `mtl` or `MTL`
* Use: storing materials
* (Line) comment characters:
  * `#`
* Delimiters: 
  * `_` (space character) 
  * `\t` (tab character)
  * `\n` (EOL: end of line character)
  * `\r`(CR: carriage return character)
* Syntax: see [MTL format](http://paulbourke.net/dataformats/mtl/)

| Definitions        | Syntax                                      | Arguments                          |
|--------------------|---------------------------------------------|------------------------------------|
| base color         | `base_color <F32>`                          | R=G=B channel (A=1)          [0,1] |
| base color         | `base_color <F32> <F32> <F32>`              | R, G, B channels (A=1)       [0,1] |
| base color         | `base_color <F32> <F32> <F32> <F32>`        | R, G, B, A channels          [0,1] |
| base color texture | `texture_base_color <string>`               | relative file name                 |
| emissive             | `emissive`                                | no light interaction               |
| metalness          | `metalness <F32>`                           | metalness value              [0,1] |
| material texture   | `material_base_color <string>`              | relative file name                 |
| new material       | `newmtl <string>`                           | material name                      |
| normal texture     | `normal_base_color <string>`                | relative file name                 |
| opaque             | `opaque`                                    | opaque base color      (= default) |
| roughness          | `roughness <F32>`                           | roughness value              [0,1] |
| transparent        | `transparent`                               | transparent base color (= default) |
| `<string>`         | `<ANSI string without delimiters and EOFs>` |                                    |

## Meshes

### .msh
* File mode: binary
* File extension: `msh` or `MSH`
* Use: storing one vertex buffer and its associated index buffer. `VertexT` and `IndexT` are not included in the file.
* Magic: `MAGEmesh`
* Syntax:

| Definitions        | Syntax                                                     |
|--------------------|------------------------------------------------------------|
|                    | `MAGEmesh <nb-vertices> <nb-indices> <vertices> <indices>` |
| `<nb-vertices>`    | `<U32>`                                                    |
| `<nb-indices>`     | `<U32>`                                                    |
| `<vertices>`       | `<VertexT>...<VertexT>` (`<nb-vertices>` *times*)          |
| `<indices>`        | `<IndexT>...<IndexT>` (`<nb-indices>` *times*)             |
     
### .obj
* File mode: ANSI
* File extension: `obj` or `OBJ`
* Use: storing meshes/models
* (Line) comment characters:
  * `#`
* Delimiters: 
  * `_` (space character) 
  * `\t` (tab character)
  * `\n` (EOL: end of line character)
  * `\r`(CR: carriage return character)
* Syntax: see [OBJ format](http://paulbourke.net/dataformats/obj/)
  * only a subset is supported
  * `g` has different usage
  * UVW vertex texture coordinates will be converted to UV vertex texture coordinates
  
## Models
  
### .mdl
* File mode: ANSI
* File extension: `mdl` or `MDL`
* Use: storing models
* (Line) comment characters:
  * `#`
* Delimiters: 
  * `_` (space character) 
  * `\t` (tab character)
  * `\n` (EOL: end of line character)
  * `\r`(CR: carriage return character)
* Syntax:
     
| Definitions       | Syntax                                                                    |
|-------------------|---------------------------------------------------------------------------|
| material library  | `mtllib <string>.mtl`                                                     |
| model part        | `s <child-name> <parent-name> <material-name> <start-index> <nb-indices>` |
| `<child-name>`    | `<string>`                                                                |
| `<parent-name>`   | `<string>`                                                                |
| `<material-name>` | `<string>`                                                                |
| `<start-index>`   | `<U32>`                                                                   |
| `<nb-indices>`    | `<U32>`                                                                   |
| `<string>`        | `<ANSI string without delimiters and EOFs>`                               |
 
## Textures
     
### .dds
* File mode: binary
* File extension: `dds` or `DDS`
* Use: storing textures
* Magic: `DDS`
* Syntax: see [DDS format](https://msdn.microsoft.com/en-us/library/windows/desktop/bb943991%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396#File_Layout1).

## Variable Scripts

### .var
* File mode: ANSI
* File extension: `var` or `VAR`
* Use: storing simple properties
* (Line) comment characters:
  * `#`
* Delimiters: 
  * `_` (space character) 
  * `\t` (tab character)
  * `\n` (EOL: end of line character)
  * `\r`(CR: carriage return character)
* Syntax:

| Definitions       | Syntax                                                             |
|-------------------|--------------------------------------------------------------------|
| property          | `bool <property-name> true`                                        |
| property          | `bool <property-name> false`                                       |
| property          | `int <property-name> <S32>`                                        |  
| property          | `int2 <property-name> <S32> <S32>`                                 |
| property          | `int3 <property-name> <S32> <S32> <S32>`                           |
| property          | `float <property-name> <F32>`                                      |
| property          | `float2 <property-name> <F32> <F32>`                               |
| property          | `float3 <property-name> <F32> <F32> <F32>`                         |
| property          | `float4 <property-name> <F32> <F32> <F32> <F32>`                   |
| property          | `color <property-name> <F32> <F32> <F32> <F32>`                    |
| property          | `string <property-name> <string>`                                  |
| `<property-name>` | `<string>`                                                         |
| `<string>`        | `<ANSI string without delimiters and EOFs>`                        |
