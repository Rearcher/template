#include "utility"
/* struct Binary_node starts from here */
template <class Entry>
struct Binary_node
{
	Entry data;
	Binary_node<Entry> *left;
	Binary_node<Entry> *right;

	Binary_node();
	Binary_node(const Entry &x);
};

template <class Entry>
Binary_node<Entry>::Binary_node()
{
	left = right = NULL;
}

template <class Entry>
Binary_node<Entry>::Binary_node(const Entry &x)
{
	data = x;
	left = right = NULL;
}

/* class Binary_tree starts from here*/
template <class Entry>
class Binary_tree
{
public:
	Binary_tree();
	bool empty()const;

	void preorder(void (*visit)(const Entry &));
	void recursive_preorder(Binary_tree<Entry> *sub_root, void (*visit)(const Entry &));
	void inorder(void (*visit)(const Entry &));
	void recursive_inorder(Binary_tree<Entry> *sub_root, void (*visit)(const Entry &));
	void postorder(void (*visit)(const Entry &));
	void recursive_postorder(Binary_tree<Entry> *sub_root, void (*visit)(const Entry &));
	
	int size()const;
	void clear();
	int height()const;
	void insert(const Entry &);

	Binary_tree(const Binary_tree<Entry> &original);
	Binary_tree & operator = (const Binary_tree<Entry> &original);
	~Binary_tree();
protected:
	Binary_node<Entry> *root;
};

template <class Enrty>
Binary_tree<Entry>::Binary_tree()
{
	root = NULL;
}

template <class Entry>
bool Binary_tree<Entry>::empty()const
{
	return root == NULL;
}

template <class Entry>
void Binary_tree<Entry>::inorder(void (*visit)(Entry &))
{
	recursive_inorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &))
{
	if(sub_root != NULL)
	{
		recursive_inorder(sub_root->left, visit);
		(*visit)(sub_root->data);
		recursive_inorder(sub_root->right, visit);
	}
}


template <class Entry>
void Binary_tree<Entry>::preorder(void (*visit)(Entry &))
{
	recursive_inorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &))
{
	if(sub_root != NULL)
	{
		(*visit)(sub_root->data);
		recursive_inorder(sub_root->left, visit);
		recursive_inorder(sub_root->right, visit);
	}
}


template <class Entry>
void Binary_tree<Entry>::postorder(void (*visit)(Entry &))
{
	recursive_inorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &))
{
	if(sub_root != NULL)
	{
		recursive_inorder(sub_root->left, visit);
		recursive_inorder(sub_root->right, visit);
		(*visit)(sub_root->data);
	}
}


/* Search_tree starts from here */
template <class Record>
class Search_tree : public Binary_tree<Record>
{
public:
	Error_code insert(const Record &new_data);
	Error_code remove(const Record &old_data);
	Error_code tree_search(Record &target)const;
	Error_code *search_for_node(Binary_node<Record> *sub_root, const Record &target)const;
	Error_code search_and_insert(Binary_node<Record> *sub_root, const Record &new_data);
private:
};

template <class Record>
Error_code *Search_tree<Record>::search_for_node(Binary_node<Record>*sub_root, const Record &target)const
{
	while(sub_root != NULL && sub_root->data != target)
	{
		if(sub_root->data < target) sub_root = sub_root->right;
		else sub_root = sub_root->left;
	}
	return sub_root;
}

template <class Record>
Error_code Search_tree<Record>::tree_search(Record &target)const
{
	Error_code result = success;
	Binary_node<Record> *found = search_for_node(root, target);
	if(found == NULL)
		result = not_present;
	else
		target = found->data;
	return result;
}

template <class Record>
Error_code Search_tree<Record>::insert(const Record &new_data)
{
	return search_and_insert(root, new_data);
}

