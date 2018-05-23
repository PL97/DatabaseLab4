#include<iostream>
#include<time.h>
#include<fstream>
#include <string>
#include<sstream>

using namespace std;

#define MSIZE (1024*1024)		//1M 空间内存
#define FILENAME "myfile.txt"
#define STAGEONE "iteration0.txt"
#define RECORDSIZE 16
#define BUFFER (int)(MSIZE/(16*3))
//#define SWAP(a, b) {(a) = (a)+(b); (b) = (a) - (b); (a) = (a) - (b);}//overflow

int dataSize = 1000000;


#include<iostream>
#include<vector>

using namespace std;
#define M 3
#define SECTION pair<int, BNode*>//a pair of K and A

struct BNode{
	BNode* A0;			//第一个指针
	BNode * parent;		//指向父亲节点的指针
	vector<SECTION> A;	//键值一个一个索引，A为该结构的一个容器
	BNode(){
		A0 = NULL;
		parent = NULL;
		A.clear();
	}
	BNode(BNode *_parent, int key){
		parent = _parent;
		A0 = NULL;
		A.push_back(SECTION(key, NULL));
	}
};

//插入数据key， 返回根节点
BNode* insert(BNode* root, int key);

//查找节点，返回一个pair，里面保存一个指向查找的节点的索引和数据所在的数组下标
SECTION search(BNode* root, int key);

//在一个节点上进行线性查找， 返回键值位于的数组下标
//如果没查找到则返回恰好大于该数的键值的下标
int nodeSearch(BNode* current, int key);

//将一个节点分裂成两个节点，返回值为两个节点和一个中间键值
pair<int, pair<BNode*, BNode*>> breakNode(BNode* current);

//删除键值， 返回根节点
BNode* deleteKey(BNode *root, int key);

//以先序的顺序展示树结构
void display(BNode *root);

BNode* change(BNode* current, int sub);




//test
//#define MSIZE 1024		//1M 空间内存
//#define BUFFER (int)(MSIZE/(16*3))
//int dataSize = 1000000;

struct myfile{
	int A;
	char B[12];
	myfile(){
		//B = new char[12];
		memset(this, 0, sizeof(myfile));
	}
};

/*
随机产生索引
返回索引数组的头指针
*/
int* createRandonIndex();

/*
生成记录文件，文件中含1000000条记录
记录格式：前4byte：int型数据，后13byte：字符串（filex）
*/
void createMyFile();

/*
归并排序F
对索引文件进行排序
*/
void mergeSort();

pair<myfile*, pair<int, int>> merge(pair<myfile*, int> x, pair<myfile*, int> y, int resultSize);

/*
读取文件
输入参数：读取的行数
*/
pair<myfile*, int> readFile(string fname, int begin, int size);

int myCompare(const void* f1, const void* f2){
	return (*(myfile*)f1).A - (*(myfile*)f2).A;
}

int myCompare1(const void* f1, const void* f2){
	return (*(int*)f1) - (*(int*)f2);
}

void writeBack(ofstream* fout, pair<myfile*, int> data);

BNode* loadData(BNode *root, int n);

int main(){
	srand((unsigned int)time(NULL));
	int opt;
	BNode *root = new BNode();
	cin >> opt;
	if (opt == 0){
		createMyFile();
		mergeSort();
		getchar();
	}
	cout << "输入建立索引数目：" << endl;
	int n;
	cin >> n;
	root = loadData(root, n);
	while (1){
		int opt;
		cout << "操作模式：0:查找， 1删除, 2插入" << endl;
		cin >> opt;
		if (opt == 0){
			cout << "输入查找数据" << endl;
			int key;
			cin >> key;
			SECTION result = search(root, key);
			BNode* searchedNode = result.second;
			int sub = result.first;
			if (sub >= 1 && searchedNode->A[sub - 1].first == key){
				cout << "数据存在！" << endl;
			}
			else{
				cout << "数据不存在！" << endl;
			}
		}
		else if (opt == 1){
			cout << "开始删除，输入待删除数据：" << endl;
			display(root);
			int key;
			cin >> key;
			root = deleteKey(root, key);
			display(root);
		}
		else{
			int key;
			cin >> key;
			root = insert(root, key);
			display(root);
		}
	}
	system("pause");
}

