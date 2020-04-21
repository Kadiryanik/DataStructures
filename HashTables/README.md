## Hash Tables
A simple hash table implementations. Supported collision handling techniques.

 - Linear Probing
 - Quadratic Probing
 - Separate Chaining

For more detailed prints you can modify **project-conf.h**. Such as set **LOG_LEVEL_CONF_HASH_TABLE** to **LOG_LEVEL_DBG** and **PRINT_WITH_FUNC_LINE** to **1**.

#### Compiling and Testing
 You can compile and test it with following command.
```sh
$ cd HashTables
$ make && make run
```
 You can clean unnecessary files with following command.
```sh
$ make clean
```
#### Change Collision Handling Technique
Set the **TECH** flag while compiling. Clean before changing techniques. Default technique is *LinearProbing*.
```sh
$ make TECH=QuadraticProbing
```