template <class Record>
Error_code Search_tree<Record>::search_and_insert(Binary_node<Record>* &sub_root, const Record &new_data)
{
	if(sub_root == NULL)
	{
		sub_root = new Binary_node<Record>(new_data);
		return success;
	}
	else if(new_data < sub_root->data)
		return search_and_insert(sub_root->left, new_data);
	else if(new_data > sub_root->data)
		return search_and_insert(sub_root->left, new_data);
	else return duplicat_error;
}

template <class Record>
Error_code Search_tree<Record>::remove_root(Binary_node<Record> *&sub_root)
{
	if(sub_root == NULL) return not_present;
	Binary_node<Record> *to_delete = sub_root;

	if(sub_root->right == NULL) sub_root = sub_root->left;
	else if(sub_root->left == NULL) sub_root = sub_root->rigtt;
	else
	{
		to_delete = sub_root->left;
		Binary_node<Record> *parent = sub_root;
		while(to_delete->right != NULL)
		{
			parent = to_delete;
			to_delete = to_delete->right;
		}
		sub_root->data = to_delete->data;
		if(parent == sub_root) sub_root->left = to_delete->left;
		else parent->right = sub_root->left;
	}
	delete to_delete;
	return success;
}

template <class Record>
Error_code Search_tree<Record>::search_and_destory(Binary_node<Record>*&sub_root, const Record &target)
{
	if(sub_root == NULL || sub_root->data == target)
		return remove_root(sub_root);
	else if(target < sub_root->data)
		return search_and_destory(sub_root->left, target);
	else
		return search_and_destory(sub_root->rigth, target);
}
		
template <class Record>
Error_code Search_tree<Record>::remove(const Record &target)
{
	return search_and_destory(root, target);
}


/* build search_tree starts from here */
template <class Record>
class Buildable_tree : public Search_tree<Record>
{
public:
	Error_code build_tree(const List<Record> &supply);
private;
};

template <class Record>
Error_code Buildable_tree<Record>::connect_trees(const List<Binary_node<Record> *> &last_node)
{
	Binary_node<Record> *high_node, *low_node;
	int high_level = last_node.size()-1, low_level;
	while(high_level > 2)
	{
		last_node.retrieve(high_level, high_node);
		if(high_node->right != NULL)
			high_level--;
		else
		{
			low_level = high_level;
			do{
				last_node.retrieve(--low_level, low_node);
			}while(low_node != NULL && low_node->data < high_node->data);
			high_node->right = low_node;
			high_level = low_level;
		}
	}
}

template <class Record>
Error_code Buildable_tree<Record>::find_root(List<Binary_node<Record>*> &last_node)
{
	Bianry_node<Record> *high_node;
	last_node.retrieve(last_node.size()-1, high_node);
	return high_node;
}

template <class Record>
Error_code Buildable_tree<Record>::build_insert(int count, const Record &new_data, List<Binary_node<Record>*> &last_node)
{
	int level;
	for(level = 1; count%2==0; level++)
		count /= 2;
	Binary_node<Record> *next_node = new Binary_node<Record>(new_data), *parent;
	last_node.retrieve(level-1, next_node->left);
	if(last_node.size() <= level)
		last_node.insert(level, next_node);
	else
		last_node.insert(level, next_node);
	if(last_node.retrieve(level+1, parent) == success && parent->right == NULL)
		parent->right = next_node;
}


template <class Record>
Error_code Buildable_tree<Record>::build_tree(const List<Record> &supply)
{
	Error_code ordered_data = success;
	int count = 0;
	Record x, last_x;
	List<Binary_node<Record>*> last_node;

	Binary_node<Record> *none = NULL;
	last_node.insert(0,none);
	while(supply.retrieve(count, x)==success)
	{
		if(count > 0 && x <= last_x)
		{
			ordered_data = fail;
			break;
		}
		build_insert(++count, x, last_node);
		last_x = x;
	}
	root = find_root(last_node);
	connect_trees(last_node);
	return ordered_data;
}
