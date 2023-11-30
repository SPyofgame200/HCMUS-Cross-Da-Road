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
    bool OnRenderPlayerIdle() const;
    bool OnRenderPlayerJumpStart() const;
    bool OnRenderPlayerJumpContinue() const;
    bool OnRenderPlayerJumpStop() const;

public: // Player Renderers
    bool OnRenderPlayer() const;
    bool OnRenderPlayerDeath();
    bool OnRender();
};

#endif // H_PLAYER_RENDER_H
