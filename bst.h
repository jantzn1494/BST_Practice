#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>

template <typename T>
class bst {

  private: 
    struct bst_node {
      T      val;
      bst_node *left;
      int leftSize;
      bst_node *right;
      int rightSize;
      bst_node ( const T & _val = T{}, bst_node * l = nullptr, bst_node *r = nullptr, int size = 0)
        : val { _val },  left { l }, right {r}, leftSize{size}, rightSize{size} 
      { }

bst_node * maxSubtree(){
    int nL = left->leftSize + left->rightSize + 1;
    int nR = right->leftSize + right->rightSize + 1;
    if(nL > nR){ return left; }
    else{ return right; }
}

bool is_balanced(bst_node * root){
    bool balanced;
    int maxN;
    int minN;
    bst_node * max;
    bst_node * min;
    
    max = root->maxSubtree();

    if(max == left){ min = right; }
    else{ min = left; }
    
    maxN = max->leftSize + max->rightSize + 1;
    minN = min->leftSize + min->rightSize + 1;

    if (maxN <= ((2 * minN) + 1)){ return true; }
    else{ return false; }
}

void makeVector(bst_node * root, std::vector<T> * elements){
    if (root == nullptr){return;}
    else{
        makeVector(root->left, elements);
        elements->push_back(root->val);
        makeVector(root->right, elements);
        return;
    }
}

bst_node * balanceHelper(const std::vector<T> &a, int low, int hi){
    int m;
    bst_node *root;

    if(hi < low){ return nullptr; }

    else{
        m = (low+hi)/2;
        root = new bst_node(a[m]);
        //add new left node
        root->left  = balanceHelper(a, low, m-1);
        if(root->left != nullptr){
            root->leftSize = root->leftSize + 1;
        }
        //add new right node
        root->right = balanceHelper(a, m+1, hi);
        if(root->right != nullptr){
            root->leftSize = root->leftSize + 1;
        }
        return root;
    }

}

void balance(bst_node * root){
        std::vector<T> * elements;
        makeVector( root, elements);
        root = balanceHelper(*elements, 0, (elements->size() - 1));
        return;
}

    };



  public:
    // constructor:  initializes an empty tree
    bst(){
      root = nullptr;
    }

  private:
    // helper function which recursively deallocates nodes
    //   in a tree.
    static void delete_nodes(bst_node *r){
      if(r==nullptr) return;
      delete_nodes(r->left);
      delete_nodes(r->right);
      delete r;
    }

  public:
    // destructor
    ~bst() {
      delete_nodes(root);
    }

  private:

/**
 * function:  insert()
 * desc:      recursive helper function inserting x into
 *            binary search tree rooted  at r.
 *
 * returns:   pointer to root of tree after insertion.
 *
 * notes:     if x is already in tree, no modifications are made.
 */
    static bst_node * _insert(bst_node *r, T & x, bool &success){
      if(r == nullptr){
        success = true;
        return new bst_node(x, nullptr, nullptr);
      }

      if(r->val == x){
        success = false;
        return r;
      }
      if(x < r->val){
        r->left = _insert(r->left, x, success);
        if(success == true){
            r->leftSize = r->leftSize + 1;
        }
        if(r->rightSize != 0){
            if(!(r->is_balanced(r))){
                r->balance(r);
            }
        }
        return r;
      }
      else {
        r->right = _insert(r->right, x, success);
        if(success == true){
            r->rightSize = r->rightSize + 1;
        }
        if(r->leftSize != 0){
            if(!(r->is_balanced(r))){
                r->balance(r);
            }
        }
        return r;
      }
    }


  public:
  /**
   * function:  insert
   * desc:      inserts x into BST given by t.  Note that
   *            a BST stores a SET -- no duplicates.  Thus,
   *            if x is already in t when call made, no 
   *            modifications to tree result.
   *
   * note:      helper function does most of the work.
   *
   */
   bool insert(T & x){
      bool success;
      root = _insert(root, x, success);
      return success;
   }

/**
 * function:  contains()
 * desc:      returns true or false depending on whether x is an
 *            element of BST (calling object)
 *
 */
    bool contains(const T & x){
      bst_node *p = root;

      while(p != nullptr){

        if(p->val == x)
          return true;
        if(x < p->val){
          p = p->left;
        }
        else
          p = p->right;
      }
      return false;  
    }

  private:
    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _min_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->left != nullptr)
        r = r->left;
      return r;
    }

    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _max_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->right != nullptr)
        r = r->right;
      return r;
    }

    // recursive helper function for node removal
    //   returns root of resulting tree after removal.
