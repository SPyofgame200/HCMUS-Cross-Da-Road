# Map Standard

## Table of Contents

- [Table of Contents](#table-of-contents)
- [Map File Name](#map-file-name)
- [Map File Data](#map-file-data)

## Map File Name

The map name should have the form of `map<id>.txt`, where `<id>` is an unsigned integer

For example:

- `map0.txt`
- `map27.txt`
Negative ids can be considered as an easter egg but have not been implemented yet.

## Map File Data

The map utilizes objects to control graphic and map objects, defined as follows:

```cpp
struct GraphicCell
{
    char graphic;            ///< Character representing the graphic
    int nRowPos;             ///< Row of the cell
    int nColPos;             ///< Column of the cell

    // Constructors & Destructor
    GraphicCell();
    GraphicCell(char graphic, int nRowPos, int nColPos);
    ~GraphicCell();
};

class MapObject
{
private: // Identity attributes
    char code;                ///< Sprite code chacters for map editor
    std::string sCategory;      ///< Category, allow categorize configuration if needed

private: // Flag attributes
    bool isWinning;             ///< If the player will win the game to move here
    bool isBlocked;             ///< If the player shouldn't be able to move here
    bool isDanger;              ///< If the player should be killed to move here

private: // Sprite attributes
    std::string sSpriteName;    ///< Sprite name (*.png), for sprite loading
    int32_t nSpritePosX;        ///< X initial position for drawing sprite
    int32_t nSpritePosY;        ///< Y initial position for drawing sprite
    int32_t nSpriteFrame;       ///< The number of frame the sprite run, for animation
    
private: // Background attributes
    std::string sBackgroundName;///< Background name (*.png), for sprite's background
    int32_t nBackgroundPosX;    ///< X initial position for drawing background
    int32_t nBackgroundPosY;    ///< Y initial position for drawing background
    int32_t nBackgroundFrame;   ///< The number of frame the background run, for animation
    
private: // Lane attributes
    float fPlatformDrag;        ///< Platform dragging speed if the player land on them

private: // Summon attributes
    char summon;                ///< The chance of summoning another sprite with encoded = summon
    float fDuration;            ///< The duration (in seconds) of that sprite to be appeared
    float fCooldown;            ///< The cooldown durations for the two consecutive summoning
    float fChance;              ///< The probability of summoning in each second
    float fPredelay;            ///< The first delayed duration before the summon happened
    int32_t nSummonLimit;        ///< The limitation of summons
}

std::map<char, MapObject> mapSprites;
```

We use `attribute=value` style in order to extract data from a txt file.

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
