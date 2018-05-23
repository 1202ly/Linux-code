#include"hp.hpp"
void TestHeap()
{
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
	Heap<int>hp(array, sizeof(array) / sizeof(array[0]));
	cout << "hp.Top()=" << hp.Top() << endl;
	cout << "hp.Size()=" << hp.Size() << endl;
	hp.Push(5);
	cout << "hp.Top()=" << hp.Top() << endl;
	cout << "hp.Size()=" << hp.Size() << endl;
	hp.Pop();
	cout << "hp.Top()=" << hp.Top() << endl;
	cout << "hp.Size()=" << hp.Size() << endl;
	if (hp.Empty())
	{
		cout << "Îª¿Õ" << endl;
	}
	else
	{
		cout << "·Ç¿Õ" << endl;
	}
}

int main()
{
	TestHeap();
	system("pause");
	return 0;
}
