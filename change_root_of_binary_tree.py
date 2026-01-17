# Definition for a Node.
class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None


class Solution:
    def flipBinaryTree(self, root: Node, leaf: Node) -> Node:
        """
        Flips a binary tree to make the given leaf node the new root.

        Args:
            root: The current root of the binary tree
            leaf: The leaf node that will become the new root

        Returns:
            The new root of the flipped tree (the original leaf node)
        """

        curr_node = leaf
        parent_node = curr_node.parent

        while curr_node != root:

            grand_parent_node = parent_node.parent

            if curr_node.left:
                curr_node.right = curr_node.left

            curr_node.left = parent_node
            parent_node.parent = curr_node
            

            if curr_node == parent_node.left:
                parent_node.left = None
            elif curr_node == parent_node.right:
                parent_node.right = None

            curr_node = parent_node
            parent_node = grand_parent_node
        
        leaf.parent = None

        return leaf
