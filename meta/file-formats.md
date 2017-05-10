# File Formats

## Fonts

### .spritefont
* File mode: binary
* File extension: `spritefont` or `SPRITEFONT`
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
  * only a subset is supported
  * `map_decal` instead of `decal`
  * `map_disp` instead of `disp`
  * `map_bump` instead of `bump`

## Meshes

### .msh
* File mode: binary
* File extension: `msh` or `MSH`
* Use: storing one vertex buffer and its associated index buffer. `VertexT` and `IndexT` are not included in the file.
* Magic: `MAGEmesh`
* Syntax:
  * `MAGEmesh <nb-vertices> <nb-indices> <vertices> <indices>`
     * `<nb-vertices>` = `<uint32_t>`
     * `<nb-indices>` = `<uint32_t>`
     * `<vertices>` = `<VertexT> ... <VertexT>` (`<nb-vertices>` *times*)
     * `<indices>` = `<IndexT> ... <IndexT>` (`<nb-indices>` *times*)
     
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
  * [comment line] `# <comment> \n`
  * [empty line] `\n`
  * [material library] `mtllib <delimiter> <ANSI string without delimiters and EOFs>.mtl` *`<delimiter>`* `\n`
  * [model part] `s <delimiter> <child-name> <delimiter> <parent-name> <delimiter> <material-name> <delimiter> <start-index> <delimiter> <nb-indices>`*`<delimiter>`* `\n`
     * `<child-name>` = `<ANSI string without delimiters and EOFs>`
     * `<parent-name>` = `<ANSI string without delimiters and EOFs>`
     * `<material-name>` = `<ANSI string without delimiters and EOFs>`
     * `<start-index>` = `<uint32_t>`
     * `<nb-indices>` = `<uint32_t>`
     
## Textures
     
### .dds
* File mode: binary
* File extension: `dds` or `DDS`
* Use: storing textures
* Magic: `DDS`
* Syntax: see [DDS format](https://msdn.microsoft.com/en-us/library/windows/desktop/bb943991%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396#File_Layout1).

## Variable Scripts

### .vs
* File mode: ANSI
* File extension: `vs` or `VS`
* Use: storing simple properties
* (Line) comment characters:
  * `#`
* Delimiters: 
  * `_` (space character) 
  * `\t` (tab character)
  * `\n` (EOL: end of line character)
  * `\r`(CR: carriage return character)
* Syntax:
  * [comment line] `# <comment> \n`
  * [empty line] `\n`
  * [property] `<property-type> <delimiter> <property-name> <delimiter> <property-value>` *`<delimiter>`* `\n`
    * `<property-type>` = `bool|int|int2|int3|float|float2|float3|float4|color|string`
    * `<property-name>` = `<ANSI string without delimiters and EOFs>`
    * `<property-value>` =
        * `true|false` (`bool`)
        * `<int32_t>` (`int`)
        * `<int32_t> <delimiter> <int32_t>` (`int2`)
        * `<int32_t> <delimiter> <int32_t> <delimiter> <int32_t>` (`int3`)
        * `<float>` (`float`)
        * `<float> <delimiter> <float>` (`float2`)
        * `<float> <delimiter> <float> <delimiter> <float>` (`float3`)
        * `<float> <delimiter> <float> <delimiter> <float> <delimiter> <float>` (`float4`)
        * `<float> <delimiter> <float> <delimiter> <float> <delimiter> <float>` (`color`)
        * `"<ANSI string without EOFs>"` (`string`) (`"` characters in the string must be escaped like `\"`)
