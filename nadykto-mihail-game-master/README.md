# Hike

## Unix systems

Check the Python2.7 is installed on the system. Usually it's already installed.

### Run

From the project root path just run:

```bash
make
```

## Windows

Supposing you are using MSYS2 and MinGW toolchain. Other toolchains aren't supported.

Check the Python2.7 is installed:

```bash
pacman -S python2 # install it
python2 --version
```

Check the make is installed:

```bash
mingw32-make.exe
```

### Run

From the project root path just run:

```bash
mingw32-make.exe
```

## Features
Game entities can have loot - sword and armor. Sword adds damage from 1 to 3, armor adds protection from 1 to 3 depending on their types. If entity haves loot, it will be visible in graphical mode. ![entity](resource/textures/loot_entities.png)   
If you kill an enemy entity with loot, it will drop out into free slots around the entity. In text mode sword visible `S` and armor `A`. Loot characteristics can be seen in the interface. If the player already has loot and gets a new one, the old one will drop out in free slot if there is one.  
  
Player can add health with potions ![entity](resource/textures/red_potion.png) ![entity](resource/textures/yellow_potion.png). In text mode visible `P`.    
