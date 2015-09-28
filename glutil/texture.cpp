/*
solution:	glib
			raytracing
project:	prenderer
			rtengine1
			glutil
file:		texture.cpp
author:		cj
*/

#include "texture.h"

namespace GLU {

	int FormatToSize(GLenum format) {
		switch(format) {
		case GL_RGB32F: return sizeof(float) * 3;
		default: throw COM::UnknownFormatException();
		}
	}

	/* Texture Impl */

	void Texture::Init(const COM::byte_t* pixelData) {
		COM_assert(0 < _width);
		COM_assert(0 < _height);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);
		if(GL_NO_ERROR != glGetError()) {
			COM::log << "Texture::Init: gen/bind texture failed" << std::endl;
			throw COM::GLException();
		}

		glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _format,
			_type, pixelData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	Texture::Texture(int width, int height, GLenum internalFormat, GLenum format,
		GLenum type, const COM::byte_t* pixelData)
		: _internalFormat(internalFormat), _format(format), _type(type), _width(width), _height(height)
	{
		Init(pixelData);
	}

	Texture::Texture(int width, int height, GLenum format, const COM::byte_t* pixelData) 
		: _internalFormat(format), _format(format), _type(GL_UNSIGNED_BYTE), _width(width), _height(height)
	{
		Init(pixelData);
	}

	void Texture::Bind(unsigned level) const {
		glx.ActiveTexture(GL_TEXTURE0 + level);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _id);
	}

	int Texture::Size(void) const {
		return _width * _height * FormatToSize(_internalFormat);
	}

	/* TextureManager Impl */

	std::string ToLower(const std::string& str) {
		std::string ret;
		for(std::size_t i = 0; i < str.length(); ++i) {
			char c = str[i];
			if(c >= 'A' && c <= 'Z') ret.push_back('a' + (c - 'A'));
			else ret.push_back(c);
		}
		return ret;
	}

	std::string Suffix(const std::string& str) {
		std::string suffix;
		std::size_t pos = str.find_last_of('.');
		if(std::string::npos != pos) {
			suffix = str.substr(pos + 1);
		}
		return suffix;
	}

	void TextureManager::RegisterAlloc(const std::string& suffix, texAlloc_t alloc) {
		if(std::string::npos != suffix.find('.')) {
			COM::log << "TextureManager::RegisterAlloc: suffix " << suffix << " contains '.'" << std::endl;
		}
		_allocs[ToLower(suffix)] = alloc;
	}

	GEN::Pointer<Texture> TextureManager::Get(const std::string& filename, FS::Loader& loader) {
		texIt_t texIt = _textures.find(filename);
		if(_textures.end() == texIt) {
			std::string suffix = ToLower(Suffix(filename));
			allocIt_t allocIt = _allocs.find(suffix);
			if(_allocs.end() == allocIt) {
				COM::log << "TextureManager::Get: for suffix '" << suffix << "' of filename " << filename
					<< " is no allocator registered" << std::endl;
				throw std::exception();
			}

			GEN::Pointer<FS::File> file = loader.GetFile(filename);
			GEN::Pointer<Texture> texture(allocIt->second(file));
			_textures[filename] = texture;

			return texture;
		} else {
			return texIt->second;
		}
	}

} // namespace GLU