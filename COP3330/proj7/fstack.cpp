/*

  fstack.cpp
  
  Jon Crawford

  12/2/2017

  Test Driver for Stack project

*/

#include <iostream>
#include <string>
#include <tstack.h>
#include <cstdlib>

void Menu();

template <typename Stack>
void CopyTest(Stack s);

template <typename Stack>
void AssignTest(const Stack& s);

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

typedef fsu::Stack<ValueType> stack;

int main()
{
  // ID value = ID();
  ValueType value;
  char user, ofc;
    
  stack s(fill,'\0',0);
  std::cout << "This is a Stack < " << displayName <<  " > test program" << std::endl;
  Menu();
  do
  {
    std::cout << "Enter [command][argument] ('M' for menu, 'Q' to quit): ";
    std::cin >> user;

    switch (user)
    {
      case '+':
      case '1':
        if (s.Size() < s.Capacity())
        {
          std::cin >> value;
          s.Push(value);
        }
        else
        {
          std::cin >> value;
          std::cout << "** Stack error: Push(" << value << ") called on full stack" << std::endl;
          
        }
        break;
      case '-':
      case '2':
        if (s.Size() == 0)
        std::cout << "** Stack error: Pop() called on Empty Stack" << std::endl;
        else
        s.Pop();
        break;
      case 'C':
      case 'c':
        s.Clear();
        break;
      case 'T':
      case 't':
        if (!s.Empty())
          std::cout << "Top of Stack: " << s.Top() << std::endl;
        else
        {
          std::cerr << "** Stack error: Top() called on Empty Stack\n" 
                    << "Top of Stack: " << s.Top() << std::endl;
        }  
        break;
      case 'E':
      case 'e':
        if (s.Empty())
          std::cout << "Stack is empty" << std::endl;
        else
          std::cout << "Stack is not empty" << std::endl;
        break;
      case 'S':
      case 's':
        std::cout << "Stack size     = " << s.Size() << std::endl;
        break;
      case '=':
        CopyTest(s);
        AssignTest(s);
        break;
      case 'D':
      case 'd':
        std::cout << "Stack contents:   ";
        s.Display(std::cout);
        std::cout << '\n';
        break;
      case 'U':
      case 'u':
        s.Dump(std::cout);
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
        s.SetOFC(ofc);
        break;
      case '<': // SetDIR(bottom-to-top) - horizontal displays, top at right
        s.SetDIR(+1);
        break;
      case '>': // SetDIR(top-to-bottom) - vertical displays, top on top
        s.SetDIR(-1);
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
            << "Top()  ..................  " << "T\n"
            << "Empty()  ................  " << "E\n"
            << "Size()  .................  " << "S\n"
            << "Copy tests  .............  " << "=\n"
            << "Display()  ..............  " << "D\n"
            << "SetOFC(ofc)  ............  " << "O 0|b|t|n\n"
            << "SetDIR(+1)  .............  " << "< (horizontal -->)\n"
            << "SetDIR(-1)  .............  " << "> (vertical   ^  )\n"
            << "Dump()  .................  " << "U\n"
            << "Display this menu  ......  " << "M\n";
}

template <typename Stack>
void CopyTest(Stack s)
{
  
  //stack test(s);
  
  if (s.Size() > 0)
  {
    stack test(s);
    std::cout << "CopyTest:\n";
    std::cout << "Copied object       size: "
              << test.Size() << "\n"
              << "                contents: ";
    test.Display(std::cout);
    std::cout << "\n";
  }
  else
  {
    stack test;
    std::cout << "CopyTest:\n" << "Copied object       size: "
              << test.Size() << "\n" << "                contents: ";
    test.Display(std::cout);
    std::cout << "\n";
  }

}

template <typename Stack>
void AssignTest(const Stack& s)
{
  stack test;
  test = s;

  if (s.Size() > 0)
  {
    std::cout << "AssignTest:\n" << "Original object     size: "
              << s.Size() << "\n" << "                contents: ";
    s.Display(std::cout);
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
              << s.Size() << "\n" << "                contents: ";
    s.Display(std::cout);
    std::cout << "\n";

    std::cout << "Assignee object     size: "
              << test.Size() << "\n" << "                contents: ";
    test.Display(std::cout);
    std::cout << "\n";
    std::cout << "ConstTest: inactive on empty stack" << std::endl;
  }
}




