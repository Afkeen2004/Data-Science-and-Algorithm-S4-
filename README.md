# Data-Science-and-Algorithm-S4-README

## S4-Semester-Assignments
This repository contains the solutions for the assignments given during the S4 semester. All codes provided here have passed all test cases provided by the instructors.

## Table of Contents
* [Cycle 1 Part A Assignment](#cycle-1-part-a-assignment)
* [Cycle 1 Part B Assignment](#Cycle-1-Part-B-Assignment)
* [Cycle 1 Part C Assignment](#Cycle-1-Part-C-Assignment)


## Cycle-1-Part-A-Assignment

Q1: You have given mathematical expressions which have some duplicate parentheses. The expressions
consist of lowercase alphabets and operators (+, -, *, /, ˆ , %) without space, Your goal is to
identify and flag expressions that have duplicate parentheses. Duplicate parentheses occur when 
the same subexpression is enclosed by multiple sets of parentheses. It’s important to note that a
single alphabet or operator by itself is also considered a valid expression.

Q2: A Singly linked list L is a data structure in which the objects are arranged in a linear order.
Each node of a Singly linked list L is an object with an attribute key and one pointer attribute,
next. Given a node x in the list, x.next points to its successor in the linked list. An attribute
L.head points to the first node of the list.
Write a menu driven program to implement an unsorted Singly linked list L. Your program
must contain the following functions:
Your main() function shall read the choice from the console and call the following functions appro-
priately: Your program must contain the following functions:
• Main() - repeatedly reads a character ‘a’, ‘r’, ‘d’, ‘p’, ‘s’ from the terminal and calls the
sub-functions appropriately until character ‘e’ is entered.
• CREATE-NODE(k) - creates a new node with key k and pointer next of node points to
NULL. This procedure returns a pointer to the new node.
• LIST-INSERT(L, x) - inserts x as the last node of L.
• LIST-DELETE(L, i) - deletes the node at index i from L and print the deleted key value.
The position is determined by its index, considering first node at index 1. If i is not found in
L, then print −1
• LIST-Rduplicate(L) - Remove duplicates: This function will remove duplicates from the
list L and after removal the updated list L is printed.
• LIST-Pal(L): Function is used to check whether the linkedlist L is palindrome or not.The
function will return Y (if it is a palindrome) otherwise N.
(In case of even length linkedlist , the first node is considered as middle node).
• LIST-DISPLAY(L) - prints the list L
Note:- For every INSERT operation, the node x is created by calling CREATE-NODE() function.

Q3: You are responsible for designing a system to manage an emergency room (ER) using a priority
queue(max heap). Patients arrive at the ER and are characterized by their name, condition
severity (priority), and admit time(admitTime). The system needs to support the following
functions:
• main(): Repeatedly reads an input character from the menu list through the terminal and
execute menu driven operations accordingly.The Menu list is [‘a’,’t’,’c’,’d’,’u’,’p’,’e’].The pro-
gram ends on input ‘e’.
• admitPatient(priorityQ,name,priority,admitTime): Add a new patient to the ER with
their name, condition severity(priority), and admit time.
• treatNextPatient(priorityQ): Treat the next patient in the ER with high severity. If
multiple patients have the same severity, treat the one who was admitted first. Discharges
the patient after treatment.
• checkNextPatient(priorityQ): Print the details(space separated) of the next patient to be
treated without removing them from the priority queue.
• dischargePatient(priorityQ,name,admitTime): Discharge a specific patient from the
ER based on their name and admitTime.
• updateConditionSeverity(priorityQ,name,admitTime, newPriority): Update the con-
dition severity of a specific patient currently in the ER. This operation may change the pa-
tient’s position in the priority queue.
• printAllPatients(priorityQ): Print the details (space separated) of all patients (each pa-
tient in a new line) in the priority order. Consider admitting time for patients with the same
priority.
