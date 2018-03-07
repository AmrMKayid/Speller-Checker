/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

#define SIZE 26

typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
}
node;


node *hashtable[SIZE];

int hashFunc(char *word)
{
    char c = toupper(word[0]);
    return (c-65)%26;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    
    char c = toupper(word[0]);
    int i = (c-65)%26;
    
    node *n = hashtable[i];
    while(n != NULL)
    {
        if(strcasecmp(word, n->word) == 0) 
            return true;
        n = n->next;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO

    // Opening the file of the dictionary
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }
    
    // Word to be loaded
    char word[LENGTH+1];
    
    // Reading each word in the dictionary file
    while(fscanf(dict, "%s", word) != EOF)
    {
        node *newNode = malloc(sizeof(node));
        if(newNode == NULL)
        {
            unload();
            return false;
        }
        
        //printf("%s\n", word);
        strcpy(newNode->word, word);
        //printf("%s\n", newNode->word);
        int hashedPos = hashFunc(word);
        newNode->next = hashtable[hashedPos];
        hashtable[hashedPos] = newNode;
        //free(newNode);
    }
    
    fclose(dict);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    int c = 0;
    for(int i = 0; i < SIZE; i++)
    {
        node *n = hashtable[i];
        while(n != NULL)
        {
            c++;
            n = n->next;
        }
    }
    return c;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    for(int i = 0; i < SIZE; i++)
    {
        node *n = hashtable[i];
        while(n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }
        //free(hashtable[i]);
    }
    return true;
}
