#include<buttonsList.h>
#include<userInterface.h>
namespace textRendererNS {


	ButtonsList::~ButtonsList(){}


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
	altrimenti aggiorna il contenuto trovato alla chiave specificata
	(inserisce il branch di appartenenza)*/
	uiNS::ButtonInterface* ButtonsList::mapStringOnBranch(string branchID, string stringID, string stringcontent, unsigned buttonLevel, float scale)
	{
			
		buttonsListIter it = getIteratorOf(stringID);
		if (it == buttons.end())
		{
			/*must guarantee that ypos is always updated in case we erase some string*/
			if(buttons.size() > 0 )	ypos = buttons.back().button.y_min;
			/*must delete memory allocation before delete the button!*/
			uiNS::Button* b= new uiNS::Button(
				{ stringID, stringcontent, xpos,ypos,static_cast<unsigned>(buttonslistSize), scale });
			buttons.push_back(*b);
			
			buttons.back().button.parentNode = branchID;
			++buttonslistSize;
			text_tot_size += stringcontent.length();
			ypos = b->y_min;
			xpos = b->x_min;
			return &buttons.back();
		}

		else
		{
			it->button.buttonName = stringcontent;
			
			it->button.parentNode = branchID;
			text_tot_size -= it->button.buttonName.length();
			text_tot_size += stringcontent.length();
			return &(*it);
		}

	}


	void ButtonsList::substituteButton(const unsigned& lvl, const string buttonString)
	{
		/*fetching iterator of button A*/
		list_it = getIteratorOf(buttonString);
		/*saving button b*/
		ButtonInterface b = buttons[lvl];
		/*overwriting button b*/
		buttons[lvl] = *(list_it);
		/*restoring button b in place of button A*/
		//buttons[lvl] = b;
		*list_it = b;

		

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



}