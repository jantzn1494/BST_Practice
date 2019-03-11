


Name:   
Nathan Jantz 
-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL
functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of
zero!)

YES




Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what types / data members did you change and why?

I added leftSize and rightSize to the bst_node class. This was in order to keep track of the size of the subtrees on the left and right of each root.
-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  

bool remove(T & x)
bool insert(T & x)
static bst * from_sorted_vec(const std::vector<T> &a, int n)
-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime 
remained the same?

By only changing these data members through addition or subtraction.
-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


to_vector level of completion:  _____5______  


-----------------------------------------------
get_ith level of completion:  _____4______  

    How did you ensure O(h) runtime?

    ANSWER:

-----------------------------------------------
num_geq level of completion:  _____2______  

    How did you ensure O(h) runtime?

    ANSWER:

-----------------------------------------------
num_leq level of completion:  ______2______

    How did you ensure O(h) runtime?

    ANSWER:

-----------------------------------------------
num_range level of completion:  ______2______

    How did you ensure O(h) runtime?

    ANSWER:
I kept the bst in balance during all insertions and deletions
-----------------------------------------------
Implementation of size-balanced criteria according to 
the given guidelines (including bst_sb_work):

    Level of completion: _____4______


Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?


I wish that I had done more tests surrounding num_geq function because the range function formula depends on this function to work correctly.








