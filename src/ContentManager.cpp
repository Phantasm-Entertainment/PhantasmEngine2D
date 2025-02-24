#include "PhEngine/ContentManager.h"

#include <brotli/decode.h>

#include <iostream>

namespace PHENGINE_NAMESPACE
{
    const char ContentManager::m_FileHeader[8] = { 80, 69, 67, 70, 2, 3, 1, 7 };

    std::uint32_t ContentManager::ReadUInt32(char* b)
    {
        unsigned char* buffer = reinterpret_cast<unsigned char*>(b);
        return std::uint32_t((buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | (buffer[3]));
    }

    std::uint16_t ContentManager::ReadUInt16(char* b)
    {
        unsigned char* buffer = reinterpret_cast<unsigned char*>(b);
        return std::uint16_t((buffer[0] << 8) | (buffer[1]));
    }

    static void PE_CloseFile(std::FILE* fp) noexcept(true)
    {
        std::fclose(fp);
    }

    struct SpriteFontInfo
    {
        SpriteFontInfo(const std::string& name, std::uint16_t a, std::uint16_t d, std::uint16_t l)
        : m_Name(name), m_Ascender(a), m_Descender(d), m_LineSpacing(l) {}

        std::string m_Name;
        std::uint16_t m_Ascender;
        std::uint16_t m_Descender;
        std::uint16_t m_LineSpacing;
    };

    void ContentManager::LoadContentFile(const std::string& path)
    {
        std::unique_ptr<std::FILE, decltype(&PE_CloseFile)> fp(std::fopen(path.c_str(), "rb"), &PE_CloseFile);

        if (!fp) { throw Exception("could not open file"); }

        char buffer[255];

        if (std::fread(&buffer, 1, 22, fp.get()) != 22) { throw Exception("not a valid content file 1"); }

        if (std::memcmp(&buffer, &m_FileHeader, 8) != 0) { throw Exception("not a valid content file 2"); }

        std::uint32_t version = ReadUInt32(&buffer[8]);
        std::uint16_t atlasPages = ReadUInt16(&buffer[12]);
        std::uint32_t textureListSize = ReadUInt32(&buffer[14]);
        std::uint32_t fontListSize = ReadUInt32(&buffer[18]);
        std::uint16_t ascender, descender, lineSpacing;
        std::uint8_t nameLen;
        std::vector<SpriteFontInfo> spriteFontInfo;

        for (std::uint32_t i = 0; i < fontListSize; ++i)
        {
            if (std::fread(buffer, 1, 7, fp.get()) != 7) { throw Exception("not a valid content file 3"); }

            ascender = ReadUInt16(buffer);
            descender = ReadUInt16(buffer + 2);
            lineSpacing = ReadUInt16(buffer + 4);
            nameLen = buffer[6];

            if (std::fread(buffer, 1, nameLen, fp.get()) != nameLen) { throw Exception("not a valid content file 4"); }

            spriteFontInfo.emplace_back(std::string(buffer, nameLen), ascender, descender, lineSpacing);
        }

        std::uint16_t pageNum, x, y, w, h;
        std::size_t imageDataSize;
        std::uint8_t compressType;
        std::int32_t bearingX, bearingY, advance;
        std::uint8_t code;

        std::vector<AtlasPage> pages;

        for (std::uint16_t i = 0; i < atlasPages; ++i)
        {
            std::unique_ptr<unsigned char[]> data = std::make_unique<unsigned char[]>(4096 * 4096 * 4);
            std::memset(data.get(), 0, 4096 * 4096 * 4);
            pages.emplace_back(4096, 4096, std::move(data));
        }

        for (std::uint32_t i = 0; i < textureListSize; ++i)
        {
            if (std::fread(buffer, 1, 1, fp.get()) != 1) { throw std::string("not a valid content file 5"); }

            if (buffer[0] == 0)
            {
                if (std::fread(&buffer, 1, 11, fp.get()) != 11) { throw std::string("not a valid content file 6"); }

                pageNum = ReadUInt16(buffer);
                x = ReadUInt16(buffer + 2);
                y = ReadUInt16(buffer + 4);
                w = ReadUInt16(buffer + 6);
                h = ReadUInt16(buffer + 8);
                imageDataSize = w * h * 4;
                nameLen = buffer[10];
                std::cout << pageNum << '\n';
                std::cout << x << '\n';
                std::cout << y << '\n';
                std::cout << w << '\n';
                std::cout << h << '\n';

                if (std::fread(&buffer, 1, nameLen, fp.get()) != nameLen) { throw std::string("not a valid content file 7"); }

                std::string name(buffer, nameLen);

                if (std::fread(&buffer, 1, 1, fp.get()) != 1) { throw std::string("not a valid content file 8"); }

                compressType = buffer[0];

                std::shared_ptr<char[]> imageData = std::make_shared<char[]>(imageDataSize);

                if (compressType == 0)
                {
                    if (std::fread(imageData.get(), 1, imageDataSize, fp.get()) != imageDataSize) { throw std::string("not a valid content file 9"); }
                }
                else
                {
                    if (std::fread(&buffer, 1, 4, fp.get()) != 4) { throw std::string("not a valid content file 10"); }

                    std::uint32_t compressLen = ReadUInt32(buffer);
                    std::unique_ptr<char[]> compressedBuff = std::make_unique<char[]>(compressLen);

                    if (std::fread(compressedBuff.get(), 1, compressLen, fp.get()) != compressLen) { throw std::string("not a valid content file 11"); }

                    if (BrotliDecoderDecompress(compressLen, reinterpret_cast<uint8_t*>(compressedBuff.get()), &imageDataSize, reinterpret_cast<uint8_t*>(imageData.get())) != BROTLI_DECODER_RESULT_SUCCESS)
                    {
                        throw std::string("decompress error");
                    }
                }

                std::cout << "Found " << name << " on page " << std::to_string(pageNum) << '\n';
                std::size_t atlasRowSize = 4096*4;

                for (std::uint16_t blitY = 0; blitY < h; ++blitY)
                {
                    for (std::uint16_t blitX = 0; blitX < w; ++blitX)
                    {
                        std::size_t destIndex = (y + blitY) * atlasRowSize + (x + blitX) * 4;
                        std::size_t sourceIndex = blitY * (w * 4) + (blitX * 4);
                        //std::cout << destIndex << ' ' << sourceIndex << '\n';

                        for (std::uint16_t i = 0; i < 4; ++i)
                        {
                            pages[pageNum].GetData()[destIndex + i] = imageData.get()[sourceIndex + i];
                        }
                    }
                }
            }
            else if (buffer[0] == 1)
            {
                if (std::fread(&buffer, 1, 24, fp.get()) != 24) { throw std::string("not a valid content file 12"); }

                pageNum = ReadUInt16(buffer);
                x = ReadUInt16(buffer + 2);
                y = ReadUInt16(buffer + 4);
                w = ReadUInt16(buffer + 6);
                h = ReadUInt16(buffer + 8);
                imageDataSize = w * h * 4;
                code = buffer[10];
                bearingX = ReadUInt32(buffer + 11);
                bearingY = ReadUInt32(buffer + 15);
                advance = ReadUInt32(buffer + 19);
                nameLen = buffer[23];

                if (std::fread(&buffer, 1, nameLen, fp.get()) != nameLen) { throw std::string("not a valid content file 13"); }

                std::string name(reinterpret_cast<const char*>(&buffer), nameLen);
                std::shared_ptr<char[]> imageData;

                if (w != 0 && h != 0)
                {
                    if (std::fread(&buffer, 1, 1, fp.get()) != 1) { throw std::string("not a valid content file 14"); }

                    compressType = buffer[0];

                    imageData = std::make_shared<char[]>(imageDataSize);

                    if (compressType == 0)
                    {
                        if (std::fread(imageData.get(), 1, imageDataSize, fp.get()) != imageDataSize) { throw std::string("not a valid content file 15"); }
                    }
                    else
                    {
                        if (std::fread(&buffer, 1, 4, fp.get()) != 4) { throw std::string("not a valid content file 16"); }

                        std::uint32_t compressLen = ReadUInt32(buffer);
                        std::unique_ptr<std::uint8_t[]> compressedBuff = std::make_unique<std::uint8_t[]>(compressLen);

                        if (std::fread(compressedBuff.get(), 1, compressLen, fp.get()) != compressLen) { throw std::string("not a valid content file 17"); }

                        if (BrotliDecoderDecompress(compressLen, compressedBuff.get(), &imageDataSize, reinterpret_cast<uint8_t*>(imageData.get())) != BROTLI_DECODER_RESULT_SUCCESS)
                        {
                            throw std::string("decompress error");
                        }
                    }
                }

                //contentFile->m_Pages[pageNum]->m_Textures.push_back(std::make_shared<PageTexture>(name, x, y, w, h, imageData, code, bearingX, bearingY, advance));
            }
            else
            {
                throw std::string("not a valid content file 18");
            }
        }

        fp.reset();
        if (m_Atlas != nullptr) { delete m_Atlas; }
        m_Atlas = new TextureAtlas(m_GL, std::move(pages));
        // m_AtlasPageCount = atlasPages;
        // m_AtlasPageSize = 4096;
        // m_GL->GenTextures(1, &m_AtlasTexture);
        // m_GL->BindTexture(GL_TEXTURE_2D, m_AtlasTexture);
        // m_GL->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // m_GL->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // m_GL->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // m_GL->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // m_GL->TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_AtlasPageSize, m_AtlasPageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, pages[0].GetData());
        //m_GL->TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1920, 1080, 0, GL_RGBA, GL_UNSIGNED_BYTE, pages[0].GetData());
    }
}