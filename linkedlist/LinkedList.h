#include <initializer_list>
#include <iostream>


template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val) : data(_val) {}

        friend class SingleLinkedList<T>;
    };
    Node *head = nullptr;
    int size = 0;
    Node *currentPos = nullptr;

    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);

public:
    /// 返回当前位置的值
    T getCurrentVal() const;
    /// 设置当前位置的值
    void setCurrentVal(T &_val);
    /// 如果链表为空，返回 true；否则返回 false
    bool isEmpty() const;

    int getSize() const;
    void emptyList();
    bool find(const T &_val);
    SingleLinkedList() {}
    ~SingleLinkedList();
    SingleLinkedList(std::initializer_list<T> _l);
    void printList() const;
    SingleLinkedList(const SingleLinkedList<T> &_l);
    SingleLinkedList<T> &operator=(const SingleLinkedList<T> &_l);

    /// 在 currentPos 后面插入一个元素，数据为 _val
    void insert(T _val);
    /// 删除 currentPos 后面的元素
    void remove();
};

/// 返回当前位置的值
template <typename T>
T SingleLinkedList<T>::getCurrentVal() const
{
    if (currentPos)
        return currentPos->data;
    throw std::out_of_range("Current position is null");
}

/// 设置当前位置的值
template <typename T>
void SingleLinkedList<T>::setCurrentVal(T &_val)
{
    if (currentPos)
        currentPos->data = _val;
    else
        throw std::out_of_range("Current position is null");
}

/// 如果链表为空，返回 true；否则返回 false
template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    return head == nullptr;
}

/// 在 currentPos 后面插入一个元素，数据为 _val
template <typename T>
void SingleLinkedList<T>::insert(T _val)
{
    Node *newNode = new Node(_val);
    if (currentPos == nullptr)
    {
        // 如果currentPos为空，插入到头节点前
        newNode->next = head;
        head = newNode;
        currentPos = head; // 更新 currentPos 到新的 head
    }
    else
    {
        // 插入到 currentPos 后面
        newNode->next = currentPos->next;
        currentPos->next = newNode;
    }
    ++size;
}

/// 删除 currentPos 后面的元素
template <typename T>
void SingleLinkedList<T>::remove()
{
    if (currentPos == nullptr || head == nullptr) {
        return;  // 如果链表为空或 currentPos 为 nullptr，直接返回
    }

    if (currentPos == head) {
        // 如果 currentPos 是头节点，删除头节点
        Node* temp = head;
        head = head->next;  // 更新 head 指向下一个节点
        delete temp;
        currentPos = head;  // 更新 currentPos 指向新的头节点
    } else {
        // 查找 currentPos 前面的节点
        Node* prev = head;
        while (prev->next != currentPos) {
            prev = prev->next;
        }
        // 删除 currentPos
        prev->next = currentPos->next;
        delete currentPos;
        currentPos = prev->next;  // 更新 currentPos 为删除节点后的下一个节点
    }

    --size;  // 更新链表大小
}

template <typename T>
bool SingleLinkedList<T>::find(const T &_val)
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->data == _val)
        {
            currentPos = p;
            return true;
        }
        p = p->next;
    }
    return false;
}

template <typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node *newNode = new Node(*i);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
}

template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    Node *p = head;
    while (p != nullptr)
    {
        Node *t = p;
        p = p->next;
        delete t;
    }
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node *p = head;
    while (p != nullptr)
    {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
};

template <typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    _copy(_l);
}

template <typename T>
void SingleLinkedList<T>::emptyList()
{
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template <typename T>
SingleLinkedList<T> &SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.head;
    while (p != nullptr)
    {
        Node *newNode = new Node(p->data);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
}
