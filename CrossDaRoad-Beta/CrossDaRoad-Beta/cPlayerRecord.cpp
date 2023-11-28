#include "cPlayerRecord.h"

cPlayerRecord::cPlayerRecord()
{
    Reset();
}

void cPlayerRecord::Reset()
{
    sName = "";
}

/// @brief Getter for player name
std::string cPlayerRecord::GetName() const
{
    return sName;
}

/// @brief Setter for player name
/// @param Name Name of player
void cPlayerRecord::SetName(const std::string& Name)
{
    this->sName = Name;
}

void cPlayerRecord::Read(std::istream& input) {
    input >> sName;
}

void cPlayerRecord::Write(std::ostream& output) const {
    output << sName;
}

std::istream& operator>>(std::istream& input, cPlayerRecord& playerRecord) {
    playerRecord.Read(input);
    return input;
}

std::ostream& operator<<(std::ostream& output, const cPlayerRecord& playerRecord) {
    playerRecord.Write(output);
    return output;
}