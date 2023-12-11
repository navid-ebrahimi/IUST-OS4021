#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_CUSTOMERS 5 // number of customers
#define NUM_TRANSACTION 6 // number of transactions/threads
#define INIT_STOCK 100 // the initial value for each person stock

// type transaction. you should pass an object of this type to the function arguments while creating thread
typedef struct
{
    double amount;
    int customer_id;
} transaction_t;

double safeBox = 1000.0; // shared variable for all customers

///////// Start your code here ///////////

/*1. define an array to store the stock of all customers
  2. define the necessary mutexes for each customer account and safe box*/
......

void* withdraw(void* arg){
    /*be aware to print the result in each situation.
      for example in one case that the stock isn't adequate and customer took money from safe box, you can report like the following:
      Customer <customerID> withdrew <transaction-amount> and <the amount taken from safe box> from safe-box. New balance: <new amount of customer stock>\tsafe-box value: <new amount of safe box>\n
      don't forget to report the new balance and new safe box value*/

}

void* deposit(void* arg){
    /*be aware to print the result in the following form:
      Customer <customerID> stock was charged by <transaction-amount>. New balance: <new amount of customer stock>\tsafe-box value: <new amount of safe box>\n
      don't forget to report the new balance and new safe box value*/

}


int main(){
    srand(time(NULL));

    /* for each customer, value the stock with INIT_STOCK
    init mutex for each account and safe box */
    ......

    /* create thread for each transaction
    for each thread:
    if rand() % 2 == 0
        create thread for withdraw
    otherwise
        create thread for deposit*/
    .......

    ///////// End of your code ///////////
    return 0;
}