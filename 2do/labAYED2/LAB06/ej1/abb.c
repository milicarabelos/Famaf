#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb
{
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b)
{
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b)
{
    return a < b;
}

static bool invrep(abb tree)
{   
    static bool b;
    if (tree != NULL)
    {
        if (tree->left != NULL)
        {
            b = (tree->left->elem < tree->elem) && invrep(tree->left);
        }
        if (tree->right != NULL)
        {
            b = (tree->right->elem > tree->elem) && invrep(tree->right);
        }
    }
    else{
        b = (tree == NULL);
    } 
    return b;
/*     return tree == NULL ||
           // El elemento a la izquierda es valido
           ((tree->left == NULL || tree->elem > tree->left->elem) &&
            // El elemento a la derecha es valido
            (tree->right == NULL || tree->elem < tree->right->elem) &&
            // El arbol de la izquierda es valido
            invrep(tree->left) &&
            // El arbol de la derecha es valido
            invrep(tree->right)); */
}

abb abb_empty(void)
{
    abb tree;
    /*
     * Needs implementation                                 listo
     */
    tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e)
{
    assert(invrep(tree));
    /*
     * Needs implementation                                     listo
     */

    if (tree == NULL)
    {
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    }

    else
    {
        if (!elem_eq(tree->elem, e))
        {

            if (elem_less(e, tree->elem))
            {
                tree->left = abb_add(tree->left, e);
            }
            else
            {
                tree->right = abb_add(tree->right, e);
            }
        }

        assert(invrep(tree) && abb_exists(tree, e));
    }
    return tree;
}

bool abb_is_empty(abb tree)
{
    bool is_empty = (tree == NULL);
    assert(invrep(tree));
    /*
     *                                                              listo
     */
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e)
{
    bool exists = false;
    assert(invrep(tree));
    /*
     * Needs implementation                                          listo
     */
    if (abb_is_empty(tree))
    {
        return exists;
    }
    else
    {
        if (elem_eq(e, tree->elem))
        {
            exists = true;
        }
        else
        {
            if (elem_less(e, tree->elem))
            {
                exists = abb_exists(tree->left, e);
            }
            else
            {
                exists = abb_exists(tree->right, e);
            }
        }
    }
    return exists;
}

unsigned int abb_length(abb tree)
{
    unsigned int length = 0;
    assert(invrep(tree));
    /*
     * Needs implementation                                     listo
     */
    if (!abb_is_empty(tree))
    {
        unsigned int length_right = 0, length_left = 0;
        length_left = length_left + abb_length(tree->left);
        length_right = length_right + abb_length(tree->right);
        length = 1 + length_right + length_left;
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e)
{
    assert(invrep(tree));
    /*
     * Needs implementation
     */

    if (abb_exists(tree, e))
    {

        if (!elem_eq(tree->elem, e))
        {
            if (elem_less(e, tree->elem))
            {
                tree->left = abb_remove(tree->left, e);
            }
            else
            {
                tree->right = abb_remove(tree->right, e);
            }
        }
        else // tree.elem = e
        {
            if ((tree->right == NULL) && (tree->left == NULL))
            {
                free(tree);
                tree = NULL;
                return NULL;
            }
            else
            {
                if (tree->right != NULL)
                {
                    abb_elem min = abb_min(tree->right);
                    tree->elem = min;
                    tree->right = abb_remove(tree->right, min);
                }
                else
                {

                    abb_elem max = abb_max(tree->left);
                    tree->elem = max;
                    tree->left = abb_remove(tree->left, max);
                }
            }
        }
    }

    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}

abb_elem abb_root(abb tree)
{
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    /*
     * Needs implementation                                             listo
     */
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree)
{
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    /*
     * Needs implementation
     */
    if (tree->right == NULL)
    {
        max_e = tree->elem;
    }
    else
    {
        max_e = abb_max(tree->right);
    }
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree)
{
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    /*
     * Needs implementation
     */

    if (tree->left == NULL)
    {
        min_e = tree->elem;
    }
    else
    {
        min_e = abb_min(tree->left);
    }
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree)
{
    assert(invrep(tree));
    if (tree != NULL)
    {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree)
{
    assert(invrep(tree));
    /*
     * Needs implementation
     */

    if(tree->left != NULL){
        abb_destroy(tree->left);
    }
    if(tree->right != NULL)
    {
        abb_destroy(tree->right);
    }

    free(tree);
    tree = NULL;
    assert(tree == NULL);
    return tree; // tree;
}
