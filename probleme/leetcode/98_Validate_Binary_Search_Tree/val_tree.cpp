

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
 
class Solution {
public:

    bool valid(TreeNode* root, TreeNode* higher, TreeNode* lower)
    {
        if(!root)
            return true;
        if(higher && root -> val <= higher -> val)
            return false;
        if(lower && root -> val >= lower -> val)
            return false;

        return valid(root -> left, higher, root) &&
               valid(root -> right, root, lower);

        //So the logic is: 

        //Does the current root has to be higher then any other root? If so, 
        //let's check if it is    (and with lower too)
        //
        //And if it's both greater and lower then the roots it has to be comp to
        //It's a valid root and we go onto the next one

        //The higher and lower roots are the most recent ancestors
    }

    bool isValidBST(TreeNode* root) {
        
        return valid(root, nullptr, nullptr);
    }
};