BNode* loadData(BNode *root, int n){
	ifstream fin(FILENAME, ios::ios_base::in);
	stringstream ss;
	char* temp = new char[16];
	char* data = new char[12];
	int count = 0;
	if (fin){
		while (!fin.eof()){
			int key;
			fin.getline(temp, 16);
			ss << temp;
			ss >> key;
			ss >> data;
			root= insert(root, key);
			ss.clear();
			count++;
			if (count == n)
				break;
			//cout << ++count << endl;
		}
	}
	fin.close();
	cout << "插入完成！" << endl;
	cout << "数据先序排列" << endl;
	display(root);
	return root;
}

int* createRandonIndex(){
	int *index = new int[dataSize];
	for (int j = 0; j < dataSize; j++){
		index[j] = j;
	}
	int temp;
	for (int i = 0; i<dataSize; i++){
		int sub = rand() % (dataSize - i);
		//SWAP(index[dataSize - i - 1], index[sub]);
		temp = index[dataSize - i - 1];
		index[dataSize - i - 1] = index[sub];
		index[sub] = temp;
	}
	return index;
}

void createMyFile(){
	fstream f;
	f.open(FILENAME, ios::ios_base::in | ios_base::out);
	if (!f){
		cout << "文件打开失败！" << endl;
		cout << "创建文件" << FILENAME << ".txt" << endl;
		ofstream fout(FILENAME);
		if (fout) { // 如果创建成功
			cout << "文件创建成功！" << endl;
			int *index = createRandonIndex();
			string temp = "F";
			for (int i = 0; i < dataSize; i++){
				string temp1 = temp +  to_string(i);
				fout << index[i] << temp1 << endl;
			}
			cout << "文件创建完毕！" << endl;
			fout.close();  // 执行完操作后关闭文件句柄
		}
	}
	else{
		cout << "文件存在，可以直接读取..." << endl;
	}
}

