#include<iostream>
using namespace std;
#include<vector>
template<class T>
class Less
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left < right;
	}
};

template<class T>
class Great
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};

template<class T, class Compare = Less<T> >
class Heap
{
public:
	Heap()
	{}
	Heap(const T* array, size_t size)
	{
		//�������е�Ԫ�ش���������ȫ��������
		_array.resize(size);//����
		for (size_t i = 0; i < size; i++)
		{
			_array[i] = array[i];
		}
		//����
		//2.����ȫ�������е�����һ����Ҷ�ӽڵ�
		int pRoot = (size - 1 - 1) >> 1;//�����һ��Ԫ�ص��±�-1��/2
		for (; pRoot >= 0; --pRoot)
		{
			_AdjustDown(pRoot);
		}
	}
	void Push(const T& data)
	{
		_array.push_back(data);
		if (_array.size() > 1)
		{
			_AdjustUp(_array.size() - 1);
		}
	}
	void Pop()
	{
		size_t size = _array.size() - 1;//���һ��Ԫ�ص��±�
		//�նѣ�ֱ�ӷ���
		if (Empty())
		{
			return;
		}
		//ֻ��һ��Ԫ�أ�ֱ��ɾ��
		else if (_array.size() == 1)
		{
			_array.pop_back();
		}
		//����ж��Ԫ�أ�ɾ���Ѷ�Ԫ��
		else
		{
			swap(_array[0], _array[size]);
			_array.pop_back();
			if (_array.size() > 1)
			{
				_AdjustDown(0);
			}
		}
	}
	T Top()const
	{
		return _array[0];
	}
	bool Empty()const
	{
		return _array.empty();
	}
	size_t Size()const
	{
		return _array.size();
	}

private:
	void _AdjustDown(size_t parent)
	{
		//������Һ�������С�ĺ��ӣ�Ĭ��������С��
		size_t child = parent * 2 + 1;
		size_t size = _array.size();
		while (child<size)
		{
			Compare com;
			//�����Һ�������С�ĺ���
			if (com(child + 1, size) && com(_array[child + 1], _array[child]))
			{
				child = child + 1;//��С�ĸ���Ϊ�Һ���
			}
			//�ж�˫�׺ͺ����Ƿ���Ҫ��������
			if (com(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
	void _AdjustUp(size_t child)//��ʱchildΪ�±�
	{
		Compare com;
		size_t parent = (child - 1) >> 1;
		while (child > 0)
		{
			if (com(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}
private:
	std::vector<T> _array;
};