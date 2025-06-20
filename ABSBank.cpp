#include<iostream>
#include<cstdlib>
#include<string.h>
#include<math.h>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <limits>
#include <ios>
using namespace std;

//----------structure for main account-----
struct main1
{
 long int acno;
 char acctype,custname[25];
 float balance;
} M[100]={{1,'s',"a",500},{2,'s',"b",500},{3,'c',"c",2000},{4,'s',"d",500},{5,'c',"e",2000},{6,'c',"f",2000}};
//---------structure for transaction account-----
struct trans
{
 long int acno;
 char ttype;
 float amount;
}T[100];
//-------- pointers to main1 and trans array of structure---
int mp=6,tp=0;
//------- Keeping records in main account------ 

void create()
{
  char choice;
  do
    {
     system("cls");
     cout<<"\n Entering New Records.";
     cout<<"\n Enter Account Number:";cin>>M[mp].acno;
     cout<<"\n Enter Customer Name:";cin.ignore();cin.getline(M[mp].custname, 25);
     cout<<"\n Enter Account Type[S-Savings C-Current]:";cin>>M[mp].acctype;
     if(M[mp].acctype=='S' || M[mp].acctype=='s')
       M[mp].balance=500;
     else if(M[mp].acctype=='C' || M[mp].acctype=='c')
		  M[mp].balance=2000;
     mp++;
     cout<<"\n Do you want to add more records[y/n]";
     cin>>choice;
     }while(choice=='y' || choice=='Y');
}
//--------Displaying Records----
void disprec()
{
 int i=0;
 while(i<mp)
 {
  cout<<"\n"<<setw(10)<<M[i].acno<<setw(25)<<M[i].custname<<"\t"<<setw(20)<<M[i].acctype<<setw(15)<<M[i].balance;
  i++;
 }
}
//----------------Modifying Records
void modify()
{
  char vacctype,vcustname[25];
  long int vacno;
  int i=0;
  char found='f';
  main1 temp;
  cout<<"\n Enter the Account Number to Modify:";cin>>vacno;
  while(i<mp)
     {
      if(M[i].acno==vacno)
	 {
	   found='t';
	   cout<<"\n Account No:"<<M[i].acno;
	   temp.acno=M[i].acno;
	   cout<<"\n Account Type:"<<M[i].acctype;
	   cout<<"\n Enter New Account Type:\'.\' to skip:";
	   cin>>vacctype;
	   if(vacctype=='.')
	       temp.acctype=M[i].acctype;
	   else
	       temp.acctype=vacctype;
	   //------------------------
	   cout<<"\n Customer Name:"<<M[i].custname;
	   cout<<"\n Enter New Customer Name \'.\' to skip:";
	  cin.ignore(); // flush leftover newline
cin.getline(vcustname, 25);
	   if(strcmp(vcustname,".")==0)
	       strcpy(temp.custname,M[i].custname);
	   else
	       strcpy(temp.custname,vcustname);
	   //------Calculating Temp Balance----------------
	       float bal;
	       temp.balance=0;
	       bal=M[i].balance-2000;
	       if(bal<0)
		 {
		   cout<<"\n Kindly deposit Rs."<<abs(bal)<<" to maintain minimum balance";
		   temp.balance=abs(bal);
		 }
	       temp.balance=temp.balance+M[i].balance;
	     break;
	 }
	 i++;
      }
  if(found=='t')
    {
     char ans;
     cout<<"\n Do you want to keep changes[y/n]:";
     cin>>ans;
     if(ans=='y' || ans=='Y')
	M[i]=temp;
     else
       cout<<"\n Changes Discarded";
     }
  else
    cout<<"\n Record Not Found";
}
//--------------Searching  an account
void search()
{
  long int vacno;
  int i=0;
  char found='f';
  cout<<"\n Enter the Account Number to Search:";cin>>vacno;
  while(i<mp)
     {
      if(M[i].acno==vacno)
	 {
	   found='t';
	   cout<<"\n Account No:"<<M[i].acno;
	   cout<<"\n Account Type:"<<M[i].acctype;
	   cout<<"\n Customer Name:"<<M[i].custname;
	   cout<<"\n Balance:"<<M[i].balance;
	 }
	 i++;
      }
  if(found=='f')
     cout<<"\n Record Not Found";
}
//------------ Deleting an account
void delacc()
{
  long int vacno;
  int i=0;
  char found='f';
  cout<<"\n Enter the Account Number to delete:";cin>>vacno;
  while(i<mp)
     {
      if(M[i].acno==vacno)
	 {
	   char ans;
	   found='t';
	   cout<<"\n Account No:"<<M[i].acno;
	   cout<<"\n Account Type:"<<M[i].acctype;
	   cout<<"\n Customer Name:"<<M[i].custname;
	   cout<<"\n Balance:"<<M[i].balance;
	   cout<<"\n Do you want to delete above record[y/n]:";
	   cin>>ans;
	   if(ans=='y' || ans=='Y')
	     {
	     for(;i<mp-1;i++)
		M[i]=M[i+1];
	     mp--;
	     cout<<"\n Record Deleted";
	     }
	   else
	     cout<<"\n Record remain intact";
	   break;
	 }
	 i++;
      }
  if(found=='t')
     cout<<"\n Process completed sucessfully";
  else
     cout<<"\n Record not found";
}

