# Frequently Asked Questions 

## Meta

### What is MAGE?

> *I return each time leaving fresh markers that I hope, in the full glare of my hopelessness, will have blossomed into fresh insight in the interim.*

First and foremost, MAGE is a rendering and game engine (or at the very least is supposed to be in the long run). Furthermore, MAGE is a journey. A journey of exploring and mastering C++ standards. A journey of best practices and proper designs aiming at consistency, clarity, efficiency and effectiveness. A journey of falling and changing directions. A journey of continuous learning, reflecting and philosophizing.

### Is MAGE still under (active) development?

MAGE v1 is still under active development.

### Does the MAGE logo refer to a *Black Mage* of Final Fantasy?

Apparently, the author of the full image intended to portray a *Black Mage* of the Final Fantasy game series. 
I, however, never played any Final Fantasy game and nor was I aware of the existence of these characters till some friend pointed this out at first glance. 
So for me, the logo just represents a mysterious, unknown mage 🧙 and not some reference to a particular game or game series.

## Use

### How to build the demo project?

1. Open the Solution file `MAGE\IDE\VS\MAGE.sln` in Visual Studio 2019 (or higher).
2. Build the Solution (Platform: `x64|x86`, Configuration: `Debug|Release`).
3. Reposition the [assets directory](https://github.com/matt77hias/MAGE-Assets) and all of its contents to the `MAGE\Bin\<Platform>\<Configuration>\Demo\assets` directory. This is required for running the .exe from inside and outside Visual Studio.
4. Run `MAGE\Bin\<Platform>\<Configuration>\Demo\Demo.exe` from inside or outside Visual Studio.
5. Have fun! 🧙

Sample scene - buttons:
  * mouse: camera
  * arrows (or WASD): movement
  * left shift: vertical down movement
  * right shift: vertical up movement
  * F1: terminate
  * F2: toggle freezing camera orientation
  * F3: switch scene
  * F4: toggle editor
