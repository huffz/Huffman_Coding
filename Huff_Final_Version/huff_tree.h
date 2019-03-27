#include "global.h"



node *create_node(unsigned char data, int freq, node* left, node* right);
node *add(node *head, unsigned char c, int f, node *l, node *r);
node *make_tree_from_list(node *head);

h_tree *create_t_node(unsigned char c, h_tree* left, h_tree* right);
h_tree *montar_arvore(FILE *output, h_tree *tree, int tree_size, int cont);

void print_pre_order(h_tree *tree);
void print_lista(node *tree);
void makeHuffmanTree(node **head);
void FrequencyEnqueue(FILE *p, int *arr, node **head);



node *create_node(unsigned char data, int freq, node* left, node* right)
{
	node *novo = (node *) malloc(sizeof(node));
	novo->f = freq;
	novo->c = data;
	novo->next = NULL;
	novo->left = left;
	novo->right = right;
	return novo;
}

node *add(node *head, unsigned char c, int f, node *l, node *r)//compress
{
	node *novo = create_node(c, f, l, r);
	if(head != NULL)
	{
		node *current = head;
		node *previous = NULL;
		while(current != NULL && current->f < f)
		{
			previous = current;
			current = current->next;
		}
		if(previous == NULL) // na cabeça
		{
			novo->next = current;
			current = novo;
			return current;
		}
		else
		{
			previous->next = novo;
			novo->next = current;
			return head;			
		}
	}
	return novo;
}

void print_pre_order(h_tree *tree)
{	
	if(tree != NULL)
	{
    	printf("%c ", tree->c);
    	print_pre_order(tree->left);
    	print_pre_order(tree->right);
	}
}

void print_lista(node *tree)
{	
	if(tree != NULL)
	{
    	printf("%c ", tree->c);
    	print_lista(tree->left);
    	print_lista(tree->right);
	}
}

h_tree *create_t_node(unsigned char c, h_tree* left, h_tree* right)
{
	h_tree *novo = (h_tree *) malloc(sizeof(h_tree));
	novo->c = c;
	novo->left = left;
	novo->right = right;
	return novo;
}

node *make_tree_from_list(node *head) //compress
{
	node *aux1, *aux2;

	aux1 = head; //primeiro (menor_f).
	aux2 = head->next; //segundo (menor_f).
	head = head->next->next; //terceiro menor da lista

	head = add(head,'*', aux1->f + aux2->f, aux1, aux2); // adicionar na lista com prioridade
	return head;
}

h_tree *montar_arvore(FILE *compactado, h_tree *tree, int tree_size, int cont) //descomprimir
{
	unsigned char c;
	if(cont == tree_size)
		return NULL;
	
	fscanf(compactado, "%c", &c);
  
	if(c == '\\')
	{
		fscanf(compactado, "%c", &c);
	
		return create_t_node(c, NULL, NULL);

	}
	else if(c != '*')
	{
		return create_t_node(c, NULL, NULL);
	}
	else if(tree == NULL)
	{

		tree = create_t_node(c, NULL, NULL);

		tree->left = montar_arvore(compactado, tree->left, tree_size, cont+1);
		tree->right = montar_arvore(compactado, tree->right, tree_size, cont+1);
	}

	return tree;
}

void makeHuffmanTree(node **head) // compress
{
	if((*head)->next == NULL) // caso possua um unico node
	{
		node *aux = *head;

		*head = add(*head, '*', aux->f, aux, NULL);
	}
	else
	{
		while((*head)->next != NULL)
		{
			*head = make_tree_from_list(*head);
		}		
	}
}

void FrequencyEnqueue(FILE *p, int *arr, node **head) // compress
{
	int i;
	unsigned char c; 

	while(fscanf(p, "%c", &c) != EOF)
	{
		arr[c] += 1; 
	}
	for (i = 0; i < MAX; ++i) 
	{
		if(arr[i] != 0) // existe o caractere
		{
			*head = add(*head, i, arr[i], NULL, NULL); //ordem crescente
		}
	}
}