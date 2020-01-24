#ifndef TYPETREE_RENJUBASIC_H_
#define TYPETREE_RENJUBASIC_H_

#include "chesstype.h"
#include "enum.h"
#include "typetree.h"

class TypeTreeRenjuBasic : public TypeTree {
 public:
    static TypeTreeRenjuBasic* getInstance();

 private:
    /** The singleton instance. */
    static TypeTreeRenjuBasic* singleton_;

    /** Private constructor for singleton. */
    TypeTreeRenjuBasic();

    void setAnalyzeLength();

    SingleType typeAnalyze(StoneStatus *status, StoneStatus color, bool checkLevel);

};

#endif