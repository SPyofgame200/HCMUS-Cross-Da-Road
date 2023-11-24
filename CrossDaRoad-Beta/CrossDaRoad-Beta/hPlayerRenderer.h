#ifndef H_PLAYER_RENDERER_H
#define H_PLAYER_RENDERER_H

// forward declaration
class hPlayer;

class hPlayerRenderer
{
private: // Dependency
	hPlayer* ptrPlayer;

public: // Constructors & Destructor
	hPlayerRenderer();
	hPlayerRenderer(hPlayer* ptrPlayer);
	~hPlayerRenderer();

public: // Initializer & Clean-up
	bool SetupTarget(hPlayer* ptrPlayer);

public: // Player Renderer 
	bool OnRenderPlayerIdle() const;
	bool OnRenderPlayerJumpStart() const;
	bool OnRenderPlayerJumpContinue() const;
	bool OnRenderPlayerJumpStop() const;

public: // Player Renderers
	bool OnRenderPlayer() const;
	bool OnRenderPlayerDeath();

};

#endif //H_PLAYER_RENDERER_H
