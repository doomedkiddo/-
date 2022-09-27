#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<sstream>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(): val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode *right): val(x), left(left), right(right){}
};

class BinaryTree
{
public:
	TreeNode* root;		
	BinaryTree(vector<string> nodes)
	{

		int i = 0;
		int n = nodes.size();
		if (nodes[0] == "null" && n == 1)
		{
			root = nullptr;
			return;
		}

		stringstream ss;
		ss << nodes[0];
		int val;
		ss >> val;
		root = new TreeNode(val);
		i++;

		queue<TreeNode*> que;

		que.push(root);

		while (!que.empty() && i < n)
		{

			TreeNode* node = que.front();
			que.pop();

			for (int j = 1; j <= 2 && i < n; ++j, ++i)
			{
		
				if (nodes[i] == "null" && j == 1)
				{
					node->left = nullptr;
				}
				else if (nodes[i] == "null" && j == 2)
				{
					node->right = nullptr;
				}
				
				else if(j == 1)
				{
					node->left = new TreeNode(stoi(nodes[i]));
					que.push(node->left);
				}
				else
				{
					node->right = new TreeNode(stoi(nodes[i]));
					que.push(node->right);
				}
			}
		}
	}

  vector<vector<int>> pathSumEntry(TreeNode* r,int K,int dept){
        vector<vector<int>> result;
        vector<int> currentResult;
        pathSum(r,K,result, currentResult, dept);
        return result;
     }
  void pathSum(TreeNode *r,int K,vector<vector<int>> &result, vector<int> &currentResult, int dept) {
         if(r==nullptr)return;
         currentResult.push_back(r->val);
         if(!r->left&&!r->right&&K==r->val+dept) {
             result.push_back(currentResult);
         }else {
             pathSum(r->left,K-r->val-dept,result, currentResult,dept+1);
             pathSum(r->right,K-r->val-dept,result, currentResult,dept+1);
         }
         currentResult.pop_back();
     }
  void printTree(TreeNode *r,int K,int dept) {
         if(r==nullptr)return;
         vector<vector<int>> result = pathSumEntry(r, K, dept);
         for (int cnt = 0; cnt < result.size(); cnt ++) {
            for(int j = 0; j < result[cnt].size(); j ++) {
                cout << result[cnt][j] << " ";
            }
            cout << endl;
         }
         printTree(r->left,K,dept+1);
         printTree(r->right,K,dept+1);
     }
  void printallpaths(int K, int dept) {
    printTree(root, K, dept);
  }
};

int main(int agrc, char** argv)
{
	int n = 0, K;
  string str;
  cin >> K;
  cin.ignore();
	vector<string> nodes;
	getline(cin, str);
  int size = str.size();
  int j = 0;
  for (int i = 0; i < size; i++) {
    if (str[i] == ' '){
      nodes.push_back(str.substr(j, i - j));
      j = i+1;
  }}
  nodes.push_back(str.substr(j, size - j));

	BinaryTree* bt = new BinaryTree(nodes);
  bt->printallpaths(K, 0);



	return 0;
}


