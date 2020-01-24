#ifndef TYPETREE_H_
#define TYPETREE_H_

#include <stddef.h>

#include "chesstype.h"
#include "enum.h"
#include "point.h"
#include "virtualboard.h"

class TypeTree {
 public:
    TypeTree();
    
    /**
     * Classifies the type of the given point.
     * Sets the classified result on analyzePoint.
     * @param analyzePoint The point to be analyzed.
     * @param neighborAccessor Controls which direction of the point is analyzed.
     * 
     */
    ChessType classify(Point *analyzePoint, VirtualBoard::NeighborIterator& neighborIterator);

    int analyzeLength() { return analyzeLength_; }
 protected:
    struct Node {
        // Next point occupied by:
        // 0: black, 1: white, 2:empty 3: bound
        Node *childNode_[4];

        ChessType type_;

        bool jump_, leaf_;

        Node(): jump_(false), leaf_(false) {
          for (int i = 0; i < 4; ++i)
            childNode_[i] = NULL;
        }

        ~Node() {
          for (int i = 0; i < 4; ++i) {
            if (childNode_[i] != NULL) {
              delete childNode_[i];
              childNode_[i] = NULL;
            }
          }
        }
    };

    virtual void setAnalyzeLength() = 0;

    /** 
     * Initialize the typetree.
     * Note: This is seperated from the constructor because it calls virtual methods.
     * See "Never Call Virtual Functions during Construction or Destruction.""
     */
    void init();

    /**
     * Trims the tree. Done in a deepth-first manner.
     * @param root The subtree starting from it is trimmed.
     * @return The common Chesstype of the subtree if it is trimmed, otherwise NULL. 
     */
    ChessType *cutSameResultChild(Node *root);

    /**
     * Grows the typetree from root. Initiates call to dfsGrowTree.
     */
    void plantTree();


    /**
     * Analyze the type of the given ChessType Array.
     * Used by dfsGrowTree during the construction of the tree.
     */
    virtual SingleType typeAnalyze(StoneStatus *status, StoneStatus color, bool checkLevel) = 0;
    
    int analyzeLength_;

 private:
    /** 
     * Grows the typetree in a deepth-first manner.
     * The initial call should be called with the root node, an all-empty status array,
     * the middle index of the status array, move=-1, connections set to 0 and blocks set
     * to false. 
     * @param node The current node.
     * @param status The stone status array
     * @param location The current position of the status array being branched
     * @param move The direction of the next move. -1 or 1
     * @param blackConnect The number of connected black stones on the side currently being 
     * analyzed. It is used to prevent generating a 5, for example : OOOOO*OOX-- ; --X  *OOOOO
     * @param whiteConnect Same as blackConnect
     * @param blackBlock True if the side currently being analyzed is already blocked by black stone.
     * @param whiteBlock Same as blackBlock
     */
    void dfsGrowTree(Node *node, StoneStatus *status, int location, int move,
                     int blackConnect, int whiteConnect, bool blackBlock, bool whiteBlock);

    Node* root_; /* The root of the tree */
};

#endif