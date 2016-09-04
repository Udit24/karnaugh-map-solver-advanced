#include "kmap.h"

KMap::KMap() {

    this->NOV=4;
    this->ROW=4;
    this->COLUMN=4;
    this->side=16;
    SOP=1;

    //setting the HEADER pointers to NULL, Indicating an empty NODE
    MTtop = NULL; COtop = NULL; FTtop = NULL; FHTtop = NULL;
    initGray();
    //inputMap();

    /*
    //Initializing all co-ordinates to 1
    for(int i=0;i<ROW;i++){
    for(int j=0;j<COLUMN;j++){
    cout<<"\n Enter entry for ["<<i<<"]["<<j<<"] : ";
    cin>>Map[i][j];

    }
    }
    */



}

void KMap::TheMapIs()
{
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COLUMN;j++){
            int l= Map[i][j];
            
        }
    }

}


/*This function is the heart of the program, it is designed to identify all possible maps in the Map*/
void KMap::MapGenerator() {

    //Traversing each element of the Map
    for (int i = 0;i<ROW;i++) {
        for (int j = 0;j<COLUMN;j++) {
            //A search for a Map of 1s cannot start with zero, common thats obvious
            if (Map[i][j] == !SOP)continue;

            ///DECIDING THE SIZE OF THE MAP
            /*here a contraction of the size is adopted
            which means the possibility is always tested for the Maximum map in the beginning
            i.e a ROW X COLUMN size
            the possibility gets reduced by a factor of two (prioritizing the x(j) side by mere choice)
            till a Map is found*/
            for (int iSize = ROW;iSize>0;iSize /= 2) {
                for (int jSize = COLUMN;jSize>0;jSize /= 2) {
                    bool isMapped = true;
                    bool allD = true;

                    //If the attempted Mapping exceeds the dimension of the Map
                    if ((i + iSize>ROW) || (j + jSize>COLUMN))continue;

                    //Traversing the region (where theres a possibility of Map with dimensions iSize and jSize)
                    for (int ti = i;ti<i + iSize;ti++) {
                        for (int tj = j;tj<j + jSize;tj++) {
                            if (Map[ti][tj] == !SOP)isMapped = false;
                            if (Map[ti][tj] == SOP)allD = false;
                        }
                    }

                    if (isMapped == true) { //If the region consists of all 1s
                                            //cout<<"\nA map found from location "<<i<<" "<<j<<" of size "<<iSize<<" "<<jSize;
                                            ///THE DECISION FOR ADDING TO THE MAP TABLE
                                            /*Being too good at its job, comes with its pitfall for our Mapgenerator
                                            the function generates just too many Maps , than thats really needed
                                            But thats not for it to care, as it has got its best buddy at help
                                            the redundancyEliminator eliminates all the repeated or unnecessary maps...
                                            and delivers a clean input to the Map table*/
                                            ///The filter
                        if (allD == false)
                            redundancyEliminator(i, j, iSize, jSize);
                    }
                }
            }
        }
    }
}

void KMap::redundancyEliminator(int i, int j, int iSize, int jSize) {

    //setting the HEADER pointer to NULL, Indicating an empty NODE
    COtop = NULL;

    //Creating the List of co-ordinates for the requested Map
    for (int r = i;r<i + iSize;r++) {
        for (int s = j;s<j + jSize;s++) {
            insertCoOrdinate(emergeCoOrdinate(r, s));
        }
    }

    /*Theres no controversy with the first element ,
    so it goes as an entry to the Map table anyways */
    if (MTtop == NULL) {
        pushEntry(CreateEntry(i, j, iSize, jSize)); //cout<<"\n added to MT table :"<<i<<" "<<j<<" "<<iSize<<" "<<jSize;
    }
    else {
        MTptr = MTtop;
        //Traversing each entry of the Map table
        while (MTptr != NULL) {
            //For each entry , traversing all elements of the entry
            for (int r = MTptr->i;r < MTptr->i + MTptr->iSize;r++) {
                for (int s = MTptr->j;s < MTptr->j + MTptr->jSize; s++) {
                    COptr = COtop;
                    /*traversing the list of co-ordinates
                    each element of individual entry of the map table is compared with the whole list of co-ordinates*/
                    while (COptr != NULL) {
                        if ((COptr->i == r) && (COptr->j == s)) {
                            COptr->status = true;
                        }
                        COptr = COptr->next;
                    }
                }
            }
            MTptr = MTptr->next;
        }

        COptr = COtop;
        while (COptr != NULL) {
            if (COptr->status == false) { //If any one of the element in the List of co-ordinates is not mapped
                pushEntry(CreateEntry(i, j, iSize, jSize));//Then add the Map to the Map table
                                                           //cout<<"\n added to MT table :"<<i<<" "<<j<<" "<<iSize<<" "<<jSize;
                break;
            }
            COptr = COptr->next;
        }
    }


}

/*This function is the heart of the program, it is designed to identify all possible maps in the Map*/
void KMap::FringeMapGenerator_Vertical() {
    //Traversing each element of the Map
    for (int rowSelect = 0;rowSelect<ROW;rowSelect++) {
        //A search for a Map of 1s cannot start with zero, common thats obvious
        if (Map[rowSelect][0] == !SOP)continue;

        ///DECIDING THE SIZE OF THE MAP
        /*here a contraction of the size is adopted
        which means the possibility is always tested for the Maximum map in the beginning
        i.e a ROW X COLUMN size
        the possibility gets reduced by a factor of two (prioritizing the x(j) side by mere choice)
        till a Map is found*/
        for (int iSize = ROW;iSize>0;iSize /= 2) {
            for (int jSize = (COLUMN) / 2;jSize>0;jSize /= 2) {
                bool isMappedOne = true;
                bool isMappedTwo = true;
                bool allD = true;

                //If the attempted Mapping exceeds the dimension of the Map
                if ((rowSelect + iSize>ROW))continue;

                //Traversing the region (where theres a possibility of Map with dimensions iSize and jSize)
                for (int i = rowSelect;i<rowSelect + iSize;i++) {
                    for (int j = 0;j<jSize;j++) {
                        if (Map[i][j] == !SOP)isMappedOne = false;
                        if (Map[i][j] == SOP)allD = false;
                    }
                }
                for (int i = rowSelect;i<rowSelect + iSize;i++) {
                    for (int j = COLUMN - 1;j >= COLUMN - jSize;j--) {
                        if (Map[i][j] == !SOP)isMappedTwo = false;
                        if (Map[i][j] == SOP)allD = false;
                    }
                }

                if (isMappedOne == true && isMappedTwo == true) {//If the region consists of all 1s
                                                                 //cout<<"\nA map found from location "<<rowSelect<<" 0"<<" of size "<<iSize<<" "<<jSize<<" and form "<<rowSelect<<" "<<COLUMN-1;
                                                                 ///THE DECISION FOR ADDING TO THE MAP TABLE
                                                                 /*Being too good at its job, comes with its pitfall for our Mapgenerator
                                                                 the function generates just too many Maps , than thats really needed
                                                                 But thats not for it to care, as it has got its best buddy at help
                                                                 the redundancyEliminator eliminates all the repeated or unnecessary maps...
                                                                 and delivers a clean input to the Map table*/
                                                                 ///The filter
                    if (allD == false)
                        FringeRedundancyEliminator_Vertical(rowSelect, 0, rowSelect, COLUMN - 1, iSize, jSize);

                }
            }
        }

    }
}

