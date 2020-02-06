#ifndef TYPETREE_FREESTYLE_H_
#define TYPETREE_FREESTYLE_H_

#include "chesstype.h"
#include "enum.h"
#include "typetree.h"

class TypeTreeFreeStyle : public TypeTree {
 public:
    static TypeTreeFreeStyle* getInstance();

 private:
    /** The singleton instance. */
    static TypeTreeFreeStyle* singleton_;

    TypeTreeFreeStyle();

    void setAnalyzeLength();

    SingleType typeAnalyze(StoneStatus *status, StoneStatus color, bool checkLevel);

};

#endif