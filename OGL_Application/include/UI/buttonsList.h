#pragma once


#include<buttons.h>
#include<vector>
using namespace std;
using namespace uiNS;
namespace textRendererNS {
	

	struct ButtonsList {
		typedef vector<ButtonInterface>::iterator buttonsListIter;
		std::vector<ButtonInterface> buttons;
		buttonsListIter list_it;
	
		float LINESPACING;
		size_t buttonslistSize;
		size_t text_tot_size;
		string find(string id);
		/*fixed text beginnning position*/
		const float x_beg_pos, y_beg_pos;
		/*text cursor position (incrementing
		for each string insertion)*/
		float xpos, ypos, text_scale;
		buttonsListIter getIteratorOf(string id);

		ButtonsList(const float& x, const float& y, const float& s):
			x_beg_pos(x),y_beg_pos(y),
			xpos(x),ypos(y), text_scale(s)
		{
			LINESPACING = 0.1*text_scale;
			buttonslistSize = 0;
			text_tot_size = 0;
			list_it = buttons.begin();	
		}
		~ButtonsList();

		//void mapStringOnBranch(string branchID, string key, string content);
		uiNS::ButtonInterface* mapStringOnBranch(string branchID, string key, string content, unsigned buttonLevel, float scale = 0.3);
		void resetPosition()
		{
			xpos = x_beg_pos;
			ypos = y_beg_pos;
		}

		void erase(string id);
		void eraseByIterator(const buttonsListIter it);
		void substituteButton(const unsigned& lvl, const string buttonString);
		void eraseByIterator(const buttonsListIter beg, const buttonsListIter end);
		buttonsListIter begin();
		buttonsListIter end();

	};




}