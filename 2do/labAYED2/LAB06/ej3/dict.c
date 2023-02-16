#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t
{
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

/* static bool invrep(dict_t d)
{
    needs implementation 
    return true;
} */

dict_t dict_empty(void)
{
    dict_t dict = NULL;
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def)
{
    if (dict == NULL)
    {
        dict = calloc(1, (sizeof(struct _node_t)));
        dict->key = word;
        dict->value = def;
        dict->left = NULL;
        dict->right = NULL;
    }
    else
    {
        if (!key_eq(dict->key, word))
        {

            if (key_less(word, dict->key))
            {
                dict->left = dict_add(dict->left, word, def);
            }
            else
            {
                dict->right = dict_add(dict->right, word, def);
            }
        }
        else
        {
            dict->value = def;
        }
    }
    return dict;
}

value_t dict_search(dict_t dict, key_t word)
{
    key_t def = NULL;

    if (dict_exists(dict, word))
    {
        if (key_eq(word, dict->key))
        {
            def = dict->value;
        }
        else
        {

            if (key_less(word, dict->key))
            {
                def = dict_search(dict->left, word);
            }
            else
            {
                def = dict_search(dict->right, word);
            }
        }
    }

    return def;
}

bool dict_exists(dict_t dict, key_t word)
{
    bool b = false;
    if (dict == NULL)
    {
        return b;
    }
    else
    {
        if (key_eq(dict->key, word))
        {
            b = true;
        }
        else
        {
            if (key_less(word, dict->key))
            {
                b = dict_exists(dict->left, word);
            }
            else
            {
                b = dict_exists(dict->right, word);
            }
        }
    }
    return b;
}

unsigned int dict_length(dict_t dict)
{
    unsigned int lenght = 0;

    if (dict != NULL)
    {
        lenght += dict_length(dict->right);
        lenght += dict_length(dict->left);
        lenght++;
    }
    return lenght;
}

dict_t dict_remove(dict_t dict, key_t word)
{
    if (dict_exists(dict, word))
    {

        if (!key_eq(dict->key, word))
        {
            if (key_less(word, dict->key))
            {
                dict->left = dict_remove(dict->left, word);
            }
            else
            {
                dict->right = dict_remove(dict->right, word);
            }
        }
        else // dict->key = word
        {
            if ((dict->right == NULL) && (dict->left == NULL))
            {
                free(dict);
                dict = NULL;
                return NULL;
            }
            else
            {
                if (dict->right != NULL)
                {
                    key_t min = dict_min_key(dict->right);
                    key_t def = dict_min_value(dict->right);
                    dict->key = min;
                    dict->value= def;
                    dict->right = dict_remove(dict->right, min);
                }
                else
                {

                    key_t max = dict_max_key(dict->left);
                    key_t def = dict_max_value(dict->left);
                    dict->key = max;
                    dict->value = def;
                    dict->left = dict_remove(dict->left, max);
                } 
            }
        }
    }

    return dict;
}

key_t dict_max_key(dict_t dict)
{

    key_t  max_k;

    if (dict->right == NULL)
    {
        max_k = dict->key;
    }
    else
    {
        max_k = dict_max_key(dict->right);
    }

    return max_k;
}

key_t dict_max_value(dict_t dict)
{

    key_t  max_v;

    if (dict->right == NULL)
    {
        max_v = dict->value;
    }
    else
    {
        max_v = dict_max_value(dict->right);
    }

    return max_v;
}

key_t dict_min_key(dict_t dict)
{
    key_t min_k;

    if (dict->left == NULL)
    {
        min_k = dict->key;
    }
    else
    {
        min_k = dict_min_key(dict->left);
    }

    return min_k;
}

key_t dict_min_value(dict_t dict)
{
    key_t min_v;

    if (dict->left == NULL)
    {
        min_v = dict->value;
    }
    else
    {
        min_v = dict_min_value(dict->left);
    }

    return min_v;
}

dict_t dict_remove_all(dict_t dict)
{
    if (dict->left == NULL && dict->right == NULL)
    {
        key_destroy(dict->key);
        key_destroy(dict->value);
    }
    else
    {
        if (dict->right != NULL)
        {
            dict->right = dict_remove_all(dict->right);
        }
        if (dict->left != NULL)
        {
            dict->left = dict_remove_all(dict->left);
        }

        dict = dict_remove_all(dict);
        free(dict);
        dict = NULL;
    }

    return dict;
}

void dict_dump(dict_t dict, FILE *file)
{
    // fprintf("%s \n definition: %s", dict->key, dict->value,stdout);
    if (dict != NULL)
    {
        dict_dump(dict->left, file);
        key_dump(dict->key, stdout);
        printf(" : ");
        key_dump(dict->value, stdout);
        printf("\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict)
{
    dict = dict_remove_all(dict);
    if (dict != NULL)
    {
        free(dict);
        dict = NULL;
    }
    return dict;
}