void KMap::FringeRedundancyEliminator_Vertical(int i1, int j1, int i2, int j2, int iSize, int jSize) {

    //setting the HEADER pointer to NULL, Indicating an empty NODE
    COtop = NULL;

    //Creating the List of co-ordinates for the requested Map
    for (int r = i1;r<i1 + iSize;r++) {
        for (int s = j1;s<j1 + jSize;s++) {
            insertCoOrdinate(emergeCoOrdinate(r, s));
        }
    }

    /*Theres no controversy with the first element ,
    so it goes as an entry to the Map table anyways */
    if (FTtop == NULL) {
        pushEntry(CreateEntry(i1, j1, i2, j2, iSize, jSize));//cout<<"\n added to FT table :"<<i1<<" "<<j1<<" "<<i2<<" "<<j2<<" "<<iSize<<" "<<jSize;
    }
    else {
        FTptr = FTtop;
        //Traversing each entry of the Map table
        while (FTptr != NULL) {
            //For each entry , traversing all elements of the entry
            for (int r = FTptr->i1;r < FTptr->i1 + FTptr->iSize;r++) {
                for (int s = FTptr->j1;s < FTptr->j1 + FTptr->jSize; s++) {
                    COptr = COtop;
                    /*traversing the list of co-ordinates
                    each element of individual entry of the map table is compared with the whole list of co-ordinates*/
                    while (COptr != NULL) {
                        if ((COptr->i == r) && (COptr->j == s)) {
                            COptr->status = true;
                        }
                        COptr = COptr->next;
                    }
                }
            }
            FTptr = FTptr->next;
        }

        COptr = COtop;
        while (COptr != NULL) {
            if (COptr->status == false) { //If any one of the element in the List of co-ordinates is not mapped
                pushEntry(CreateEntry(i1, j1, i2, j2, iSize, jSize));//Then add the Map to the Map table
                                                                     //cout<<"\n added to FT table :"<<i1<<" "<<j1<<" "<<i2<<" "<<j2<<" "<<iSize<<" "<<jSize;
                break;
            }
            COptr = COptr->next;
        }
    }



}

/*This function is the heart of the program, it is designed to identify all possible maps in the Map*/
void KMap::FringeMapGenerator_Horizontal() {
    for (int columnSelect = 0;columnSelect<COLUMN;columnSelect++) {
        //Traversing each element of the Map
        if (Map[0][columnSelect] == !SOP)continue;

        ///DECIDING THE SIZE OF THE MAP
        /*here a contraction of the size is adopted
        which means the possibility is always tested for the Maximum map in the beginning
        i.e a ROW X COLUMN size
        the possibility gets reduced by a factor of two (prioritizing the x(j) side by mere choice)
        till a Map is found*/
        for (int iSize = ROW / 2;iSize>0;iSize /= 2) {
            for (int jSize = COLUMN;jSize>0;jSize /= 2) {
                bool isMappedOne = true;
                bool isMappedTwo = true;
                bool allD = true;


                //If the attempted Mapping exceeds the dimension of the Map
                if ((columnSelect + jSize>COLUMN))continue;

                //Traversing the region (where theres a possibility of Map with dimensions iSize and jSize)
                for (int i = 0;i<iSize;i++) {
                    for (int j = columnSelect;j<columnSelect + jSize;j++) {
                        if (Map[i][j] == !SOP)isMappedOne = false;
                        if (Map[i][j] == SOP)allD = false;
                    }
                }
                for (int i = ROW - 1;i >= ROW - iSize;i--) {
                    for (int j = columnSelect;j<columnSelect + jSize;j++) {
                        if (Map[i][j] == !SOP)isMappedTwo = false;
                        if (Map[i][j] == SOP)allD = false;
                    }
                }

                if (isMappedOne == true && isMappedTwo == true) {//If the region consists of all 1s
                                                                 //cout<<"\nA map found from location "<<" 0 "<<columnSelect<<" of size "<<iSize<<" "<<jSize<<" and form "<<ROW-1<<" "<<columnSelect;
                                                                 ///THE DECISION FOR ADDING TO THE MAP TABLE
                                                                 /*Being too good at its job, comes with its pitfall for our Mapgenerator
                                                                 the function generates just too many Maps , than thats really needed
                                                                 But thats not for it to care, as it has got its best buddy at help
                                                                 the redundancyEliminator eliminates all the repeated or unnecessary maps...
                                                                 and delivers a clean input to the Map table*/

                                                                 ///The filter
                    if (allD == false)
                        FringeRedundancyEliminator_Horizontal(0, columnSelect, ROW - 1, columnSelect, iSize, jSize);

                }
            }
        }

    }
    FTptr = FTtop;
    if (FTptr != NULL) { // If FTtop is NULL then the program should not face abnormal termination
        while (FTptr->next != NULL)FTptr = FTptr->next;
        FTptr->next = FHTtop;
    }
    else {
        FTtop = FHTtop;
    }
}

