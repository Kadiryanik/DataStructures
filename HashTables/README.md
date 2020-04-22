## Hash Tables

A simple hash table implementations. Supported collision handling techniques.

 - Linear Probing
 - Quadratic Probing
 - Separate Chaining

For more detailed prints you can modify **project-conf.h**. Such as set **LOG_LEVEL_CONF_HASH_TABLE** to **LOG_LEVEL_DBG** and **PRINT_WITH_FUNC_LINE** to **1**.

### Performance Test Results
The tests were run on msi ge60-2oe-215x machine which has Intel Core i7 4700MQ CPU.

| Technique | head | middle | tail | 
| - | - | - | - | 
| Linear Probing | **950** | **941** | **69905** |
| Quadratic Probing | **896** | **853** | **1649** |
| Separate Chaining | **1054**  | **1030**  | **1104** | 
| Without HashTable | **819** | **292067** | **617482** | 

<img align="center" src="performance.gif">

### Compiling and Testing
 You can compile and test it with following command.
```sh
$ cd HashTables
$ make && make run
```
 Or you can compile and test it with your file which contain your data set.
```sh
$ cd HashTables
$ make && ./Test.out <file-name>
```
 You can clean unnecessary files with following command.
```sh
$ make clean
```
### Change Collision Handling Technique
Set the **TECH** flag while compiling. Clean before changing techniques. Default technique is *LinearProbing*.
```sh
$ make TECH=SeparateChaining
```