static bst_node * _remove(bst_node *r, T & x, bool &success){
    bst_node *tmp;
    bool sanity;

    if(r==nullptr){
        success = false;
        return nullptr;
    }
    if(r->val == x){
        success = true;

        if(r->left == nullptr){
            tmp = r->right;
            delete r;
            r->rightSize = r->rightSize-1;
            return tmp;
        }
        if(r->right == nullptr){
            tmp = r->left;
            delete r;
            r->leftSize = r->leftSize - 1;
            return tmp;
        }
        // if we get here, r has two children
        r->val = _min_node(r->right)->val;
        r->right = _remove(r->right, r->val, sanity);
        if(!sanity)
            std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
            return r;
    }
    if(x < r->val){
        r->left = _remove(r->left, x, success);
    }
    else {
        r->right = _remove(r->right, x, success);
    }

    return r;

}

  public:

    bool remove(T & x){
      bool success;
      root = _remove(root, x, success);
      return success;
    }


  private:
    // recursive helper function to compute size of
    //   tree rooted at r
    static int _size(bst_node *r){
      if(r==nullptr) return 0;
      return _size(r->left) + _size(r->right) + 1;
    }

  public: 
    int size() {
      return _size(root);
    }

  private:

    static int _height(bst_node *r){
      int l_h, r_h;

      if(r==nullptr) return -1;
      l_h = _height(r->left);
      r_h = _height(r->right);
      return 1 + (l_h > r_h ? l_h : r_h);
    }

  public:

    int height() {
      return _height(root);
    }

    bool min(T & answer) {
      if(root == nullptr){
        return false;
      }
      answer = _min_node(root)->val;
      return true;
    }

    T max() {
      return _max_node(root)->val;
    }

    /******************************************
     *
     * "stubs" for assigned TODO functions below 
     *
     *****************************************/
void to_vectorHelper(bst_node * root, std::vector<T> * elements){
    if (root == nullptr){return;}
    else{
        to_vectorHelper(root->left, elements);
        elements->push_back(root);
        to_vectorHelper(root->right, elements);
        return;
    }
}
    // TODO
    std::vector<T> * to_vector() {
        std::vector<T> * elements;
        to_vectorHelper( root, elements);
        return elements;
    }

void get_ithHelper(bst_node * root, int left, int i, T &x){
    int n = root->leftSize + root->rightSize + 1 + left;
    if(i == (n - root->rightSize)){
        x = root->val;
        return;
    }
    else if(i < (n - root->rightSize)){
        get_ithHelper(root->left, left, i, x);
        return;
    }
    else{
        get_ithHelper(root->right, (left + root->leftSize + 1), i, x);
        return;
    }
}
    /* TODO
     * Function:  get_ith
     * Description:  determines the ith smallest element in t and
     *    "passes it back" to the caller via the reference parameter x.  
     *    i ranges from 1..n where n is the number of elements in the 
     *    tree.
     *
     *    If i is outside this range, false is returned.
     *    Otherwise, true is returned (indicating "success").
     *
     * Runtime:  O(h) where h is the tree height
     */
bool get_ith(int i, T &x) {
    int n = root->leftSize + root->rightSize + 1;
    if(i < 1 || i > n){ return false; }
    else{
        get_ithHelper(root, 0, i, x);
        return true;
    }
}


    bool get_ith_SLOW(int i, T &x) {
      int n = size();
      int sofar=0;

      if(i < 1 || i > n) 
        return false;

      _get_ith_SLOW(root, i, x, sofar);
      return true;
    }

int num_geqHelper(bst_node * root, int right, const T & x) {
    int total;
    int n = right;
    if(root->val == x){
        total = root->rightSize + 1 + n;
        return total;
    }
    else if( root->val > x){ 
        n = root->rightSize + 1;
        total = num_geqHelper( root->left, n, x);
        return total;
    }
    else{
        total = num_geqHelper( root->right, n, x);
        return total;
    }
}

    /* TODO
     * Function:  num_geq
     * Description:  returns the number of elements in tree which are 
     *       greater than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     */
int num_geq(const T & x) {
    int total;
    if(root == nullptr){ return  0; }
    else{
        total = num_geqHelper(root, 0, x);
        return total;
    }
}

    /*
     * function:     num_geq_SLOW
     * description:  same functionality as num_geq but sloooow (linear time)
     *
     */
    int num_geq_SLOW(const T & x) {
      return _num_geq_SLOW(root, x);
    }
    
