#include <stdio.h>
#include <stdlib.h>

struct node 
{
	int size;
	int status;
	//if 0 then not occupied, if 1 then occupied, if 2 then split
	struct node *right, *left;
};
typedef struct node *NP, N;

NP create_node (int,int);
int check_space(NP,int);
void make_buddy (NP);
int try_to_remove (NP,int);
void display_tree (NP);

int main ()
{
	int size, choice;
	while (1)
	{
		printf ("Enter the size of memory - a power of 2: ");
		scanf ("%d",&size);
		//check for power of 2 by bitwise and operation
		if (size&(size-1))
		{
			printf ("Enter a power of two!!\n");
		}
		else
			break;
	}
	NP head = create_node (size,0);
	while (1)
	{
		printf ("MEMORY SLICE:OCCUPANCY-\n");
		display_tree (head);
		printf ("\nEnter 1. to allocate process, 2. to deallocate process 3. to exit: ");
		scanf ("%d",&choice);
		switch(choice)
		{
			case 1: printf ("Enter the size of the process:");
				   scanf ("%d",&size);
				   choice = check_space(head,size);
				   if (choice)
				   	printf ("Successfully allocated.\n");
				   else
				   	printf ("Unable to allocate.\n");
				   break;
			case 2: printf ("Enter the size of the block that needs to be deallocated:");
				   scanf ("%d",&size);
				   choice = try_to_remove(head,size);
				   if (choice)
				   	printf ("Successfully deallocated.\n");
				   else
				   	printf ("unable to deallocate.\n");
				   make_buddy (head);
				   	
				   break;
			case 3: return 0;
			default: printf ("Wrong input!!\n");
					break;
				   
		}
	}
	return 0;
}

NP create_node (int size, int status)
{
	NP temp = (NP)malloc (sizeof (N));
	temp->size = size;
	temp->right = temp->left = NULL;
	temp->status = status;
	return temp;
}

int check_space(NP head, int size)
{
	if (head->size<size)//process too big
			return 0;
	if (head->status == 0)//not divided & unoccupied
	{
		if ((head->size)/2>=size)//if division possible
		{
			//create two additional children
			head->status = 2;
			head->left = create_node(head->size/2,0);
			head->right = create_node (head->size/2,0);
			return check_space(head->left,size);
		}
		else
		{
			//it should be allocated in the same node
			head->status = 1;
			return 1;
		}
	}
	else if (head->status == 1)
		return 0;
	else
	{
		//means that it has been split 
		if (check_space(head->left,size))
			return 1;
		else 
			return check_space(head->right,size);
	}
}

void display_tree (NP head)
{
	if (head->status == 2)
	{
		display_tree (head->left);
		display_tree (head->right);
	}
	else
		printf ("%d:%d\t",head->size,head->status);
}

int try_to_remove (NP head,int size)
{
	if (head->status == 1)
	{
		if (head->size == size)
		{
			head->status = 0;
			return 1;	//successful removal	   
		}
	}
	else if (head->status == 2)
	{
		if (try_to_remove (head->left,size))
			return 1;
		return try_to_remove (head->right,size);
	}
	return 0;
}
//important af
void make_buddy (NP head)
{
	if (head->status == 0||head->status == 1)
		return;
	make_buddy(head->left);
	make_buddy(head->right);
	if (head->left->status == 0 && head->right->status == 0)
	{
		NP temp = head->left;
		free (temp);
		temp = head->right;
		free (temp);
		head->status = 0;
	}
}
