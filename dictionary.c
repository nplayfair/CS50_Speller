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

#include "dictionary.h"

typedef struct node
    {
        struct node* words[LENGTH + 1];
        bool isWord;
    }
node;

struct node* first = {NULL};

// Global variables

unsigned int dictionarySize = 0;
char word[LENGTH + 1];


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // setup node
    node* head = first;
    int str = 0;
    int index = 0;
    
    while (str != '\0')
    {
        str = word[index];
        
        // deal with upper case
        if ((str >= 'A') && (str <= 'Z'))
        {
            str = str + 32;
        }
        
        // apostrophe
        if ((str == 39) || (str <= 'z' && str >= 'a'))
        {
            if (str == 39)
            {
                str = LENGTH + 'a';
            }
            if (head->words[str - 'a'] == NULL)
            {
                return 0;
            }
            else
            {
                head = head->words[str - 'a'];
            }
        }
        
        index++;
    }
    
    return head->isWord;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Load file
    FILE* file = fopen(dictionary, "r"); //open dictionary file in read only mode
    // Check loaded ok
    if (file == NULL)
    {
        return false;
    }
    
    // allocate mem for first node
    first = malloc(sizeof(node));
    
    int str = 0;
    node* temp = NULL;
    
    // loop through whole file
    while (fgetc(file) != EOF)
    {
        fseek(file, -1, SEEK_CUR);
        temp = first;
        
        for  (  str = fgetc(file); str != '\n';
                str = fgetc(file))
        {
            // apostrophe
            if (str == 39)
            {
                //put at the end
                str = 'z' + 1;
            }
            if (temp->words[str - 'a'] == NULL)
            {
                temp->words[str - 'a'] = malloc(sizeof(node));
                
                // temp new node
                temp = temp->words[str - 'a'];
            }
            else
            {
                temp = temp->words[str - 'a'];
            }
        }
        
        temp->isWord =  true;
        dictionarySize++;
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
 helper function to recursively clear nodes
 */
 
 bool clearNode(node* currentNode)
 {
    for (int i = 0; i < LENGTH; i++)
    {
        if (currentNode->words[i] != NULL)
        {
            clearNode(currentNode->words[i]);
        }
    }
    free(currentNode);
    return true;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return clearNode(first);
}
