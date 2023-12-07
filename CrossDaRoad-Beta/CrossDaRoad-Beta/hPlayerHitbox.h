#ifndef H_PLAYER_HITBOX_H
#define H_PLAYER_HITBOX_H

// forward declaration
class hPlayer;

class hPlayerHitbox
{
private: // Dependency
    hPlayer* ptrPlayer;

public: // Constructors & Destructor
    hPlayerHitbox();
    hPlayerHitbox(hPlayer* ptrPlayer);
    ~hPlayerHitbox();

public: // Initializer & Clean-up
    bool SetupTarget(hPlayer* ptrPlayer);

public: // Hit detection
    bool IsHitTopLeft() const;
    bool IsHitTopRight() const;
    bool IsHitBottomLeft() const;
    bool IsHitBottomRight() const;
    bool IsHit() const;

public: // Blockage detection
    bool IsBlockedTopLeft() const;
    bool IsBlockedTopRight() const;
    bool IsBlockedBottomLeft() const;
    bool IsBlockedBottomRight() const;
    bool IsBlocked() const;

public: // Winning detection
    bool IsWinningTopLeft() const;
    bool IsWinningTopRight() const;
    bool IsWinningBottomLeft() const;
    bool IsWinningBottomRight() const;
    bool IsWinning() const;

public: // Platform detection
    bool IsOnPlatformTopLeft() const;
    bool IsOnPlatformTopRight() const;
    bool IsOnPlatformBottomLeft() const;
    bool IsOnPlatformBottomRight() const;
    bool IsOnPlatform() const;
};

#endif // H_PLAYER_HITBOX_H
