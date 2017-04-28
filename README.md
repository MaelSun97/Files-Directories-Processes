Project 01 - README
===================

Members
-------
 Ruochen Sun (rsun2@nd.edu)
 Jimmy Gam(jgam@nd.edu)

Responses
---------
 1. command line arguments would be interpreted into the members of Setting structure. Different argument would be interpreted differently as boolean, int, or string. For example, the "-excutable" would be interpreted as binary X_OK, which is convenient to use in the filter; the "-uid" would allow the program to take next arguement as a string and to pass it to settings.uid

 2. I use the recursion in the search.c to walk through the directory tree. Everytime when the program find the current file's type is a directory then we would call search.c and current file would be root.

 3. The filter.c would decide whether current file satisfied the all the argument given by user. If it satisfied all, then it would be printed out.

Contributions
-------------