void mergeSort(){
	int maxBlock = MSIZE / RECORDSIZE;
	int left = dataSize%maxBlock;
	int mergeDimension = dataSize / maxBlock;
	if (left != 0) mergeDimension++;
	ofstream fout(STAGEONE, ios::ios_base::in);
	if (!fout){
		fout.open(STAGEONE);
		//step1:将小块进行排序-----------------------------------------------
		for (int i = 0; i < mergeDimension; i++){
			pair<myfile*, int> p = readFile(FILENAME, i*maxBlock, maxBlock);
			std::qsort(p.first, p.second, sizeof(myfile), myCompare);
			for (int j = 0; j < p.second; j++){
				fout << p.first[j].A << "	" << p.first[j].B << endl;
			}
		}
	}
	fout.close();
	//step2:进行两两归并排序---------------------------------------------
	//int count = mergeDimension/2;//需要归并的块数
	int size = maxBlock;//当前块的大小
	//left = mergeDimension % 2;//是否有剩余（两两归并）
	left = 0;
	int count = mergeDimension;
	string name = "iteration";
	int nameSuffix = 0;
	while (count>=1){
		//将文件中的有序数据块进行归并排序，并产生一个迭代文件
		string temp1 = name + to_string(nameSuffix++)+".txt";
		string temp2 = name + to_string(nameSuffix) + ".txt";
		ofstream fout2(temp2, ios::ios_base::in);
		int temp = count + left;
		count = temp / 2;
		left = temp % 2;
		if (fout2)
			continue;
		fout2.open(temp2);
		//有n个有序块则需要count = n/2次排序，余数存在left里
		for (int i = 0; i < count; i++){
			pair<myfile*, int> p1 = readFile(temp1, pow(2, nameSuffix-1)*maxBlock * 2 * i, BUFFER);
			pair<myfile*, int> p2 = readFile(temp1, pow(2, nameSuffix-1)*maxBlock*(2 * i + 1), BUFFER);
			int mergeSize = BUFFER;
			int times1 = 1, times2 = 1;
			do{
				if (p1.second + p2.second < BUFFER){
					mergeSize = p1.second + p2.second;
				}
				else{
					mergeSize = BUFFER;
				}
				pair<myfile*, pair<int, int>> p3 = merge(p1, p2, mergeSize);
				writeBack(&fout2, make_pair(p3.first, p3.second.first+p3.second.second));
				if (p1.second - p3.second.first == 0){
					//更新p2的指针
					p2.first = &p2.first[p3.second.second];
					p2.second = p2.second - p3.second.second;
					if (BUFFER*(times1 + 1) < maxBlock*pow(2, nameSuffix - 1))
						p1 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * 2 * i + BUFFER*times1, BUFFER);
					else{
						p1 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * 2 * i + BUFFER*times1, maxBlock*pow(2, nameSuffix - 1) - BUFFER*times1);
					}
					if (p1.second == -1){
						//当其中一个已经排序完成，另一个将剩余数据直接写入内存
						writeBack(&fout2, make_pair(p2.first, p2.second));
						if (BUFFER*times2 < maxBlock*pow(2, nameSuffix - 1)){//是否还有剩余
							while (BUFFER*(times2 + 1) < maxBlock*pow(2, nameSuffix - 1)){
								p2 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * (2 * i + 1) + BUFFER*times2, BUFFER);
								writeBack(&fout2, make_pair(p2.first, p2.second));
								times2++;
							}
							p2 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * (2 * i + 1) + BUFFER*times2, maxBlock*pow(2, nameSuffix - 1) - BUFFER*times2);
							writeBack(&fout2, make_pair(p2.first, p2.second));
						}
						break;
					}
					times1++;
				}
				else if (p2.second - p3.second.second == 0){
					//更新p1指针
					p1.first = &p1.first[p3.second.first];
					p1.second = p1.second - p3.second.first;
					if (BUFFER*(times2 + 1) < maxBlock*pow(2, nameSuffix - 1))
						p2 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * (2 * i + 1) + BUFFER*times2, BUFFER);
					else {
						p2 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * (2 * i + 1) + BUFFER*times2, maxBlock*pow(2, nameSuffix - 1) - BUFFER*times2);
					}
					if (p2.second == -1){
						//当其中一个已经排序完成，另一个将剩余数据直接写入内存
						writeBack(&fout2, make_pair(p1.first, p1.second));
						//判断是否还有剩余
						if (BUFFER*times1 < maxBlock*pow(2, nameSuffix - 1)){
							while (BUFFER*(times1 + 1) < maxBlock*pow(2, nameSuffix - 1)){
								p1 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * 2 * i + BUFFER*times1, BUFFER);
								writeBack(&fout2, make_pair(p1.first, p1.second));
								times1++;
							}
							p1 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * 2 * i + BUFFER*times1, maxBlock*pow(2, nameSuffix - 1) - BUFFER*times1);
							writeBack(&fout2, make_pair(p1.first, p1.second));
						}
						break;
					}
					times2++;
				}
				else{
					p1.first = &p1.first[p3.second.first];
					p2.first = &p2.first[p3.second.second];
					p1.second = p1.second - p3.second.first;
					p2.second = p2.second - p3.second.second;
				}
			} while (1);
		}
		if (count!=0&&left){//将剩余数据写回
			int k = 0;
			while (1){
				pair<myfile*, int> p1 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * 2 * count + BUFFER*k++, BUFFER);
				if (p1.second == -1)
					break;
				writeBack(&fout2, make_pair(p1.first, p1.second));
			}
		}
		fout2.close();
		//int temp = count + left;
		//count = temp / 2;
		//left = temp % 2;
	}
}

pair<myfile*, int> readFile(string fname, int begin, int size){
	if (size <= 0){
		return pair<myfile*, int>(NULL, -1);
	}
	myfile *data = new myfile[size];//待排序变量
	std::stringstream ss;//字符流，用于转换类型
	//读取文件------------------------------------------------------------------
	ifstream fin(fname);
	//fread(buff, 16, 1, fp);
	//ss << buff;
	char temp[16];
	int count = 0;
	while (begin-- > 0){
		fin.getline(temp, 16);
	}
	while (!fin.eof() && count<size){
		fin.getline(temp, 16);
		ss << temp;
		ss >> data[count].A;
		ss >> data[count++].B;
		ss.clear();
	}
	if (fin.eof()){
		count--;
	}
	fin.close();
	//for (int i = 0; i < count; i++){
	//	cout << data[i].A << "	" << data[i].B << endl;
	//}
	return pair<myfile*, int>(data, count);
}

pair<myfile*, pair<int, int>> merge(pair<myfile*, int> x, pair<myfile*, int> y, int resultSize){
	pair<int, int> pointer(0, 0);
	myfile* sorted = new myfile[resultSize];
	for (int i = 0; i < resultSize; i++){
		//如果其中一个有序对已经为空
		if (pointer.first >= x.second || pointer.second >= y.second){
			break;
		}
		//如果两个有序对都不为空
		if (x.first[pointer.first].A < y.first[pointer.second].A){
			sorted[i] = x.first[pointer.first++];
		}
		else{
			sorted[i] = y.first[pointer.second++];
		}
	}
	return pair<myfile*, pair<int, int>>(sorted, pointer);
}

