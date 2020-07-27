#include<text.h>
#include<buttonsList.h>
namespace textRendererNS {


	//void ButtonsList::setButtonFrame(const textButton& buttonFrame)
	//{
	//	textButtonsMap.push_back(buttonFrame);
	//}


	string ButtonsList::find(string id)
	{
		for (int i = 0; i < buttons.size(); i++)
			if (buttons[i].button.buttonID == id)
				return buttons[i].button.buttonName;
	}

	ButtonsList::buttonsListIter ButtonsList::getIteratorOf(string id)
	{
		for (list_it = buttons.begin(); list_it != buttons.end(); list_it++)
		{
			if (list_it->getButtonID_() == id)
				return list_it;
		}
		return list_it;
	}

	/*aggiunge una nuova coppia di stringhe alla mappa se non trova la chiave
	altrimenti aggiorna il contenuto trovato alla chiave specificata*/
	void ButtonsList::mapString(string key, string content)
	{
		buttonsListIter it = getIteratorOf(key);
		if (it == buttons.end())
		{
			/*LINESPACING = 0.1 * text_scale;
			ypos -= LINESPACING;*/
			uiNS::ButtonInterface b({ key, content, xpos, ypos,text_scale });
			buttons.push_back(b);
			text_tot_size += content.length();
			++buttonslistSize;
			ypos = b.button.y_min;
		}

		else
		{
			it->button.buttonName = content;
			text_tot_size -= it->button.buttonName.length();
			text_tot_size += content.length();
		}
	}


	/*aggiunge una nuova coppia di stringhe alla mappa se non trova la chiave
	altrimenti aggiorna il contenuto trovato alla chiave specificata
	(inserisce il branch di appartenenza)*/
	void ButtonsList::mapStringOnBranch(string branchID, string key, string content, float scale)
	{
		buttonsListIter it = getIteratorOf(key);
		if (it == buttons.end())
		{
			/*must guarantee that ypos is always updated in case we erase some string*/
			if(buttons.size() > 0 )	ypos = buttons.back().button.y_min;
			uiNS::Button b({ key, content, xpos,ypos, scale });
			buttons.push_back(b);
			buttons.back().button.parentNodes.clear();
			buttons.back().button.parentNodes.push_back(branchID);
			++buttonslistSize;
			text_tot_size += content.length();
			ypos = b.y_min;
		}

		else
		{
			it->button.buttonName = content;
			it->button.parentNodes.push_back(branchID);
			text_tot_size -= it->button.buttonName.length();
			text_tot_size += content.length();
		}
	}


	/*aggiunge una nuova coppia di stringhe alla mappa se non trova la chiave
	altrimenti concatena il contenuto trovato alla chiave specificata*/
	void ButtonsList::concatenate(string key, string content)
	{
		/*buttonsListIter it = getIteratorOf(key);
		if (it == map.end())
		{
			ypos -= LINESPACING;
			map.push_back({ key, content,xpos,ypos });
			++mapSize;
		}

		else
		{
			it->buttonName += content;
			
		}*/
	}

	void ButtonsList::erase(string id)
	{
		buttonsListIter element_to_delete = getIteratorOf(id);
		if (element_to_delete != buttons.end())
		{
			
			buttons.erase(element_to_delete);
			--buttonslistSize;
		}
	}

	void ButtonsList::eraseByIterator(const buttonsListIter it)
	{
		buttons.erase(it);
	}

	void ButtonsList::eraseByIterator(const buttonsListIter beg, const buttonsListIter end)
	{
		buttons.erase(beg, end);
	}


	ButtonsList::buttonsListIter ButtonsList::begin() { return { this->buttons.begin() }; }
	ButtonsList::buttonsListIter ButtonsList::end()
	{
		/*non funzionaaaaaa! il puntatore ritornato
		è rotto*/
		return buttons.end();
	}

	/*void textMap::insert(std::string key, std::string value)
	{
		map.push_back(myPair<string, string>{key, value});
	}*/



}