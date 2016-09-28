#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
#include "ware.h"
#include "list.h"
#include "shelf.h"




_node *create_node(){
	_node *base = (struct node*)malloc(sizeof(struct node));
	base -> item = NULL;
	base -> left = NULL;
	base -> right = NULL; 
	return base; 
}

tree_t *tree_new(){
	tree_t *root = (struct tree*)malloc(sizeof(struct tree));
	root->head = NULL;
	return root; 
}


char *return_Node_name(_node*name){
	return get_name(name -> item); 
}

_node*return_node_head(tree_t *root){
	return root -> head; 
}

ware *return_ware(tree_t *root){
	return root -> head -> item; 
}
ware *returnNodeware(_node*wareName){
	return wareName -> item; 
}

void print(_node*d){
	print(d -> left);
	printf("%s", return_Node_name(d));
	print(d-> right); 
}


bool isShelfexist(_node *root, shelf *shelfName){
	if(root ==NULL)
		return false;
	if(strcmp(get_name(root->item), get_shelf(shelfName)) > 0){
		_node *current = root;
		root = current -> left; 
		while(root !=NULL){
			if(isexist(return_list(returnNodeware(root)) ,shelfName)){
				return true;
			}
			root = current ->left; 
 		}
		return false; 
	}
	if(strcmp(get_name(root->item), get_shelf(shelfName)) < 0){
		_node *current = root;
		root = current -> right;  
		while(root!=NULL){
			if(isexist(return_list(returnNodeware(root)), shelfName)){
				return true; 
			}
			root = current -> right; 
		}
		return false; 
	}
	else {
		return false; 
	}
}





int tree_size(_node* root){
	if(root == NULL){
		return 0;}
	else{
		return (tree_size(root-> left) + 1 + tree_size(root->right));
	}
}




char*get_name_node(tree_t *root){
	if(root -> head == NULL){
		return NULL;}
	else {
		return get_name(root->head ->item);
	}
	return NULL; 
}

char *getNodename(_node * leaf){
  if(leaf == NULL){
    return NULL; 
  }
  else {return get_name(leaf -> item); 
}
  return NULL; 
}



_node*find_node(_node *root, char*Itemname){
	if (root== NULL)
		return NULL;
  
	else if(root!= NULL){
		if(strcmp(get_name(root->item), Itemname)== 0){
			return root;
		}
		else if(strcmp(get_name(root-> item), Itemname) > 0){
			_node *temp = root;
			root = temp -> left; 
			return find_node(root, Itemname);
		}
		else{
			_node *temp = root;
			root = temp -> right; 
			return find_node(root, Itemname);
		}
	}
	else{
		return NULL; 
	}

}



int tree_depth(_node *leaf){
	if(leaf == NULL){
		return 0;
	}
	else {
		int lDepth = tree_depth(leaf -> left);
		int rDepth = tree_depth(leaf -> right);
		
		if(lDepth > rDepth){
			return (lDepth +1);} 
		else{
			return(rDepth +1);}
	}
	return 0; 
};



void insertNode(tree_t *root, char*Itemname){ 
	if(root -> head ==NULL){
		root -> head = create_node(); 
		root->head -> item = create_ware(); 
		root-> head-> left = NULL;
		root -> head -> right = NULL; 
	}
	else if(strcmp(get_name(root-> head-> item), Itemname)== 0){
		
		printf("the item already existed");
		shelf * newShelf = new_shelf();
		list_append(return_list(return_ware(root)), newShelf);
	}
	
	else if(strcmp(get_name(root -> head-> item), Itemname) > 0){
		_node*temp = root -> head-> left;
        root -> head = temp; 
		insertNode(root, Itemname);
		free(temp); 
	}
	
	else if(strcmp(get_name(root ->head ->item), Itemname) <0){
		_node *temp = root -> head->right; 
		root -> head = temp; 
		insertNode(root, Itemname);
		free(temp); 
	}

}





_node * min_Value(_node* root){
	if(root == NULL){
		return NULL; 
	}
	else {
		_node *current = root ; 
		root= current -> right; 
	
		while (root!=NULL){
			root= root->left;}
		return root;
	}
}



void remove_N(tree_t *root, char*Itemname){
	if(root -> head == NULL) {
		printf("the root is empty\n");
		return;
	}
	else if(strcmp(get_name(root ->head -> item), Itemname) > 0){
		_node *temp = root -> head->left;
		root -> head  = temp; 
		remove_N(root, Itemname);
	}
	else if(strcmp(get_name(root ->head -> item), Itemname) < 0){
		_node *temp = root -> head-> right; 
		root -> head  = temp; 
		remove_N(root, Itemname);}

	else{
		// delete root and the root has no left or right child
    
		_node *temp = find_node(root-> head, Itemname);
		
		if(root -> head == temp && temp !=NULL && root -> head -> left == NULL && root -> head-> right == NULL){
			free(root);
			root = NULL; 
		}
		// delete root when the root has only right child
		else if(root -> head == temp && temp !=NULL && root -> head -> left == NULL && root -> head -> right != NULL){
			_node *var  = root-> head->right;
			root -> head = var;   
			free(var);
	}
		// delete root when the root has  only left child
		else if((root -> head== temp) && temp !=NULL&& root -> head -> left != NULL && root -> head -> right == NULL){
			_node *var = root-> head-> left;
			root -> head = var; 
			free(var);
		}
		// delte root when the root has two child
		else{
			_node *min = min_Value(root->head);
			root -> head = min; 
			remove_N(root, return_Node_name(min));
		}
	
		}
	}



char* dump_tree(_node *leaf, char *arry[], int *p_t){
  int size = tree_size(leaf);
  while(*p_t < size){
    if(leaf != NULL){
      dump_tree(leaf-> left, arry, p_t);
      arry[*p_t] = return_Node_name(leaf);
      *p_t += 1; 
      dump_tree(leaf -> right, arry, p_t);
    }
    else {
		printf("There is no item to print");
		return NULL; 
    }
  } 
}


void print_p(_node*Node_name, char *ItemName){
	
	if(strcmp(return_Node_name(find_node(Node_name, ItemName)), return_Node_name(Node_name)) ==0){
		printf("%s\n", get_name(returnNodeware(Node_name)));
		printf("%s\n", get_des(returnNodeware(Node_name)));
		printf("%d\n", get_price(returnNodeware(Node_name)));
		printf("%s\n", get_shelf(return_shelf(return_list((returnNodeware(Node_name))))));
		printf("%d\n", get_quantity(return_shelf(return_list((returnNodeware(Node_name)))))); 
	}
	else{
		printf("The item you are looking is not on database");
		return; 
	}
	}

void printTree(tree_t*root){
	int i = 0 , j = 1, c;
    c = 0;
	int size = tree_size(root-> head); 
    char* empty[size]; 

	char *hello = (char*)malloc(10*sizeof(char)); 
	printf("Do you wannt to see printed information?\n");
	printf("%s\n", "Yes");
	printf("%s\n", "No");
	
	scanf("%s", hello);
	if(strcmp(hello, "Yes") ==0){	
	
	loop: 
		for(i = c, j = 0; i < size; i++, ++j){
		    c++;
			printf("%d. %s\n", j, dump_tree(root-> head, empty, &i));
			if(j == 20)
				goto nextstep;
		}
	 nextstep:
		printf("do you wann print more?\n");
		scanf("%s", hello);
		if(strcmp(hello, "Yes") ==0){
			goto loop;
		}
		else{
		 
				
		}
}

	free(hello); 
	
}

