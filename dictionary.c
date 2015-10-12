/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

// hash table
int hash(const char* word);

char word[LENGTH + 1];


typedef struct node
    {
        char* word;
        struct node* next;
    }
node;

node* hasht[HASHTABLESIZE];


unsigned int dictionarySize = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int wlength = strlen(word);
    char temp[LENGTH +1];
    node* nodep;
    
    // Convert to all lower case
    
    for (int i = 0; i <= wlength; i++)
    {
        //int low = tolower(word[i]);
        temp[i] = tolower(word[i]);
    }
    
    // add null ending
    temp[wlength] = '\0';
    
    int hashvalue = hash(temp);
    nodep = hasht[hashvalue];
    if (!nodep)
    {
        //no node created
        return false;
    }
    
    //search the list of words in dict for the word passed in
    while (nodep)
    {
        if (!strcmp(nodep->word,temp))
        {
            return true;
        }
        nodep = nodep->next;
    }
    // else not in list
    //printf( "%s not in dictionary.\n",word);
    return false; 
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Load file
    FILE* file = fopen(dictionary, "r");
    // Check loaded ok
    if (file == NULL)
    {
        return false;
    }
    
    int hashvalue;
    
    // init hashtable
    for (int i = 0; i < HASHTABLESIZE; i++)
    {
        hasht[i] = NULL;
    }
    
    // loop through whole file
    while (fscanf(file,"%s\n",word) != EOF)
    {
        // insert word into a node
        node *nodep = malloc(sizeof(node));
        nodep->word = malloc(strlen(word)+1);
        strcpy(nodep->word,word);
        
        hashvalue = hash(word);
        
        //debug
        //printf( "%s hash = %d\n",word,hashvalue);
        
        dictionarySize++;
        if (hasht[hashvalue] == NULL)
        // insert at head of list
        {
            hasht[hashvalue] = nodep;
            nodep->next = NULL;
        }
        else
        {
            //insert node at head of list
            nodep->next = hasht[hashvalue];
            hasht[hashvalue] = nodep;
        }
        
    }
    // close file
    fclose(file);
    
    //end
    return true; 
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionarySize;
}

/**
 hash function
 */
 
 int hash(const char* word)
 {
    int length = strlen(word);
    int hash = 0;
    
    for (int i = 0; i < length; i++)
    {
        hash += word[i];
    }
    return hash%HASHTABLESIZE;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    node* nextnodep;
    node* nodep;
    for (int i = 0; i < HASHTABLESIZE; i++)
    {
        nodep = hasht[i];
        while (nodep)
        {
            free(nodep->word);
            nextnodep = nodep->next;
            free(nodep);
            nodep = nextnodep;
        }
        
        hasht[i] = NULL;
    }
    return true;
}
