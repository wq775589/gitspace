#include <iostream>
using namespace std;

class Soldier
{
public:
	typedef void (*Function)();
        Soldier(Function fun)
	{
 	   m_fun = fun;
	}
	void attack()
	{
	 m_fun();
	}	
private:
	Function m_fun;
};

void fun1()
{

 std::cout<<"test"<<std::endl;
}

int main()
{
     Soldier* soldier = new Soldier(fun1);
     soldier->attack();
	return 0;
}
