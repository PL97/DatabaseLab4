//#include<iostream>
//#include<time.h>
//#include<fstream>
//#include <string>
//#include<sstream>
//
//using namespace std;
//#define  MAX   3
//#define  MIN   1.5
//
//typedef struct node
//{
//
//	int key[MAX + 1];//����ؼ��֣�����k[0]������ؼ��֣����Ǵ��浱ǰ����д���Ĺؼ��ָ���
//	struct node *parent;//ָ�򸸽ڵ�
//	struct node *son[MAX + 1];//ָ����ӽڵ�
//} BTreeNode;
//
//typedef   BTreeNode   *BTREE;
//int insertBTREE(BTREE root, int key);
//int realinsert(BTREE low, int key);
//int display(BTREE root)//���������ӡB-��
//{
//
//	if (root != NULL)
//	{
//		cout << root->key[1] << ' ' << root->key[2] << ' ' << root->key[3] << endl;
//		display(root->son[0]);
//		display(root->son[1]);
//		display(root->son[2]);
//		display(root->son[3]);
//	}
//	return 0;
//}
//BTREE search(BTREE root, int key) /*���õݹ���ã��Ӹ��ڵ���ҹؼ��֣�����ؼ��������ڵĽڵ���ô���������㡣
//								  ������ڣ��������㲻��Ҷ��㣬��ô���ǿ�������Ĺؼ���K[1]��K[2],K[3],
//								  ���С��K[1]�������������son[0]�в��ң��������key[1]��key[2]֮�����son[1]�в���
//								  �������key[2]����son[2]�в��ң�ǰ���������������ָ�����㲻��Ҷ���������
//								  ����ý����Ҷ��㣬��ô���������㣬��ʱҪô�ؼ��������Ҷ����У�Ҫô���Ҷ����Ǹùؼ���Ӧ�ò����λ��*/
//{
//	int flag = 0;
//	int i;
//	if (root->son[0] == NULL)
//	{
//		return root;
//	}
//	else if (root->son[0] != NULL)
//	{
//		if (root->key[0] == 1)//����һ���ؼ���
//		{
//			if (key == root->key[1])
//				return root;
//			else if (key<root->key[1])
//				search(root->son[0], key);
//			else if (key>root->key[1])
//				search(root->son[1], key);
//		}
//		else if (root->key[0] == 2)//���������ؼ���
//		{
//			if (key == root->key[1] || key == root->key[2])
//				return root;
//			else if (key<root->key[1])
//				search(root->son[0], key);
//			else if (key>root->key[1] && key<root->key[2])
//				search(root->son[1], key);
//			else if (key>root->key[2])
//				search(root->son[2], key);
//		}
//	}
//}
//
//void splitBTREE(BTREE low)/*����realinsert�����йؼ��ָ����ﵽ3ʱ���Ǿ�Ҫ���ô˺���������������
//						 ��ʱ���������*/
//{
//	BTREE lchild, rchild;
//	int i, j;
//	lchild = new node;
//	rchild = new node;
//	int key;
//	if (low->parent == NULL)/*��һ�֣�Ҫ���ѵĽ��aΪ����㣬����Ҫ���˽����Ϊ�µĸ����洢key[2]��ͬʱnew����BTREE�½��lchild��rchild
//							��Ϊ�¸�����son[1]��son[0],�洢key[1]��key[2]��ͬʱ��ԭ����a����son[0],son[1]��lchild��son[2]��son[3]��
//							rchild*/
//
//	{
//		lchild->parent = low;
//		rchild->parent = low;
//
//		lchild->key[0] = 1;
//		rchild->key[0] = 1;
//
//		lchild->key[1] = low->key[1];
//		for (i = 2; i <= MAX; i++)
//		{
//			lchild->key[i] = 0;
//		}
//		rchild->key[1] = low->key[3];
//		for (i = 2; i <= MAX; i++)
//		{
//			rchild->key[i] = 0;
//		}
//
//		lchild->son[0] = low->son[0];
//		lchild->son[1] = low->son[1];
//		if (low->son[0] != NULL)
//		{
//			low->son[0]->parent = lchild;
//			low->son[1]->parent = lchild;
//		}
//		lchild->son[2] = NULL;
//		lchild->son[3] = NULL;
//		rchild->son[0] = low->son[2];
//		rchild->son[1] = low->son[3];
//		if (low->son[2] != NULL)
//		{
//			low->son[2]->parent = rchild;
//			low->son[3]->parent = rchild;
//		}
//		rchild->son[2] = NULL;
//		rchild->son[3] = NULL;
//
//		low->son[0] = lchild;
//		low->son[1] = rchild;
//		low->son[2] = NULL;
//		low->son[3] = NULL;
//		low->key[0] = 1;
//		low->key[1] = low->key[2];
//		low->key[2] = 0;
//		low->key[3] = 0;
//	}
//	else if (low->parent != NULL)//�ڶ�����ý�㲻Ϊ����㣬ӵ�и����
//	{
//		if (low->parent->son[2] == NULL)/*�ڶ��֣�����ý��a�ĸ��������������ʱ�����ʱa���ֻ��1���ؼ���
//										��ʱ�����½���һ��BTREE���rchild�����ڴ���a��key[3],����rchild�����Ϣ��������*/
//		{
//			rchild->parent = low->parent;
//			rchild->key[0] = 1;
//			rchild->key[1] = low->key[3];
//			rchild->son[0] = low->son[2];
//			rchild->son[1] = low->son[3];
//			if (low->son[2] != NULL)
//				low->son[2]->parent = rchild;
//			if (low->son[3] != NULL)
//				low->son[3]->parent = rchild;
//
//			low->son[2] = NULL;
//			low->son[3] = NULL;
//			for (i = 2; i <= 3; i++)
//			{
//				rchild->son[i] = NULL;
//			}
//			for (i = 2; i <= 3; i++)
//			{
//				rchild->key[i] = 0;
//			}
//			low->parent->son[2] = rchild;
//			key = low->key[2];
//			for (i = 2; i <= MAX; i++)
//			{
//				low->key[i] = 0;
//			}
//			low->key[0] = 1;
//			realinsert(low->parent, key);
//
//		}
//		else if (low->parent->son[2] != NULL&&low->parent->son[3] == NULL)/*�����֣�Ҫ���ѵ�a���ĸ������3������ʱ
//																		  ���ѷ�ʽ��ڶ������ƣ���Ҫ�������丸�����a�����Ѻ�Ҫ��������*/
//		{
//			rchild->parent = low->parent;
//			rchild->key[0] = 1;
//			rchild->key[1] = low->key[3];
//			for (i = 0; i <= MAX; i++)
//			{
//				rchild->son[i] = NULL;
//			}
//			for (i = 0, j = 2; i <= 1; i++, j++)
//			{
//				rchild->son[i] = low->son[j];
//				if (low->son[j] != NULL)
//					low->son[i]->parent = rchild;
//			}
//			low->son[2] = NULL;
//			low->son[3] = NULL;
//			for (i = 2; i <= MAX; i++)
//			{
//				rchild->key[i] = 0;
//			}
//			low->parent->son[3] = rchild;
//			key = low->key[2];
//			for (i = 2; i <= MAX; i++)
//			{
//				low->key[i] = 0;
//			}
//			low->key[0] = 1;
//			realinsert(low->parent, key);
//		}
//
//	}
//
//}
//
//BTREE creatBTREE()//����һ����B-�������ݵ�����loadBTREE����
//{
//	BTREE root;
//	root = new node;
//	int i;
//	for (i = 0; i <= MAX; i++)
//	{
//		root->key[i] = 0;
//	}
//	root->parent = NULL;
//	for (i = 0; i <= MAX; i++)
//	{
//		root->son[i] = NULL;
//	}
//	return root;
//}
//
//
//BTREE loadData(BTREE root, int n){
//
//	char* temp = new char[16];
//	char* data = new char[12];
//	int count = 0;
//	for (int i = 0; i < n; i++){
//		insertBTREE(root, i);
//		display(root);
//		cout << "-----------" << endl;
//	}
//	cout << "������ɣ�" << endl;
//
//	return root;
//}
//
//int realinsert(BTREE low, int key)//�˺���Ϊ��ȷ���Ľ���в���ȷ���ؼ��ֵĺ����������к����ж��е���
////���������а���С�����˳���������ؼ��֣���������key[0]�����ؼ��ָ������ﵽ��3���͵��÷��Ѻ���splitBTREE
//{
//	if (low->key[0] == 0)
//	{
//		low->key[0] = 1;
//		low->key[1] = key;
//	}
//	else if (low->key[0] == 1)
//	{
//		if (key>low->key[1])
//			low->key[2] = key;
//		else
//		{
//			low->key[2] = low->key[1];
//			low->key[1] = key;
//		}
//		low->key[0] = 2;
//	}
//	else if (low->key[0] == 2)
//	{
//		if (key>low->key[1] && key<low->key[2])
//		{
//			low->key[3] = low->key[2];
//			low->key[2] = key;
//		}
//		else if (key <= low->key[1])
//		{
//			low->key[3] = low->key[2];
//			low->key[2] = low->key[1];
//			low->key[1] = key;
//		}
//		else if (key >= (low->key[2]))
//		{
//			low->key[3] = key;
//		}
//		low->key[0] = 3;
//	}
//
//	if (low->key[0] == 3)
//	{
//		splitBTREE(low);
//	}
//	return 0;
//}
//int insertBTREE(BTREE root, int key)//�˺���Ϊ����ĳ�ؼ��ֲ���λ�õĺ�������������search��������ͬ��������ֻѰ�ҿ��Բ���ĳ�ؼ��ֵĺ��ʵ�Ҷ���
////���ҵ�������Ҷ����͵���realinsert�������ùؼ��ֲ��뵽��Ҷ�ڵ��С�
//{
//
//	if (root->son[0] == NULL)
//	{
//		realinsert(root, key);//����realinsert����
//		return 0;
//	}
//	else if (root->son[0] != NULL)
//	{
//
//		if (root->son[2] != NULL)
//		{
//			if (key<root->key[1])
//				insertBTREE(root->son[0], key);
//			else if (key >= root->key[1] && key<root->key[2])
//				insertBTREE(root->son[1], key);
//			else if (key >= root->key[2])
//				insertBTREE(root->son[2], key);
//		}
//		else if (root->son[1] != NULL&&root->son[2] == NULL)
//		{
//			if (key<root->key[1])
//				insertBTREE(root->son[0], key);
//			else if (key >= root->key[1])
//				insertBTREE(root->son[1], key);
//		}
//	}
//	return 0;
//}
//int realdelete(BTREE a, int key)//����ɾ����������ȷ���Ľ����ɾ��ȷ���Ĺؼ���
//{
//	if (a->key[0] == 1)
//	{
//		a->key[1] = 0;//�˴����ǵ�ֻҪ�õ�realdelete��Ҫ�����Ԫ��
//		a->key[0] = 0;
//	}
//	else if (a->key[0] == 2)
//	{
//		if (a->key[1] == key)
//		{
//			a->key[1] = a->key[2];
//			a->key[2] = a->key[3];
//		}
//		else if (a->key[2] == key)
//		{
//			a->key[2] = 0;
//		}
//		a->key[0] = 1;
//	}
//	return 0;
//}
//BTREE rcousin(BTREE a)//�ҵ�a�������ֵܺ���������ɾ������
//{
//	if (a->parent->son[0] == a)
//		return a->parent->son[1];
//	else if (a->parent->son[1] == a)
//		return a->parent->son[2];
//	else
//		return NULL;
//}
//BTREE lcousin(BTREE a)//�ҵ�a�������ֵܺ���������ɾ������
//{
//	if (a->parent->son[1] == a)
//		return a->parent->son[0];
//	else if (a->parent->son[2] == a)
//		return a->parent->son[1];
//	else
//		return NULL;
//}
//
//int sum(BTREE a, BTREE b, int x)//�ϲ����������������
//{
//
//	int i, n, j;
//	if (b == rcousin(a) && b->key[0] == 1)//��һ�֣�b��a�����ֵܣ���bֻ��һ���ؼ���
//	{
//		realdelete(a, a->key[1]);
//		realinsert(a, b->key[1]);
//		realinsert(a, x);
//		for (i = 0; i <= 2; i++)
//		{
//			if (b == a->parent->son[i])
//			{
//				a->parent->son[i] = NULL;
//				for (n = i; n <= 2; n++)
//				{
//					a->parent->son[n] = a->parent->son[n + 1];
//				}
//				break;
//			}
//		}
//		realdelete(a->parent, x);
//		for (i = 0, j = 0; i <= 2; i++)
//		{
//			if (a->son[i] == NULL)
//			{
//				a->son[i] = b->son[j];
//				j++;
//			}
//
//		}
//		delete b;
//		if (a->parent->parent != NULL&&a->parent->key[0] == 0)
//		{
//			if (rcousin(a->parent) != NULL)
//			{
//				sum(a->parent, rcousin(a->parent), a->parent->parent->key[1]);
//			}
//			else if (lcousin(a->parent) != NULL)
//			{
//				sum(a->parent, lcousin(a->parent), a->parent->parent->key[a->parent->parent->key[0]]);
//			}
//		}
//		else if (a->parent->parent == NULL&&a->parent->key[0] == 0)
//		{
//			for (i = 0; i <= 3; i++)
//			{
//				a->parent->son[i] = a->son[i];
//				if (b->son[i] != NULL)
//					a->son[i]->parent = a->parent;
//			}
//			for (i = 0; i <= 3; i++)
//			{
//				a->parent->key[i] = a->key[i];
//			}
//			delete a;
//
//		}
//	}
//	else if (b == rcousin(a) && b->key[0] == 2)//�ڶ��֣�b��a�����ֵܣ���b��2���ؼ��֣���ʱ��a��bΪ��Ҷ���
//	{
//		realdelete(a, a->key[1]);
//		realinsert(a, x);
//		realdelete(a->parent, x);
//		realinsert(a->parent, b->key[1]);
//		realdelete(b, b->key[1]);
//		for (i = 0; i <= 3; i++)
//		{
//			if (a->son[i] == NULL)
//			{
//				a->son[i] = b->son[0];
//				b->son[0]->parent = a;
//				b->son[0] = b->son[1];
//				b->son[1] = b->son[2];
//				b->son[2] = b->son[3];
//			}
//		}
//	}
//	else if (b == lcousin(a) && b->key[0] == 1)//�����֣�b��a�����ֵܣ���bֻ��һ���ؼ���
//	{
//		realinsert(b, x);
//		for (i = 0; i <= 2; i++)
//		{
//			if (a == b->parent->son[i])
//			{
//				a->parent->son[i] = NULL;
//				for (n = i; n <= 2; n++)
//				{
//					a->parent->son[n] = a->parent->son[n + 1];
//				}
//			}
//		}
//		realdelete(a->parent, x);
//		for (i = 0, j = 0; i <= 2; i++)
//		{
//			if (b->son[i] == NULL)
//			{
//				b->son[i] = a->son[j];
//				j++;
//			}
//		}
//		delete a;
//		if (b->parent->parent != NULL&&b->parent->key[0] == 0)
//		{
//			if (rcousin(b->parent) != NULL)
//			{
//				sum(b->parent, rcousin(b->parent), b->parent->parent->key[1]);
//				return 0;
//			}
//			else if (lcousin(b->parent) != NULL)
//			{
//				sum(b->parent, lcousin(b->parent), b->parent->parent->key[a->parent->parent->key[0]]);
//				return 0;
//			}
//		}
//		else if (b->parent->parent == NULL&&b->parent->key[0] == 0)
//		{
//			for (i = 0; i <= 3; i++)
//			{
//				b->parent->son[i] = b->son[i];
//				if (b->son[i] != NULL)
//					b->son[i]->parent = b->parent;
//			}
//			for (i = 0; i <= 3; i++)
//			{
//				b->parent->key[i] = b->key[i];
//			}
//			delete b;
//
//		}
//	}
//	else if (b == lcousin(a) && b->key[0] == 2)//�����֣�b��a�����ֵܣ���b��2���ؼ��֣���ʱ��a��bΪ��Ҷ���
//	{
//		realdelete(a, a->key[1]);
//		realinsert(a, x);
//		realdelete(a->parent, x);
//		realinsert(a->parent, b->key[b->key[0]]);
//		realdelete(b, b->key[b->key[0]]);
//		a->son[3] = a->son[2];
//		a->son[2] = a->son[1];
//		a->son[1] = a->son[0];
//		a->son[0] = b->son[b->key[0]];
//		b->son[b->key[0]]->parent = a;
//		b->son[b->key[0]] = NULL;
//
//	}
//
//}
//int deleteBTREE(BTREE root, int x)/*ɾ���������������ȵ���search��������Ҫɾ���Ĺؼ��֣�������صĽ���д���Ҫɾ���Ĺؼ��������
//								  ���ֻ�Ƿ�����һ��Ӧ�ò���ùؼ��ֵ�Ҷ�ڵ�λ�ã�������������ڸùؼ��֡�
//
//								  ������ʱ�������������*/
//
//{
//	BTREE a, b;
//	int i;
//	int u;
//	a = search(root, x);
//	if (a->key[1] != x&&a->key[2] != x&&a->key[3] != x)
//	{
//		cout << "B-���в����ڹؼ���" << x << endl;
//		return -1;
//	}
//	if (a->son[0] != NULL) //��һ���ࣺ���Ҫɾ����key�ڷ�Ҷ����У���Ϊkey[i]��ô����Ҫ�ڸý�������son[i]����һ����С�Ľ���滻key
//		//��������son[i]��ɾ��key����ʱ�ݹ���ú���deleteBTREE(a->son[i],x);
//	{
//		if (a->parent == NULL)//��һ������������ �����aΪ����㣬��������а���key��2��Ԫ��������ɾ��key����ֻ��һ��Ԫ����ɾ����ɾ�ɿ���������B-��ɾ��������˲�����
//		{
//			if (a->key[0] == 1)
//			{
//				a->key[1] = 0;
//				a->key[0] = 0;
//				a = NULL;
//			}
//			else if (a->key[0] == 2)
//			{
//				realdelete(a, x);
//			}
//		}
//		else//��һ������������
//		{
//			for (i = 1; i <= a->key[0]; i++)
//			{
//
//				if (a->key[i] == x)
//				{
//					int temp;
//					temp = a->son[i]->key[1];
//					realdelete(a->son[i], temp);
//					realinsert(a->son[i], x);
//					realdelete(a, x);
//					realinsert(a, temp);
//					deleteBTREE(a->son[i], x);
//					break;
//				}
//			}
//		}
//
//	}
//	else if (a->son[0] == NULL)//�ڶ����࣬aΪҶ��㣬key��a�У���ʱ��5�����
//	{
//		if (a->parent == NULL)//�ڶ���������������Ϊ����㣨ʵ���ϲ����ڴ����������һ��if���ѹ��ˣ�
//		{
//			if (a->key[0] == 1)
//			{
//				a->key[1] = 0;
//				a->key[0] = 0;
//				a = NULL;
//			}
//			else if (a->key[0] == 2)
//			{
//				realdelete(a, x);
//			}
//		}
//		else if (a->parent != NULL)
//		{
//
//			if (a->key[0] == 2)//��һ�֣��ý�����key��2��Ԫ�أ���ʱֱ��ɾ��key����
//			{
//				realdelete(a, x);
//				return 0;
//			}
//			else if (a->key[0] == 1)
//			{
//				b = rcousin(a);
//				if (b != NULL&&b->key[0] == 2)//�ڶ��֣��ýڵ�aֻ��keyһ��Ԫ���������ֵܽ���������2��Ԫ��
//					//��ʱ����Ҫ�����ֵܽ���Ԫ�أ����ֵ�����СԪ�ؽ��a�ĸ���㣬������д���key����СԪ�ؽ��a���
//				{
//					for (i = 1; i <= a->parent->key[0]; i++)
//					{
//						if (a->parent->key[i]>x)
//							u = a->parent->key[i];
//					}
//					a->key[1] = u;
//					realdelete(a->parent, u);
//					realinsert(a->parent, b->key[1]);
//					realdelete(b, b->key[1]);
//					for (i = 0; i <= 2; i++)
//					{
//						if (a->son[i] == NULL)
//							a->son[i] = b->son[1];
//					}
//					b->son[0] = b->son[1];
//					b->son[1] = b->son[2];
//					b->son[2] = b->son[3];
//					return 0;
//				}
//				b = lcousin(a);
//				if (b != NULL&&b->key[0] == 2)//�����֣��ý��a�ýڵ�aֻ��keyһ��Ԫ�������ֵܲ��浫�������ֵܽ���������2��Ԫ��
//					//��ʱ����Ҫ�����ֵܽ���Ԫ�أ����ֵ������Ԫ�ؽ��a�ĸ���㣬�������С��key�����Ԫ�ؽ��a���
//				{
//					for (i = a->parent->key[0]; i >= 1; i--)
//					{
//						if (a->parent->key[i]<x)
//							u = a->parent->key[i];
//					}
//					realdelete(a->parent, u);
//					realinsert(a->parent, b->key[2]);
//					realdelete(b, b->key[2]);
//					a->son[3] = a->son[2];
//					a->son[2] = a->son[1];
//					a->son[1] = a->son[0];
//					for (i = 0; i <= 2; i++)
//					{
//						if (b->son[i] == NULL)
//						{
//							a->son[0] = b->son[i - 1];
//							b->son[i - 1] = NULL;
//						}
//					}
//					return 0;
//
//				}
//				b = rcousin(a);
//				if (b != NULL&&b->key[0] == 1)//�����֣��ý��aֻ��keyһ��Ԫ���������ֵܽ����ڵ�ֻ��1��Ԫ��
//					//��ʱ����Ҫ�ϲ��ý��͸ý������ֵܽ�㣬����sum������ͬʱ�򸸽������key����С��Ԫ��
//				{
//					for (i = 1; i <= a->parent->key[0]; i++)
//					{
//						if (a->parent->key[i]>x)
//						{
//							sum(a, b, a->parent->key[i]);
//							break;
//						}
//					}
//					return 0;
//				}
//
//				b = lcousin(a);
//				if (b != NULL&&b->key[0] == 1)//�����֣��ý��aֻ��keyһ��Ԫ�������ֵܲ����ڣ������ֵܽ����ڵ�ֻ��1��Ԫ��
//					//��ʱ����Ҫ�ϲ��ý��͸ý������ֵܽ�㣬����sum������ͬʱ�򸸽�������Ԫ��
//				{
//					cout << "succeed4" << endl;
//					for (i = a->parent->key[0]; i >= 0; i--)
//					{
//						if (a->parent->key[i] != 0)
//						{
//							sum(a, b, a->parent->key[i]);
//							break;
//						}
//					}
//					return 0;
//				}
//			}
//		}
//	}
//	return 0;
//}
//
//int main()
//{
//	BTREE A;
//	int x, y, l = 1;
//	BTREE root;
//	root = creatBTREE();
//	int count;
//	cin >> count;
//	cout << "---------------------------------------------" << endl;
//	loadData(root, count);
//	cout << "---------------------------------------------" << endl;
//	while (l)
//	{
//		cout << "delete what?" << endl;
//		cin >> y;
//
//		deleteBTREE(root, y);
//		if (root->key[0] == 0)
//			cout << "��ɾ�ɿ���" << endl;
//		else
//		{
//			display(root);
//		}
//		cout << "����ɾ������1���˳�ɾ������0" << endl;
//		cin >> l;
//	}
//	return 0;
//}
