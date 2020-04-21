## Linked Lists
A simple linked list implementations. Followed linked lists implemented.

 - Singly Linked List
 - Doubly Linked List
 - Circular Linked List

For more detailed prints you can modify **project-conf.h**. Such as set **LOG_LEVEL_CONF_LIST** to **LOG_LEVEL_DBG** and **PRINT_WITH_FUNC_LINE** to **1**.

#### Compiling and Testing
 You can compile and test it with following command.
```sh
$ cd LinkedLists
$ make && make run
```
 You can clean unnecessary files with following command.
```sh
$ make clean
```
#### Changing Linked List
Set the **LL** flag while compiling. Clean before changing linked list. Default linked list is *SinglyLinkedList*.
```sh
$ make LL=DoublyLinkedList
```