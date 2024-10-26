// Implements a dictionary's functionality
// Built based on data structure Hash Table
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int h = hash(word);
    node *temp = table[h];
    while (temp != NULL)
    {
        if (strcasecmp(temp->word, word) == 0)
            return true;
        else
            temp = temp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
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
    while (fscanf(source, "%s", temp) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("internal error.");
            return false;
        }
        strcpy(new_node->word, temp);
        new_node->next = NULL;
        int h = hash(new_node->word);
        if (table[h] != NULL)
        {
            new_node->next = table[hash(new_node->word)];
            table[h] = new_node;
        }
        else
        {
            table[h] = new_node;
        }
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];
        while (temp != NULL)
        {
            temp = temp->next;
            sum += 1;
        }
    }
    return sum;
}

// Unloads dictionary from memory, returning true if successful, else false
void freem(node *temp)
{
    if (temp == NULL)
        return;
    else
    {
        freem(temp->next);
    }

    free(temp);
}

bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];
        freem(temp);
    }
    return true;
}