//--------------Function for deposit
void deposit()
{
  long int vacno;
  int i=0;
  char found='f';
  cout<<"\n Enter the Account Number to Deposit:";cin>>vacno;
  while(i<mp)
     {
      if(M[i].acno==vacno)
	 {
	   found='t';
	   break;
	  }
      i++;
      }
if(found=='f')
  cout<<"\n Account doesn't exist!!!";
else
   {
    cout<<"\n Enter Amount :";
    cin>>T[tp].amount;
    T[tp].acno=vacno;
    T[tp].ttype='D';
    M[i].balance+=T[tp].amount;
    tp++;
    cout<<"\n Amount deposited sucessfully";
    }
}
//-------------Function to withdraw amount---------
void withdraw()
{
  long int vacno;
  int i=0;
  char found='f';
  cout<<"\n Enter the Account Number to Withdraw:";cin>>vacno;
  while(i<mp)
     {
      if(M[i].acno==vacno)
	 {
	   found='t';
	   break;
	  }
      i++;
      }
if(found=='f')
  cout<<"\n Account doesn't exist!!!";
else
   {
    float amt,bal;
    cout<<"\n Enter Amount :";
    cin>>amt;
    bal=M[i].balance-amt;
    if(amt<M[i].balance)
       {
       if(M[i].acctype=='s' || M[i].acctype=='S')
	 if(bal<500)
	       cout<<"\n Balance is less than Minimum Balance";
       if(M[i].acctype=='c' || M[i].acctype=='C')
	 if(bal<2000)
	       cout<<"\n Balance is less than Minimum Balance";

	T[tp].acno=vacno;
	T[tp].ttype='W';
	T[tp].amount=amt;
	M[i].balance-=T[tp].amount;
	tp++;
	cout<<"\n Amount sucessfully withdrawn";
	}
    else
       cout<<"\n Insufficient Fund";
   }
}
//------------Report of Deposit Amount
void reportD()
{
 int i=0;
 float totalamt=0.0;
 while(i<tp)
   {
      if(T[i].ttype=='D')
      {
	cout<<"\n"<<T[i].acno<<"\t" <<T[i].amount;
	totalamt+=T[i].amount;
      }
      i++;
    }
 cout<<"\n Total Amount Deposited :"<<totalamt;
 }
//------------Report of Witdrawn Amount
void reportW()
{
 int i=0;
 float totalamt=0.0;
 while(i<tp)
   {
      if(T[i].ttype=='W')
      {
	cout<<"\n"<<T[i].acno<<"\t" <<T[i].amount;
	totalamt+=T[i].amount;
      }
      i++;
    }
 cout<<"\n Total Amount Withdrawn :"<<totalamt;
 }

//----------------------- Menu for ABS Banking System
void menu()
{
 int choice;
 do{
  system("cls");
  cout<<"\n ABS Banking System";
  cout<<"\n 1. Creating a new Account.";
  cout<<"\n 2. Display Account Detail.";
  cout<<"\n 3. Modifying an existing Account.";
  cout<<"\n 4. Searching an Account.";
  cout<<"\n 5. Delete Account.";
  cout<<"\n 6. Deposit Amount.";
  cout<<"\n 7. Withdrawal Amount.";
  cout<<"\n 8. Report - Deposit.";
  cout<<"\n 9. Report - Withdrawal";
  cout<<"\n 10. Quit";
  cout<<"\n Enter your choice[1-10]:";
  cin>>choice;
  switch(choice)
  {
   case 1:
	  create();
	  break;
   case 2:
	  disprec();cin.ignore();
cin.get();

	  break;
  case 3: modify();
	  break;
  case 4:
	  search();
    cin.ignore();
cin.get();
	  break;
   case 5:
	  delacc();
	  break;
  case 6: deposit();
	  break;
  case 7:
	  withdraw();
	  break;
   case 8:
	  reportD();cin.ignore();
cin.get();

	  break;
  case 9: reportW();cin.ignore();
cin.get();

	  break;

  case 10:
	  cout<<"\n Exiting from the program";
	  cin.get();
	  exit(1);
	  break;
  default:
	   cout<<"\n Enter appropraite choice[1--10]";
     }
  cin.get();
  }while(choice!=10);
 }

int main()
{
//textcolor(4);
//textbackground(6);
cout << "\033[1;31m"; // Set text color to bright red
    cout << "Welcome to ABS Banking System!" << endl;

    cout << "\033[0m"; // Reset to default

menu();
return 0;
}
