# Map Standard

## Table of Contents

- [Map Standard](#map-standard)
  - [Table of Contents](#table-of-contents)
  - [Map File Name](#map-file-name)
  - [Map File Data](#map-file-data)

## Map File Name

The map name should have the form of `map<id>.txt`, where `<id>` is an unsigned integer

For example:

- `map0.txt`
- `map27.txt`

Negative id can be considered as an easter egg, but not implemented yet

## Map File Data

In each map, the data should be like this, in order for the game to read it

```cpp
sMapLane[i] fVelocity[i]
#
$ char[i] sprite=sSpriteName[i] background=sBackgroundName[i] category=sCategory[i]
: block=isBlocked[i] danger=isDanger[i] platformspeed=fPlatform[i] 
: drawX=nPosX[i] drawY=nPosY[i]
```

Using

```cpp
struct spriteData {
    char encode;
    std::string sSpriteName;
    std::string sBackgroundName;
    std::string sCategory;
    bool isBlocked;
    bool isDanger;
    float fPlatform;
    int32_t nPosX;
    int32_t nPosY;
    int32_t nID;
};

std::map<char, SpriteData> mapSprites;
```

For example

```cpp
x....x.............x 0
<@.............<@... 5.0
x....x.....x....x... 0
.....<@......<@.<@.. 2.7
x................x.. 0
#
$ x sprite=block
: block=true danger=false platformspeed=0.0
: drawY=0 drawX=0
$ . sprite=road
: block=false platformspeed=0.0 danger=false
: drawX=0 drawY=0
$ < background=road sprite=car1
: platformspeed=5.0 block=false danger=true
$ @ sprite=car2 background=road
: danger=true block=false platformspeed=5.0
: drawY=1 drawX=0 id = 0
#
music="ncs0"
```

The prefix of each defines its type, in another way

```cpp
string[0] float[0]
string[1] float[1]
...
string[N] float[N]
#
float[0] char[0] char[0] string[0] string[0] int[0] int[0]
float[1] char[1] char[1] string[1] string[1] int[1] int[1]
...
float[N] char[N] char[N] string[N] string[N] int[N] int[N]
```
