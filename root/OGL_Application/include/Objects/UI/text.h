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
#include<baseObject.h>
#include<string>
#include<applicationObject.h>
#include <texture_ext.h>






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

	class PrintHelper;

	// A renderer class for rendering text displayed by a font loaded using the 
	// FreeType library. A single font is loaded, processed into a list of Character
	// items for later rendering.
	class TextRenderer : public myobjectNS::ApplicationObject, public myobjectNS::BaseObject
	{
		
	public:
		static vector<PrintHelper*> printList;

		TextRenderer(std::string sh_prog_name) :
			ApplicationObject(sh_prog_name),
			BaseObject(sh_prog_name) {}
		

		void render(const fpcameraNS::Transformation&) override;
		void RenderText(PrintHelper&);
		void create()override;
		static void Load(std::string font, GLuint fontSize);// Pre-compiles a list of characters from the given font
		static void refreshText();
		static void printMatrix33(const GLfloat mat[3][3], std::string);
		static void printMatrix43(Matrix4&, std::string matrixName);
		static string Matrix44ToString(const vmath::mat4&, std::string);
		static void printMatrix44(std::string& , vmath::mat4&, std::string);
		static void printVector3(const GLfloat vec[3], std::string);
		static void printScalar1(const GLfloat, std::string);
		static void printScalar1(std::string&, GLfloat, std::string);
		static string Scalar3ToString(const GLfloat, const  GLfloat, const GLfloat, std::string);
		static string Scalar4ToString(const GLfloat, const  GLfloat, const GLfloat, const GLfloat, std::string);
		static void printvmathVector4(const vmath::vec4 vec, std::string vecName);
		static void printvmathVector4(std::string&,const vmath::vec4 vec, std::string vecName);
		static void printEditableObjectInfos();
		static void printExistingObject(const string&);
		static void printAssetObjectList(const string&);

		
		
	private:
		// Holds a list of pre-compiled Characters
		static std::map<GLchar, Character> charMap;
		static GLfloat x_off, y_off;
		GLfloat xy_offset[2];
		GLfloat integral_x_advance = 0;
		static bool printInfos ;
		
		
	};





}


#endif 

