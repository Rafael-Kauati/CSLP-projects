#include <iostream>
#include <string>
using namespace std;

class Tank 
{
    private:
        int id;
    public:
		string name;
		string type;
        Tank(){
            cout << name << " is on wheels !!";
        }


};

int main()

{


	Tank tanks[5] ;

    Tank nulltank ; nulltank.name= "null"; nulltank.type="null";

    for(int i = 0; i < sizeof(tanks)/sizeof(tanks[0]); i++)
    {
        tanks[i] = nulltank;
    }

    Tank panzerIV; panzerIV.name = "panzerIV aug mk II"; panzerIV.type ="Medium";

    Tank Panzerkampf ; Panzerkampf.name = "Panzerkampfwange ausch I"; Panzerkampf.type = "Heavy";

	tanks[0] = panzerIV; tanks[1] = Panzerkampf;

	string  asr;

	while (true)
	{
		cout << "Want to add a new tank to the wiki ? \n [y/n] >>>";
		cin >> asr;
		if (asr != "y"){
		return 0;}
		Tank newTank;
		cout << "\nInsert the name\n";
		cin >>  newTank.name;
		cout << "\nInsert the type (Light, Medium, Heavy, Super-Heavy, Amphibious, AA, Tank-Hunter)\n";
		cin >>  newTank.type;

        for(int i = 0; i < sizeof(tanks)/sizeof(tanks[0]); i++)
        {
           if(tanks[i].name == nulltank.name){
               tanks[i] = newTank;
               break;
           }
        }

		for(int i = 0; i < sizeof(tanks)/sizeof(tanks[0]); i++)
		{
		  cout << "\n" << i << " -- " << tanks[i].name;
		} 

	}	

	return 0; 
}
