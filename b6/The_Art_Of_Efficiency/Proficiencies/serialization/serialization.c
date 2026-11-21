#include "serialization.h"
#include <stdlib.h>

/*
struct node
{
    uint16_t value;
    struct node *left;
    struct node *right;
};


*/

size_t  cpt_bit(const struct node*root )
{
    if(root==NULL)
    {
        return 0;
    }
    size_t cpt;
    if(root->right==NULL && root->left==NULL)
    {
        cpt=18;
    }
    else 
    {
        cpt = 2 + cpt_bit(root->left) + cpt_bit(root->right);
    }
    return cpt;

}
/*


        A
       B c


    11 00 16BIT 00 16BIT



*/

void aux(const struct node *root, uint8_t *box, size_t *idx)
{
    if (root == NULL)
        return;

    uint8_t flag;

    if (root->left == NULL && root->right == NULL)
    {
        flag = 0;
    }
    else if (root->left != NULL && root->right == NULL)
    {
        flag = 2;
    }
    else if (root->left == NULL && root->right != NULL)
    {
        flag = 1;
    }
    else
    {
        flag = 3;
    }

    for (int i = 0; i < 2; i++)// 2bit par node
    {
        if ((flag >> i) & 1)
        {
            box[*idx / 8] = box[*idx / 8] | (1 << (*idx % 8));
        }
        (*idx)++;
    }

    if (flag == 0)
    {
        for (int i = 0; i < 16; i++)// cas de leaf 16 bit
        {
            if ((root->value >> i) & 1)
            {
                box[*idx / 8] = box[*idx / 8] |(1 << (*idx % 8));
            }
            (*idx)++;
        }
    }

    aux(root->left, box, idx);
    aux(root->right, box, idx);
}
uint8_t *tree_serialize(const struct node *root, size_t *byte_count)
{
  
       if (!root)
    {
        *byte_count = 0;
        return NULL;
    }
    size_t r=0;
    size_t cpt=cpt_bit(root);
    if(cpt%8!=0)
    {
        r=1;
    }
    size_t nb_o=cpt/8+r;
    uint8_t *box=calloc(nb_o,sizeof(uint8_t));
   
    if (!box)
    {
        *byte_count = 0;
        return NULL;
    }
    size_t idx=0;

    aux(root, box, &idx);

    *byte_count = nb_o;

    return box;


}
void destroy_tree(struct node *root)
{
    if (root == NULL)
        return;

    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}
struct node *aux_d(const uint8_t *data, size_t byte_count, size_t *idx)
{
    if (*idx + 2 > byte_count * 8)//chek si reste bit a lire 
        return NULL;

    uint8_t flag = 0;

    //  2 bits du flag
    for (int i = 0; i < 2; i++)
    {
        flag =flag | ((data[*idx / 8] >> (*idx % 8)) & 1) << i;
        (*idx)++;
    }

    //  nv node
    struct node *nv_node = malloc(sizeof(struct node));
    if (!nv_node)
        return NULL;

    nv_node->value = 0;
    nv_node->left = NULL;
    nv_node->right = NULL;

    //feuille
    if (flag == 0)
    {
        if (*idx + 16 > byte_count * 8)// suffisament de bit
        {
            free(nv_node);
            return NULL;
        }

        for (int i = 0; i < 16; i++)
        {
            nv_node->value = nv_node->value |((data[*idx / 8] >> (*idx % 8)) & 1) << i;
            (*idx)++;
        }
    }

    //  child gauch
    else if (flag == 2)
    {
        nv_node->left = aux_d(data, byte_count, idx);
        if (!nv_node->left)
        {
            free(nv_node);
            return NULL;
        }
    }

    // child droit uniquement
    else if (flag == 1)
    {
        nv_node->right = aux_d(data, byte_count, idx);
        if (!nv_node->right)
        {
            free(nv_node);
            return NULL;
        }
    }

    // point double
    else
    {
        nv_node->left = aux_d(data, byte_count, idx);
        if (!nv_node->left)
        {
            free(nv_node);
            return NULL;
        }

        nv_node->right = aux_d(data, byte_count, idx);
        if (!nv_node->right)
        {
            destroy_tree(nv_node->left);
            free(nv_node);
            return NULL;
        }
    }

    return nv_node;
}

struct node *tree_deserialize(const uint8_t *data, size_t byte_count)
{
     if (byte_count == 0 || data == NULL)return NULL;
        

    size_t idx = 0;

    struct node *root = aux_d(data, byte_count, &idx);

    return root;
}
/*
#include "serialization.h"

#include <stdio.h>
#include <stdlib.h>



int main(void)
{
    struct node leaf = {
        .value = 42,
        .left = NULL,
        .right = NULL
    };
    struct node branch = {
        .value = 99,
        .left = NULL,
        .right = &leaf
    };
    struct node root = {
        .value = 123,
        .left = &branch,
        .right = NULL
    };

    size_t byte_count;
    uint8_t *data = tree_serialize(&root, &byte_count);
    if (data == NULL)
    {
        return EXIT_FAILURE;
    }
   // printf("Serialized bytes: %zu\n", byte_count);
    struct node *decoded = tree_deserialize(data, byte_count);
    if (decoded == NULL)
    {
        free(data);
        return EXIT_FAILURE;
    }

    printf("Serialized bytes: %zu\n", byte_count);
    printf("Root: %u\n", (unsigned int)decoded->value);
    printf("Left child: %u\n",
           (unsigned int)decoded->left->value);
    printf("Leaf: %u\n",
           (unsigned int)decoded->left->right->value);
    printf("Root has no right child: %d\n",
           decoded->right == NULL);
    printf("Original root: %u\n", (unsigned int)root.value);

    destroy_tree(decoded);
    free(data);

    return EXIT_SUCCESS;
}
*/