int num_leqHelper(bst_node * root, int left, const T & x) {
    int total;
    int n = left;
    if(root->val == x){
        total = root->leftSize + 1 + n;
        return total;
    }
    else if( root->val > x){ 
        total = num_geqHelper( root->left, n, x);
        return total;
    }
    else{
        n = root->leftSize + 1;
        total = num_geqHelper( root->right, n, x);
        return total;
    }
}
    /* TODO
     * Function:  num_leq
     * Description:  returns the number of elements in tree which are less
     *      than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
int num_leq(const T &x) {
    int total;
    if(root == nullptr){ return  0; }
    else{
        total = num_leqHelper(root, 0, x);
        return total;
    }
}

    /*
     * function:     num_leq_SLOW
     * description:  same functionality as num_leq but sloooow (linear time)
     *
     */
    int num_leq_SLOW(const T & x) {
      return _num_leq_SLOW(root, x);
    }

    /* TODO
     * Function:  num_range
     * Description:  returns the number of elements in tree which are
     *       between min and max (inclusive).
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
int num_range(const T & min, const T & max) {
    int range;
    if(root == nullptr){ return 0; }
    else{
        range = num_geq(min) - num_geq(max) + 1;
        return range;
    }
}

    /*
     * function:     num_range_SLOW
     * description:  same functionality as num_range but sloooow (linear time)
     *
     */
    int num_range_SLOW(const T & min, const T & max) {
      return _num_range_SLOW(root, min, max);
    }

  private:


    static void _get_ith_SLOW(bst_node *t, int i, T &x, int &sofar) {
      if(t==nullptr) 
        return;
      _get_ith_SLOW(t->left, i, x, sofar);

      if(sofar==i) 
        return;
      sofar++;
      if(sofar==i) {
        x = t->val;
        return;
      }
      _get_ith_SLOW(t->right, i, x, sofar);
    }

    static int _num_geq_SLOW(bst_node * t, const T & x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

      if(t->val >= x)
        total++;
      return total;
    }

    static int _num_leq_SLOW(bst_node *t, const T &x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

      if(t->val <= x)
        total++;
      return total;
    }

    static int _num_range_SLOW(bst_node *t, const T &min, const T &max) {
      int total;

      if(t==nullptr) return 0;
      total =_num_range_SLOW(t->left, min, max) + 
                _num_range_SLOW(t->right, min, max);

      if(t->val >= min && t->val <= max)
        total++;
      return total;
    }





  private:
    static void indent(int m){
      int i;
      for(i=0; i<m; i++)
        std::cout << "-";
    }

    static void _inorder(bst_node *r){
      if(r==nullptr) return;
      _inorder(r->left);
      std::cout << "[ " << r->val << " ]\n";
      _inorder(r->right);
    }

    static void _preorder(bst_node *r, int margin){
      if(r==nullptr) {
        indent(margin);
        std::cout << " nullptr \n";
      } 
      else {
        indent(margin);
        std::cout << "[ " << r->val << " ]\n";
        _preorder(r->left, margin+3);
        _preorder(r->right, margin+3);
      }
    }

    /* 
     * TODO:
     * Complete the (recursive) helper function for the post-order traversal.
     * Remember: the indentation needs to be proportional to the height of the node!
     */
static void _postorder(bst_node *r, int margin){
    if(r==nullptr){
        indent(margin);
        std::cout << "nullptr\n";
    }
    else{
        indent(margin);
        _postorder(r->left, margin+3);
        _postorder(r->right, margin+3);
        std::cout << "[ " << r->val << " ]\n";
    }
}

  public:
    void inorder() {
      std::cout << "\n======== BEGIN INORDER ============\n";
      _inorder(root);
      std::cout << "\n========  END INORDER  ============\n";
    }


    void preorder() {

      std::cout << "\n======== BEGIN PREORDER ============\n";
      _preorder(root, 0);
      std::cout << "\n========  END PREORDER  ============\n";

    }

    // indentation is proportional to depth of node being printed
    //   depth is #hops from root.
    void postorder() {

      std::cout << "\n======== BEGIN POSTORDER ============\n";
      _postorder(root, 0);
      std::cout << "\n========  END POSTORDER  ============\n";

    }

  private:
    /* 
     * Recursive  helper function _from_vec, used by
     * bst_from_sorted_arr(...). The function must return a sub-tree that is
     * perfectly balanced, given a sorted array of elements a.
     */
static bst_node * _from_vec(const std::vector<T> &a, int low, int hi){
    int m;
    bst_node *root;

    if(hi < low){ return nullptr; }

    else{
        m = (low+hi)/2;
        root = new bst_node(a[m]);
        //add new left node
        root->left  = _from_vec(a, low, m-1);
        if(root->left != nullptr){
            root->leftSize = root->leftSize + 1;
        }
        //add new right node
        root->right = _from_vec(a, m+1, hi);
        if(root->right != nullptr){
            root->leftSize = root->leftSize + 1;
        }
        return root;
    }

}

  public:
static bst * from_sorted_vec(const std::vector<T> &a, int n){

    bst * t = new bst();
    t->root = _from_vec(a, 0, n-1);
    return t;
}

int num_leavesHelper(bst_node *root) {
    int leaves;
    if(root==nullptr){ return 0; }
    else if( (root->left == nullptr) && (root->right == nullptr) ) { return 1; }
    else{
        leaves = num_leavesHelper(root->right) + num_leavesHelper(root->left);
        return leaves;
    }
}
    // TODO:  num_leaves
    //   Hint:  feel free to write a helper function!!
int num_leaves() {
    int leaves;
    leaves = num_leavesHelper(root);
    return leaves;
}

int num_at_levelHelper(bst_node * root, int level) {
    int nodes;
    if(root == nullptr){ return 0; }
    else if( level > 0){
        nodes = num_at_levelHelper(root->left, level-1) + num_at_levelHelper(root->right, level-1);
        return nodes;
    }
    else if( level == 0){ return 1; }
}
    // TODO:  num_at_level
    // description:  returns the number of nodes at specified level
    //   in tree.
    // note:  the root is at level 0.
    // Hint:  recursive helper function?
int num_at_level(int level) {
    int nodes;
    nodes = num_at_levelHelper(root, level);
    return nodes;
}


  private:
    bst_node *root;


}; // end class bst

#endif
