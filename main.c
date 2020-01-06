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

node_t* lookup(node_t* root, int data){
    int retVal=0;
    //check if there is a tree root
    if(root == NULL) return -1;
    node_t* currentNode =  root;

    while(1){
        //check value
        if(data == currentNode->data){
            return currentNode;
        }
        //right side?
        if(data > currentNode->data){
            if(currentNode->right == NULL){
                return -1;
            }else{
                //dig deeper
                currentNode = currentNode->right;
            }
            //left side
        }else if(data < currentNode->data){
            if(currentNode->left == NULL){
                return -1;
            }else{
                //dig deeper
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
int remove_val(node_t* root, node_t* newNode){
    /*find node and it's parent*/

    /*Option 1 is a leaf*/
    /*terminate leaf*/

    /*Option 2 one child*/
    /*bypass to chiled*/
    /*teminate node*/

    /*Option 3 one child*/
    /*breplace node with sucessor*/
    /*teminate node*/

    return 0;
}
int create_and_insert_node(GArray * nodeArray, int data){
    int ret=0;

    node_t  temp;
    //*Initialize left and right children as NULL*/
    temp.right=NULL;
    temp.left=NULL;

    /*set data*/
    temp.data=data;

    g_array_append_val(nodeArray,temp);


    if(nodeArray->len>1) {
        ret = insert(&g_array_index(nodeArray, node_t, 0), &g_array_index(nodeArray, node_t, (nodeArray->len) - 1));
    }
    return ret;
}


int main(void) {
    int ret=0;
    /*this can be a vector-like or queue structure*/
    GArray * nodeArray=g_array_new (FALSE, TRUE, sizeof(node_t));
    /*create root*/

    create_and_insert_node(nodeArray,1);

    /*create some nodes*/
    create_and_insert_node(nodeArray,2);
    create_and_insert_node(nodeArray,10);
    create_and_insert_node(nodeArray,3);
    create_and_insert_node(nodeArray,7);
    create_and_insert_node(nodeArray,13);

    node_t *root = &g_array_index(nodeArray,node_t,0);
    /*print existing nodes*/
    traverse(root);

    /*test lookup*/
    node_t* foundNode=lookup(root, 1);
    if(foundNode!=NULL) printf("Node found!\n");
    else  printf("Node null!\n");

    /*remove*/

    /*traverse again*/


    printf("Done!\n");
    g_array_free(nodeArray, TRUE);
    return 0;
}