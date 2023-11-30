#include "Work.h"
Work* p = new Work;
int main()
{
	while (1)
	{
		int choice = p->Menu_main();
		switch (choice % 10)
		{
		case M_admin:
			p->Menu_admin();
			break;
		case M_user:
			p->Menu_user(choice/10);
			break;
		default:
			break;
		}
		cout << endl;
	}
	delete p;
}
