#include <iostream>
#include <cstdlib>

// poor practice
using namespace std;

struct node
{
	int key_value;
	node *p_left;
	node *p_right;
};

void print_left_subtree_ascending(node*);
void print_current_node_value(node*);
void print_right_subtree_ascending(node*);
void print_left_subtree_descending(node*);
void print_right_subtree_descending(node*);

node* insert(node *p_tree, int key)
{
	// base case, we have reached an empty tree and need to insert our new node here
	if ( p_tree == NULL )
	{
		node* p_new_tree = new node;
		p_new_tree->p_left = NULL;
		p_new_tree->p_right = NULL;
		p_new_tree->key_value = key;
		return p_new_tree;
	}
	// decide whether to insert into the left subtree or the right subtree
	// depending on the value of the node
	if( key < p_tree->key_value )
	{
		p_tree->p_left = insert( p_tree->p_left, key );
	}
	else
	{
		// Insert right is exactly symmetric to insert left
		p_tree->p_right = insert( p_tree->p_right, key );
	}
	return p_tree;
}

node *search(node *p_tree, int key)
{
	// if we reach the empty tree, it's not here
	if ( p_tree == NULL )
	{
		return NULL;
	}
	// if we find the key, we're done!
	else if ( key == p_tree->key_value )
	{
		return p_tree;
	}
	// otherwise, try looking in either the left or the right sub-tree
	else if ( key < p_tree->key_value )
	{
		return search( p_tree->p_left, key );
	}
	else
	{
		return search( p_tree->p_right, key );
	}
}

void destroy_tree(node *p_tree)
{
	if ( p_tree != NULL )
	{
		destroy_tree( p_tree->p_left );
		destroy_tree( p_tree->p_right );
		cout << "Deleting node: " << p_tree->key_value;
		delete p_tree;
 	}
}

node* remove_max_node(node* p_tree, node* p_max_node)
{
	if ( p_tree == NULL )
	{
		return NULL;
	}
	// found the node, now replace it
	if ( p_tree == p_max_node )
	{
		// If p_max_node has no left sub-tree, then we will just return NULL from this
		// branch, which will result in p_max_node being replaced with an empty tree,
		// which is what we want.
		return p_max_node->p_left;
	}
	// each recursive call replaces the right sub-tree tree with a 
	// new sub-tree that does not contain p_max_node.
	p_tree->p_right = remove_max_node( p_tree->p_right, p_max_node );
	return p_tree;
}

// keep going right until p_tree->p_right == NULL
node* find_max(node* p_tree)
{
	if ( p_tree == NULL )
	{
		return NULL;
	}
	if ( p_tree->p_right == NULL )
	{
		return p_tree;
	}
	return find_max( p_tree->p_right );
}

node* remove (node* p_tree, int key)
{
	if ( p_tree == NULL )
	{
		return NULL;
	}
	if ( p_tree->key_value == key )
	{
		// the first two cases handle having zero or one child node
		if ( p_tree->p_left == NULL )
		{
			node* p_right_subtree = p_tree->p_right;
			delete p_tree;
			// this might return NULL if there are zero child nodes
			return p_right_subtree;
		}
		if ( p_tree->p_right == NULL )
		{
			node* p_left_subtree = p_tree->p_left;
			delete p_tree;
			return p_left_subtree;
		}
		node* p_max_node = find_max( p_tree->p_left );
		// since p_max_node came from the left sub-tree, we need to
		// remove it from that sub-tree before re-linking that sub-tree
		// back into the rest of the tree
		p_max_node->p_left = remove_max_node( p_tree->p_left, p_max_node );
		p_max_node->p_right = p_tree->p_right;
		delete p_tree;
		return p_max_node;
	}
	else if ( key < p_tree->key_value )
	{
		p_tree->p_left = remove( p_tree->p_left, key );
	}
	else
	{
		p_tree->p_right = remove( p_tree->p_right, key );
	}
	return p_tree;
}

void swap( int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
}

// print tree in sorted order
void print_subtree_ascending(node* p_tree)
{
	if ( p_tree != NULL )
	{
		print_left_subtree_ascending(p_tree);
		print_current_node_value(p_tree);
		print_right_subtree_ascending(p_tree);	
	}
}

void print_left_subtree_ascending(node* p_tree)
{
	print_subtree_ascending(p_tree->p_left);
}

void print_current_node_value(node* p_tree)
{
	cout << p_tree->key_value << "  ";
}

void print_right_subtree_ascending(node* p_tree)
{
	print_subtree_ascending(p_tree->p_right);
}

// print tree in reverse sorted order
void print_subtree_descending(node* p_tree)
{
	if ( p_tree != NULL)
	{
		print_right_subtree_descending(p_tree);
		print_current_node_value(p_tree);
		print_left_subtree_descending(p_tree);
	}
}

void print_right_subtree_descending(node* p_tree)
{
	print_subtree_descending(p_tree->p_right);
}

void print_left_subtree_descending(node* p_tree)
{
	print_subtree_descending(p_tree->p_left);
}

int main ()
{
    int choice = 0;
    int node_value = 0;
    node *p_root = NULL;

    while (true)
    {
		cout << "What would you like to do?\n\n"
			"1. Add a node\n"
			"2. Remove a node\n"
			"3. Destroy the tree\n"
			"4. Check if a node is in the tree\n"
			"5. Print the tree in ascending sorted order\n"
			"6. Print the tree in descending sorted order\n"
			"7. Exit the program\n";
		cin >> choice;
		switch (choice)
		{
	    	case 1:
			cout << "Please enter a value to insert: ";
			cin >> node_value;
			p_root = insert( p_root, node_value );
			cout << "\nAdded value " << node_value << " to tree\n\n";
			break;
	    	case 2:
			cout << "Please enter a value to remove: ";
			cin >> node_value;
			p_root = remove( p_root, node_value );
			cout << "\nRemoved value " << node_value << " from tree\n\n";
			break;
	    	case 3:
			destroy_tree( p_root );
			p_root = NULL;
			cout << "\nDestroyed tree\n\n";
			break;
	    	case 4:
	    	// add an extra scope in order to declare p_search_node
	    	// without leaking it beyond the case statement
	    	{
				cout << "Please enter a value to find: ";
				cin >> node_value;
				node* p_search_node = search( p_root, node_value );
				if ( p_search_node != NULL )
				{
		    		cout << "\nFound node\n\n";
				}
				else
				{
		    		cout << "\nNode not found\n\n";
				}
	    	}
	    	break;
			case 5:
			{
				cout << "\n";
				if ( p_root == NULL)
				{
					cout << "Tree is empty";
				}
				print_subtree_ascending(p_root);
				cout << "\n\n";
			}
			break;
			case 6:
			{
				cout << "\n";
				if ( p_root == NULL)
				{
					cout << "Tree is empty";
				}
				print_subtree_descending(p_root);
				cout << "\n\n";
			}
			break;
	    	case 7:
			return 0;
	    	default:
			cout << "Bad input...\n\n";
		}
    }
}
