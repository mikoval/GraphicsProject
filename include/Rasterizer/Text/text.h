#ifndef GL_TEXT_H
#define GL_TEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <Rasterizer/Core/glContextUtil.h>

#define ARIEL_FONT "assets/Fonts/arial.ttf"


struct character_info {
  float ax; // advance.x
  float ay; // advance.y
  
  float bw; // bitmap.width;
  float bh; // bitmap.rows;
  
  float bl; // bitmap_left;
  float bt; // bitmap_top;
  
  float tx; // x offset of glyph in texture coordinates
};



class TextRenderer {
private:
	character_info c[128];

	int atlas_width;
	int atlas_height;
	GLuint tex;
	GLuint *program;

public:
	TextRenderer(string path, GLuint *program);
	void drawText(const char *text, float x, float y, float sx, float sy);
};

#endif