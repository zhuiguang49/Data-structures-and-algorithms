# 数据结构与算法 2024秋 课程仓库
## Lab 1

hello目录下编写源文件hello.cpp，Makefile，make后可得到可执行文件hello，运行后显示"Hello World!"。

## Lab 2 (Chicken)

1. **深度拷贝与连续赋值：**

* **复制操作:**
在拷贝对象时，为`name`动态分配新的内存，并将源对象的`name`内容复制到新对象中，确保两个对象拥有独立的内存。

* **赋值操作符重载:**
重载`operator = `，在赋值时进行深拷贝，返回`*this`，支持了连续赋值。且每个对象独立地管理自己的内存，避免指针共享导致的潜在问题。

2. **内存管理**

* 在`setName()`和赋值运算符中检查并释放旧的`name`内存，避免内存泄漏，通过`delete[]`释放动态分配的内存，使得对象析构时不会产生内存泄漏。
* 在赋值运算符中，检查`this != &other`，避免自我赋值导致错误的内存释放。

3. **左值引用、指针和`const`关键字**：
* 使用`const`关键字保护`getName`和`getAge`，保证这些函数不会被修改对象成员，并且在传递对象时使用`const`引用。

4. **valgrind检查内存泄漏：**
截图如下

![无内存泄漏](./images/noPossibleLeaks.png)

## Lab 3 Linkedlist

1. **`getCurrentVal()`：**
- 当`currentPos`不为`nullptr`时返回当前节点的值，如果`currentPos`为`nullptr`，报错`Empty current position! Can't get value!`。

2. **`setCurrentVal(T &_val)`：**
- 确保`currentPos`不为`nullptr`时允许修改数据，如若为`nullptr`则报错`Empty current position! Can't setvalue!`

3. **`isEmpty()`：**
- 修改了老妖的拼写错误（手动狗头）。
- 检查链表是否为空，返回`true`表示链表为空，`false`表示链表不为空。

4. **`insert(T _val)`：**
- 如果`currentPos`为`nullptr`，表示链表为空，将元素插入为新的头结点，并更新`currentPos`指向新插入的节点；若`currentPos`不为空，则在其后插入新节点,并更新`currentPos`。
- 插入后，链表的大小增加。

5. **`remove()`：**
>`remove()`函数原先删除的是`currentPos`后面的元素而非`currentPos`指向的当前元素，这不符合实际工作的需求，我们将其改为删除`currentPos`**指向的元素本身**。
- 如若链表为空或`currentPos`为空，则不进行任何操作。
- 若`currentPos`是链表的头结点，删除头结点并更新`head`和`currentPos`。
- 如若`currentPos`不是链表的头结点，删除该节点并更新`currentPos`为其后的节点。
- 删除后，链表的大小减小

**修改了remove()函数后的输出：**

![无内存泄漏](./images/output_lab3.png)

