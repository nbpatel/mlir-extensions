#pragma once

#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/Optional.h>
#include <llvm/ADT/simple_ilist.h>
#include <llvm/Support/Allocator.h>

namespace mlir
{
struct LogicalResult;
class Operation;
class Region;
}

namespace plier
{

class MemorySSA
{
public:
    struct Node;

    Node* createDef(mlir::Operation* op, Node* arg);
    Node* createUse(mlir::Operation* op, Node* arg);
    Node* createPhi(mlir::Operation* op, llvm::ArrayRef<Node*> args);


    void eraseNode(Node* node);

    Node* getRoot();

    MemorySSA() = default;
    MemorySSA(const MemorySSA&) = delete;
    MemorySSA(MemorySSA&&) = default;

    Node* getNode(mlir::Operation* op) const;

    auto& getNodes()
    {
        return nodes;
    }

    void print(Node* node, llvm::raw_ostream& os);

private:
    Node* root = nullptr;
    llvm::DenseMap<mlir::Operation*, Node*> nodesMap;
    llvm::BumpPtrAllocator allocator;
    llvm::simple_ilist<Node> nodes;

    enum class NodeType
    {
        Root,
        Def,
        Use,
        Phi
    };
    Node* createNode(mlir::Operation* op, NodeType type, llvm::ArrayRef<Node*> args);
};

llvm::Optional<plier::MemorySSA> buildMemorySSA(mlir::Region& region);
}
