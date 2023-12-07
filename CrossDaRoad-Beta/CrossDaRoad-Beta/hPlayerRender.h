#ifndef H_PLAYER_RENDER_H
#define H_PLAYER_RENDER_H

// forward declaration
class hPlayer;

class hPlayerRender
{
private: // Dependency
    hPlayer* ptrPlayer;

public: // Constructors & Destructor
    hPlayerRender();
    hPlayerRender(hPlayer* ptrPlayer);
    ~hPlayerRender();

public: // Initializer & Clean-up
    bool SetupTarget(hPlayer* ptrPlayer);

public: // Player Render 
    bool OnRenderPlayerIdle(bool bSwim = false) const;
    bool OnRenderPlayerJumpStart(bool bSwim = false) const;
    bool OnRenderPlayerJumpContinue(bool bSwim = false) const;
    bool OnRenderPlayerJumpStop(bool bSwim = false) const;

public: // Player Renderers
    bool OnRenderPlayer(bool bSwim = false) const;
    bool OnRender(bool bSwim = false) const;
};

#endif // H_PLAYER_RENDER_H
