#include "gResourcePack.h"

/**
 * @file gResourcePack.cpp
 *
 * @brief Contains resource pack class implementation
 *
 * This file implements resource pack class for resource pack management (pack/unpack).
**/

namespace app
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////// CONSTRuCTORS & DESTRUCTOR ///////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor 
	ResourcePack::ResourcePack() = default;

	/// @brief Destructor
	ResourcePack::~ResourcePack()
	{
		ClearPack();
		std::cerr << "app::ResourcePack::~ResourcePack(): Successfully destructed" << std::endl;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////// PACK/UNPACK ////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// @brief Add file to pack (map)
	/// @param sFile File name
	/// @return engine::Code engine::SUCCESS if file was added to pack (map), engine::FAILURE otherwise
	engine::Code ResourcePack::AddToPack(const std::string& sFile)
	{
		std::ifstream ifs(sFile, std::ifstream::binary);
		if (!ifs.is_open())
			return engine::FAILURE;

		// Get File Size
		std::streampos p = ifs.tellg();
		ifs.seekg(0, std::ios::end);
		p = ifs.tellg() - p;
		ifs.seekg(0, std::ios::beg);

		// Create entry
		sEntry e;
		e.data = nullptr;
		e.nFileSize = static_cast<uint32_t>(p);

		// Read file into memory
		e.data = new uint8_t[(uint32_t)e.nFileSize];
		ifs.read(reinterpret_cast<char*>(e.data), e.nFileSize);
		ifs.close();

		// Add To Map
		mapFiles[sFile] = e;
		return engine::SUCCESS;
	}

	/// @brief Save pack to file
	/// @param sFile File name
	/// @return engine::Code engine::SUCCESS if pack was saved to file, engine::FAILURE otherwise
	engine::Code ResourcePack::SavePack(const std::string& sFile)
	{
		std::ofstream ofs(sFile, std::ofstream::binary);
		if (!ofs.is_open())
			return engine::FAILURE;

		// 1) Write Map
		size_t nMapSize = mapFiles.size();
		ofs.write(reinterpret_cast<char*>(&nMapSize), sizeof(size_t));
		for (auto& e : mapFiles) {
			size_t nPathSize = e.first.size();
			ofs.write(reinterpret_cast<char*>(&nPathSize), sizeof(size_t));
			ofs.write(e.first.c_str(), nPathSize);
			ofs.write(reinterpret_cast<char*>(&e.second.nID), sizeof(uint32_t));
			ofs.write(reinterpret_cast<char*>(&e.second.nFileSize), sizeof(uint32_t));
			ofs.write(reinterpret_cast<char*>(&e.second.nFileOffset), sizeof(uint32_t));
		}

		// 2) Write Data
		std::streampos offset = ofs.tellp();
		for (auto& e : mapFiles) {
			e.second.nFileOffset = static_cast<uint32_t>(offset);
			ofs.write(reinterpret_cast<char*>(e.second.data), e.second.nFileSize);
			offset += e.second.nFileSize;
		}

		// 3) Rewrite Map (it has been updated with offsets now)
		ofs.seekp(std::ios::beg);
		ofs.write(reinterpret_cast<char*>(&nMapSize), sizeof(size_t));
		for (auto& e : mapFiles) {
			size_t nPathSize = e.first.size();
			ofs.write(reinterpret_cast<char*>(&nPathSize), sizeof(size_t));
			ofs.write(e.first.c_str(), nPathSize);
			ofs.write(reinterpret_cast<char*>(&e.second.nID), sizeof(uint32_t));
			ofs.write(reinterpret_cast<char*>(&e.second.nFileSize), sizeof(uint32_t));
			ofs.write(reinterpret_cast<char*>(&e.second.nFileOffset), sizeof(uint32_t));
		}
		ofs.close();

		return engine::SUCCESS;
	}

	/// @brief Load pack from file
	/// @param sFile File name
	/// @return engine::Code engine::SUCCESS if pack was loaded from file, engine::FAILURE otherwise
	engine::Code ResourcePack::LoadPack(const std::string& sFile)
	{
		std::ifstream ifs(sFile, std::ifstream::binary);
		if (!ifs.is_open())
			return engine::FAILURE;

		// 1) Read Map
		size_t nMapEntries;
		ifs.read(reinterpret_cast<char*>(&nMapEntries), sizeof(size_t));
		for (size_t i = 0; i < nMapEntries; i++) {
			size_t nFilePathSize = 0;
			ifs.read(reinterpret_cast<char*>(&nFilePathSize), sizeof(size_t));

			std::string sFileName(nFilePathSize, ' ');
			for (size_t j = 0; j < nFilePathSize; j++)
				sFileName[j] = ifs.get();

			sEntry e;
			e.data = nullptr;
			ifs.read(reinterpret_cast<char*>(&e.nID), sizeof(uint32_t));
			ifs.read(reinterpret_cast<char*>(&e.nFileSize), sizeof(uint32_t));
			ifs.read(reinterpret_cast<char*>(&e.nFileOffset), sizeof(uint32_t));
			mapFiles[sFileName] = e;
		}

		// 2) Read Data
		for (auto& e : mapFiles) {
			e.second.data = new uint8_t[(uint32_t)e.second.nFileSize];
			ifs.seekg(e.second.nFileOffset);
			ifs.read(reinterpret_cast<char*>(e.second.data), e.second.nFileSize);
			e.second._config();
		}

		ifs.close();
		return engine::SUCCESS;
	}

	/// @brief Free memory for all files in pack (map)
	/// @return Always returns engine::SUCCESS by default
	engine::Code ResourcePack::ClearPack()
	{
		for (const auto& e : mapFiles) {
			delete[] e.second.data;
		}

		mapFiles.clear();
		return engine::SUCCESS;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////// GETTERS /////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// @brief Get stream buffer for file in pack (map)
	/// @param sFile File name
	/// @return Stream buffer for file in pack (map)
	app::ResourcePack::sEntry ResourcePack::GetStreamBuffer(const std::string& sFile)
	{
		return mapFiles[sFile];
	}

} // namespace app

////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// END OF FILE ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////