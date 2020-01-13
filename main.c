//
// Created by jsb on 06.12.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


typedef struct nodes
{
    int data;
    struct nodes *left;
    struct nodes *right;

}node_t;


/* newNode() allocates a new node with the given data and NULL left and
   right pointers. */
node_t* newNode(int data)
{
    // Allocate memory for new node
    node_t* node = (node_t*)malloc(sizeof(node_t));

    // Assign data to this node
    node->data = data;


    // Initialize left and right children as NULL
    node->left = NULL;
    node->right = NULL;


    return(node);
}

// A utility function to check if a tree node
// has both left and right children
int hasBothChild(node_t* temp)
{
    return temp && temp->left && temp->right;
}

//inserting new node
int insert(node_t* root, node_t* newNode){
    //check if there is a tree root
    if(root == NULL) return -1;

    //assign temporary root
    node_t* currentNode = root;
    while(1){
        //eight side?
        if(newNode->data > currentNode->data){
            if(currentNode->right == NULL){
                printf("Added %d on the right of %d\n",newNode->data,currentNode->data);
                currentNode->right = newNode;
                return 0;
            }else{
                //dig deeper
                currentNode = currentNode->right;
            }
            //left side
        }else if(newNode->data < currentNode->data){
            if(currentNode->left == NULL){
                printf("Added %d on the left of %d\n",newNode->data,currentNode->data);
                currentNode->left = newNode;
                return 0;
            }else{
                //dig deeper
                currentNode = currentNode->left;
            }
        }
    }

    //element already exists, nothing to do
    return 0;
}

int lookup(node_t* root,node_t** found, node_t** parent, int data){
    int retVal=0;
    //check if there is a tree root
    if(root == NULL) return -1;
    node_t* currentNode  = root;

    while(1){
        //check value
        if(data == currentNode->data){
            *found=currentNode;
            return 0;
        }
        //right side?
        if(data > currentNode->data){
            if(currentNode->right == NULL){
                return -1;
            }else{
                //dig deeper
               *parent=currentNode;
                currentNode = currentNode->right;
            }
            //left side
        }else if(data < currentNode->data){
            if(currentNode->left == NULL){
                return -1;
            }else{
                //dig deeper
                *parent=currentNode;
                currentNode = currentNode->left;
            }
        }
    }
    return -1;
}


int traverse(node_t* currentNode){

    if(currentNode == NULL) return -1;
    node_t* nextNode = currentNode->left;
    traverse(nextNode);
    printf("%d\n", currentNode->data);
    nextNode = currentNode->right;
    traverse(nextNode);

    return 0;
}
void clear_parent_entry( node_t**parent_p, node_t** found_p){
    if((*parent_p)->right== (*found_p)){
        (*parent_p)->right=NULL;
    }else{
        (*parent_p)->left=NULL;
    }
    free((*found_p));
}


void bypass(node_t** found_p,node_t** parent_p){
    if((*found_p)==(*parent_p)->right)
        (*parent_p)->right=(*found_p)->right;
    else
        (*parent_p)->left=(*found_p)->left?(*found_p)->left:(*found_p)->right;
    free((*found_p));
}

void replace_with_successor(node_t** found_p,node_t** parent_p){
    node_t* leftMost = (*found_p)->right;
    node_t* leftMostParent = (*found_p);
    while (leftMost->left || leftMost->right) {
        leftMostParent = leftMost;
        if(leftMost->left!=NULL){
            leftMost = leftMost->left;
        }else{
            leftMost = leftMost->right;
        }
    }
    /*found leftmost*/
    /*it is a leaf*/

    /*switch node values*/
    if ((*found_p) == (*parent_p)->right)
        (*parent_p)->right->data = leftMost->data;
    else
        (*parent_p)->left->data = leftMost->data;

    /*clear parent entry*/
    clear_parent_entry(&leftMostParent, &leftMost);
    free(leftMost);

}

int remove_val(node_t* root, int data){
    /*find node and it's parent*/
    int ret=0;

    node_t* found;
    node_t* parent;
    lookup(root,&found, &parent, data);
    if(ret!=0) return -1;

    /*Option 1 is a leaf*/
    if(!(found->right || found->left)){
        clear_parent_entry( &parent, &found);
        printf("Deleted a leaf\n");
        return 0;
    }

    /*Option 2 two children*/
    else if((found->right && found->left)){
        replace_with_successor(&found, &parent);
        printf("Deleted a node with two children\n");

        return 0;
    }else{
    /*Option 3 one child*/
        bypass(&found, &parent);
        printf("Deleted a node with one child\n");
        return 0;
    }
    return 0;
}


int create_and_insert_node( GPtrArray* nodeArray, int data){
    int ret=0;

    node_t*  temp=newNode(data);
    g_ptr_array_add(nodeArray,temp);


    if(nodeArray->len>1) {

        ret = insert(g_ptr_array_index(nodeArray, 0),
                g_ptr_array_index(nodeArray, (nodeArray->len)-1 ));
    }
    return ret;
}


int main(void) {
    int ret=0;
    /*this can be a vector-like or queue structure*/
    GPtrArray* tree=g_ptr_array_new();

    /*create root*/


    create_and_insert_node(tree,2);

    /*create some nodes*/
    create_and_insert_node(tree,3);
    create_and_insert_node(tree,10);
    create_and_insert_node(tree,4);
    create_and_insert_node(tree,13);
    create_and_insert_node(tree,7);
    create_and_insert_node(tree,6);
    create_and_insert_node(tree,9);

    node_t *root =g_ptr_array_index(tree, 0);

    /*print existing nodes*/
    traverse(root);

    /*test lookup*/
    node_t* found;
    node_t* parent;
    ret=lookup(root,&found, &parent, 7);
    if(ret==0){
        printf("Node found!\n");
        printf("Found val: %d\n",found->data);
        printf("Parent val: %d\n",parent->data);
    }



    /*remove*/
    remove_val( root, 10);
    /*traverse again*/
    traverse(root);

    printf("Done!\n");
    /*memory leaking a little bit. Might free ptr resources earlier*/
    g_ptr_array_free (tree,TRUE);
    return 0;
}