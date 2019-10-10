# StudentManagementSystemInC


A simple project using generic linked lists and trees in C. The tree is used as a key-value map. 

The List structure has two function pointer fields <br><br>
  -> toString: to represent a data item as a string <br>
  -> equal: to compare two data items for equality <br>
 
  <br>
  
These two need to be specified while initializing a list using the 'newsList' function available in List.h <br> <br>

The Tree structure has three function pointer fields <br><br>
  -> toString: to obtain a string representation of the data item <br>
  -> key: to compute the key given a data item <br>
  -> equal: compare two data items for equality <br>
  <br>
These need to be specified during initialization of the tree
