#include<stdio.h>
#include<stdlib.h>


typedef int item_type;
typedef enum{R,B}colour;
typedef struct rbt_node_tag
{
    item_type data;
    colour col;
    struct rbt_node_tag* left;
    struct rbt_node_tag* right;
    struct rbt_node_tag* parent;
}rbt_node;

void RotateLeft(rbt_node**root)
{
    rbt_node* ptr=*root;
    rbt_node* rptr=ptr->right;
    ptr->right=rptr->left;
    rptr->left=ptr;
    ptr->parent=rptr;
    if(ptr->right!=NULL)
    {
        (ptr->right)->parent=ptr;
    }
}

void RotateRight(rbt_node**root)
{
    rbt_node* ptr=*root;
    rbt_node* lptr=ptr->left;
    ptr->left=lptr->right;
    lptr->right=ptr;
    ptr->parent=lptr;
    if(ptr->left!=NULL)
    {
        (ptr->left)->parent=ptr;
    }
}

void ShiftProb(rbt_node**root)
{
    rbt_node*ptr=*root;
    (ptr->right)->col=B;
    (ptr->left)->col=B;
    ptr->col=R;
    if(ptr->parent==NULL)
    {
        ptr->col=B;
    }
    else
    {
        if((ptr->parent)->parent!=NULL&&(ptr->parent)->col==R)
        {
            ((ptr->parent)->parent)-> //









                                    //
        }
    }

}

void PutVal(rbt_node**root,rbt_node*nptr,int c)
{
    rbt_node* ptr=*root;
    switch(c)
    {
    case 0:
        ptr=nptr;
        break;
    case 1:
        ptr->left=nptr;
        nptr->parent=ptr;
        break;
    case 2:
        ptr->right=nptr;
        nptr->parent=ptr;
        break;
    case 3:                                    //LLB
        rbt_node* gptr= ptr->parent;
        rbt_node* ggptr=(ptr->parent)->parent;
        ptr->left=nptr;
        RotateRight(&gptr);
        ptr->col=B;
        gptr->col=R;
        if((ptr->parent)->parent==NULL)
        {
            ptr->parent=NULL;
        }
        else if(ggptr->data>gptr->data)
        {
            ggptr->left=ptr;
        }
        else if(ggptr->data<gptr->data)
        {
            ggptr->right=ptr;
        }
        break;
    case 4:                                                                //LLR
        rbt_node* gptr= ptr->parent;
        ShiftProb(&gptr);
        break;
    case 5:                                                                //LRB
        rbt_node* ggptr=(ptr->parent)->parent;
        rbt_node* gptr= ptr->parent;
        ptr->right=nptr;
        RotateLeft(&ptr);
        gptr->left=nptr;
        RotateRight(&gptr);
        nptr->col=B;
        gptr->col=R;
        if(ggptr==NULL)
        {
            nptr->parent=NULL;
        }
        else if(ggptr->data>gptr->data)
        {
            ggptr->left=nptr;
            nptr->parent=ggptr;
        }
        else if(ggptr->data<gptr->data)
        {
            ggptr->right=nptr;
            nptr->parent=ggptr;
        }
        break;
    case 6:                                     //LRR
        rbt_node* gptr= ptr->parent;
        ShiftProb(&gptr);
        break;
    case 7:                                     //RLB
        rbt_node* ggptr=(ptr->parent)->parent;
        rbt_node* gptr= ptr->parent;
        ptr->left=nptr;
        RotateRight(&ptr);
        gptr->right=nptr;
        RotateLeft(&gptr);
        nptr->col=B;
        gptr->col=R;
        if(ggptr==NULL)
        {
            nptr->parent=NULL;
        }
        else if(ggptr->data>gptr->data)
        {
            ggptr->left=nptr;
            nptr->parent=ggptr;
        }
        else if(ggptr->data<gptr->data)
        {
            ggptr->right=nptr;
            nptr->parent=ggptr;
        }
        break;
    case 8:                                     //RLR
        rbt_node* gptr= ptr->parent;
        ShiftProb(&gptr);
        break;
    case 9:                                     //RRB
        rbt_node* gptr= ptr->parent;
        rbt_node* ggptr=(ptr->parent)->parent;
        ptr->left=nptr;
        RotateLeft(&gptr);
        ptr->col=B;
        gptr->col=R;
        if((ptr->parent)->parent==NULL)
        {
            ptr->parent=NULL;
        }
        else if(ggptr->data>gptr->data)
        {
            ggptr->left=ptr;
        }
        else if(ggptr->data<gptr->data)
        {
            ggptr->right=ptr;
        }
        break;
    case 10:                                       //RRR
        rbt_node* gptr= ptr->parent;
        ShiftProb(&gptr);
        break;
    }
}

rbt_node* InsertRBT(rbt_node* root, int d)
{
    int c;
    rbt_node* ptr=root;
    rbt_node* nptr=(rbt_node*)malloc(sizeof(rbt_node));
    nptr->data=d;
    nptr->col=B;
    nptr->left=NULL;
    nptr->right=NULL;
    nptr->parent=NULL;

    if(ptr==NULL)
    {
        nptr->col=B;
        c=0;
    }
    else
    {
        while(!(ptr->left==NULL&&ptr->data>d)&&!(ptr->right==NULL&&ptr->data<d))
        {
            if(ptr->data<d)
            {
                ptr=ptr->right;
            }
            else if(ptr->data>d)
            {
                ptr=ptr->left;
            }
        }

        if(ptr->col==B)
        {
            if(ptr->data>d)
            {
                c=1;         //parent B L
            }
            else if(ptr->data<d)
            {
                c=2;         //parent B R
            }
        }
        else
        {
            rbt_node* gptr=ptr->parent;

            if(ptr->data<gptr->data)        //L
            {
                if(d<ptr->data)                 //L
                {
                    if((gptr->right)->col==B||gptr->right==NULL)
                    {
                        c=3;                            //LLB
                    }
                    else
                    {
                        c=4;                            //LLR
                    }
                }
                else if(d>ptr->data)            //R
                {
                    if((gptr->right)->col==B||gptr->right==NULL)
                    {
                        c=5;                            //LRB
                    }
                    else
                    {
                        c=6;                            //LRR
                    }
                }
            }
            else if(ptr->data>gptr->data)   //R
            {
                if(d<ptr->data)                 //L
                {
                    if((gptr->left)->col==B||gptr->left==NULL)
                    {
                        c=7;                            //RLB
                    }
                    else
                    {
                        c=8;                            //RLR
                    }
                }
                else if(d>ptr->data)            //R
                {
                    if((gptr->left)->col==B||gptr->left==NULL)
                    {
                        c=9;                            //RRB
                    }
                    else
                    {
                        c=10;                            //RRR
                    }
                }
            }
        }
    }
    PutVal(&ptr,nptr,c);
}

rbt_node* InitializeRBT(rbt_node* root)
{
    int d;
    FILE* fptr=fopen("data.txt","r");
    fseek(fptr,0,SEEK_END);
    unsigned int len=ftell(fptr);
    if(len>0)
    {
        rewind(fptr);
        while(!feof(fptr))
        {
            fscanf(fptr,"%d",&d);
            root=InsertRBT(root,d);
            //printf("%d, ",d);
        }
    }
    fclose(fptr);
    return root;
}

void main()
{
    rbt_node* root=NULL;
    root=InitializeRBT(root);
}
