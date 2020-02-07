/*

  fqueue.cpp
  
  Jon Crawford

  12/9/2017

  Test Driver for Queue project

*/

#include <iostream>
#include <string>
#include <tqueue.h>
#include <cstdlib>

void Menu();

template <typename Queue>
void CopyTest(Queue q);

template <typename Queue>
void AssignTest(const Queue& q);

#include <id.h>

//ID fill = ID();
//const char* displayName = "ID";
//typedef fsu::Stack <ID> stack;

//typedef int ValueType;
//ValueType fill = 0;
//const char* displayName = "int";


typedef char ValueType;
ValueType fill = '*';
const char* displayName = "char";
//const size_t area51 = 15;
//typedef fsu::Stack<ValueType, area51> stack;

typedef fsu::Queue<ValueType> queue;

int main()
{
  // ID value = ID();
  ValueType value;
  char user, ofc;
    
  queue q;
  std::cout << "This is a Queue < " << displayName <<  " > test program" << std::endl;
  Menu();
  do
  {
    std::cout << "Enter [command][argument] ('M' for menu, 'Q' to quit): ";
    std::cin >> user;

    switch (user)
    {
      case '+':
      case '1':
        std::cin >> value;
        q.Push(value);         
        break;
      case '-':
      case '2':
        q.Pop();
        break;
      case 'C':
      case 'c':
        q.Clear();
        break;
      case 'F':
      case 'f':
        std::cout << "Front of Queue: " << q.Front() << std::endl;
        break;
      case 'E':
      case 'e':
        if (q.Empty())
          std::cout << "Queue is empty" << std::endl;
        else
          std::cout << "Queue is not empty" << std::endl;
        break;
      case 'S':
      case 's':
        std::cout << "Queue size     = " << q.Size() << std::endl;
        break;
      case '=':
        CopyTest(q);
        AssignTest(q);
        break;
      case 'D':
      case 'd':
        std::cout << "Queue Display(): ";
        q.Display(std::cout);
        std::cout << '\n';
        break;
      case 'U':
      case 'u':
        std::cout << "Queue    Dump(): ";
        q.Dump(std::cout);
        std::cout << '\n';
        break;
      case 'M':
      case 'm':
        Menu();
        break;
      case 'Q':
      case 'q':
        break;
      case 'o': case 'O':   // void SetOFC()
        std::cin >> ofc;
        if      (ofc == '0')               ofc = '\0';
        else if (ofc == 'b' || ofc == 'B') ofc = ' ';
        else if (ofc == 't' || ofc == 'T') ofc = '\t';
        else if (ofc == 'n' || ofc == 'N') ofc = '\n';
        else
        {
          std::cout << " ** bad ofc: only 0, b|B, t|T, n|N accepted\n";
          break;
        }
        q.SetOFC(ofc);
        break;
      default:
        std::cout << "** Unrecognized command -- please try again.\n";
    }
  } while (user != 'Q' && user != 'q'); //end do

std::cout << "\nHave a nice day." << std::endl;
return 0;

}

void Menu()
{
  std::cout << "Push(Tval)  .............  " << "+ tval or 1 tval\n"
            << "Pop()  ..................  " << "- or 2\n"
            << "Clear()  ................  " << "C\n"
            << "Front()  ................  " << "F\n"
            << "Empty()  ................  " << "E\n"
            << "Size()  .................  " << "S\n"
            << "Copy tests  .............  " << "=\n"
            << "Display()  ..............  " << "D\n"
            << "SetOFC(ofc)  ............  " << "O 0|b|t|n\n"
            << "Dump()  .................  " << "U\n"
            << "Display this menu  ......  " << "M\n";
}

template <typename Queue>
void CopyTest(Queue q)
{
  
  queue test(q);
  
  if (q.Size() > 0)
  {
    //queue test(q);
    std::cout << "CopyTest:\n";
    std::cout << "Copied object       size: "
              << test.Size() << "\n"
              << "                contents: ";
    test.Display(std::cout);
    std::cout << "\n";
  }
  else
  {
    //queue test;
    std::cout << "CopyTest:\n" << "Copied object       size: "
              << test.Size() << "\n" << "                contents: ";
    test.Display(std::cout);
    std::cout << "\n";
  }

}

template <typename Queue>
void AssignTest(const Queue& q)
{
  queue test;
  test = q;

  if (q.Size() > 0)
  {
    std::cout << "AssignTest:\n" << "Original object     size: "
              << q.Size() << "\n" << "                contents: ";
    q.Display(std::cout);
    std::cout << "\n";

    std::cout << "Assignee object     size: " << test.Size() << "\n"
              << "                contents: ";
    test.Display(std::cout);
    std::cout << "\n";
    std::cout << "ConstTest: OK" << std::endl;

  }
  else 
  {
    std::cout << "AssignTest:\n" << "Original object     size: "
              << q.Size() << "\n" << "                contents: ";
    q.Display(std::cout);
    std::cout << "\n";

    std::cout << "Assignee object     size: "
              << test.Size() << "\n" << "                contents: ";
    test.Display(std::cout);
    std::cout << "\n";
    std::cout << "ConstTest: inactive on empty queue" << std::endl;
  }
}




