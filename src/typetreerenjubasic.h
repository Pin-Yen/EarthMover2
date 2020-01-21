#ifndef TYPETREE_RENJUBASIC_H
#define TYPETREE_RENJUBASIC_H

#include "chesstype.h"
#include "stonestatus.h"
#include "typetree.h"

class TypeTreeRenjuBasic : public TypeTree {
 public:
    static TypeTreeRenjuBasic* getInstance();

 private:
    /** The singleton instance. */
    static TypeTreeRenjuBasic* singleton;

    /** Private constructor for singleton. */
    TypeTreeRenjuBasic();

    void setAnalyzeLength();

    SingleType typeAnalyze(StoneStatus *status, StoneStatus color, bool checkLevel);

};

#endif