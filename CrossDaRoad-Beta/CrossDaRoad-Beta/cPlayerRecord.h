#ifndef C_PLAYER_RECORD_H
#define C_PLAYER_RECORD_H

#include <iostream>
#include <string>

class cPlayerRecord
{
private: // Player data 
    std::string sName;

public: // Constructors & Destructor
    cPlayerRecord();

public: // Initializer & Clean-up
    void Reset();

public: // Getters
    std::string GetName() const;

public: // Setters
    void SetName(const std::string& sName);

public: // Input - Output
    void Read(std::istream& input);
    void Write(std::ostream& output) const;
    friend std::istream& operator>>(std::istream& input, cPlayerRecord& playerRecord);
    friend std::ostream& operator<<(std::ostream& output, const cPlayerRecord& playerRecord);
};

#endif // C_PLAYER_RECORD_H