void writeBack(ofstream* fout, pair<myfile*, int> data){
	for (int i = 0; i < data.second; i++){
		*fout << data.first[i].A << "	" << data.first[i].B << endl;
	}
}

int nodeSearch(BNode* current, int key){
	BNode *tempRoot = current;
	int size = tempRoot->A.size();
	int sub = 0;
	if (tempRoot->A[0].first>key){
		return 0;
	}
	for (int i = 0; i < size; i++){
		if (key >= tempRoot->A[i].first){
			sub = i + 1;
			continue;
		}
		sub = i;
		break;
	}
	if (tempRoot->A[size - 1].first < key){
		sub = size;
	}
	return sub;
}

SECTION search(BNode *root, int key){
	BNode* tempRoot = root;
	int sub = -1;
	//if on root is null
	if (tempRoot->A.size() != 0){
		do{
			sub = nodeSearch(tempRoot, key);
			if (sub == 0 && tempRoot->A0 != NULL){
				tempRoot = tempRoot->A0;
				continue;
			}
			else if (sub == 0 && tempRoot->A0 == NULL){
				break;
			}
			//overwhelmed not bigger than any other
			if (tempRoot->A[sub - 1].first == key || (tempRoot->A.size() >= sub && tempRoot->A[sub - 1].second == NULL))
				break;
			tempRoot = tempRoot->A[sub - 1].second;
		} while (1);
	}
	return make_pair(sub, tempRoot);
}

BNode* insert(BNode* root, int key){
	BNode* tempRoot = root;
	if (tempRoot->A.size() == 0){
		root->A0 = NULL;
		root->parent = NULL;
		root->A.push_back(SECTION(key, NULL));
		return root;
	}
	pair<int, BNode*> tempPair = search(root, key);
	BNode* searchedNode = tempPair.second;
	int sub = tempPair.first;
	if (sub != 0 && sub <= searchedNode->A.size() && searchedNode->A[sub - 1].first == key){
		cout << "节点已经存在！" << endl;
	}
	else{
		//insert directly
		//连接指针
		SECTION newSEC;
		newSEC.first = key;
		newSEC.second = NULL;
		searchedNode->A.insert(searchedNode->A.begin() + sub, newSEC);
		while (searchedNode->A.size() >= M){
			pair<int, pair<BNode*, BNode*>> tempNodes = breakNode(searchedNode);
			int middleKey = tempNodes.first;
			BNode* lchild = tempNodes.second.first;
			BNode* rchild = tempNodes.second.second;
			searchedNode = searchedNode->parent;
			if (searchedNode == NULL){
				BNode *newRoot = new BNode();
				lchild->parent = newRoot;
				rchild->parent = newRoot;
				newRoot->A0 = lchild;
				newRoot->A.push_back(SECTION(middleKey, rchild));
				return newRoot;
			}
			//find the parent position
			lchild->parent = searchedNode;
			rchild->parent = searchedNode;
			int sub = nodeSearch(searchedNode, middleKey);
			searchedNode->A.insert(searchedNode->A.begin() + sub, SECTION(middleKey, rchild));
			if (sub == 0)
				searchedNode->A0 = lchild;
			else
				searchedNode->A[sub - 1].second = lchild;
		}
	}
	return root;
}

pair<int, pair<BNode*, BNode*>> breakNode(BNode* root){
	BNode *current = root;
	int childSize1 = current->A.size() / 2;
	int childSize2 = current->A.size() - 1 - childSize1;
	int parentSub = childSize1;
	BNode* lchild = new BNode();
	BNode* rchild = new BNode();
	//lchild 
	lchild->A0 = current->A0;
	if (current->A0 != NULL)
		current->A0->parent = lchild;
	for (int i = 0; i < childSize1; i++){
		lchild->A.push_back(current->A[i]);
		if (current->A[i].second != NULL)
			current->A[i].second->parent = lchild;

	}
	//rchild
	rchild->A0 = current->A[parentSub].second;
	if (current->A[parentSub].second!=NULL)
		current->A[parentSub].second->parent = rchild;
	for (int j = 0; j < childSize2; j++){
		rchild->A.push_back(current->A[j + parentSub + 1]);
		if (current->A[j + parentSub + 1].second != NULL)
			current->A[j + parentSub + 1].second->parent = rchild;
	}
	return make_pair(current->A[parentSub].first, make_pair(lchild, rchild));
}

