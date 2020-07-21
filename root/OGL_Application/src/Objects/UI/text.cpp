/*in this first example of text printing i'm using an array of VBO for 
of the same size of the string. This way is easy to make it work but
when it comes to having a text that refresh at each frame it's a mess
in terms of memory leakage*/
#include <iostream>
#include<text.h>
#include <ft2build.h>
#include<applicationObjectManager.h>
#include<PrintHelper.h>
#include FT_FREETYPE_H


namespace textRendererNS {

	//GLuint TextRenderer::VAO;
	std::map<GLchar, Character> TextRenderer::charMap;
	bool TextRenderer::printInfos(false);
	vector<PrintHelper*> TextRenderer::printList;
	

	void TextRenderer::render(const fpcameraNS::Transformation& cam) {

		
		TextRenderer::refreshText();
		for(int i = 0 ; i < printList.size(); i++)
			if(printList[i]->mapIDbutton_button.buttonslistSize != 0)
				RenderText(*printList[i]);
		

	}

	

	void TextRenderer::refreshText() {		
		
		for (int i = 0; i < printList.size(); i++)
			printList[i]->update();
	
	}




	void TextRenderer::RenderText(PrintHelper& ph)
	{

		if (ph.mapIDbutton_button.xpos < -1 || ph.mapIDbutton_button.xpos > 1 || ph.mapIDbutton_button.ypos < -1 || ph.mapIDbutton_button.ypos > 1) {
			logNS::Logger::writeLog(
				"le coorinate x, y del testo nello schermo possono spaziare tra [-1,1].\
		\n tutto ciò che cade al di fuori non è visibile a schermo.\
        \n assicurarsi che pos_x sia contenuto nel range [-1,1-larghezza testo].\
		\n associrarsi che pos_y sia contenuto nel range [-1,1-altezza test]", "text_log");
		//	throw std::string("exception ! error ");
		}

		glUseProgram(shader_prog);

		static GLint textSampler_loc = glGetUniformLocation(shader_prog, "textSampler");//fragment
		static GLint textcolor_loc = glGetUniformLocation(shader_prog, "textColor");//fragment
		static GLint textFrameColor_loc = glGetUniformLocation(shader_prog, "textFrameColor");//fragment
		static GLint vertex_loc = glGetAttribLocation(shader_prog, "vertex");	//vertex	
		static GLint char_advance_loc = glGetUniformLocation(shader_prog, "char_advance");
		static GLint main_scale_loc = glGetUniformLocation(shader_prog, "main_scale");
		static GLint xy_offset_loc = glGetUniformLocation(shader_prog, "xy_offset");

		

		
		GLfloat x = ph.mapIDbutton_button.xpos;
		GLfloat x_advance = 0.f;

		auto lambda_reset_xCoords = [&]()
		{
			x = ph.mapIDbutton_button.xpos;
			x_advance = 0.f;
			integral_x_advance = 0;
		};

		std::string::const_iterator c;

		string textID, textString;
		/*empty frame map*/
		//ph.mapIDbutton_button.textButtonsMap.clear();

		size_t buffer_index = 0;

		for(int i = 0; i < ph.mapIDbutton_button.buttonslistSize; i++)
		{
			textID = ph.mapIDbutton_button.buttons[i].button.buttonID;
			textString = ph.mapIDbutton_button.buttons[i].button.buttonName;
			size_t string_size = textString.size();
			float text_scale = ph.mapIDbutton_button.buttons[i].button.textScale;

			glUniform4fv(textcolor_loc, 1, ph.color_text);
			glUniform1f(main_scale_loc, text_scale);
			glUniform4fv(textcolor_loc, 1, ph.mapIDbutton_button.buttons[i].frameColor);
			
			
			
			
			lambda_reset_xCoords();
		

			for (c = textString.begin(); c != textString.end(); c++)
			{
				char ch_ = *c;

				Character ch = charMap[ch_];
				//GLfloat xpos = x + ch.Bearing.x * scale;
				GLfloat ypos = ph.mapIDbutton_button.buttons[i].button.y_min + (ch.Bearing.y)*0.0001*text_scale;
				GLfloat xpos = x;
				xy_offset[0] = -ph.mapIDbutton_button.xpos;
				xy_offset[1] = -ypos;

				static constexpr GLfloat scalex = 0.0001;
				static constexpr GLfloat scaley = 0.0003;

				GLfloat w = ch.Size.x * scalex*text_scale;
				GLfloat h = (ch.Size.y + ch.Bearing.y)* scaley*text_scale;
				
				GLfloat vertices[6][4] = {

					{ xpos ,     ypos + h,   0.0, 1 },
					{ xpos + w, ypos,       0.0, 1 },
					{ xpos,     ypos,       0.0, 1 },

					{ xpos,     ypos + h,   0.0, 1 },
					{ xpos + w, ypos + h,   0.0, 1 },
					{ xpos + w, ypos,       0.0, 1 }
				};

			

				// Update content of VBO memory					
				glBindBuffer(GL_ARRAY_BUFFER, ph.VBO[buffer_index]);
				glNamedBufferSubData(ph.VBO[buffer_index], 0, sizeof(vertices), vertices);

				glVertexArrayAttribBinding(ph.VAO, vertex_loc, ph.instanceVBBI);
				glVertexArrayVertexBuffer(ph.VAO, ph.instanceVBBI, ph.VBO[buffer_index], 0 /*offset*/, sizeof(GLfloat) * 4);
				glVertexArrayAttribFormat(ph.VAO, vertex_loc, 4/*num coord per vert*/, GL_FLOAT, GL_FALSE, 0);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, ch.TextureID);
				glBindVertexArray(ph.VAO);
				glEnableVertexArrayAttrib(ph.VAO, vertex_loc);



				glUniform1i(textSampler_loc, 0);
				
				glUniform1f(char_advance_loc, integral_x_advance);
			
				glUniform2fv(xy_offset_loc, 1, xy_offset);

				glDrawArrays(GL_TRIANGLES, 0, 6);
				// Now advance cursors for next glyph


				x_advance = ch.Advance / 700000.0*text_scale;//incrementare il denominatore per stringere il testo
				x += x_advance;
				integral_x_advance += x_advance;

				buffer_index++;
				//ph.incrementBufferIndex();
				

			}
			glDisableVertexArrayAttrib(ph.VAO, vertex_loc);
			
			
			//ph.mapIDbutton_button.setButtonFrame(text_frame);
		}
		

	}

	void TextRenderer::printMatrix44(std::string& out, vmath::mat4& matrix, std::string matrixName) {
		
		out.append(logNS::Logger::matrix44ToString(matrix, matrixName));
	}





	void TextRenderer::printEditableObjectInfos() {


		if (printInfos)
			printInfos = false;


		else
		{
			/*eraseFromMap("EDITABLEOBJECTINFOS");
			printInfos = true;*/
		}


	}





	void TextRenderer::create() {

		setShaders();
		
		Load("C:/Users/aloforte/source/repos/OGL_Application/root/OGL_Application/DEPENDENCIES/arial.ttf", 1);

		for (int i = 0; i < printList.size(); i++)
			printList[i]->create();

	}



	void TextRenderer::printExistingObject(const string& branchID)
	{
		/*generatin a new list to print existing object*/
		//printList.push_back(new PrintHelper({ "TextRenderer" }));
		//for (int i = 0; i < myobjectNS::ApplicationObjectManager::ApplicationCollectorList.size(); i++)
		//{
		//	string s = myobjectNS::ApplicationObjectManager::ApplicationCollectorList[i]->getCollectorID();//+"_"+std::to_string(i);
		//	printList.back()->mapButtonOnBranch(branchID,s, s);
		//}

	}

	void TextRenderer::printAssetObjectList(const string& branchID)
	{

		/*std::map<std::string, int>* assetIndex = AssetNS::Assets::getAssetIndex();
		std::map<std::string, int>::iterator it = assetIndex->begin();

		printList.push_back(new PrintHelper({ "TextRenderer" }));

		for (it; it != assetIndex->end(); it++)
			printList.back()->mapButtonOnBranch(branchID,it->first, it->first);*/
		
	}














	string TextRenderer::Matrix44ToString(const vmath::mat4& matrix, std::string matrixName) {
		string text;
		text.append(logNS::Logger::matrix44ToString(matrix, matrixName));
		return text;
	}



	void TextRenderer::printMatrix43(Matrix4& matrix, std::string matrixName) {
		
		/*text.append(
			NEWLINE + NEWLINE + matrixName +
			NEWLINE + "xx : " + std::to_string(matrix[0]) +
			"	xy : " + std::to_string(matrix[4]) +
			"	xz : " + std::to_string(matrix[8]) +
			"	xw :    0" +
			NEWLINE + "yx : " + std::to_string(matrix[1]) +
			"	yy : " + std::to_string(matrix[5]) +
			"	yz : " + std::to_string(matrix[9]) +
			"	yw :    0" +
			NEWLINE + "zx : " + std::to_string(matrix[2]) +
			"	zy : " + std::to_string(matrix[6]) +
			"	zz : " + std::to_string(matrix[10]) +
			"	zw :    0" +
			NEWLINE + "wx : " + std::to_string(matrix[3]) +
			"	wy : " + std::to_string(matrix[7]) +
			"	wz : " + std::to_string(matrix[11]) +
			"	ww :    1"
		);
*/



	}








	string TextRenderer::Scalar4ToString(const GLfloat w, const  GLfloat x, const GLfloat y, const GLfloat z, std::string vecName) {

		string text;
		text.append(
			NEWLINE+NEWLINE+ vecName +
			NEWLINE+"w : " + std::to_string(w) +
			"	x : " + std::to_string(x) +
			"	y : " + std::to_string(y) +
			"   z : " + std::to_string(z));

		return text;
	}


	void TextRenderer::printMatrix33(const GLfloat matrix[3][3], std::string matrixName) {
		/*text.append(
			NEWLINE+NEWLINE+ matrixName +
			NEWLINE+"xx : " + std::to_string(matrix[0][0]) +
			"	xy : " + std::to_string(matrix[0][1]) +
			"	xz : " + std::to_string(matrix[0][2]) +
			NEWLINE+"yx : " + std::to_string(matrix[1][0]) +
			"	yy : " + std::to_string(matrix[1][1]) +
			"	yz : " + std::to_string(matrix[1][2]) +
			NEWLINE+"zx : " + std::to_string(matrix[2][0]) +
			"	zy : " + std::to_string(matrix[2][1]) +
			"	zz : " + std::to_string(matrix[2][2]));
*/
	}

	void TextRenderer::printVector3(const GLfloat vec[3], std::string vecName) {

		//text.append(
		//	NEWLINE+vecName +
		//	NEWLINE+"x : " + std::to_string(vec[0]) +
		//	"	y : " + std::to_string(vec[1]) +
		//	"	z : " + std::to_string(vec[2]));

	}


	void TextRenderer::printvmathVector4(const vmath::vec4 vec, std::string vecName) {

		/*text.append(
			NEWLINE+vecName +
			NEWLINE+"x : " + std::to_string(vec[0]) +
			"	y : " + std::to_string(vec[1]) +
			"	z : " + std::to_string(vec[2]) +
			"	w : " + std::to_string(vec[3]));
*/
	}

	void TextRenderer::printvmathVector4(std::string &out, vmath::vec4 vec, std::string vecName) {

		out.append(
			NEWLINE + vecName +
			NEWLINE + "x : " + std::to_string(vec[0]) +
			"	y : " + std::to_string(vec[1]) +
			"	z : " + std::to_string(vec[2]) +
			"	w : " + std::to_string(vec[3]));

	

	}




	void TextRenderer::printScalar1(const GLfloat s, std::string scalarName) {
		//text.append(NEWLINE + NEWLINE + scalarName +" : " + std::to_string(s));

	}

	void  TextRenderer::printScalar1(std::string& out, GLfloat s, std::string scalarName) {
		out.append(NEWLINE + NEWLINE + scalarName +" : " + std::to_string(s));
		//printer::mapNewString("PRINTSCALAR1", NEWLINE + NEWLINE + scalarName + " : " + std::to_string(s));
	}


	string TextRenderer::Scalar3ToString(const GLfloat s1, const GLfloat s2, const GLfloat s3, std::string vecName) {
		string text;
		text.append(
			NEWLINE + NEWLINE + vecName +
			NEWLINE + "x : " + std::to_string(s1) +
			"	y : " + std::to_string(s2) +
			"	z : " + std::to_string(s3));

		return text;

	}







	void TextRenderer::Load(std::string font, GLuint fontSize)
	{
		// First clear the previously loaded Characters
		charMap.clear();
		// Then initialize and load the FreeType library

		FT_Library ft;
		if (FT_Init_FreeType(&ft)) // All functions return a value different than 0 whenever an error occurred
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		// Load font as face
		FT_Face face;
		if (FT_New_Face(ft, font.c_str(), 0, &face))
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		// Set size to load glyphs as
		//FT_Set_Pixel_Sizes(face, 0, fontSize);
		FT_Set_Pixel_Sizes(face, 0., 1000);

		// Disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		// Then for the first 128 ASCII characters, pre-load/compile their characters and store them
		for (GLubyte c = 0; c < 128; c++) // lol see what I did there 
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};


			charMap.insert(std::pair<GLchar, Character>(c, character));
		}


		glBindTexture(GL_TEXTURE_2D, 0);
		// Destroy FreeType once we're finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}









}