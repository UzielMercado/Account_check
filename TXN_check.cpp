#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <windows.h> 

using namespace std;

int timer()
{
   auto t = time(nullptr);
   auto tm = *localtime(&t);

   ostringstream oss;
   oss << put_time(&tm, "%H-%M-%S %d-%m-%Y");
   auto str = oss.str();
}

int print_review(string text)
{
   ofstream review_file; 
   review_file.open("review.txt", std::ios_base::app);
   review_file << text;
   review_file.close();
   
}

int print_signals(string text1)
{
   ofstream Signals_file; 
   Signals_file.open("Signals.txt", std::ios_base::app);
   Signals_file << text1;
   Signals_file.close();
   
}

int main()
{
   double starting_delta_balance = 0;
   double starting_app_balance = 0;
   double starting_non_balance = 0;
   double displa_delta_balance = 0;
   double displa_delta_app_balance = 0;
   double displa_delta_non_balance = 0;
   double origin = 30000000000;
   double origin_app = 0;
   double origin_non = 0;
   int base_approved =0;
   string filecout;

   while (true){    
      fstream TXNfile;

      TXNfile.open("Balance.txt",ios::in); //open a file to perform read operation using file object
      string tp;
      getline(TXNfile, tp);
      double balance = stod(tp);
      double final_balance = balance * 100.0;

      double Current_balance = final_balance;
      
      string filename("ApprovedTXNs.txt");
      vector<string> lines;
      string line;

      ifstream input_file(filename);

      while (getline(input_file, line)){
        lines.push_back(line);
        lines.push_back(line);
      }

      input_file.close();

      print_review("------------------------------------------------------------------\n\n");
      cout << "------------------------------------------------------------------\n\n";

      if (base_approved < lines.size()){

         string input = lines[base_approved];
	      istringstream ss(input);
	      string token;

	      vector<string> no_space;
	      while(getline(ss, token, ' ')) {
		      no_space.push_back(token);
         }
         double monto = stod(no_space[1]);
         double cuenta = stod(no_space[0]);
         if (0<=monto)
         {
            cout << "Received: " << setprecision(0) << monto << " to: " << setprecision(0) << cuenta << '\n' << "\n------------------------------------------------------------------\n";
            
            auto t = time(nullptr);
            auto tm = *localtime(&t);

            ostringstream oss;
            oss << put_time(&tm, "%H-%M-%S-%MS %d-%m-%Y");
            auto str = oss.str();
            filecout = "Received: " + to_string(monto) + " to: " + to_string(cuenta) + '\n' + "\n------------------------------------------------------------------\n";
            print_review(filecout);
            filecout = '\n' + str +" Received: " + to_string(monto) + " to: " + to_string(cuenta) + '\n' + "\n------------------------------------------------------------------\n";
            print_signals(filecout);

            displa_delta_non_balance -= abs(monto * 100.0);
            displa_delta_app_balance += abs(monto * 100.0);

            base_approved = lines.size();
         }
         else if (monto<0)
         {
            cout << "Cashed out: " << setprecision(0) << monto << " from: " << setprecision(0) << cuenta << '\n' << "\n------------------------------------------------------------------\n";
            
            auto t = time(nullptr);
            auto tm = *localtime(&t);

            ostringstream oss;
            oss << put_time(&tm, "%H-%M-%S-%MS %d-%m-%Y");
            auto str = oss.str();
            filecout = "Cashed out: " + to_string(monto) + " from: " + to_string(cuenta) + '\n' + "\n------------------------------------------------------------------\n";
            print_review(filecout);
            filecout = '\n' + str +" Cashed out: " + to_string(monto) + " from: " + to_string(cuenta) + '\n' + "\n------------------------------------------------------------------\n";
            print_signals(filecout);

            displa_delta_non_balance -= abs(monto * 100.0);
            displa_delta_app_balance += abs(monto * 100.0);

            base_approved = lines.size();
         }
         
      }
      
      filecout = "Current balance:\n" + to_string(Current_balance) + "\n\n";
      print_review(filecout);
      cout << fixed << setprecision(2) << "Current balance:\n" <<Current_balance << "\n\n";

      double change1 = origin - Current_balance;
         
      if (starting_delta_balance != change1)
      {
         displa_delta_balance = abs(change1);
         starting_delta_balance = 0;
         origin = Current_balance;

         filecout = "Balance change:\n" + to_string(displa_delta_balance) + "\n\n";
         print_review(filecout);
         cout << fixed << setprecision(1) << "Balance change:\n" << displa_delta_balance << "\n\n";
      }
      else
      {
         displa_delta_balance = 0;

         filecout = "Balance change:\n" + to_string(displa_delta_balance) + "\n\n";
         print_review(filecout);
         cout << fixed << setprecision(1) << "Balance change:\n" << displa_delta_balance << "\n\n";
      }

      filecout = "Approved balance change:\n" + to_string(displa_delta_app_balance) + "\n\n";
      print_review(filecout);
      cout << fixed << setprecision(1) << "Approved balance change:\n" << displa_delta_app_balance << "\n\n";
      double Approved_balance = displa_delta_app_balance;
      double change2 = origin_app - Approved_balance;
         
      if (starting_app_balance != change2)
      {
         displa_delta_app_balance = 0;
         origin_app = 0;
      }

      double Non_approved_balance = displa_delta_balance;
      double change3 = origin_non - Non_approved_balance;
         
      if (starting_non_balance != change3)
      {
         displa_delta_non_balance += abs(change3);
         starting_non_balance = 0;
         origin_non = 0;
      }
      
      filecout = "Non approved balance:\n" + to_string(displa_delta_non_balance) + "\n\n";
      print_review(filecout);
      cout << fixed << setprecision(1) << "Non approved balance:\n" << displa_delta_non_balance << "\n\n";

      Sleep(500);

      TXNfile.close();
   }
}