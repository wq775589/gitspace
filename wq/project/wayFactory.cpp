#include <iostream>
using namespace std;
class Tank
{
public:
	virtual const string& type() = 0;
};

class Tank1 :public Tank
{
public:
	Tank1(){m_str = "Tank1";};
	const string& type()override
	{
  	   cout<<m_str.data()<<endl;
	   return m_str;
	}
private:
 	string m_str;
};

class Tank2 :public Tank
{
public:
	Tank2(){m_str = "Tank2";};
 	const string& type()override
	{
	   cout<<m_str.data()<<endl;
	   return m_str;
	};
private:
	string m_str;
};

class TankFactory
{
public:
	virtual Tank* createTank() = 0;
};

class Tank1Factory :public TankFactory
{
public:
	Tank* createTank()override
	{
	 	return new Tank1();
	}
};
class Tank2Factory:public TankFactory
{
public:
	Tank* createTank()override
	{
		return new Tank2();
	}
};
int main()
{
        TankFactory* factory1 = new Tank1Factory();
	Tank* tank1 = factory1->createTank();
 	tank1->type();

        TankFactory* factory2 = new Tank2Factory();
	Tank* tank2 = factory2->createTank();
	tank2->type();

        delete tank1;
	tank1 = NULL;
	delete tank2;
	tank2 = NULL;

  	delete factory1;
	factory1 = NULL;
	delete factory2;
	factory2 = NULL;

 	return 0;
}
