#pragma once
#include<PrintHelper.h>
namespace printHelperNS {

	
		void PrintHelperCollector::updateRenderer()
		{
			
			for (it = printHmap.begin(); it != printHmap.end(); it++)
			{
				textRendererNS::TextRenderer::printList.push_back(&it->second);
			}

				
		}


		PrintHelper& PrintHelperCollector::getPH(unsigned index)
		{
			it = printHmap.begin();
			for (int i = 0; i < index; i++)
				it++;
			return it->second;
		}


		PrintHelper& PrintHelperCollector::getPHbyID(const string& phID)
		{
			it = printHmap.find(phID);
			if(it != printHmap.end())
			return it->second;
		}

		string PrintHelperCollector::getPHID(unsigned index)
		{
			it = printHmap.begin();
			for (int i = 0; i < index; i++)
				it++;
			return it->first;
		}



		PrintHelper& PrintHelperCollector::operator [](unsigned i)
		{ return getPH(i); }




		void PrintHelperCollector::showButton(const string& phID, const string& stringID, const string& text, const unsigned& buttonLevel, const float& scale )
		{
				
			it = printHmap.find(phID);
			if (it == printHmap.end())
			{
				static PrintHelper p{ "WARNINGPRINT",-0.4,-0.8,0.0 };
				textRendererNS::TextRenderer::printList.push_back(&p);
				p.mapButtonOnBranch("WARNINGPRINT", 
					"printHelperCollector.cpp : PRINTING ERROR",
					"printHelperCollector.cpp : some text could not be printed correctly");
				return;
			}
				

			PrintHelper& p = it->second;

			if (text == "_DEFAULT")
				p.mapButtonOnBranch(
					phID,
					stringID,
					stringID, buttonLevel, scale);
			else
			p.mapButtonOnBranch(
				phID,
				stringID,
				text, buttonLevel, scale);

		}


		void PrintHelperCollector::showDropDownMenu(const string& phID, const vector<string>& buttonsList, const float& scale)
		{
			hideDropDownMenu();

			PrintHelper& p = printHmap.at(phID);

			for(int i = 0; i < buttonsList.size(); i++)
			p.mapButtonOnBranch(
				phID,
				buttonsList[i],
				buttonsList[i],1, scale);

		}


		void PrintHelperCollector::hideDropDownMenu(const string& phID, const unsigned& buttonLevel)
		{
			it = printHmap.find(phID);
			if (it != printHmap.end())
				it->second.eraseByBranch(phID, buttonLevel);
	

		}


		void PrintHelperCollector::hideDropDownMenu()
		{

			it = printHmap.find(activePHbutton.first);
			if (it != printHmap.end())
				it->second.eraseByBranch(activePHbutton.second, 1);

		}


		void PrintHelperCollector::turnOffAllButtons()
		{
			it = printHmap.begin();
			for (it; it != printHmap.end(); it++)
				it->second.eraseByBranch(it->first,0);

			/*it = printHmap.find(activePHbutton.first);
			if (it != printHmap.end())
				it->second.eraseByBranch(activePHbutton.second, 0);*/
		}



		void PrintHelperCollector::click(const string& phID, const string& buttonID)
		{
			if (phID == activePHbutton.first) return;
			hideDropDownMenu();
			activePHbutton.first = phID;
			activePHbutton.second = buttonID;
		}

		void PrintHelperCollector::turnOffButton(const string& phID)
		{
			it = printHmap.find(phID);
			if(it != printHmap.end())
				printHmap.erase(it);
		}




}