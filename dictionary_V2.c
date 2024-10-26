// Implements a dictionary's functionality
// Built based on data structure Trie, rather than a hash table
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Declare 2 global variants
const unsigned int N = 27;
int sumdic = 0;

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *next[N];
    // We use 27 for the sake of apostrophes('), in other words,
    // the previous 26 elements in the array is used to store characters, the last for '.
} node;

// The first node of tries
node *new_node;

// Add a new prototype, which can be used to avoid a memory leak when an error occurs.
void freem(node *temp);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *tnode;
    tnode = new_node;
    for (int i = 0; i < strlen(word); i++)
    {
        int h = hash(word, i);
        tnode = tnode->next[h];
        if (tnode == NULL)
        {
            // printf("1");
            return false;
        }
    }
    if (tnode->is_word == false)
    {
        // printf("2");
        return false;
    }
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word, int i)
{
    // TODO: Improve this hash function
    if (word[i] != '\'')
        return toupper(word[i]) - 'A';
    else
        return 26;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("unable to open dict.\n");
        return false;
    }
    char temp[LENGTH + 1];
    new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("internal error.");
        return false;
    }
    // Initialization of a new node in the trie.
    // It actually can be packed into a fucntion
    for (int j = 0; j < N; j++)
        new_node->next[j] = NULL;
    new_node->is_word = false;
    // create a temporary node* to iterate in the loop,
    // to prevent that we lose control of the initial node.
    node *tnode;
    tnode = new_node;
    while (fscanf(source, "%s", temp) != EOF)
    {
        sumdic += 1;
        int len = strlen(temp);
        for (int k = 0; k < len; k++)
        {
            int h = hash(temp, k);
            // Pay attention to this if-else:
            // we only need to allocate new chunk of memories when the node has no memory
            if (tnode->next[h] == NULL)
            {
                tnode->next[h] = malloc(sizeof(node));
                if (tnode->next[h] == NULL)
                {
                    printf("internal error.");
                    freem(new_node);
                    return false;
                }
                tnode = tnode->next[h];
                for (int j = 0; j < N; j++)
                    tnode->next[j] = NULL;
                tnode->is_word = false;
            }
            // Notice here: if there ALREADY exist something in this node,
            // DO NOT CHANGE ANYTHING! Just move forward, or we will experience an mistake
            // Well i just madde that mistake last night->(2024, 10, 25)
            else
                tnode = tnode->next[h];
        }
        tnode->is_word = true;
        tnode = new_node;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sumdic;
}

// Unloads dictionary from memory, returning true if successful, else false
// The idea here is quite similar to that of hash table, core thought is recursion.
void freem(node *temp)
{
    if (temp == NULL)
        return;
    for (int i = 0; i < N; i++)
    {
        if (temp->next[i] != NULL)
            freem(temp->next[i]);
    }
    free(temp);
}
// Looks stupid here. But I've got to do this.
// 'Cause i cannot modify the speller.c, which means that i cannot give unload() any arguments
bool unload(void)
{
    freem(new_node);
    return true;
}
