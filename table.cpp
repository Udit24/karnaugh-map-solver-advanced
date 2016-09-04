#include "table.h"


Table::MapTable *Table::CreateEntry(int i, int j, int iSize, int jSize){

            MTptr = new MapTable;
            MTptr->i = i;
            MTptr->j = j;
            MTptr->iSize = iSize;
            MTptr->jSize = jSize;
            MTptr->next = NULL;
            return MTptr;
}

void Table::pushEntry(Table::MapTable *np)
{
     // Stack or LIFO approach
           if (MTtop == NULL)
           {
               MTtop = np;
           }
           else {
               MTptr = MTtop;
               MTtop = np;
               np->next = MTptr;
           }

}

Table::coOrdinates *Table::emergeCoOrdinate(int i, int j, bool status)
{
        COptr = new coOrdinates;
        COptr->i = i;
        COptr->j = j;
        COptr->status = status;
        COptr->next = NULL;
        return  COptr;
}

void Table::insertCoOrdinate(Table::coOrdinates *np)
{ // Stack or LIFO approach
        if (COtop == NULL)
        {
            COtop = np;
        }
        else {
            COptr = COtop;
            COtop = np;
            np->next = COptr;
        }

}

void Table::deleteCoOrdinateList(Table::coOrdinates *top)
{
    coOrdinates *save;
    if(top!=NULL){
        save=top->next;
        while(top!=NULL){
            delete top;
            top=save;
            if(top!=NULL)save=top->next;
        }
    }
}

Table::coOrdinates *Table::emergeCoOrdinate2(int i, int j, bool status)
{
        COptr2 = new coOrdinates;
        COptr2->i = i;
        COptr2->j = j;
        COptr2->status = status;
        COptr2->next = NULL;
        return  COptr2;

}

void Table::insertCoOrdinate2(Table::coOrdinates *np)
{ // Stack or LIFO approach
        if (COtop2 == NULL)
        {
            COtop2 = np;
        }
        else {
            COptr2 = COtop2;
            COtop2 = np;
            np->next = COptr2;
        }


}

Table::FringeMapTable *Table::CreateEntry(int i1, int j1, int i2, int j2, int iSize, int jSize)
{
        FTptr = new FringeMapTable;
        FTptr->i1 = i1;
        FTptr->j1 = j1;
        FTptr->i2 = i2;
        FTptr->j2 = j2;
        FTptr->iSize = iSize;
        FTptr->jSize = jSize;
        FTptr->next = NULL;
        return FTptr;
}

void Table::pushEntry(Table::FringeMapTable *np)
{
            if (FTtop == NULL) { FTtop = np; }
            else {
                FTptr = FTtop;
                FTtop = np;
                np->next = FTptr;
            }

}

void Table::pushHEntry(Table::FringeMapTable *np)
{
           if (FHTtop == NULL) { FHTtop = np; }
           else {
               FTptr = FHTtop;
               FHTtop = np;
               np->next = FTptr;
           }

}
