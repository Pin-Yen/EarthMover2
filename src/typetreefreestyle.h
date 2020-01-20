#ifndef TYPETREE_FREESTYLE_H
#define TYPETREE_FREESTYLE_H

#include "chesstype.h"
#include "stonestatus.h"
#include "typetree.h"

class TypeTreeFreeStyle : public TypeTree {
 public:
    static TypeTreeFreeStyle* getInstance();

 private:
    /** The singleton instance. */
    static TypeTreeFreeStyle* singleton;

    void setAnalyzeLength();

    SingleType typeAnalyze(StoneStatus *status, StoneStatus color, bool checkLevel);

};

#endif