#ifndef KMAP_H
#define KMAP_H

#define MROW 16
#define MCOLUMN 16

#include <string>
#include <QDebug>
#include "table.h"
class KMap : protected Table {
public:
    int Map[MROW][MCOLUMN];
    string grayX[MCOLUMN], grayY[MROW];
    int NOV,ROW,COLUMN,side,SOP;
    bool MapCorner;
public:
    KMap();
    void TheMapIs();
    void MapGenerator();
    void FringeMapGenerator_Vertical();
    void FringeMapGenerator_Horizontal();
    void redundancyEliminator(int, int, int, int);
    void FringeRedundancyEliminator_Vertical(int, int, int, int, int, int);
    void FringeRedundancyEliminator_Horizontal(int, int, int, int, int, int);
//	void displayMap() {
//		MTptr = MTtop;
//		while (MTptr != NULL) {
//			cout << "\nA map found from location " << MTptr->i << " " << MTptr->j << " of size " << MTptr->iSize << " " << MTptr->jSize;
//			MTptr = MTptr->next;
//		}
//	}
//	void FringeDisplayMap() {
//		FTptr = FTtop;
//		while (FTptr != NULL) {
//			cout << "\nA map found from location " << FTptr->i1 << " " << FTptr->j1 << " and" << FTptr->i2 << " " << FTptr->j2 << " of size " << FTptr->iSize << " " << FTptr->jSize;
//			FTptr = FTptr->next;
//		}
//	}

    void TheEliminator();
    void TheEliminatorSecondary();
    void cleaner();
    void cornerMap();
    void cleanerSecondary();
public:
    void ExpressionGen();

    bool checkChangesY(int index, int start, int end);
    bool checkChangesX(int index, int start, int end);


    void initGray();
    void initYGray();
    void initXGray();
    QString printExp();
    QString printMT();
    QString printFT();
    QString printCorner();
    void outputMap();
    void outputMTMap();
    void outputFTMap();
    void checkCornerMap();

    void inputMap();
    void setSOP(int i);
    int GenerateBoxNO(int XCo, int YCo);
    void set(int NOV,int ROW,int COLUMN,int side);
    ~KMap();



};
#endif // KMAP_H
