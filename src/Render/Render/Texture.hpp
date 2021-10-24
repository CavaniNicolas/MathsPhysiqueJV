#pragma once

#include <string>

namespace render
{

class Texture
{
  private:
    unsigned int m_rendererID;
    std::string m_filepath;
    unsigned char* m_localBuffer;
    int m_width;
    int m_height;
    int m_bpp; // bits per pixel

  public:
    Texture(const std::string& path);
    ~Texture();

    // We dont want to be able to copy as we simply handle it using an int
    // for the moment, and not a memory address to the actual opengl object
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int getWidth() const
    {
        return m_width;
    }
    inline int getHeight() const
    {
        return m_height;
    }
};

} // namespace render
