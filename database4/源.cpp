#include<iostream>
#include<time.h>
#include<fstream>
#include <string>
#include<sstream>

using namespace std;

#define MSIZE (1024*1024)		//1M �ռ��ڴ�
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
	BNode* A0;			//��һ��ָ��
	BNode * parent;		//ָ���׽ڵ��ָ��
	vector<SECTION> A;	//��ֵһ��һ��������AΪ�ýṹ��һ������
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

//��������key�� ���ظ��ڵ�
BNode* insert(BNode* root, int key);

//���ҽڵ㣬����һ��pair�����汣��һ��ָ����ҵĽڵ���������������ڵ������±�
SECTION search(BNode* root, int key);

//��һ���ڵ��Ͻ������Բ��ң� ���ؼ�ֵλ�ڵ������±�
//���û���ҵ��򷵻�ǡ�ô��ڸ����ļ�ֵ���±�
int nodeSearch(BNode* current, int key);

//��һ���ڵ���ѳ������ڵ㣬����ֵΪ�����ڵ��һ���м��ֵ
pair<int, pair<BNode*, BNode*>> breakNode(BNode* current);

//ɾ����ֵ�� ���ظ��ڵ�
BNode* deleteKey(BNode *root, int key);

//�������˳��չʾ���ṹ
void display(BNode *root);

BNode* change(BNode* current, int sub);




//test
//#define MSIZE 1024		//1M �ռ��ڴ�
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
�����������
�������������ͷָ��
*/
int* createRandonIndex();

/*
���ɼ�¼�ļ����ļ��к�1000000����¼
��¼��ʽ��ǰ4byte��int�����ݣ���13byte���ַ�����filex��
*/
void createMyFile();

/*
�鲢����F
�������ļ���������
*/
void mergeSort();

pair<myfile*, pair<int, int>> merge(pair<myfile*, int> x, pair<myfile*, int> y, int resultSize);

/*
��ȡ�ļ�
�����������ȡ������
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
	cout << "���뽨��������Ŀ��" << endl;
	int n;
	cin >> n;
	root = loadData(root, n);
	while (1){
		int opt;
		cout << "����ģʽ��0:���ң� 1ɾ��, 2����" << endl;
		cin >> opt;
		if (opt == 0){
			cout << "�����������" << endl;
			int key;
			cin >> key;
			SECTION result = search(root, key);
			BNode* searchedNode = result.second;
			int sub = result.first;
			if (sub >= 1 && searchedNode->A[sub - 1].first == key){
				cout << "���ݴ��ڣ�" << endl;
			}
			else{
				cout << "���ݲ����ڣ�" << endl;
			}
		}
		else if (opt == 1){
			cout << "��ʼɾ���������ɾ�����ݣ�" << endl;
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
	cout << "������ɣ�" << endl;
	cout << "������������" << endl;
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
		cout << "�ļ���ʧ�ܣ�" << endl;
		cout << "�����ļ�" << FILENAME << ".txt" << endl;
		ofstream fout(FILENAME);
		if (fout) { // ��������ɹ�
			cout << "�ļ������ɹ���" << endl;
			int *index = createRandonIndex();
			string temp = "F";
			for (int i = 0; i < dataSize; i++){
				string temp1 = temp +  to_string(i);
				fout << index[i] << temp1 << endl;
			}
			cout << "�ļ�������ϣ�" << endl;
			fout.close();  // ִ���������ر��ļ����
		}
	}
	else{
		cout << "�ļ����ڣ�����ֱ�Ӷ�ȡ..." << endl;
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
		//step1:��С���������-----------------------------------------------
		for (int i = 0; i < mergeDimension; i++){
			pair<myfile*, int> p = readFile(FILENAME, i*maxBlock, maxBlock);
			std::qsort(p.first, p.second, sizeof(myfile), myCompare);
			for (int j = 0; j < p.second; j++){
				fout << p.first[j].A << "	" << p.first[j].B << endl;
			}
		}
	}
	fout.close();
	//step2:���������鲢����---------------------------------------------
	//int count = mergeDimension/2;//��Ҫ�鲢�Ŀ���
	int size = maxBlock;//��ǰ��Ĵ�С
	//left = mergeDimension % 2;//�Ƿ���ʣ�ࣨ�����鲢��
	left = 0;
	int count = mergeDimension;
	string name = "iteration";
	int nameSuffix = 0;
	while (count>=1){
		//���ļ��е��������ݿ���й鲢���򣬲�����һ�������ļ�
		string temp1 = name + to_string(nameSuffix++)+".txt";
		string temp2 = name + to_string(nameSuffix) + ".txt";
		ofstream fout2(temp2, ios::ios_base::in);
		int temp = count + left;
		count = temp / 2;
		left = temp % 2;
		if (fout2)
			continue;
		fout2.open(temp2);
		//��n�����������Ҫcount = n/2��������������left��
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
					//����p2��ָ��
					p2.first = &p2.first[p3.second.second];
					p2.second = p2.second - p3.second.second;
					if (BUFFER*(times1 + 1) < maxBlock*pow(2, nameSuffix - 1))
						p1 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * 2 * i + BUFFER*times1, BUFFER);
					else{
						p1 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * 2 * i + BUFFER*times1, maxBlock*pow(2, nameSuffix - 1) - BUFFER*times1);
					}
					if (p1.second == -1){
						//������һ���Ѿ�������ɣ���һ����ʣ������ֱ��д���ڴ�
						writeBack(&fout2, make_pair(p2.first, p2.second));
						if (BUFFER*times2 < maxBlock*pow(2, nameSuffix - 1)){//�Ƿ���ʣ��
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
					//����p1ָ��
					p1.first = &p1.first[p3.second.first];
					p1.second = p1.second - p3.second.first;
					if (BUFFER*(times2 + 1) < maxBlock*pow(2, nameSuffix - 1))
						p2 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * (2 * i + 1) + BUFFER*times2, BUFFER);
					else {
						p2 = readFile(temp1, pow(2, nameSuffix - 1)*maxBlock * (2 * i + 1) + BUFFER*times2, maxBlock*pow(2, nameSuffix - 1) - BUFFER*times2);
					}
					if (p2.second == -1){
						//������һ���Ѿ�������ɣ���һ����ʣ������ֱ��д���ڴ�
						writeBack(&fout2, make_pair(p1.first, p1.second));
						//�ж��Ƿ���ʣ��
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
		if (count!=0&&left){//��ʣ������д��
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
	myfile *data = new myfile[size];//���������
	std::stringstream ss;//�ַ���������ת������
	//��ȡ�ļ�------------------------------------------------------------------
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
		//�������һ��������Ѿ�Ϊ��
		if (pointer.first >= x.second || pointer.second >= y.second){
			break;
		}
		//�����������Զ���Ϊ��
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
		cout << "�ڵ��Ѿ����ڣ�" << endl;
	}
	else{
		//insert directly
		//����ָ��
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
		cout << "��Ϊ�գ�" << endl;
	BNode *tempNode = root;
	SECTION searched = search(tempNode, key);
	BNode* searchedNode = searched.second;
	int sub = searched.first;
	if (sub != 0 && sub <= searchedNode->A.size() && searchedNode->A[sub - 1].first == key){
		cout << "�ڵ����, ����ɾ����" << endl;
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
		cout << "�ڵ㲻���ڣ�" << endl;
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