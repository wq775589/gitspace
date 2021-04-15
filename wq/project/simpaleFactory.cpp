#include <iostream>
using namespace std;

class Tank
{
public:
	virtual  void type () = 0;
};

class a :public Tank
{
public:
    void type()override
  {
        m_str = "a";
	cout<< m_str<<endl;
  }

public:
   string m_str;
 
};

class b :public Tank
{
public:
   void type()override
   {
        m_str = "b";
        cout<<m_str<<endl;
   }
public:
   string m_str;

};

class Factory
{
public:
     Tank* CreateTank(int type)
     {
        switch(type)
	{
          case 0:
          return new a; 
          break;
 	  case 1:
          return new b; 
 	  break;
 	  default:
          break;
	}
     }  
  
};
int main()
{
   Factory* fac = new Factory;
   Tank* ss =  fac->CreateTank(0);
   Tank* sw =  fac->CreateTank(1);
   ss->type();
   sw->type();   
   delete fac;
   fac = NULL;
   delete ss;
   ss = NULL;
   delete sw;
   sw = NULL;  
   return 0;
}

