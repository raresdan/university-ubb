#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
"""
5. Apartment Building Administrator
Jane is the administrator of an apartment building, and she wants to manage the monthly expenses for each apartment.
Each expense is stored using the following elements: apartment (number of apartment, positive integer),
amount (positive integer), type (from one of the predefined categories water, heating, electricity, gas and other).
Write a program that implements the functionalities exemplified below:

(A) Add new transaction
add <apartment> <type> <amount>
e.g.
add 25 gas 100 – add to apartment 25 an expense for gas in amount of 100 RON

(B) Modify expenses
remove <apartment>
remove <start apartment> to <end apartment>
remove <type>
replace <apartment> <type> with <amount>
e.g.
remove 15 – remove all expenses for apartment 15
remove 5 to 10 – remove all expenses for apartments between 5 and 10
remove gas – remove all gas expenses from all apartments
replace 12 gas with 200 – replace the amount of the expense with type gas for apartment 12 with 200 RON

(C) Display expenses having different properties
list
list <apartment>
list [ < | = | > ] <amount>
e.g.
list – display all expenses
list 15 – display all expenses for apartment 15
list > 100 - display all apartments having total expenses >100 RON
list = 17 - display all apartments having total expenses =17 RON

(D) Filter
filter <type>
filter <value>
e.g.
filter gas – keep only expenses for gas
filter 300 – keep only expenses having an amount of money smaller than 300 RON

(E) Undo
*undo – the last operation that modified program data is reversed. The user can undo all operations performed
since program start by repeatedly calling this function.
"""
from ui import *

if __name__ == "__main__":
    start()
