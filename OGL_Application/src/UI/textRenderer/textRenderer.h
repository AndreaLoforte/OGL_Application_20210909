/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef TEXT_RENDERER_TEST_H2
#define TEXT_RENDERER_TEST_H2

#include <map>
#include<gl3w.h>
#include<glfw3.h>
#include <glm.hpp>
#include<shaderObject.h>
#include<string>
#include<applicationObject.h>

namespace printHelperNS {
	class PrintHelper;
}


namespace textRendererNS {
	static const std::string NEWLINE("\n");
	static const std::string NEWLINE2("\n\n");
	static const std::string NEWLINE3("\n\n\n");
	static const std::string NEWLINE4("\n\n\n\n");
	static const std::string TAB16("																");
	static const std::string TAB4("				");
	static const std::string TAB8("								");

	
	
	/// Holds all state information relevant to a character as loaded using FreeType
	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
		GLuint Advance;     // Horizontal offset to advance to next glyph
	};

	

	// A renderer class for rendering text displayed by a font loaded using the 
	// FreeType library. A single font is loaded, processed into a list of Character
	// items for later rendering.
	class TextRenderer : public myobjectNS::ApplicationObject
	{
		static myobjectNS::ShaderObject shaderObj;
	public:
		static vector<printHelperNS::PrintHelper*> printList;

		TextRenderer(std::string sh_prog_name) :
			ApplicationObject(sh_prog_name)
		{
			shaderObj.setShaders();
		}
		

		static void render(const vector<printHelperNS::PrintHelper*> ph = printList);
		static void RenderText(printHelperNS::PrintHelper&);
		void create()override;
		static void Load(std::string font, GLuint fontSize);// Pre-compiles a list of characters from the given font
		static void printMatrix44(std::string& , vmath::mat4&, std::string);
		static void printEditableObjectInfos();

	private:
		// Holds a list of pre-compiled Characters
		static std::map<GLchar, Character> charMap;
		static GLfloat x_off, y_off;
		static GLfloat xy_offset[2];
		static GLfloat integral_x_advance;
		static bool printInfos ;
		
		
	};





}


#endif 

