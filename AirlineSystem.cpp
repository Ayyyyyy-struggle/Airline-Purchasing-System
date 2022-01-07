// This airline system is design for client purchasing flight ticket.
// The departure city is Detroit DTW. 
// Destination includes 10 cities: Orlando, LasVegas, NewYork, LosAngels, SaltLakeCity, Dallas, Atlanta, Washington, Charlotte.
// The application provides a menu that the client can select 5 functions: menu usage, purchase, order detail, payment, print ticket.
// Client is able to only type letter to choose each options. 
// Before turn off the system, Client will get flight ticket in text file.


#include <iostream>    //these are the i/o manipulators we will be using
#include <string> 
#include <algorithm>
#include <fstream>
#include <iomanip>
using namespace std;

// Declare functions
void MenuDisplay();
void LuggageCost(int& LuggageCost);
void RoundTrip(int& Price);
string AskDestination();
void AskDate(string& iDepartDate);
void ClassSelection(int& cost);

// Main class
int main()
{
    // Decclaring variables
    string cityname, Airport, ArrivalCity, AirlineCompany, DepartDate; //variable string
    string destination[10], airport[10], airline[10];
    int orderTotal = 0; // Total order cost
    int luggageCost = 0; // variable double
    int distance; // distance betwen two Cities
    int price[10], mileage[10];
    char option;//variable char
    bool operation = true;
    bool payment = false;


    // Headlines 
    cout << setfill('*');
    cout << setw(100) << " " << endl;
    cout << setw(60) << " Welcome to Airline Chek-In "  << setw(40)  << " " << endl;
    cout << setw(100) << "\n" << endl;

    // Call out menu function
    MenuDisplay();
    cout << "\nYour departure city is Detroit (Default)" << endl;

    // Open and read file
    ifstream Infile;
    ofstream Myfile;
    string InfileName = "AirlineSystem.txt" ;
    string OutfileName = "Airlineticket.txt"; //this will create a file to write to

    // Open file and throw exceptions
    Infile.open(InfileName);
    if (!Infile)
    {
        cout << "Sorry, our system is under maintanence." << endl;
        cout << "Please come back later" << endl;
        system("PAUSE");
        return 0;
    }
    else 
    {
        while (!Infile.eof())
        {
            for (int i = 0; i < 10; i++)   // Use loop to store airline information in 5 different arrays
            {
                Infile >> cityname >> destination[i] >> airport[i] >> price[i] >> airline[i] >> mileage[i];
            }
        }
    }

    // Respond to option typed by user
    while (operation == true)
    {
        cout << "\nPlease enter your selection: ";
        cin >> option;
        option = toupper(option);

        // Start excute program
        switch (option){
            case 'S':
                MenuDisplay();
                break;
            case 'P':
                Airport = AskDestination();   // Call function to ask destination
                
                for (int i= 0; i < 10; i++)      // use for loop to match destination in the file
                {
                    if (Airport == airport[i])
                    {
                        ArrivalCity = destination[i];
                        orderTotal = price[i];
                        distance = mileage[i];
                        AirlineCompany = airline[i];
                    }
                }
                AskDate(DepartDate); // Ask user departure Date by calling a function
                LuggageCost(luggageCost); // Calculate luggage cost
                ClassSelection(orderTotal); // Ask user about flight class by calling ClassSelection()
                RoundTrip(orderTotal); // Calculation total cost
                break;
            case 'V':
                if (orderTotal == 0)
                {
                    cout << "No purchases made yet. " << endl; // User has to make purchase to view total cost
                }
                else {
                    // Print order detail on the console
                    cout << setfill(' ');
                    cout << fixed << showpoint << setprecision(2);
                    cout << left << "Your takeoff city is " << right << setw(39) << " " << cityname << endl; // writing to Order.txt file
                    cout << left << "Your luggage cost is " << right << setw(40) << "$" << luggageCost << endl;
                    cout << left << "You are traveling to " << right << setw(39) << " " << ArrivalCity << endl;
                    cout << left << "The distance from here to destination is " << setw(19) << " " << distance << " miles" << endl;
                    cout << left << "Your total flight costs are " << right << setw(33) << "$" << luggageCost + orderTotal << endl;
                    cout << left << "Your departure date is " << right << setw(37) << " " << DepartDate << endl;
                    cout << setfill('.') << setw(40) << "Thank You!" << setw(30) << " "<< endl; 
                }
                break;
            case 'C':
            // View order detail
            if (orderTotal == 0)
            {
                cout << "Your total is $" << luggageCost + orderTotal << endl;
                cout << "No purchase made yet." << endl;
            }
            else{
                    cout << "Your total is $" << luggageCost + orderTotal << endl; 
                    cout << "Your order has been processed " << endl;
                    cout << "Thank you for choosing us" << endl;
                    cout << "Please select 'T' for print ticket " << endl; // Suggesting user to print flight ticket
                    payment = true; // Payment has been made, boolean variable is set as true
            }
                break;
            case 'T':
                if (orderTotal == 0)
                {
                    cout << "No purchases made yet. " << endl;
                }
                else {
                    if (payment == true)   // Ticket can only be printed after payment has been made
                    {
                        Myfile.open(OutfileName);    // Open output file to print ticket
                        Myfile << fixed << showpoint << setprecision(2);
                        Myfile << setfill('.') << setw(43) << "Airline Ticket" << setw(26) << "." << endl << endl;
                        Myfile << setfill(' ');
                        Myfile << left << " Takeoff City " << right << setw(40) << " " << cityname << endl; // writing to Order.txt file
                        Myfile << left << " Luggage Cost " << right << setw(41) << "$" << luggageCost << endl;
                        Myfile << left << " Destination "  << right << setw(41) << " " << ArrivalCity << endl;
                        Myfile << left << " Distance " << right << setw(44) << " " << distance << " miles" << endl;
                        Myfile << left << " Flight Cost " << right << setw(42) << "$" << luggageCost + orderTotal << endl;
                        Myfile << left << " Departure Date " << right << setw(38) << " " << DepartDate << endl;
                        Myfile << setfill('.') << setw(40) << "Thank You!" << setw(30) << " "<< endl;
                        Myfile.close(); 
                        operation = false;
                    }
                    else {
                        // Make sure user make a payment first before printing the ticket
                        cout << "Please make a payment first." << endl;
                        cout << "Select 'C' to make a payment " << endl;
                    }
                }
                break;
            default :
                cout << "Valid entry, please try again" << endl;
                break;
        }
        
    }

    // Exit the program
    cout << "\n\nThank you for your purchase " << endl;
    cout << "Please take your ticket " << endl;
    cout << "Hope you have a good trip \n\n" << endl;

    Infile.close(); // Close file
    system("PAUSE");
    return 0;
}


