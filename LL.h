template <typename T>
class LL 
{
    struct node 
    {
        T data;
        node* prev;
        node* next;
    };
   public:
    class Iterator 
    {
       public:
        friend class LL;
        Iterator();
        Iterator(node*);
        T operator*() const;
        Iterator operator++(int);
        Iterator operator++();
        Iterator operator--(int);
        Iterator operator--();
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;

       private:
        node* current;
    };

    LL();
    LL(const LL<T>&);
    const LL<T>& operator=(const LL<T>&);
    ~LL();
    void headInsert(const T&);
    void tailInsert(const T&);
    void headRemove();
    bool isEmpty() const;
    std::size_t size() const;
    Iterator begin() const;
    Iterator end() const;

   private:
    node * portal;
};

//default constructor
template <typename T>
LL<T>::Iterator::Iterator() 
{   
    current = nullptr;
}

//constructor that sets current to passed value
template <typename T>
LL<T>::Iterator::Iterator(node* ptr) 
{
    current = ptr;
}

//operator * overload to get data
template <typename T>
T LL<T>::Iterator::operator*() const 
{
    return current->data;
}

//operator ++ overload 
template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator++(int) 
{
   this->current = this->current->next;
   return this->current;
}

//operator ++ overload 
template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator++() 
{
    this->current = this->current->next;
    return this->current->prev;
}

//operator -- overload 
template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator--(int) 
{
    this->current = this->current->prev;
    return this->current;
}

//operator -- overload 
template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator--() 
{
    this->current = this->current->prev;
    return this->current->next;
}

//operator == overload to compare values
template <typename T>
bool LL<T>::Iterator::operator==(const Iterator& rhs) const 
{
    if(this->current == rhs.current){
        return true;
    }

    return false;
}

//operator != overload to compare values
template <typename T>
bool LL<T>::Iterator::operator!=(const Iterator& rhs) const 
{
    if(this->current != rhs.current){
        return true;
    }
    
    return false;
}

//Linked list class implementation
//default constructor
template <typename T>
LL<T>::LL() 
{   
    portal = new node;
    portal->prev = portal;
    portal->next = portal;
}

//copy constructor 
template <typename T>
LL<T>::LL(const LL<T>& copy) 
{
    portal = new node;
    portal->prev = portal;
    portal->next = portal;

    node* temp = copy.portal->next;

    //copy copy.data to this
    while(temp != copy.portal){
        tailInsert(temp->data);
        temp = temp->next;

    }
}

//operator == overaload to copy linked list
template <typename T>
const LL<T>& LL<T>::operator=(const LL<T>& rhs) 
{
    node* temp = portal->next;
    while (temp != portal){
        node* next = temp->next;
        delete temp;
        temp = next;
    }

    portal->next = portal;
    portal->prev = portal;

    //create temp variable to iterate through rhs
    node* temp2 = rhs.portal->next;

    //copy rhs.data to this
    while(temp2 != rhs.portal){
        tailInsert(temp2->data);
        temp2 = temp2->next;

    }

    //return this
    return *this;
}

//destructor
template <typename T>
LL<T>::~LL() 
{   
    node* temp = portal->next;
    while (temp != portal){
        node* next = temp->next;
        delete temp;
        temp = next;
    }

    delete portal;
}

//head insert: add to beginning of list
template <typename T>
void LL<T>::headInsert(const T& item) 
{   
    //create temp varibale to hold item
    node* temp = new node();
    temp->data = item;

    //if list is empty set portal and temp to point at each other
    if(portal->next == portal){
        temp->prev = portal;
        temp->next = portal;
        portal->prev = temp;
        portal->next = temp;
    }
    //if list is not empty set temp to point to head and portal to
    //point to temp and temp 
    else{
        node* head = portal->next;
        head->prev = temp;
        portal->next = temp;
        temp->next = head;
        temp->prev = portal;
    }
    
}

//tail insert: add to end of list
template <typename T>
void LL<T>::tailInsert(const T& item) 
{
    node* temp = new node();
    temp->data = item;

    if(portal->next == portal){
        temp->prev = portal;
        temp->next = portal;
        portal->prev = temp;
        portal->next = temp;

    }
    //if list is not empty set temp to point to head and portal to
    //point to temp and temp 
    else{
        node* tail = portal->prev;
        portal->prev = temp;
        temp->prev = tail;
        temp->next = portal;
        tail->next = temp;
    }
}

//remove first node
template <typename T>
void LL<T>::headRemove()
{   
    //delete head and set head-> to portal and portal to head->next
    if(!isEmpty()){
        node* temp = portal->next;
        portal->next = temp->next;
        temp->next->prev = portal;
        temp->prev = nullptr;
        temp->next = nullptr;
        delete temp;
    }
} 

//check if list is empty
template <typename T>
bool LL<T>::isEmpty() const
{
    return portal->next == portal;
}

//retrieve size of linked list
template <typename T>
std::size_t LL<T>::size() const
{
    //iterate through node and increment counter per node
    size_t count = 0;
    node* temp = portal->next;
    while(temp != portal){
        count++;
        temp = temp->next;
    }

    return count;
}

//get address of first node
template <typename T>
typename LL<T>::Iterator LL<T>::begin() const 
{
    return Iterator(portal->next);
}

//get address of portal
template <typename T>
typename LL<T>::Iterator LL<T>::end() const 
{
    return Iterator(portal);
}