BNode* deleteKey(BNode *root, int key){
	if (root == NULL)
		cout << "树为空！" << endl;
	BNode *tempNode = root;
	SECTION searched = search(tempNode, key);
	BNode* searchedNode = searched.second;
	int sub = searched.first;
	if (sub != 0 && sub <= searchedNode->A.size() && searchedNode->A[sub - 1].first == key){
		cout << "节点存在, 可以删除！" << endl;
		//change the left smallest key to the current key and delete it
		BNode* deletedNode = change(searchedNode, sub);
		if (deletedNode->parent == NULL){//if the deleted Node is root
			return root;
		}
		if (deletedNode->A.size() >= M / 2 + M % 2 - 1){//if there are enough nodes
			return root;
		}
		int parentSub = nodeSearch(deletedNode->parent, key);
		BNode* parent = deletedNode->parent;
		BNode* lbrother;
		if (parentSub > 2){
			lbrother = parent->A[parentSub - 2].second;
		}
		else if (parentSub == 1){
			lbrother = parent->A0;
		}
		else{
			lbrother = NULL;
		}
		BNode*rbrother = (parentSub < parent->A.size()) ? parent->A[parentSub].second : NULL;
		if (lbrother == NULL){
			if (rbrother->A.size() >= M / 2 + M % 2){
				deletedNode->A.insert(deletedNode->A.end(), SECTION(parent->A[parentSub].first, rbrother->A0));
				parent->A[parentSub].first = rbrother->A.front().first;
				rbrother->A0 = rbrother->A.front().second;
				rbrother->A.erase(rbrother->A.begin());
				return root;
			}
			rbrother->A.push_back(SECTION(parent->A[parentSub]));
			parent->A.erase(parent->A.begin() + parentSub);
			vector<SECTION>::iterator it = deletedNode->A.end();
			for (int i = 0; i < deletedNode->A.size(); i++){
				rbrother->A.insert(rbrother->A.begin(), *it--);
			}
			if (parent == root &&parent->A.size() == 0){
				rbrother->parent = NULL;
				return rbrother;
			}
			else
				return root;
		}
		if (lbrother->A.size() >= M / 2 + M % 2){
			//delete Node get parent key and brother pointer
			deletedNode->A.insert(deletedNode->A.begin(), SECTION(parent->A[parentSub - 1].first, deletedNode->A0));
			deletedNode->A0 = lbrother->A.back().second;
			//parent get lbrother key
			parent->A[parentSub - 1].first = lbrother->A.back().first;
			//delete lbrother key
			lbrother->A.erase(lbrother->A.end());
			return root;
		}
		lbrother->A.push_back(SECTION(parent->A[parentSub - 1].first, deletedNode->A0));
		parent->A.erase(parent->A.begin() + parentSub - 1);
		vector<SECTION>::iterator it = deletedNode->A.begin();
		for (int i = 0; i < deletedNode->A.size(); i++){
			lbrother->A.push_back(*it);
		}
		if (parent == root &&parent->A.size() == 0){
			lbrother->parent = NULL;
			return lbrother;
		}
		else{
			return root;
		}
	}
	else{
		cout << "节点不存在！" << endl;
		return root;
	}
}

BNode* change(BNode* current, int sub){
	BNode *tempRoot = current;
	int currentKey = tempRoot->A[sub - 1].first;
	int childSub = sub - 1;
	if (tempRoot->A[sub - 1].second != NULL){//if has child to replace
		childSub = 0;
		tempRoot = tempRoot->A[sub - 1].second;
		while (tempRoot->A0 != NULL){//find the smallest rchild
			tempRoot = tempRoot->A0;
		}
	}
	current->A[sub - 1].first = tempRoot->A[childSub].first;
	if (tempRoot->A.size() == 1)
		tempRoot->A.clear();
	else
		tempRoot->A.erase(tempRoot->A.begin() + childSub);//delete the key
	return tempRoot;
}

void display(BNode *root){
	if (root == NULL)
		return;
	BNode *tempRoot = root;
	for (int i = 0; i < tempRoot->A.size(); i++){
		cout << tempRoot->A[i].first << " ";
	}
	cout << endl;
	display(tempRoot->A0);
	for (int j = 0; j < tempRoot->A.size(); j++){
		display(tempRoot->A[j].second);
	}

}