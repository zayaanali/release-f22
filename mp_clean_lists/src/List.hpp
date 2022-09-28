
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>

List<T>::List() { 
  // @TODO: graded in MP3.1
    
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1  
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  // @todo Graded in MP3.1
  ListNode* temp;
  while (length_ > 0) {
    temp = head_; // contains address of the head
    head_ = head_->next; // head = to next node
    delete temp;
    length_--;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  
  ListNode * newNode = new ListNode(ndata); // create new node

  if (head_ == NULL) { // if the list is empty
    newNode->prev = NULL;
    newNode->next = NULL;
    head_ = newNode;
    tail_ = newNode;
  } else { // the list is not empty
    newNode->next = head_;
    newNode->prev = NULL;
    head_->prev = newNode;
    head_ = newNode;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);
  if (tail_ == NULL) { // the list is empty
    head_ = newNode;
    newNode->prev = NULL;
    newNode->next = NULL;
    tail_ = newNode;
  } else {
    newNode->prev = tail_;
    newNode->next = NULL;
    tail_->next = newNode;
    tail_ = newNode;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  ListNode * temp; // tail for the first part of the list
  // this loop will result in curr = head node at splitpoint
  
  if (splitPoint==0) return start;
  if (splitPoint > length_) return NULL;

  for (int i = 0; i < splitPoint && curr != NULL; i++) { // curr = 1 past splitPoint
    curr = curr->next;
  }

  if (curr==NULL) return NULL; // if the new head is NULL return NULL
  // set the tail of the first list to NULL
  temp = curr->prev;
  temp->next = NULL; 

  // set the prev of list2 head to NULL
  curr->prev = NULL;
  
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */

template <typename T>
void List<T>::tripleRotate() {
  
  // @todo Graded in MP3.1
  int endRotate = length_ - (length_%3); // sets end of rotating function
  if (endRotate < 3) return;
  ListNode *node1, *node2, *node3, *nextGroup, *prevGroup;
  node1=head_;
  node2=head_->next;
  node3=head_->next->next;

  head_ = node2;
  head_->prev=NULL;

  for (int i=0; i<endRotate; i+=3) {
    nextGroup=node3->next;
    
    node2->next = node3;
    node3->next = node1;
    if ((i+3)>=endRotate) {node1->next = nextGroup; } else { node1->next = nextGroup->next; }

    node1->prev = node3;
    node3->prev = node2;
    if (i==0) { node2->prev = NULL; } else { node2->prev = prevGroup; }
  
    if (nextGroup!=NULL) nextGroup->prev = node1;
    prevGroup = node1;
    if (nextGroup!=NULL) { node1 = nextGroup; } else { continue; }
    if (nextGroup!=NULL) node2 = nextGroup->next;
    if (nextGroup->next!=NULL) node3 = nextGroup->next->next;
  }
  node1=head_;
  while (node1->next!=NULL) {
    node1=node1->next;
  }
  tail_ = node1;
  
  
  
  /*
  int i=0;
  ListNode *oldHead = head_; // last num in rotated ver
  ListNode *nextGroup, *midHead;

  // keep rotating until reach the endRotate
  while (i<endRotate) {
    // first group
    if (i==0) {
      nextGroup =  head_->next->next->next;
      head_ = head_->next; // set head node
    
      // first node pointers
      head_->prev = NULL; // head prev set to NULL
      // head next already pointing to the correct place
      
      // second node pointers
      head_->next->next = oldHead;
      head_->next->prev = head_;

      // 3rd node pointers
      if (i+6>length_) 
        { oldHead->next=nextGroup; nextGroup->prev=oldHead; i+=3; continue;}
      if (nextGroup!=NULL) { oldHead->next = nextGroup->next; nextGroup->next->prev = oldHead; }
      if (nextGroup==NULL) oldHead->next = NULL;
      oldHead->prev = head_->next;

      if (nextGroup == NULL) tail_=oldHead;
      
    }

    // other groups
    if (i!=0) { // not in the first group
      oldHead = nextGroup;
      midHead = nextGroup->next; // head of this group
      nextGroup = nextGroup->next->next->next; // set next group
      
      // first node pointers
      // next and prev already set

      
      midHead->next->next = oldHead; // 2nd node pointers
      midHead->next->prev = midHead;

      oldHead->prev = midHead->next; // 3rd node pointers. NextGroup here does not refer to next group head
      if (i+6>length_) 
        { oldHead->next=nextGroup; nextGroup->prev=oldHead; i+=3; continue;}
      if (nextGroup!=NULL) { oldHead->next = nextGroup->next; nextGroup->next->prev = oldHead; }
      
      if (nextGroup==NULL) oldHead->next = NULL;
      
      if (nextGroup == NULL) tail_=midHead->next->next;
      
    }
    i+=3;
  }
  */
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */


// helper function to swap pointers
template <typename T>
void List<T>::swapPointers(ListNode *&nodeA, ListNode *&nodeB, int z) {
  ListNode *nodeL = nodeA;
  ListNode *nodeR = nodeB;
  
  ListNode *tempNext = nodeL->next;
  ListNode *tempPrev = nodeL->prev;

  // swap node pointers
  nodeL->next = nodeR->next;
  nodeL->prev = nodeR->prev;
  nodeR->next = tempNext;
  nodeR->prev = tempPrev;

  if (z==1) { nodeL->prev = nodeR; nodeR->next = nodeL; }


  // change pointers around node
  if (nodeR->prev!=NULL) nodeR->prev->next = nodeR;
  if (nodeR->next!=NULL) nodeR->next->prev = nodeR;
  if (nodeL->next!=NULL) nodeL->next->prev = nodeL;
  if (nodeL->prev!=NULL) nodeL->prev->next = nodeL;

}


template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  int subLength=1;
  ListNode *start = startPoint;
  ListNode *end = endPoint;
  if (startPoint==NULL || endPoint==NULL) return;
  if (startPoint==endPoint) return;

  while (start!=end) { subLength++; start=start->next; }

  ListNode *sP = startPoint;
  ListNode *eP = endPoint;
  ListNode *left = sP->next;
  ListNode *right = eP->prev;
  ListNode *tempL, *tempR;
  int midLoops = (subLength-2)/2;
  
  // start and end. assign vars to avoid weird pointer issues
  if (subLength==2) {swapPointers(startPoint, endPoint, 1); endPoint->next = startPoint; }
  else { swapPointers(startPoint, endPoint, 0); }
  eP = startPoint;
  sP = endPoint;

  // assign head/tail
  if (startPoint == head_ && endPoint == tail_) { head_ = sP; tail_ = eP; tail_->next = NULL; }
  if (startPoint != head_ && endPoint == tail_) {tail_ = eP; tail_->next = NULL; }
  if (startPoint == head_ && endPoint != tail_) { head_ = sP; }
  
  // middle
  for (int i=0; i<midLoops; i++) {
    // swap pointers of the middle nodes
    if (subLength%2==0 && i==midLoops-1) { swapPointers(left, right, 1); }
    else { swapPointers(left, right, 0); }
    
    //update left and right pointers. Temp vars since had been swapped
    tempL = right->next;
    tempR = left->prev;
    left=tempL;
    right=tempR;   
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
typename List<T>::ListNode * List<T>::findNth(int n) {
  if (n <=0) return NULL;
  ListNode *cur = head_;
  for (int i=1; i<n; i++) { cur = cur->next; }
  return cur;
}

template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  int nStart=0;
  int nEnd=0;
  ListNode *startPoint, *endPoint;

  while (nEnd != length_) {
    // update start and end points
    nStart=nEnd+1;
    nEnd+=n;
    if (nEnd > length_) nEnd=length_;
    
    // get pointers to start and end nodes
    startPoint = findNth(nStart);
    endPoint = findNth(nEnd);

    // reverse the nodes
    reverse(startPoint, endPoint);
    
  }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
void List<T>::insertNode(ListNode *previous, ListNode *newNode) {
  
  ListNode *nextNode = previous->next;
  ListNode *prevNode = previous;

  // update prev node next pointer
  if (prevNode!=NULL) prevNode->next = newNode;

  // update new node pointers (next and prev)
  newNode->prev = prevNode;
  newNode->next = nextNode;

  // update next node prev pointer
  if (nextNode!=NULL) nextNode->prev = newNode;

}

template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  if (first==NULL && second==NULL) return NULL;
  if (first==NULL) return second;
  if (second==NULL) return first;

  ListNode *headPtr;
  
  ListNode *firstPtr = first;
  ListNode *secondPtr = second;
  ListNode *bodyPtr;
  ListNode *temp;
  ListNode *otherListPtr;
  ListNode *tailPtr;
  
  // changing head to the smallest value of either of the lists
  if (firstPtr->data < secondPtr->data) 
    { headPtr = firstPtr; otherListPtr = secondPtr; }
  else
    { headPtr = secondPtr; otherListPtr=firstPtr; }
  headPtr->prev = NULL;

  // changing body
  if (headPtr->next==NULL) tailPtr = headPtr;
  bodyPtr = headPtr->next;
  
  while (otherListPtr != NULL && bodyPtr!=NULL) {
    
    // insert node if node from other list is larger
    
    if (otherListPtr->data < bodyPtr->data) 
      { temp=otherListPtr->next; insertNode(bodyPtr->prev, otherListPtr); otherListPtr = temp; continue; }
    
    if (otherListPtr->data == bodyPtr->data)
      { temp=otherListPtr->next; insertNode(bodyPtr->prev, otherListPtr); otherListPtr = temp; continue; }
    
    if (bodyPtr->next==NULL) tailPtr=bodyPtr;
    bodyPtr=bodyPtr->next;
  }

  // add any remaining nodes
  while (otherListPtr!=NULL) {
    temp = otherListPtr->next;
    insertNode(tailPtr, otherListPtr);
    otherListPtr = temp;
    tailPtr = tailPtr->next;
  }
  
  
  return headPtr;
  
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  
  /* ---- Base case (list cannot be split) ----*/
  if (chainLength==1 ||chainLength==0) return start;

  /* ---- Recursive case ----*/
  // split list in half
  ListNode *list1 = start;
  ListNode *list2 = split(start, chainLength/2);

  // sort both halves
  list1 = mergesort(list1, chainLength/2);
  list2 = mergesort(list2, chainLength-(chainLength/2)); // if list is odd
  // merge halves together and return
  return merge(list1, list2);
}
