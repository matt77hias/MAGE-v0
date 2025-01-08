# File Formats

## Table of contents
* [Fonts](#SS-Fonts)
* [Materials](#SS-Materials)
* [Meshes](#SS-Meshes)
* [Models](#SS-Models)
* [Textures](#SS-Textures)
* [Variable Scripts](#SS-Variable-Scripts)

## <a name="SS-Fonts"></a>Fonts

### .font
* File mode: binary
* File extension: `font` or `FONT`
* Use: storing sprite fonts
* Magic: `MAGEfont`
* Syntax: see [SpriteFont format](https://github.com/matt77hias/MAGE-v0-SpriteFont)

## <a name="SS-Materials"></a>Materials

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

| Definitions        | Syntax                                      | Arguments                                |
|--------------------|---------------------------------------------|------------------------------------------|
| base color         | `base_color <F32>`                          | R=G=B channel (A=1)    [0,1]             |
| base color         | `base_color <F32> <F32> <F32>`              | R, G, B channels (A=1) [0,1]<sup>3</sup> |
| base color         | `base_color <F32> <F32> <F32> <F32>`        | R, G, B, A channels    [0,1]<sup>4</sup> |
| base color texture | `texture_base_color <string>`               | relative file name                       |
| metalness          | `metalness <F32>`                           | metalness value        [0,1]             |
| material texture   | `material_base_color <string>`              | relative file name                       |
| new material       | `newmtl <string>`                           | material name                            |
| normal texture     | `normal_base_color <string>`                | relative file name                       |
| opaque             | `opaque`                                    | opaque base color      (= default)       |
| radiance           | `radiance <F32>`                            | radiance value                           |
| roughness          | `roughness <F32>`                           | roughness value        [0,1]             |
| transparent        | `transparent`                               | transparent base color (= default)       |
| `<string>`         | `<ANSI string without delimiters and EOFs>` |                                          |

## <a name="SS-Meshes"></a>Meshes

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
  * UVW vertex texture coordinates will be converted to UV vertex texture coordinates

## <a name="SS-Models"></a>Models
  
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
     
| Definitions       | Syntax                                                                                                     |
|-------------------|------------------------------------------------------------------------------------------------------------|
| material library  | `mtllib <string>.mtl`                                                                                      |
| model part        | `s <child-name> <parent-name> <translation> <rotation> <scale> <material-name> <start-index> <nb-indices>` |
| `<child-name>`    | `<string>`                                                                                                 |
| `<parent-name>`   | `<string>`                                                                                                 |
| `<translation>`   | `<F32> <F32> <F32>`                                                                                        |
| `<rotation>`      | `<F32> <F32> <F32>`                                                                                        |
| `<scale>`         | `<F32> <F32> <F32>`                                                                                        |
| `<material-name>` | `<string>`                                                                                                 |
| `<start-index>`   | `<U32>`                                                                                                    |
| `<nb-indices>`    | `<U32>`                                                                                                    |
| `<string>`        | `<ANSI string without delimiters and EOFs>`                                                                |
 
## <a name="SS-Textures"></a>Textures
     
### .dds
* File mode: binary
* File extension: `dds` or `DDS`
* Use: storing textures
* Magic: `DDS`
* Syntax: see [DDS format](https://msdn.microsoft.com/en-us/library/windows/desktop/bb943991%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396#File_Layout1).

## <a name="SS-Variable-Scripts"></a>Variable Scripts

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
| property          | `F32   <property-name> <F32>`                                      |
| property          | `F32x2 <property-name> <F32> <F32>`                                |
| property          | `F32x3 <property-name> <F32> <F32> <F32>`                          |
| property          | `F32x4 <property-name> <F32> <F32> <F32> <F32>`                    |
| property          | `S32   <property-name> <S32>`                                      |
| property          | `S32x2 <property-name> <S32> <S32>`                                |
| property          | `S32x3 <property-name> <S32> <S32> <S32>`                          |
| property          | `S32x4 <property-name> <S32> <S32> <S32> <S32>`                    |
| property          | `U32   <property-name> <U32>`                                      |
| property          | `U32x2 <property-name> <U32> <U32>`                                |
| property          | `U32x3 <property-name> <U32> <U32> <U32>`                          |
| property          | `U32x4 <property-name> <U32> <U32> <U32> <U32>`                    |
| property          | `string <property-name> <string>`                                  |
| `<property-name>` | `<string>`                                                         |
| `<string>`        | `<ANSI string without delimiters and EOFs>`                        |

<p align="center">Copyright © 2016-2025 Matthias Moulin. All Rights Reserved.</p>
