#pragma once
#include "stdafx.h"
#include "Application.h"
#include "FileReader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

typedef unsigned int uint;
typedef const char* string;

class FontManager
{
public:
	static FontManager* instance()
	{
		static CGuard g;   // Dealocation
		if (!INSTANCE)
			INSTANCE = new FontManager();
		return INSTANCE;
	}

	virtual ~FontManager() 
	{
		for (auto face : m_Faces)
		{
			FT_Done_Face(face.second);
		}
		FT_Done_FreeType(m_Library);
	};

	static void registerFont(string fontName, string path)
	{
		instance()->registerFontLocal(fontName, path);
	}

	void registerFontLocal(string fontName, string path)
	{
		if (m_Library == nullptr || m_Faces[fontName] != nullptr)
		{
			return;
		}

		uint lowestID = m_Faces.size();
		if (lowestID >= 15)
		{
			Debug::error("Cannot add font to Library, 15 fonts is maximum!");
		}

		FT_Face face;
		if (FT_New_Face(m_Library, path, 0, &face)) {
			Debug::error("Could not open font!");
			return;
		}

		// Set Standard Values
		FT_Set_Pixel_Sizes(face, 0, 48);
		// Disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		m_Faces.insert(std::pair<std::string, FT_Face>(fontName, face));
	}

	static void removeFont(string fontName)
	{
		instance()->removeFontLocal(fontName);
	}

	void removeFontLocal(string fontName)
	{
		if (m_Library == nullptr || m_Faces[fontName] == nullptr)
		{
			return;
		}
		FT_Done_Face(m_Faces[fontName]);
		m_Faces.erase(fontName);
	}

	static FT_Face* get_Face(string fontName)
	{
		return instance()->get_FaceLocal(fontName);
	}

	FT_Face* get_FaceLocal(string fontName)
	{
		if (m_Library == nullptr || m_Faces[fontName] == nullptr)
		{
			return nullptr;
		}
		return &m_Faces[fontName];
	}

	static void renderText(string fontName, string text, float x, float y, float sx, float sy)
	{
		instance()->renderTextLocal(fontName, text, x, y, sx, sy);
	}

	void renderTextLocal(string fontName, string text, float x, float y, float sx, float sy) {
		string p;

		FT_Face* face = &m_Faces[fontName];

		for (p = text; *p; p++) {
			if (FT_Load_Char(*face, *p, FT_LOAD_RENDER))
				continue;

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				(*face)->glyph->bitmap.width,
				(*face)->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				(*face)->glyph->bitmap.buffer
			);

			float x2 = x + (*face)->glyph->bitmap_left * sx;
			float y2 = -y - (*face)->glyph->bitmap_top * sy;
			float w = (*face)->glyph->bitmap.width * sx;
			float h = (*face)->glyph->bitmap.rows * sy;

			glUseProgram(m_Program);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			GLfloat black[4] = { 0, 0, 0, 1 };
			glUniform4fv(glGetUniformLocation(m_Program, "color"), 1, black);

			glUniform4fv(2, 1, black);

			GLfloat box[4][4] = {
				{ x2,     -y2    , 0, 0 },
			{ x2 + w, -y2    , 1, 0 },
			{ x2,     -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			x += ((*face)->glyph->advance.x / 64) * sx;
			y += ((*face)->glyph->advance.y / 64) * sy;
		}
	}

private:
	FontManager() {
		if (FT_Init_FreeType(&m_Library)) {
			Debug::error("Could not init freetype library");
			Debug::warning("The Application will run but won't draw text.");
			return;
		}
		GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

		std::string shaderPath = "shaders/freetype";

		std::string result = FileReader::openFile(shaderPath + ".vert");
		if (result == "") {
			Debug::error("Impossible to open the file " + shaderPath + ".vert");
			Application::close();
			return;
		}
		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		const char *vs_source = result.c_str();
		glShaderSource(vs, 1, &vs_source, NULL);
		glCompileShader(vs);
		glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
		if (!compile_ok) {
			Debug::error("Error in vertex shader!");
			Application::close();
			return;
		}

		result = FileReader::openFile(shaderPath + ".frag");
		if (result == "") {
			Debug::error("Impossible to open the file " + shaderPath + ".frag");
			Application::close();
			return;
		}
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		const char *fs_source = result.c_str();
		glShaderSource(fs, 1, &fs_source, NULL);
		glCompileShader(fs);
		glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
		if (!compile_ok) {
			Debug::error("Error in fragment shader!");
			Application::close();
			return;
		}

		m_Program = glCreateProgram();
		glAttachShader(m_Program, vs);
		glAttachShader(m_Program, fs);
		glLinkProgram(m_Program);
		glGetProgramiv(m_Program, GL_LINK_STATUS, &link_ok);
		if (!link_ok) {
			Debug::error("Error in glLinkProgram!");
			Application::close();
			return;
		}
	}

	FontManager(const FontManager&);

	static FontManager* INSTANCE;

	FT_Library m_Library;
	std::map<std::string, FT_Face> m_Faces;
	GLuint m_Program;

	class CGuard
	{
	public:
		~CGuard()
		{
			if (NULL != FontManager::INSTANCE)
			{
				delete FontManager::INSTANCE;
				FontManager::INSTANCE = NULL;
			}
		}
	};
};

FontManager* FontManager::INSTANCE = 0;