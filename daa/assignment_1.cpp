#include<iostream>
using namespace std;

/*
    Problem Statement:
        Write a program to calculate fibonacci number using recursion and iteration.
*/


int fibRecursion(int n) {
    if(n == 0 || n == 1) return n;
    else return fibRecursion(n - 1) + fibRecursion(n - 2);
}

int fibIteration(int n) {
    if(n == 0 || n == 1) return n;
    else {
        int x1 = 0;
        int x2 = 1;
        int i = 1;
        while(i < n) {
            int temp = x1 + x2;
            x1 = x2;
            x2 = temp;
            i++;
        }
        return x2;
    }
}

int main() {
    
    int flag = 1;

    while(flag == 1) {
        int choice;
        int n;

        cout<<"Enter the number to calculate: ";
        cin>>n;

        cout<<"Which method would you like to use?"<<endl;
        cout<<"1. Recursion."<<endl;
        cout<<"2. Iterative."<<endl;
        cout<<"Response: ";
        cin>>choice;
        
        if(choice == 1) {
            cout<<"Fibonacci of "<<n<<" using recursion is: "<<fibRecursion(n)<<endl;
        }
        else if(choice == 2) {
            cout<<"Fibonacci of "<<n<<" using iteration is: "<<fibIteration(n)<<endl;
        }
        else {
            cout<<"Invalid choice!"<<endl;
        }

        cout<<"Do you want to continue?(Yes - 1, No - 2)"<<endl;
        cout<<"Response: ";
        cin>>flag;    
    }

}