// Define a function to show the menu
void MenuDisplay()
{
    cout << "To show mune usage 'S' " << endl;
    cout << "To make a purchase 'P' " << endl;
    cout << "To view order detail 'V' " << endl;
    cout << "To make a payment 'C' " << endl;
    cout << "To print out ticket 'T' " << endl;
}


// Define a function to calculate luggage cost
void LuggageCost(int& LuggageCost)
{
    char ch;
    double weight = 0;
    int Luggage_Cost = 30;   // default luggage cost
    int FreeCost = 0;

    cout << "Do you have luggage to check in? (Y for yes, N for no)" << endl;
    cin >> ch;
    ch = toupper(ch);
    switch (ch)
    {
        case 'Y':
            cout << "How much does your luggage weigh (kg)? " << endl;
            cin >> weight;
            if (weight <= 2.5)      // Default free carry-on bag
            { 
                LuggageCost = FreeCost;
                cout << "Check in bag as free carry-on. \n" << endl;
            }
            else if (weight <= 23)   // Over 23kg will be charged
            {
                LuggageCost = Luggage_Cost;
                cout << "Your luggage cost is $30. \n" << endl;
            }
            else 
            {
                cout << "You cannot go on board with a bag over 23kg. " << endl;
                cout << "Sorry for the inconvenience. " << endl;
                system("pause");
            }
            break;
        case 'N':
            cout << "You have no luggage. \n" << endl;
            LuggageCost = FreeCost;
            break;
    }
}

// Define a function to ask users if they want single trip or double trip
void RoundTrip(int& Price)
{
    char ch2;
    int discount = 30;
    cout << "Would you like to book a round trip? (Y for yes, N for no) " << endl;
    cin >> ch2;
    ch2 = toupper(ch2);
    switch(ch2)
    {
        case 'N':
            Price = Price;
        case 'Y':
            Price = Price *2 - discount;
    }
}

// Define a function to make a purchase
string AskDestination()
{
    bool input = false;
    string iAirport;

    // Use while loop to decide valid entry
    while (input == false)
    {
        // Purchasing page menu
        cout << "Our destination cities are available below : \n" << endl;
        cout << "Orlando - MCO; Las Vegas - LAS; Chicago - ORD; New York - JFK; Los Angeles - LAX" << endl;
        cout << "Salt Lake City - SLC; Dallas - DFW; Atlanta - ATL; Washingyon,DC - DCA; Charlotte - CLT\n" << endl;
        cout << "Please enter your arrival city by typing in three letters behind the city name: ";
        cin >> iAirport;
        cout << endl;
        transform(iAirport.begin(), iAirport.end(), iAirport.begin(), ::toupper);

        // Invalid entry to exit the program
        if (iAirport != "MCO" && iAirport != "LAS" && iAirport != "ORD" && iAirport != "JFK" && iAirport != "LAX" && iAirport != "SLC" && iAirport != "DFW" && iAirport != "ATL" && iAirport != "DCA" && iAirport != "CLT")
        {
            cout << "Invalid entry, please try again. \n" << endl;
            input = false;
        }
        else
        {
            input = true;
        }
    }

    return iAirport;
}


// Define a function to store the date
void AskDate(string& iDepartDate)
{
    cout << "What is your leaving date? (Please enter month/day/year) " << endl;
    cin >> iDepartDate;
    cout << endl;
}

// Define a function to ask class selection
void ClassSelection(int& cost)
{
    char ch3;
    int FirstClass = 50; // First class fee is default;
    cout << "Would you like to upgrade your cabin? (Y for yes, N for no) " << endl;
    cin >> ch3;
    ch3 = toupper(ch3);
    switch (ch3)
    {
        case 'Y':
            cout << "Your cabin has been upgraded to first class. \n" << endl;
            cost = cost + FirstClass;
            break;
        case 'N':
            cout << "You will be in the coach cabin (default). \n" << endl;
            cost = cost;
    }
}