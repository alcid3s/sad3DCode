#pragma once

#include "tigl.h"
#include <string>

class Texture {
public:
	Texture(const std::string& path);
	~Texture();

	void bind();
	void unbind();

	inline int GetWidth() const { return t_Width; }
	inline int GetHeight() const { return t_Height; }
private:
	unsigned int t_TextureID;
	std::string t_Path;
	unsigned char* t_Buffer;
	int t_Width, t_Height, t_BPP;
};