void KMap::FringeRedundancyEliminator_Horizontal(int i1, int j1, int i2, int j2, int iSize, int jSize) {

    //setting the HEADER pointer to NULL, Indicating an empty NODE
    COtop = NULL;

    //Creating the List of co-ordinates for the requested Map
    for (int r = i1;r<i1 + iSize;r++) {
        for (int s = j1;s<j1 + jSize;s++) {
            insertCoOrdinate(emergeCoOrdinate(r, s));
        }
    }

    /*Theres no controversy with the first element ,
    so it goes as an entry to the Map table anyways */
    if (FHTtop == NULL) {
        pushHEntry(CreateEntry(i1, j1, i2, j2, iSize, jSize));//cout<<"\n added to FT table :"<<i1<<" "<<j1<<" "<<i2<<" "<<j2<<" "<<iSize<<" "<<jSize;
                                                              //cout<<"\n added location "<<i1<<" "<<j1<<" of size "<<iSize<<" "<<jSize<<" and "<<i2<<" "<<j2;
    }
    else {
        FTptr = FHTtop;
        //Traversing each entry of the Map table
        while (FTptr != NULL) {
            //For each entry , traversing all elements of the entry
            for (int r = FTptr->i1;r < FTptr->i1 + FTptr->iSize;r++) {
                for (int s = FTptr->j1;s < FTptr->j1 + FTptr->jSize; s++) {
                    COptr = COtop;
                    /*traversing the list of co-ordinates
                    each element of individual entry of the map table is compared with the whole list of co-ordinates*/
                    while (COptr != NULL) {
                        if ((COptr->i == r) && (COptr->j == s)) {
                            COptr->status = true;
                        }
                        COptr = COptr->next;
                    }
                }
            }
            FTptr = FTptr->next;
        }

        COptr = COtop;
        while (COptr != NULL) {
            if (COptr->status == false) { //If any one of the element in the List of co-ordinates is not mapped
                pushHEntry(CreateEntry(i1, j1, i2, j2, iSize, jSize));//Then add the Map to the Map table
                                                                      //cout<<"\n added location "<<i1<<" "<<j1<<" of size "<<iSize<<" "<<jSize<<" and "<<i2<<" "<<j2;
                                                                      //cout<<"\n added to FT table :"<<i1<<" "<<j1<<" "<<i2<<" "<<j2<<" "<<iSize<<" "<<jSize;
                break;
            }
            COptr = COptr->next;
        }
    }

}
void KMap::TheEliminator() { //cout<<"\n Eliminator called";

    FTptr = FTtop;
    while (FTptr != NULL) {/*qDebug()<<"\n "<<FTptr->i1<<" "<<FTptr->i2<<" and"<<FTptr->i2<<" "<<FTptr->j2;*/
        COtop = NULL; //Creates a new list of co-ordinates each time
        bool deleteFTentry = false;/*qDebug("\n Inside func and I am fine");*/

        //If Vertical mapping
        if (FTptr->i1 == FTptr->i2) {/*qDebug("\n Inside condition V and I am fine");*/
            for (int i = FTptr->i1;i<FTptr->i1 + FTptr->iSize;i++) {
                for (int j = FTptr->j1;j<FTptr->j1 + FTptr->jSize;j++) {
                    insertCoOrdinate(emergeCoOrdinate(i, j));
                }
            }
            for (int i = FTptr->i2;i<FTptr->i2 + FTptr->iSize;i++) {
                for (int j = FTptr->j2;j>FTptr->j2 - FTptr->jSize;j--) {
                    insertCoOrdinate(emergeCoOrdinate(i, j));
                }
            }
        }
        //If horizontal Mapping
        else if (FTptr->j1 == FTptr->j2) {/*qDebug("\n Inside condition H and I am fine");*/
            for (int i = FTptr->i1;i<FTptr->i1 + FTptr->iSize;i++) {
                for (int j = FTptr->j1;j<FTptr->j1 + FTptr->jSize;j++) {
                    insertCoOrdinate(emergeCoOrdinate(i, j));
                }
            }
            for (int i = FTptr->i2;i>FTptr->i2 - FTptr->iSize;i--) {
                for (int j = FTptr->j2;j<FTptr->j2 + FTptr->jSize;j++) {
                    insertCoOrdinate(emergeCoOrdinate(i, j));
                }
            }
        }
//        qDebug("\n Outside condition and I am fine");

        MTptr = MTtop;
        while (MTptr != NULL) {
            COptr = COtop;
            while (COptr != NULL) {
                for (int i = MTptr->i;i<MTptr->i + MTptr->iSize;i++) {
                    for (int j = MTptr->j;j<MTptr->j + MTptr->jSize;j++) {
                        if (COptr->i == i && COptr->j == j) {
                            // if((MTptr->iSize*MTptr->jSize)<(FTptr->iSize*FTptr->jSize*2))
                            COptr->status = true;
                            //else
                            //COptr->status=false;

                        }
                    }
                }
                COptr = COptr->next;
            }

            COptr = COtop;
            while (COptr != NULL) {
                if ((COptr->i == 0 && COptr->j == 0) || (COptr->i == 0 && COptr->j == COLUMN - 1) || (COptr->i == ROW - 1 && COptr->j == 0) || (COptr->i == ROW - 1 && COptr->j == COLUMN - 1)) {
                    if (MapCorner == true) {
                        COptr->status = true;
                    }
                }
                COptr = COptr->next;
            }

            bool allTrue = true;
            COptr = COtop;
            while (COptr != NULL) {
                if (COptr->status == false) {
                    allTrue = false;
                    break;
                }
                COptr = COptr->next;
            }

            if (allTrue == true) {
                deleteFTentry = true;
                break;
            }
            else {
                COptr = COtop;
                while (COptr != NULL) {
                    COptr->status = false;
                    COptr = COptr->next;
                }

            }


            MTptr = MTptr->next;

        }

        deleteCoOrdinateList(COtop);
        if (deleteFTentry == true) {//cout<<"\n deleting FT entry "<<FTptr->i1<<" "<<FTptr->j1<<" "<<FTptr->i2<<" "<<FTptr->j2<<" "<<FTptr->iSize<<" "<<FTptr->jSize;
            if (FTptr == FTtop) {
                FTtop = FTtop->next;
                delete(FTptr);
                FTptr = NULL;
            }
            else {
                FTprev = FTnext = FTtop;
                while (FTprev->next != FTptr) { FTprev = FTprev->next; }
                while (FTnext != FTptr->next) { FTnext = FTnext->next; }
                FTprev->next = FTnext;
                delete(FTptr);
                FTptr = FTprev;

            }
        }

        if (FTptr == NULL)FTptr = FTtop;
        else FTptr = FTptr->next;
    } /*qDebug("\n Fine Till here");*/

}

