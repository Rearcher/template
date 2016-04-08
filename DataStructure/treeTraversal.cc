#include <iostream>
#include <vector>
#include <stack>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

std::vector<int> preorder(TreeNode *root) {
	if (root == nullptr) return std::vector<int>();

	std::vector<int> res;
	std::stack<TreeNode *> s;
	s.push(root);
	
	while (!s.empty()) {
		TreeNode *tmpNode = s.top();
		s.pop();
		
		if (tmpNode->right) s.push(tmpNode->right);
		if (tmpNode->left) s.push(tmpNode->left);

		res.push_back(tmpNode->val);
	}

	return res;
};

std::vector<int> inorder(TreeNode *root) {
	if (root == nullptr) return std::vector<int>();

	std::vector<int> res;
	TreeNode *curNode = root;
	std::stack<TreeNode *> s;

	while (curNode || !s.empty()) {
		if (curNode) {
			s.push(curNode);
			curNode = curNode->left;
		} else {
			TreeNode *tmpNode = s.top();
			s.pop();
			
			res.push_back(tmpNode->val);
			curNode = tmpNode->right;
		}
	}

	return res;
}

std::vector<int> postorder(TreeNode *root) {
	if (root == nullptr) return std::vector<int>();

	std::vector<int> res;
	TreeNode *curNode = root, *prevNode = nullptr;
	std::stack<TreeNode *> s;

	while (curNode || !s.empty()) {
		if (curNode) {
			s.push(curNode);
			curNode = curNode->left;
		} else {
			TreeNode *tmpNode = s.top();
			if (tmpNode->right && prevNode != tmpNode->right) {
				curNode = tmpNode->right;
			} else {
				res.push_back(tmpNode->val);
				prevNode = tmpNode;
				s.pop();
			}
		}
	}

	return res;
};

void print(std::vector<int> &a) {
	for (auto i : a)
		std::cout << i << " ";
	std::cout << "\n";
}

int main() {
	TreeNode *root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(5);
	root->right->left = new TreeNode(6);
	root->right->right = new TreeNode(7);

//	std::vector<int> preorderSeq = preorder(root);
//	std::vector<int> inorderSeq = inorder(root);
	std::vector<int> postorderSeq = postorder(root);

//	print(preorderSeq);
//	print(inorderSeq);
	print(postorderSeq);
}
