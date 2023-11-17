/**
 * @file gResourcePack.h
 *
 * @brief Contains resource pack class
 *
 * This file contains resource pack class for resource pack management (pack/unpack).
**/

#ifndef G_RESOURCE_PACK_H
#define G_RESOURCE_PACK_H

#include <fstream>
#include <string>
#include <map>
#include "gPixel.h"
#include "gConst.h"

namespace app
{
	/// @brief Class for resource pack management (pack/unpack)
	class ResourcePack
	{
	public:
		/// @brief  Structure for resource pack entry (file) information (ID, offset, size) and data (stream buffer)
		struct sEntry : public std::streambuf
		{
			uint32_t nID;         ///< File ID in pack
			uint32_t nFileOffset; ///< File offset in pack
			uint32_t nFileSize;   ///< File size in pack
			uint8_t* data;        ///< File data (stream buffer) in pack
			void _config() { this->setg(reinterpret_cast<char*>(data), reinterpret_cast<char*>(data), reinterpret_cast<char*>(data + nFileSize)); }
		};

	private:
		std::map<std::string, sEntry> mapFiles; ///< Map of files in pack (map) (key: file name, value: file entry)

	public: // Constructor & Destructor
		ResourcePack();
		~ResourcePack();

	public: // Methods for pack/unpack
		engine::Code AddToPack(const std::string& sFile);
		engine::Code SavePack(const std::string& sFile);
		engine::Code LoadPack(const std::string& sFile);
		engine::Code ClearPack();

	public: // Getters
		app::ResourcePack::sEntry GetStreamBuffer(const std::string& sFile);
	};

}

#endif // G_RESOURCE_PACK_H