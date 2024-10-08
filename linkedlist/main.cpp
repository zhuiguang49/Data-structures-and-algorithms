#include "LinkedList.h"


int main()
{
    SingleLinkedList<int> link1 {1, 2, 3, 4, 5};
    link1.printList();
    SingleLinkedList<int> link2(link1);
    SingleLinkedList<int> link3 = link1;
    link2.printList();
    link3.printList();
    link1.printList();

    return 0;
}
