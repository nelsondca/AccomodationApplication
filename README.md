# AccomodationApplication
(reminder, the code is incomplete)

#Overall, this code provides a basic framework for managing accommodation data through a console interface. Users can add, delete, and view accommodation records andgenerate a report of all accommodations. It uses a linked list to store the data and file I/O
to save and load data between program runs.

#C module Final Project
Console-based Application for managing/booking and storing information about accommodations()

#The 'login' structure stores username and password details, which the program should read from the file, and if it's correct you have admin access where you can manage the accommodations stored in the program, if not use the application as a normal user.
#The 'acc' structure represents all the accommodation details(ID, owner's name, year built, etc. ) and a reference to the next node (for creating a linked list).

#The code has various function prototypes to manage all the accommodations, including adding, deleting, displaying, and searching for accommodations.

#Main Function:
-It initializes a linked list to store accommodation information. The program loads data from a file ("acc.txt") into the linked list using the loadFile function.
-It presents the menu to the user allowing them to perform all the accommodation management system actions.
-Accommodation data can be entered by the user and added to the linked list.
-The program can save accommodation data bo the file("acc.txt") using the saveFile function.
-User can exit the program anytime he chooses '-1'.

#File I/O functions:
loadFile: Reads data from the "acc.txt" file and adds accommodations to the linked list.
saveFile: Saves lodging data to the "acc.txt" file from the linked list.
