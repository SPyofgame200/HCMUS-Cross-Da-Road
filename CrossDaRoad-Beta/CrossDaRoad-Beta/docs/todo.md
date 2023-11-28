# Version 0

#GamePlay
{
    @Directory
    {
        [x] Move all assets to data/assets/
            % finished 20/10/2023
        [x] Move all maps to data/maps/
            % finished 20/10/2023
        [ ] Move the game engine files (g-*.cpp, g-*.h) into another folders
        [ ] Move the object class files (c-*.cpp, c-*.h) into another folders
        [ ] Move the utilities functions files (u-*.cpp, u-*.h) into another folders
    }
    @Map
    {
        [x] Successfully load the map to the console
        [x] Load map data from "data/maps/map<id>.txt"
        [x] Load map names from "data/maps/mapNames.txt"
        [x] Switching map upon winning a level
        [x] Read platform information from the map 
            - platform = moveable object and lift player
            - anything that is safe and platform can lift player
            % finished 3/11/2023
        [ ] Blocked Zone detection
        [ ] Platform Zone detection
        [ ] Read music information from the map
        [ ] Separate cGame.* to uMap.* for convenient
        [ ] New effect: if Froggy stand on a platform for a short time,
            this platform will be disappear and Froggy will die
        [ ] New effect: if Froggy moves on mug environment, Froggy will move slowly.
            In there, obstacles will move quickly
        [ ] Flat land -> Swamp land -> Jungle -> Seashore -> Ocean -> Ice peak -> Lava -> Ghost land
    }
    @Music
    {
        [x] Add music to the game
            % finished noon 24/10/2023
        [x] Successfully run it as a thread
            % finished afternoon 24/10/2023
        [x] Separate music from cApp
            % finished afternoon 24/10/2023
        [x] Add function to stop the music
            % finished night 24/10/20232023
        [x] Add parameter to control the alias of the music being used
            % finished night 24/10/2023
        [x] Make the music thread less heavy
            - some sprites are being slowed down in order to run music
            % finished night 24/10/2023
                - dont use OnUserUpdate() to update distached thread
        [ ] Play music independently for each map
            - the music threads should be control safely
        [ ] Player dead soundtrack
        [ ] Menu song
    }
    @Player
    {
        [x] Jumping Animation
            % finished afternoon 3/11/2023
        [x] Safe landing on a platform
            % finished night 3/11/2023
        [ ] Reduce player hitbox
        [ ] Safe landing from platforms
        [ ] Load & Save player position cache
        [ ] Idle animation
    }
}

#App_Console
{
    @Menu
    {
        [ ] Add setting menu: using sprites newly added in cAssetsManager (with Setting Menu comment)
        [ ] Player can turn on/off music in setting menu, change the way Froggy moves (WSAD <==> Arrows)
    }
    @App
    {
        [x] Merge cApp.* and cGame.*
            - GameEngine use internal static variables that can not have multiple game engines
            - Because if the game engine is destroyed, static variables will be too
            - So we have to merge the game engine files into one, then separate them later
            % finished afternoon 25/10/2024
        [x] Separate cZone.* from cGame.*
            % finished night 25/10/2024
    }
    @Report
    {
        -> In order to report whats going on with the game, we should output something like:
        -> `cApp::OnMenu() switch to next menu <Arrow Down Key> pressed`
        -> Dont have to report too much, but important things must be outputed
        -> or atleast #ifdef #endif for debugging if needed
        [ ] report for cApp.cpp
        [ ] report for cAssetManager.cpp
        [ ] report for cGame.cpp
        [ ] report for cLane.cpp
        [ ] report for gGameEngine.cpp
        [ ] report for gPixel.cpp
        [ ] report for gResourcePack.cpp
        [ ] report for gSprite.cpp
        [ ] report for uAppConst.cpp
        [ ] report for uSound.cpp
        [ ] report for uStringUtils.cpp
    }
}