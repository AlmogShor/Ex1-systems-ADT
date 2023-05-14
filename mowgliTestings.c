//
// Created by shora on 14/05/2023.
//

#include <stdio.h>
#include "AdptArray.h"
#include "Person.h"
#include "Book.h"

int main() {
    // Test creation of Person
    printf("Testing creation of Person...\n");
    pperson p1 = creat_person("John", "Doe", 123);
    pperson p2 = creat_person("Jane", "Doe", 456);
    print_person(p1);
    print_person(p2);

    // Test creation of Book
    printf("\nTesting creation of Book...\n");
    pbook b1 = creat_book("Book1", 789);
    pbook b2 = creat_book("Book2", 101112);
    print_book(b1);
    print_book(b2);

    // Test creation of Adaptive array
    printf("\nTesting creation of Adaptive array...\n");
    PAdptArray pArray = CreateAdptArray(copy_person, delete_person, print_person);

    // Test setting elements in the Adaptive array
    printf("\nTesting setting elements in the Adaptive array...\n");
    SetAdptArrayAt(pArray, 0, p1);
    SetAdptArrayAt(pArray, 1, p2);

    // Test getting elements from the Adaptive array
    printf("\nTesting getting elements from the Adaptive array...\n");
    pperson p3 = (pperson)GetAdptArrayAt(pArray, 0);
    pperson p4 = (pperson)GetAdptArrayAt(pArray, 1);
    print_person(p3);
    print_person(p4);

    // Test getting the size of the Adaptive array
    printf("\nTesting getting the size of the Adaptive array...\n");
    int size = GetAdptArraySize(pArray);
    printf("Size of Adaptive array: %d\n", size);

    // Test printing the Adaptive array
    printf("\nTesting printing the Adaptive array...\n");
    PrintDB(pArray);

    // Test deleting the Adaptive array
    printf("\nTesting deleting the Adaptive array...\n");
    DeleteAdptArray(pArray);

    // Test creation of Adaptive array for books
    printf("\nTesting creation of Adaptive array for books...\n");
    PAdptArray bArray = CreateAdptArray(copy_book, delete_book, print_book);

    // Test setting elements in the Adaptive array
    printf("\nTesting setting elements in the Adaptive array for books...\n");
    SetAdptArrayAt(bArray, 0, b1);
    SetAdptArrayAt(bArray, 1, b2);

    // Test getting elements from the Adaptive array
    printf("\nTesting getting elements from the Adaptive array for books...\n");
    pbook b3 = (pbook)GetAdptArrayAt(bArray, 0);
    pbook b4 = (pbook)GetAdptArrayAt(bArray, 1);
    print_book(b3);
    print_book(b4);

    // Test getting the size of the Adaptive array
    printf("\nTesting getting the size of the Adaptive array for books...\n");
    size = GetAdptArraySize(bArray);
    printf("Size of Adaptive array for books: %d\n", size);

    // Test printing the Adaptive array
    printf("\nTesting printing the Adaptive array for books...\n");
    PrintDB(bArray);

    // Test deleting the Adaptive array
    printf("\nTesting deleting the Adaptive array for books...\n");
    DeleteAdptArray(bArray);

    // Clean up
    delete_person(p1);
    delete_person(p2);
    delete_book(b1);
    delete_book(b2);

    printf("\nAll tests completed.\n");
    return 0;
}

