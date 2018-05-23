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
//	int key[MAX + 1];//储存关键字，其中k[0]不储存关键字，而是储存当前结点中储存的关键字个数
//	struct node *parent;//指向父节点
//	struct node *son[MAX + 1];//指向儿子节点
//} BTreeNode;
//
//typedef   BTreeNode   *BTREE;
//int insertBTREE(BTREE root, int key);
//int realinsert(BTREE low, int key);
//int display(BTREE root)//先序遍历打印B-树
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
//BTREE search(BTREE root, int key) /*运用递归调用，从根节点查找关键字，如果关键字在现在的节点那么返回这个结点。
//								  如果不在，且这个结点不是叶结点，那么我们看这个结点的关键字K[1]，K[2],K[3],
//								  如果小于K[1]，就在这个结点的son[0]中查找，如果介于key[1]和key[2]之间就在son[1]中查找
//								  如果大于key[2]就在son[2]中查找，前面已述以上情况是指这个结点不是叶结点的情况，
//								  如果该结点是叶结点，那么返回这个结点，此时要么关键字在这个叶结点中，要么这个叶结点是该关键字应该插入的位置*/
//{
//	int flag = 0;
//	int i;
//	if (root->son[0] == NULL)
//	{
//		return root;
//	}
//	else if (root->son[0] != NULL)
//	{
//		if (root->key[0] == 1)//当有一个关键字
//		{
//			if (key == root->key[1])
//				return root;
//			else if (key<root->key[1])
//				search(root->son[0], key);
//			else if (key>root->key[1])
//				search(root->son[1], key);
//		}
//		else if (root->key[0] == 2)//当有两个关键字
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
//void splitBTREE(BTREE low)/*当在realinsert函数中关键字个数达到3时我们就要调用此函数来分裂这个结点
//						 这时有三种情况*/
//{
//	BTREE lchild, rchild;
//	int i, j;
//	lchild = new node;
//	rchild = new node;
//	int key;
//	if (low->parent == NULL)/*第一种，要分裂的结点a为根结点，我们要将此结点作为新的根结点存储key[2]，同时new两个BTREE新结点lchild和rchild
//							作为新根结点的son[1]和son[0],存储key[1]和key[2]，同时将原来的a结点的son[0],son[1]给lchild，son[2]和son[3]给
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
//	else if (low->parent != NULL)//第二大类该结点不为根结点，拥有父结点
//	{
//		if (low->parent->son[2] == NULL)/*第二种：如果该结点a的父结点有两个儿子时，则此时a结点只有1个关键字
//										此时我们新建立一个BTREE结点rchild，用于储存a的key[3],并将rchild结点信息补充完整*/
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
//		else if (low->parent->son[2] != NULL&&low->parent->son[3] == NULL)/*第三种：要分裂的a结点的父结点有3个儿子时
//																		  分裂方式与第二种类似，但要考。虑其父结点在a结点分裂后要继续分裂*/
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
//BTREE creatBTREE()//创建一个空B-树，数据导入在loadBTREE函数
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
//	cout << "插入完成！" << endl;
//
//	return root;
//}
//
//int realinsert(BTREE low, int key)//此函数为向确定的结点中插入确定关键字的函数，在所有函数中都有调用
////在这个结点中按从小到大的顺序插入这个关键字，如果插入后key[0]（即关键字个数）达到了3，就调用分裂函数splitBTREE
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
//int insertBTREE(BTREE root, int key)//此函数为查找某关键字插入位置的函数，查找类似search函数，不同的是我们只寻找可以插入某关键字的合适的叶结点
////查找到这样的叶结点后就调用realinsert函数将该关键字插入到该叶节点中。
//{
//
//	if (root->son[0] == NULL)
//	{
//		realinsert(root, key);//调用realinsert函数
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
//int realdelete(BTREE a, int key)//真正删除函数，在确定的结点中删除确定的关键字
//{
//	if (a->key[0] == 1)
//	{
//		a->key[1] = 0;//此处考虑到只要用到realdelete就要重新填补元素
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
//BTREE rcousin(BTREE a)//找到a结点的右兄弟函数，用于删除操作
//{
//	if (a->parent->son[0] == a)
//		return a->parent->son[1];
//	else if (a->parent->son[1] == a)
//		return a->parent->son[2];
//	else
//		return NULL;
//}
//BTREE lcousin(BTREE a)//找到a结点的左兄弟函数，用于删除操作
//{
//	if (a->parent->son[1] == a)
//		return a->parent->son[0];
//	else if (a->parent->son[2] == a)
//		return a->parent->son[1];
//	else
//		return NULL;
//}
//
//int sum(BTREE a, BTREE b, int x)//合并函数，共四种情况
//{
//
//	int i, n, j;
//	if (b == rcousin(a) && b->key[0] == 1)//第一种，b是a的右兄弟，且b只有一个关键字
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
//	else if (b == rcousin(a) && b->key[0] == 2)//第二种，b是a的右兄弟，且b有2个关键字，此时的a和b为非叶结点
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
//	else if (b == lcousin(a) && b->key[0] == 1)//第三种，b是a的左兄弟，且b只有一个关键字
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
//	else if (b == lcousin(a) && b->key[0] == 2)//第四种，b是a的左兄弟，且b有2个关键字，此时的a和b为非叶结点
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
//int deleteBTREE(BTREE root, int x)/*删除操作函数：首先调用search函数查找要删除的关键字，如果返回的结点中存在要删除的关键字则继续
//								  如果只是返回了一个应该插入该关键字的叶节点位置，则输出“不存在该关键字”
//
//								  当继续时，有两大类情况*/
//
//{
//	BTREE a, b;
//	int i;
//	int u;
//	a = search(root, x);
//	if (a->key[1] != x&&a->key[2] != x&&a->key[3] != x)
//	{
//		cout << "B-树中不存在关键字" << x << endl;
//		return -1;
//	}
//	if (a->son[0] != NULL) //第一大类：如果要删除的key在非叶结点中，且为key[i]那么我们要在该结点的子树son[i]中找一个最小的结点替换key
//		//并继续在son[i]中删除key，此时递归调用函数deleteBTREE(a->son[i],x);
//	{
//		if (a->parent == NULL)//第一大类的特殊情况 ：如果a为根结点，若根结点中包括key有2个元素则正常删除key，若只有一个元素再删除就删成空树（根据B-树删除定义如此操作）
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
//		else//第一大类的正常情况
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
//	else if (a->son[0] == NULL)//第二大类，a为叶结点，key在a中，此时有5种情况
//	{
//		if (a->parent == NULL)//第二大类的特殊情况，为根结点（实际上不存在此情况，在上一个if中已过滤）
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
//			if (a->key[0] == 2)//第一种，该结点包括key有2个元素，此时直接删除key即可
//			{
//				realdelete(a, x);
//				return 0;
//			}
//			else if (a->key[0] == 1)
//			{
//				b = rcousin(a);
//				if (b != NULL&&b->key[0] == 2)//第二种，该节点a只有key一个元素且其右兄弟结点存在且有2个元素
//					//此时我们要向右兄弟结点借元素，右兄弟中最小元素借给a的父结点，父结点中大于key的最小元素借给a结点
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
//				if (b != NULL&&b->key[0] == 2)//第三种，该结点a该节点a只有key一个元素其右兄弟不存但且其左兄弟结点存在且有2个元素
//					//此时我们要向左兄弟结点借元素，左兄弟中最大元素借给a的父结点，父结点中小于key的最大元素借给a结点
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
//				if (b != NULL&&b->key[0] == 1)//第四种，该结点a只有key一个元素且其右兄弟结点存在但只有1个元素
//					//此时我们要合并该结点和该结点的右兄弟结点，调用sum函数，同时向父结点借大于key的最小的元素
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
//				if (b != NULL&&b->key[0] == 1)//第五种，该结点a只有key一个元素其右兄弟不存在，其左兄弟结点存在但只有1个元素
//					//此时我们要合并该结点和该结点的左兄弟结点，调用sum函数，同时向父结点借最大的元素
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
//			cout << "已删成空树" << endl;
//		else
//		{
//			display(root);
//		}
//		cout << "继续删除输入1，退出删除输入0" << endl;
//		cin >> l;
//	}
//	return 0;
//}
