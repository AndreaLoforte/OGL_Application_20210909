#ifndef SOUND_H
#define SOUND_H

#include<stdio.h>
#include <irrKlang.h>
#include<string>
#include<array>
#include<map>
#include<text.h>
class Contact;

namespace soundNS {

	using namespace std;
	using namespace irrklang;

	class CollisionPair
	{
	public:
		CollisionPair(){}
		CollisionPair(string id1, string id2) :idObj1(id1), idObj2(id2) {}
		string idObj1;
		string idObj2;

		bool operator<(const CollisionPair& p) const
		{
			/*confronto idObj1 e idObj2 con quelli dell'argomento.
			Dò maggior peso alla prima componente*/
			
			if (idObj1  < p.idObj1)
				return true;
			if (idObj1 > p.idObj1)
				return false;

			if (idObj1 == p.idObj1)
			{
				if (idObj2 < p.idObj2)
					return true;
				if (idObj2 > p.idObj2)
					return false;
				if (idObj2 == p.idObj2)
					return false;
			}
		}
	};



	static const string SOUNDSDIR = "./root/OGL_Application/audio/";

	class soundMap 
	{

		static map<CollisionPair, string> collisionSoundMap;
		static textRendererNS::PrintHelper ph;
	public:
	static irrklang::ISoundEngine* engine;

		


		soundMap();
		~soundMap()
		{
			engine->drop();
		}

		static void collisionSound(const Contact& contact);
		static void collisionSound(const Contact* contact, const unsigned&);
		static void update();
		static void startSounds();
		static irrklang::vec3df convertIntoIrrklang(const std::array<float, 3>& vec);

	};



	struct toIrrklang
	{


		static irrklang::vec3df farray(const float arr[3])
		{
			vec3df result(arr[0], arr[1], arr[2]);
			return result;
		}

		static irrklang::vec3df stdfarray(const std::array<float, 3>& vec)
		{
			irrklang::vec3df result(vec[0], vec[1], vec[2]);
			return result;
		}
	
	};





}



#endif