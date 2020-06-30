#include <Text/text.h>


#include <Core/Base.h>

TextRenderer::TextRenderer(string path, GLuint *program){
	this->program = program;
	FT_Library  library;
	FT_Face     face;
	int error;
	string font = ARIEL_FONT;
	error = FT_Init_FreeType( &library );
	if ( error )
	{
		printf("FAILED TO INIT FT LIBRARY \n" );
	}

	error = FT_New_Face( library, font.data(), 0, &face );

	if ( error == FT_Err_Unknown_File_Format )
	{
		printf("INVALID FONT TYPE FOR : %s \n", font.data());
	} else if ( error )
	{
		printf("ERROR LOADING FONT : %s \n", font.data());
	}

	FT_Set_Pixel_Sizes(face, 0, 48);  

	FT_GlyphSlot g = face->glyph;
	unsigned int w = 0;
	unsigned int h = 0;

	for(int i = 32; i < 128; i++) {
		if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
			fprintf(stderr, "Loading character %c failed!\n", i);
			continue;
		}

		w += g->bitmap.width;
		h = std::max(h, g->bitmap.rows);
	}

	/* you might as well save this value as it is needed later on */
	atlas_width = w;
	atlas_height = h;


	glActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &tex);

	glBindTexture(GL_TEXTURE_2D, tex);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

    //glGenerateMipmap(GL_TEXTURE_2D); 



	int x = 0;

	memset(c, 0, sizeof(c));
	for(int i = 32; i < 128; i++) {
		if(FT_Load_Char(face, i, FT_LOAD_RENDER))
			continue;

		glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

		c[i].ax = g->advance.x >> 6;
		c[i].ay = g->advance.y >> 6;

		c[i].bw = g->bitmap.width;
		c[i].bh = g->bitmap.rows;

		c[i].bl = g->bitmap_left;
		c[i].bt = g->bitmap_top;

		c[i].tx = ((float)x / w);

		x += g->bitmap.width;
	}

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void TextRenderer::drawText(const char *text, float x, float y, float sx, float sy){



	struct point {
		GLfloat x;
		GLfloat y;
		GLfloat s;
		GLfloat t;
	} coords[6 * strlen(text)];

	renderer.setProgram(*program);

	int n = 0;

	for(const char *p = text; *p; p++) {


		float x2 =  x + c[*p].bl * sx;
		float y2 = -y - c[*p].bt * sy;
		float w = c[*p].bw * sx;
		float h = c[*p].bh * sy;


    /* Advance the cursor to the start of the next character */
		x += c[*p].ax * sx;
		y += c[*p].ay * sy;

    /* Skip glyphs that have no pixels */
		if(!w || !h){
			continue;
		}

		coords[n++] = (point){x2,     -y2    , c[*p].tx, 0};
		coords[n++] = (point){x2 + w, -y2    , c[*p].tx + c[*p].bw / atlas_width,   0};
	    coords[n++] = (point){x2,     -y2 - h, c[*p].tx, c[*p].bh / atlas_height}; //remember: each glyph occupies a different amount of vertical space
	    coords[n++] = (point){x2 + w, -y2    , c[*p].tx + c[*p].bw / atlas_width,   0};
	    coords[n++] = (point){x2,     -y2 - h, c[*p].tx, c[*p].bh / atlas_height};
	    coords[n++] = (point){x2 + w, -y2 - h, c[*p].tx + c[*p].bw / atlas_width,   c[*p].bh / atlas_height};
	}

	GLuint buffer;
	GLuint target = 0;

			//Create default vertex array
	GLuint vao;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);


	glGenBuffers(1,&buffer);
	glBindBuffer(GL_ARRAY_BUFFER,buffer);

	        //Enable vertex buffer
	glEnableVertexAttribArray(target);
	glVertexAttribPointer(target,4,GL_FLOAT,GL_FALSE,0,0);


	glBufferData(GL_ARRAY_BUFFER, sizeof coords, coords, GL_DYNAMIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof coords2, coords2, GL_DYNAMIC_DRAW);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glUniform1i(glGetUniformLocation(*program, "text_atlas"), 0);


	glDrawArrays(GL_TRIANGLES, 0, n);
	
}