void KMap::TheEliminatorSecondary() {//cout<<"\n Sec eliminator called";
                                     ///Traversing for all MT
    MTptr = MTtop;
    while (MTptr != NULL) {

        //Deciding variable : decides the deletion of the Map
        bool deleteMTentry = false;
        //Creating a list of CD for MT entry
        COtop = NULL;
        for (int i = MTptr->i;i< MTptr->i + MTptr->iSize; i++) {
            for (int j = MTptr->j; j < MTptr->j + MTptr->jSize; j++) {
                insertCoOrdinate(emergeCoOrdinate(i, j));
            }
        }


        //traversing FT
        FTptr = FTtop;
        while (FTptr != NULL) {

            ///Traversing CO List
            COptr = COtop;
            while (COptr != NULL) {

                ///Traversing all CO of FT
                //If Vertical mapping
                if (FTptr->i1 == FTptr->i2) {
                    for (int i = FTptr->i1;i<FTptr->i1 + FTptr->iSize;i++) {
                        for (int j = FTptr->j1;j<FTptr->j1 + FTptr->jSize;j++) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                    for (int i = FTptr->i2;i<FTptr->i2 + FTptr->iSize;i++) {
                        for (int j = FTptr->j2;j>FTptr->j2 - FTptr->jSize;j--) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                }
                //If horizontal Mapping
                else if (FTptr->j1 == FTptr->j2) {
                    for (int i = FTptr->i1;i<FTptr->i1 + FTptr->iSize;i++) {
                        for (int j = FTptr->j1;j<FTptr->j1 + FTptr->jSize;j++) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                    for (int i = FTptr->i2;i>FTptr->i2 - FTptr->iSize;i--) {
                        for (int j = FTptr->j2;j<FTptr->j2 + FTptr->jSize;j++) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                }


                COptr = COptr->next;
            }

            COptr = COtop;
            while (COptr != NULL) {
                if ((COptr->i == 0 && COptr->j == 0) || (COptr->i == 0 && COptr->j == COLUMN - 1) || (COptr->i == ROW - 1 && COptr->j == 0) || (COptr->i == ROW - 1 && COptr->j == COLUMN - 1)) {
                    if (MapCorner == true) {
                        COptr->status = true;
                    }
                }
                COptr = COptr->next;
            }

            bool allTrue = true;
            COptr = COtop;
            while (COptr != NULL) {
                if (COptr->status == false) {
                    allTrue = false;
                    break;
                }
                COptr = COptr->next;
            }

            if (allTrue == true && (MTptr->iSize*MTptr->jSize)<(FTptr->iSize*FTptr->jSize * 2)) {
                deleteMTentry = true;
                break;
            }
            else {
                COptr = COtop;
                while (COptr != NULL) {
                    COptr->status = false;
                    COptr = COptr->next;
                }

            }

            FTptr = FTptr->next;
        }
        if (deleteMTentry == true) {//cout<<"\n deleting entry "<<MTptr->i<<" "<<MTptr->j<<" "<<MTptr->iSize<<" "<<MTptr->jSize;
            if (MTptr == MTtop) {
                MTtop = MTtop->next;
                delete(MTptr);
                MTptr = NULL;
            }
            else {
                MTprev = MTnext = MTtop;
                while (MTprev->next != MTptr) { MTprev = MTprev->next; }
                while (MTnext != MTptr->next) { MTnext = MTnext->next; }
                MTprev->next = MTnext;
                delete(MTptr);
                MTptr = MTprev;

            }
        }

        if (MTptr == NULL)MTptr = MTtop;
        else MTptr = MTptr->next;
    }
}
void KMap::cleaner() {//cout<<"\n cleaner called";
    MTcur = MTtop;
    while (MTcur != NULL) {
        bool deleteMTentry = false;bool deleteFTentry = false;
        COtop = NULL;
        for (int i = MTcur->i;i< MTcur->i + MTcur->iSize; i++) {
            for (int j = MTcur->j; j < MTcur->j + MTcur->jSize; j++) {
                insertCoOrdinate(emergeCoOrdinate(i, j));
                //cout<<"\n created co-ordinate for"<<i<<" "<<j;
            }
        }


        MTptr = MTtop;
        while (MTptr != NULL) {
            //if(MTptr==MTcur){MTptr=MTptr->next;continue;}cout<<"\n here";
            if (MTptr != MTcur) {
                //cout<<"\n analysing co ordi for "<<MTptr->i<<" "<<MTptr->j;
                COptr = COtop;
                while (COptr != NULL) {
                    for (int i = MTptr->i;i< MTptr->i + MTptr->iSize; i++) {
                        for (int j = MTptr->j; j < MTptr->j + MTptr->jSize; j++) {
                            if (COptr->i == i && COptr->j == j) {

                                COptr->status = true;
                            }
                        }
                    }
                    COptr = COptr->next;
                }
            }
            else if (MapCorner == true) {
                COptr = COtop;
                while (COptr != NULL) {//cout<<"\n co ordi run for "<<COptr->i<<" "<<COptr->j;
                    if ((COptr->i == 0 && COptr->j == 0) || (COptr->i == 0 && COptr->j == COLUMN - 1) || (COptr->i == ROW - 1 && COptr->j == 0) || (COptr->i == ROW - 1 && COptr->j == COLUMN - 1)) {
                        {
                            //cout<<"\n CO status turned true for "<<COptr->i<<" "<<COptr->j;
                            COptr->status = true;
                        }
                    }
                    COptr = COptr->next;
                }
            }

            bool allTrue = true;
            COptr = COtop;
            while (COptr != NULL) {
                if (COptr->status == false) {

                    allTrue = false;
                    break;
                }
                COptr = COptr->next;
            }

            if (allTrue == true) {
                deleteMTentry = true;

                break;
            }


            MTptr = MTptr->next;
        }
        FTptr = FTtop;
        while (FTptr != NULL) {

            COptr = COtop;
            while (COptr != NULL) {
                ///Traversing all CO of FT
                //If Vertical mapping
                if (FTptr->i1 == FTptr->i2) {
                    for (int i = FTptr->i1;i<FTptr->i1 + FTptr->iSize;i++) {
                        for (int j = FTptr->j1;j<FTptr->j1 + FTptr->jSize;j++) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                    for (int i = FTptr->i2;i<FTptr->i2 + FTptr->iSize;i++) {
                        for (int j = FTptr->j2;j>FTptr->j2 - FTptr->jSize;j--) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                }
                //If horizontal Mapping
                else if (FTptr->j1 == FTptr->j2) {
                    for (int i = FTptr->i1;i<FTptr->i1 + FTptr->iSize;i++) {
                        for (int j = FTptr->j1;j<FTptr->j1 + FTptr->jSize;j++) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                    for (int i = FTptr->i2;i>FTptr->i2 - FTptr->iSize;i--) {
                        for (int j = FTptr->j2;j<FTptr->j2 + FTptr->jSize;j++) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                }


                COptr = COptr->next;
            }

            COptr = COtop;
            while (COptr != NULL) {
                if ((COptr->i == 0 && COptr->j == 0) || (COptr->i == 0 && COptr->j == COLUMN - 1) || (COptr->i == ROW - 1 && COptr->j == 0) || (COptr->i == ROW - 1 && COptr->j == COLUMN - 1)) {
                    if (MapCorner == true) {
                        COptr->status = true;
                    }
                }
                COptr = COptr->next;
            }


            bool allTrue = true;
            COptr = COtop;
            while (COptr != NULL) {
                if (COptr->status == false) {

                    allTrue = false;
                    break;
                }
                COptr = COptr->next;
            }

            if (allTrue == true) {
                deleteFTentry = true;

                break;
            }


            FTptr = FTptr->next;
        }
        //cout<<"\ndel MT : "<<deleteMTentry<<", del FT : "<<deleteFTentry;
        if (deleteMTentry == true || deleteFTentry == true) {// cout<<"\n Removing entry"<<MTcur->i<<" "<<MTcur->j<<" Size"<<MTcur->iSize<<" "<<MTcur->jSize;
            if (MTcur == MTtop) {
                MTtop = MTtop->next;
                delete(MTcur);
                MTcur = NULL;
            }
            else {
                MTprev = MTnext = MTtop;
                while (MTprev->next != MTcur) { MTprev = MTprev->next; }
                while (MTnext != MTcur->next) { MTnext = MTnext->next; }
                MTprev->next = MTnext;
                delete(MTcur);
                MTcur = MTprev;

            }
        }


        if (MTcur == NULL)MTcur = MTtop;
        else MTcur = MTcur->next;
    }

}

void KMap::cornerMap() {//cout<<"\n corner Map gen called";
    if (((Map[0][0] == SOP) || (Map[0][0] == 2)) && ((Map[0][COLUMN - 1] == SOP) || (Map[0][COLUMN - 1] == 2))
        && ((Map[ROW - 1][0] == SOP) || (Map[ROW - 1][0] == 2)) && ((Map[ROW - 1][COLUMN - 1] == SOP) || (Map[ROW - 1][COLUMN - 1] == 2))) {

        if (Map[0][0] == 2 && Map[0][COLUMN - 1] == 2 && Map[ROW - 1][0] == 2 && Map[ROW - 1][COLUMN - 1] == 2)return;

        FTptr = FTtop;
        bool found_Corner_Map = false;
        while (FTptr != NULL) {//cout<<"\n "<<FTptr->i1<<" "<<FTptr->i2<<" and"<<FTptr->i2<<" "<<FTptr->j2;
            COtop = NULL; //Creates a new list of co-ordinates each time
            bool deleteFTentry = false;
            //If Vertical mapping
            if (FTptr->i1 == FTptr->i2) {
                for (int i = FTptr->i1;i<FTptr->i1 + FTptr->iSize;i++) {
                    for (int j = FTptr->j1;j<FTptr->j1 + FTptr->jSize;j++) {
                        insertCoOrdinate(emergeCoOrdinate(i, j));
                    }
                }
                for (int i = FTptr->i2;i<FTptr->i2 + FTptr->iSize;i++) {
                    for (int j = FTptr->j2;j>FTptr->j2 - FTptr->jSize;j--) {
                        insertCoOrdinate(emergeCoOrdinate(i, j));
                    }
                }
            }
            //If horizontal Mapping
            else if (FTptr->j1 == FTptr->j2) {
                for (int i = FTptr->i1;i<FTptr->i1 + FTptr->iSize;i++) {
                    for (int j = FTptr->j1;j<FTptr->j1 + FTptr->jSize;j++) {
                        insertCoOrdinate(emergeCoOrdinate(i, j));
                    }
                }
                for (int i = FTptr->i2;i>FTptr->i2 - FTptr->iSize;i--) {
                    for (int j = FTptr->j2;j<FTptr->j2 + FTptr->jSize;j++) {
                        insertCoOrdinate(emergeCoOrdinate(i, j));
                    }
                }
            }

            COptr = COtop;
            while (COptr != NULL) {
                if ((COptr->i == 0 && COptr->j == 0) || (COptr->i == 0 && COptr->j == COLUMN - 1) || (COptr->i == ROW - 1 && COptr->j == 0) || (COptr->i == ROW - 1 && COptr->j == COLUMN - 1)) {
                    if ((FTptr->iSize * FTptr->jSize * 2)<4) {
                        deleteFTentry = true;
                        found_Corner_Map = true;
                        break;
                    }
                }
                COptr = COptr->next;
            }

            if (deleteFTentry == true) {//cout<<"\n deleting FT entry "<<FTptr->i1<<" "<<FTptr->j1<<" "<<FTptr->i2<<" "<<FTptr->j2<<" "<<FTptr->iSize<<" "<<FTptr->jSize;
                if (FTptr == FTtop) {
                    FTtop = FTtop->next;
                    delete(FTptr);
                    FTptr = NULL;
                }
                else {
                    FTprev = FTnext = FTtop;
                    while (FTprev->next != FTptr) { FTprev = FTprev->next; }
                    while (FTnext != FTptr->next) { FTnext = FTnext->next; }
                    FTprev->next = FTnext;
                    delete(FTptr);
                    FTptr = FTprev;

                }
            }


            if (FTptr == NULL)FTptr = FTtop;
            else FTptr = FTptr->next;
        }
        if (found_Corner_Map == true) {
            cout << "\n Corner Map found";
            MapCorner = true;
			return;
		}		
	}MapCorner = false;
}


void KMap::cleanerSecondary() {//cout<<"\n secondary cleaner called";
    FTcur = FTtop;
    while (FTcur != NULL) {
        bool deleteMTentry = false;bool deleteFTentry = false;
        COtop = NULL;
        //If Vertical mapping
        if (FTcur->i1 == FTcur->i2) {
            for (int i = FTcur->i1;i<FTcur->i1 + FTcur->iSize;i++) {
                for (int j = FTcur->j1;j<FTcur->j1 + FTcur->jSize;j++) {
                    insertCoOrdinate(emergeCoOrdinate(i, j));
                }
            }
            for (int i = FTcur->i2;i<FTcur->i2 + FTcur->iSize;i++) {
                for (int j = FTcur->j2;j>FTcur->j2 - FTcur->jSize;j--) {
                    insertCoOrdinate(emergeCoOrdinate(i, j));
                }
            }
        }
        //If horizontal Mapping
        else if (FTcur->j1 == FTcur->j2) {
            for (int i = FTcur->i1;i<FTcur->i1 + FTcur->iSize;i++) {
                for (int j = FTcur->j1;j<FTcur->j1 + FTcur->jSize;j++) {
                    insertCoOrdinate(emergeCoOrdinate(i, j));
                }
            }
            for (int i = FTcur->i2;i>FTcur->i2 - FTcur->iSize;i--) {
                for (int j = FTcur->j2;j<FTcur->j2 + FTcur->jSize;j++) {
                    insertCoOrdinate(emergeCoOrdinate(i, j));
                }
            }
        }


        MTptr = MTtop;
        while (MTptr != NULL) {

            COptr = COtop;
            while (COptr != NULL) {
                for (int i = MTptr->i;i< MTptr->i + MTptr->iSize; i++) {
                    for (int j = MTptr->j; j < MTptr->j + MTptr->jSize; j++) {
                        if (COptr->i == i && COptr->j == j) {
                            COptr->status = true;
                        }
                    }
                }
                COptr = COptr->next;
            }

            COptr = COtop;
            while (COptr != NULL) {
                if ((COptr->i == 0 && COptr->j == 0) || (COptr->i == 0 && COptr->j == COLUMN - 1) || (COptr->i == ROW - 1 && COptr->j == 0) || (COptr->i == ROW - 1 && COptr->j == COLUMN - 1)) {
                    if (MapCorner == true) {
                        COptr->status = true;
                    }
                }
                COptr = COptr->next;
            }

            bool allTrue = true;
            COptr = COtop;
            while (COptr != NULL) {
                if (COptr->status == false) {

                    allTrue = false;
                    break;
                }
                COptr = COptr->next;
            }

            if (allTrue == true) {
                deleteMTentry = true;

                break;
            }


            MTptr = MTptr->next;
        }
        FTptr = FTtop;
        while (FTptr != NULL) {
            if (FTptr == FTcur) { FTptr = FTptr->next;continue; }
            COptr = COtop;
            while (COptr != NULL) {
                ///Traversing all CO of FT
                //If Vertical mapping
                if (FTptr->i1 == FTptr->i2) {
                    for (int i = FTptr->i1;i<FTptr->i1 + FTptr->iSize;i++) {
                        for (int j = FTptr->j1;j<FTptr->j1 + FTptr->jSize;j++) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                    for (int i = FTptr->i2;i<FTptr->i2 + FTptr->iSize;i++) {
                        for (int j = FTptr->j2;j>FTptr->j2 - FTptr->jSize;j--) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                }
                //If horizontal Mapping
                else if (FTptr->j1 == FTptr->j2) {
                    for (int i = FTptr->i1;i<FTptr->i1 + FTptr->iSize;i++) {
                        for (int j = FTptr->j1;j<FTptr->j1 + FTptr->jSize;j++) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                    for (int i = FTptr->i2;i>FTptr->i2 - FTptr->iSize;i--) {
                        for (int j = FTptr->j2;j<FTptr->j2 + FTptr->jSize;j++) {
                            if (COptr->i == i&&COptr->j == j) {
                                COptr->status = true;
                            }
                        }
                    }
                }


                COptr = COptr->next;
            }

            COptr = COtop;
            while (COptr != NULL) {
                if ((COptr->i == 0 && COptr->j == 0) || (COptr->i == 0 && COptr->j == COLUMN - 1) || (COptr->i == ROW - 1 && COptr->j == 0) || (COptr->i == ROW - 1 && COptr->j == COLUMN - 1)) {
                    if (MapCorner == true) {
                        COptr->status = true;
                    }
                }
                COptr = COptr->next;
            }

            bool allTrue = true;
            COptr = COtop;
            while (COptr != NULL) {
                if (COptr->status == false) {

                    allTrue = false;
                    break;
                }
                COptr = COptr->next;
            }

            if (allTrue == true) {
                deleteFTentry = true;

                break;
            }


            FTptr = FTptr->next;
        }
        if (deleteMTentry == true || deleteFTentry == true) { //cout<<"\n Removing entry"<<MTcur->i<<" "<<MTptr->j<<" Size"<<MTptr->iSize<<" "<<MTptr->jSize;
            if (FTcur == FTtop) {//cout<<"\n deleting FT entry "<<FTptr->i1<<" "<<FTptr->j1<<" "<<FTptr->i2<<" "<<FTptr->j2<<" "<<FTptr->iSize<<" "<<FTptr->jSize;
                FTtop = FTtop->next;

                delete(FTcur);

                FTcur = NULL;
            }
            else {
                FTprev = FTnext = FTtop;
                while (FTprev->next != FTcur) { FTprev = FTprev->next; }
                while (FTnext != FTcur->next) { FTnext = FTnext->next; }
                FTprev->next = FTnext;

                delete(FTcur);

                FTcur = FTprev;

            }
        }


        if (FTcur == NULL)FTcur = FTtop;
        else FTcur = FTcur->next;
    }

}

void KMap::ExpressionGen() {
    initGray();
    //printExp();
}
bool KMap::checkChangesY(int index, int start, int end) {
    for (int i = start;i<end;i++) {
        if (grayY[i].at(index) != grayY[i + 1].at(index))return true;
    }
    return false;
}
bool KMap::checkChangesX(int index, int start, int end) {
    for (int i = start;i<end;i++) {
        if (grayX[i].at(index) != grayX[i + 1].at(index))return true;
    }
    return false;
}
void KMap::initGray() {
    initYGray();
    initXGray();
}
void KMap::initYGray() {
    int Ny;
    Ny = ROW;
    string gray[MROW];
    gray[0] = "0";gray[1] = "1";
    int doneTill = 1;
    for (int i = 4;i <= Ny;i *= 2) {


        for (int j = doneTill + 1, k = 0;j<i;j++, k++) {
            gray[j] = gray[doneTill - k];
            gray[j].append("1");

        }
        for (int j = 0;j <= doneTill;j++) {
            gray[j].append("0");
        }
        doneTill = i - 1;
    }

    for (int i = 0;i<Ny;i++) {
        string temp;
        for (std::string::reverse_iterator rit = gray[i].rbegin(); rit != gray[i].rend(); ++rit)
            temp.append(1, *rit);
        gray[i].swap(temp);

    }

    for (int i = 0;i<Ny;i++) {
        grayY[i] = gray[i];
    }
}

void KMap::initXGray() {
    int Nx;
    Nx = COLUMN;
    string gray[MCOLUMN];
    gray[0] = "0";gray[1] = "1";
    int doneTill = 1;
    for (int i = 4;i <= Nx;i *= 2) {


        for (int j = doneTill + 1, k = 0;j<i;j++, k++) {
            gray[j] = gray[doneTill - k];
            gray[j].append("1");

        }
        for (int j = 0;j <= doneTill;j++) {
            gray[j].append("0");
        }
        doneTill = i - 1;
    }

    for (int i = 0;i<Nx;i++) {
        string temp;
        for (std::string::reverse_iterator rit = gray[i].rbegin(); rit != gray[i].rend(); ++rit)
            temp.append(1, *rit);
        gray[i].swap(temp);

    }

    for (int i = 0;i<Nx;i++) {
        grayX[i] = gray[i];
    }
}
QString KMap::printExp() {
    QString str;
    str.append("\n The expression is: ");
//    qDebug()<< "\n The expression is: ";
    str.append(printMT());
    str.append(printFT());
    str.append(printCorner());
    return str;
}
QString KMap::printMT() {
    QString str;
    if (SOP == 1) {
        MTptr = MTtop;
        while (MTptr != NULL) {//cout<<"\n i: "<<MTptr->i<<" j: "<<MTptr->j<<" iS: "<<MTptr->iSize<<" jS: "<<MTptr->jSize;
            int index = 0;
            char var = 'A';

            while (index<(NOV / 2)) {
                if (checkChangesY(index, MTptr->i, MTptr->i + MTptr->iSize - 1) == false) {//cout<<"\n at index is:"<<grayY[MTptr->i].at(index);
                    if (grayY[MTptr->i].at(index) == '0') {
//                        qDebug() << (char)(var + index) << "'";
                        str.append((const QChar)(var + index));
                        str.append("'");
                    }
                    else {
//                        qDebug()<< (char)(var + index);
                        str.append((const QChar)(var + index));
                    }

                }index++;
            }
            index = 0;
            var = 'A' + (NOV / 2);
            while (index< ((NOV % 2 == 0) ? (NOV / 2) : ((NOV / 2) + 1))) {
                if (checkChangesX(index, MTptr->j, MTptr->j + MTptr->jSize - 1) == false) {//cout<<"\n at index for another is:"<<grayX[MTptr->j].at(index);
                    cout << (char)(var + index);
                    str.append((const QChar)(var + index));
                    if (grayX[MTptr->j].at(index) == '0') {
                        qDebug() << "'";
                        str.append("'");
                    }
                }index++;
            }
//            qDebug() << "+";
            str.append("+");
            MTptr = MTptr->next;
        }
    }
    else {
        MTptr = MTtop;
        while (MTptr != NULL) {//cout<<"\n i: "<<MTptr->i<<" j: "<<MTptr->j<<" iS: "<<MTptr->iSize<<" jS: "<<MTptr->jSize;
            int index = 0;
            char var = 'A';
//            qDebug() << "(";
            str.append("(");
            while (index<(NOV / 2)) {
                if (checkChangesY(index, MTptr->i, MTptr->i + MTptr->iSize - 1) == false) {//cout<<"\n at index is:"<<grayY[MTptr->i].at(index);
                    if (grayY[MTptr->i].at(index) == '1') {
//                        qDebug() << (char)(var + index) << "'";
                        str.append((const QChar)(var + index));
                        str.append("'");
                    }
                    else {
//                        qDebug() << (char)(var + index);
                        str.append((const QChar)(var + index));
                    }/*qDebug() << "+";*/ str.append("+");

                }index++;
            }
            index = 0;
            var = 'A' + (NOV / 2);
            while (index< ((NOV % 2 == 0) ? (NOV / 2) : ((NOV / 2) + 1))) {
                if (checkChangesX(index, MTptr->j, MTptr->j + MTptr->jSize - 1) == false) {//cout<<"\n at index for another is:"<<grayX[MTptr->j].at(index);
//                    qDebug() << (char)(var + index);
                    str.append((const QChar)(var + index));

                    if (grayX[MTptr->j].at(index) == '1') {
//                        qDebug() << "'";
                        str.append("'");
                    }qDebug() << "+";str.append("+");
                }index++;
            }/*qDebug() << "\b";
            qDebug() << ")";*/str.append(")");
            MTptr = MTptr->next;
        }
    } return str;
}
QString KMap::printFT() {
    QString str;
    if (SOP == 1) {
        FTptr = FTtop;
        while (FTptr != NULL) {
            int index = 0;
            char var = 'A';
            while (index<(NOV / 2)) {
                //Vertical Mapping
                if (FTptr->i1 == FTptr->i2) {
                    if (checkChangesY(index, FTptr->i1, FTptr->i1 + FTptr->iSize - 1) == false) {//cout<<"\n at index is:"<<grayY[MTptr->i].at(index);
                        if (grayY[FTptr->i1].at(index) == '0') {
//                            qDebug() << (char)(var + index) << "'";
                            str.append((const QChar)(var + index));
                            str.append("'");
                        }
                        else {
//                            qDebug() << (char)(var + index);
                            str.append((const QChar)(var + index));
                        }
                    }

                }
                //Horizontal Mapping
                else if (FTptr->j1 == FTptr->j2) {
                    bool changeSide1 = false, changeSide2 = false;
                    if (checkChangesY(index, FTptr->i1, FTptr->i1 + FTptr->iSize - 1) == false) {
                        changeSide1 = true;
                    }
                    if (checkChangesY(index, FTptr->i2 - FTptr->iSize + 1, ROW - 1) == false) {
                        changeSide2 = true;
                    }
                    if (changeSide1&&changeSide2) {
                        if (grayY[FTptr->i1].at(index) == grayY[FTptr->i2].at(index)) {
                            if (grayY[FTptr->i1].at(index) == '0') {
//                                qDebug() << (char)(var + index) << "'";
                                str.append((const QChar)(var + index));
                                str.append("'");
                            }
                            else {
//                                qDebug() << (char)(var + index);
                                str.append((const QChar)(var + index));
                            }
                        }
                    }

                }
                index++;
            }

            index = 0;
            var = 'A' + (NOV / 2);
            while (index< ((NOV % 2 == 0) ? (NOV / 2) : ((NOV / 2) + 1))) {
                //Vertical mapping
                if (FTptr->i1 == FTptr->i2) {

                    bool changeSide1 = false, changeSide2 = false;
                    if (checkChangesX(index, FTptr->j1, FTptr->j1 + FTptr->jSize - 1) == false) {
                        changeSide1 = true;
                    }
                    if (checkChangesX(index, FTptr->j2 - FTptr->jSize + 1, COLUMN - 1) == false) {
                        changeSide2 = true;
                    }
                    if (changeSide1&&changeSide2) {
                        if (grayX[FTptr->j1].at(index) == grayX[FTptr->j2].at(index)) {
                            if (grayX[FTptr->j1].at(index) == '0') {
//                                qDebug() << (char)(var + index) << "'";
                                str.append((const QChar)(var + index));
                                str.append("'");
                            }
                            else {
//                                qDebug() << (char)(var + index);
                                str.append((const QChar)(var + index));
                            }
                        }
                    }
                }
                //Horizontal Mapping
                else if (FTptr->j1 == FTptr->j2) {
                    if (checkChangesX(index, FTptr->j1, FTptr->j1 + FTptr->jSize - 1) == false) {//cout<<"\n at index is:"<<grayY[MTptr->i].at(index);
                        if (grayX[FTptr->j1].at(index) == '0') {
//                            qDebug() << (char)(var + index) << "'";
                            str.append((const QChar)(var + index));
                            str.append("'");
                        }
                        else {
//                            qDebug() << (char)(var + index);
                            str.append((const QChar)(var + index));
                        }
                    }


                }
                index++;
            }
//            qDebug() << "+";
            str.append("+");
            FTptr = FTptr->next;
        }

    }
    else {
        FTptr = FTtop;
        while (FTptr != NULL) {
            int index = 0;
            char var = 'A';
            cout << "(";str.append("(");
            while (index<(NOV / 2)) {
                //Vertical Mapping
                if (FTptr->i1 == FTptr->i2) {
                    if (checkChangesY(index, FTptr->i1, FTptr->i1 + FTptr->iSize - 1) == false) {//cout<<"\n at index is:"<<grayY[MTptr->i].at(index);
                        if (grayY[FTptr->i1].at(index) == '1') {
//                            qDebug() << (char)(var + index) << "'";
                            str.append((const QChar)(var + index));
                            str.append("'");
                        }
                        else {
//                            qDebug() << (char)(var + index);
                            str.append((const QChar)(var + index));
                        }/*qDebug() << "+";*/str.append("+");
                    }

                }
                //Horizontal Mapping
                else if (FTptr->j1 == FTptr->j2) {
                    bool changeSide1 = false, changeSide2 = false;
                    if (checkChangesY(index, FTptr->i1, FTptr->i1 + FTptr->iSize - 1) == false) {
                        changeSide1 = true;
                    }
                    if (checkChangesY(index, FTptr->i2 - FTptr->iSize + 1, ROW - 1) == false) {
                        changeSide2 = true;
                    }
                    if (changeSide1&&changeSide2) {
                        if (grayY[FTptr->i1].at(index) == grayY[FTptr->i2].at(index)) {
                            if (grayY[FTptr->i1].at(index) == '1') {
//                                qDebug() << (char)(var + index) << "'";
                                str.append((const QChar)(var + index));
                                str.append("'");
                            }
                            else {
//                                qDebug() << (char)(var + index);
                                str.append((const QChar)(var + index));
                            }/*qDebug() << "+";*/str.append("+");
                        }
                    }

                }
                index++;
            }

            index = 0;
            var = 'A' + (NOV / 2);
            while (index< ((NOV % 2 == 0) ? (NOV / 2) : ((NOV / 2) + 1))) {
                //Vertical mapping
                if (FTptr->i1 == FTptr->i2) {

                    bool changeSide1 = false, changeSide2 = false;
                    if (checkChangesX(index, FTptr->j1, FTptr->j1 + FTptr->jSize - 1) == false) {
                        changeSide1 = true;
                    }
                    if (checkChangesX(index, FTptr->j2 - FTptr->jSize + 1, COLUMN - 1) == false) {
                        changeSide2 = true;
                    }
                    if (changeSide1&&changeSide2) {
                        if (grayX[FTptr->j1].at(index) == grayX[FTptr->j2].at(index)) {
                            if (grayX[FTptr->j1].at(index) == '1') {
//                                qDebug() << (char)(var + index) << "'";
                                str.append((const QChar)(var + index));
                                str.append("'");
                            }
                            else {
                                cout << (char)(var + index);
                                str.append((const QChar)(var + index));
                            }/*qDebug() << "+";*/str.append("+");
                        }
                    }
                }
                //Horizontal Mapping
                else if (FTptr->j1 == FTptr->j2) {
                    if (checkChangesX(index, FTptr->j1, FTptr->j1 + FTptr->jSize - 1) == false) {//cout<<"\n at index is:"<<grayY[MTptr->i].at(index);
                        if (grayX[FTptr->j1].at(index) == '1') {
//                            qDebug() << (char)(var + index) << "'";
                            str.append((const QChar)(var + index));
                            str.append("'");
                        }
                        else {
//                            qDebug() << (char)(var + index);
                            str.append((const QChar)(var + index));
                        }/*qDebug() << "+"; */str.append("+");
                    }


                }
                index++;
            }cout << "\b";
            /*qDebug() << ")";*/str.append(")");
            FTptr = FTptr->next;
        }

    }return str;
}

QString KMap::printCorner() {
    QString str;
    if (SOP == 1) {
        if (MapCorner == true) {
            int index = 0;
            char var = 'A';
            while (index<(NOV / 2)) {
                if (grayY[0].at(index) == grayY[ROW - 1].at(index)) {
                    if (grayY[0].at(index) == '0') {
//                        qDebug() << (char)(var + index) << "'";
                        str.append((const QChar)(var + index));
                        str.append("'");
                    }
                    else {
//                       qDebug() << (char)(var + index);
                       str.append((const QChar)(var + index));
                    }
                }
                index++;
            }

            index = 0;
            var = 'A' + (NOV / 2);
            while (index< ((NOV % 2 == 0) ? (NOV / 2) : ((NOV / 2) + 1))) {
                if (grayX[0].at(index) == grayX[COLUMN - 1].at(index)) {
                    if (grayX[0].at(index) == '0') {
//                        qDebug() << (char)(var + index) << "'";
                        str.append((const QChar)(var + index));
                        str.append("'");
                    }
                    else {
//                        qDebug() << (char)(var + index);
                        str.append((const QChar)(var + index));
                    }
                }
                index++;
            }
        }
    }
    else {
        if (MapCorner == true) {
            int index = 0;
            char var = 'A';
            cout << "(";str.append("(");
            while (index<(NOV / 2)) {
                if (grayY[0].at(index) == grayY[ROW - 1].at(index)) {
                    if (grayY[0].at(index) == '1') {
//                        qDebug() << (char)(var + index) << "'";
                        str.append((const QChar)(var + index));
                        str.append("'");
                    }
                    else {
//                        qDebug() << (char)(var + index);
                        str.append((const QChar)(var + index));
                    }/*qDebug() << "+";*/str.append("+");
                }
                index++;
            }

            index = 0;
            var = 'A' + (NOV / 2);
            while (index< ((NOV % 2 == 0) ? (NOV / 2) : ((NOV / 2) + 1))) {
                if (grayX[0].at(index) == grayX[COLUMN - 1].at(index)) {
                    if (grayX[0].at(index) == '1') {
//                       qDebug() << (char)(var + index) << "'";
                       str.append((const QChar)(var + index));
                       str.append("'");
                    }
                    else {
//                        qDebug() << (char)(var + index);
                        str.append((const QChar)(var + index));
                    }/*qDebug()<< "+";*/str.append("+");
                }
                index++;
            }/*qDebug() << "\b";*/
          /* qDebug() << ")";*/str.append(")");
        }
    } return str;
}

void KMap::outputMap() {
    bool noMT = true, noFT = true;
    ofstream fo;
    fo.open("Map.txt", ios::out);
    if (MapCorner == true) {
        fo << -2;
    }
    else {
        fo << -3;
    }fo << '\n';
    MTptr = MTtop;
    while (MTptr != NULL) {
        noMT = false;
        fo << 15 << ' ' << MTptr->i << ' ' << MTptr->j << ' ' << MTptr->iSize << ' ' << MTptr->jSize << ' ';
        if (MTptr->next == NULL)fo << -1;
        else fo << 15;
        fo << '\n';
        MTptr = MTptr->next;
    }
    if (noMT == true) {
        fo << -1 << '\n';
    }
    FTptr = FTtop;
    while (FTptr != NULL) {
        noFT = false;
        fo << 15 << ' ' << FTptr->i1 << ' ' << FTptr->j1 << ' ' << FTptr->i2 << ' ' << FTptr->j2 << ' ' << FTptr->iSize << ' ' << FTptr->jSize << ' ';
        if (FTptr->next == NULL)fo << -1;
        else fo << 15;
        fo << '\n';
        FTptr = FTptr->next;
    }
    if (noFT == true) {

        fo << -1 << '\n';;
    }



    fo.close();
}

void KMap::inputMap()
{
    int row = ROW, column = COLUMN,
        side = 64, disBet = 10,
        startX = 800 / 2, startY = 600 / 2,
        startShiftFactorX = 1, startShiftFactorY = 1;


    for(int i = 0;i<row;i++) {
        for(int j = 0;j<column;j++) {
            Map[i][j] = 0;

        }
    }




    for (startShiftFactorX = 1;startShiftFactorX <= row / 2;startShiftFactorX++);
    for (startShiftFactorY = 1;startShiftFactorY <= column / 2;startShiftFactorY++);
    startShiftFactorX--;startShiftFactorY--;
    startX -= (side + disBet)*startShiftFactorY;
    startY -= (side + disBet)*startShiftFactorX;
    startX += disBet;
    startY += disBet;

    //cout<<"\nstartX : "<<startX<<" startY : "<<startY;

    while (1)
    {




        while (1)
        {


            if (1)
            {
                if (1)
                {



                    for (int i = 0;i<row;i++) {
                        for (int j = 0;j<column;j++) {
                            if (1) {
                                //cout<<"\n in box "<<i<<" "<<j;

                                if (Map[i][j]<2)
                                    Map[i][j]++;
                                else
                                    Map[i][j] = 0;
                            }
                        }
                    }
                }
            }

            if (1)
            {
                if (1)
                {
                    return;
                }
            }
        }





        for (int i = 0;i<row;i++) {
            for (int j = 0;j<column;j++) {

                if (Map[i][j] == 0)
                    ;
                else if (Map[i][j] == 2)
                    ;
                else
                    ;
            }
        }


    }


}

void KMap::setSOP(int i)
{
    SOP=i;
}

int KMap::GenerateBoxNO(int XCo, int YCo) {
    string grayNo = grayY[YCo] + grayX[XCo];
    //cout<<"\n gray :"<<grayNo;
    size_t grayNoLength = grayNo.length();
    int intNo = 0;
    for (int i = 0;i<grayNoLength;i++)
        if (grayNo.at(i) == '1')
            intNo += pow(2, (grayNoLength - 1) - i);
    //cout<<"\n In box no: "<<intNo;


    return intNo;
}

void KMap::set(int NOV, int ROW, int COLUMN, int side)
{
    this->NOV=NOV;
    this->ROW=ROW;
    this->COLUMN=COLUMN;
    this->side=side;

    MTtop = NULL; COtop = NULL; FTtop = NULL; FHTtop = NULL;
    initGray();
}

KMap::~KMap()
{
    qDebug("\n I am so destructed");
}

void KMap::checkCornerMap() {
    if (((Map[0][0] == SOP) || (Map[0][0] == 2)) && ((Map[0][COLUMN - 1] == SOP) || (Map[0][COLUMN - 1] == 2))
        && ((Map[ROW - 1][0] == SOP) || (Map[ROW - 1][0] == 2)) && ((Map[ROW - 1][COLUMN - 1] == SOP) || (Map[ROW - 1][COLUMN - 1] == 2))
        && !(Map[0][0] == 2 && Map[0][COLUMN - 1] == 2 && Map[ROW - 1][0] == 2 && Map[ROW - 1][COLUMN - 1] == 2)) {
        MapCorner = true;
    }
}
