#ifndef C_PLAYER_PHYSIC_H
#define C_PLAYER_PHYSIC_H

#include <iostream>

class cPlayerPhysic
{
private: // Velocity properties
    float fFrogVelocityX;   ///< Velocity of player in X-axis
    float fFrogVelocityY;      ///< Velocity of player in Y-axis

private: // Animation properties
    float fFrogAnimPosX;    ///< Animation position of player in X-axis
    float fFrogAnimPosY;    ///< Animation position of player in Y-axis
    
private: // Logical properties
    float fFrogLogicPosX;    ///< Logic position of player in X-axis
    float fFrogLogicPosY;    ///< Logic position of player in Y-axis

public: // Constructors & Destructor
    cPlayerPhysic();

public: // Initializer & Clean-up
    void Reset();

public: // Checkers
    bool IsPlayerOutOfBounds() const;

public: // Validators
    bool CanMoveLeft() const;
    bool CanMoveRight() const;
    bool CanMoveUp() const;
    bool CanMoveDown() const;

public: // Getters
    float GetPlayerAnimationPositionX() const;
    float GetPlayerAnimationPositionY() const;
    float GetPlayerLogicPositionX() const;
    float GetPlayerLogicPositionY() const;
    float GetPlayerVelocityX()const;
    float GetPlayerVelocityY()const;

private: // Utilities
    static float FixFloat(float fValue, int nDigits = 9);

public: // Setters
    void SetVelocityX(float fVelocityX);
    void SetVelocityY(float fVelocityY);
    void SetVelocity(float fVelocityX, float fVelocityY);
    void SetAnimationPositionX(float fPositionX);
    void SetAnimationPositionY(float fPositionY);
    void SetAnimationPosition(float fPositionX, float fPositionY);
    void SetLogicPositionX(float fPositionX);
    void SetLogicPositionY(float fPositionY);
    void SetLogicPosition(float fPositionX, float fPositionY);

public: // Synchronizer
    void SynchronizePosition(bool bAnimToLogic = true);
    bool OnFixPlayerPosition();

public: // Input - Output
    void Read(std::istream& input);
    void Write(std::ostream& output) const;
    friend std::istream& operator>>(std::istream& input, cPlayerPhysic& playerPhysic);
    friend std::ostream& operator<<(std::ostream& output, const cPlayerPhysic& playerPhysic);
};

#endif // C_PLAYER_PHYSIC_H