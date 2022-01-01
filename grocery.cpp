// Project 3
// Gocery Shopper

#include <cassert>
#include <iostream>
#include <string>
#include <cctype>
#include  <cstdlib>

using namespace std;

// declaration of functions

bool isWellFormedGroceryOrderString(string grocerystring);
int pickupCount(string grocerystring);
int deliveryCount(string grocerystring);
int shipCount(string grocerystring);
int inpersonCount(string grocerystring);

// helper functions

int extractNumber( string grocerystring, size_t& index, bool& isValid );


int main ()
{
    string grocerystring;
    cout << "What is the input?";
    getline(cin, grocerystring);
    cout.setf(ios::boolalpha);
    cout << isWellFormedGroceryOrderString(grocerystring) << endl;
    cout << "pickup count: ";
    cout << pickupCount(grocerystring) << endl;
    cout << "delivery count: ";
    cout << deliveryCount(grocerystring)<< endl;
    cout << "inperson count: ";
    cout << inpersonCount(grocerystring)<< endl;
    cout << "ship count: ";
    cout << shipCount(grocerystring)<< endl;
    
    assert( isWellFormedGroceryOrderString("") == false );
    assert( isWellFormedGroceryOrderString("    ") == false );
    assert( shipCount( "    " ) == -1 );
    assert( deliveryCount( "      " ) == -1 );
    assert( inpersonCount( "      " ) == -1 );
    assert( pickupCount( "       " ) == -1 );
    assert( isWellFormedGroceryOrderString( "1s1d1i1p1S1D1I1P" ) == true );
    assert( shipCount( "1s1d1i1p1S1D1I1P" ) == 2 );
    assert( deliveryCount( "1s1d1i1p1S1D1I1P" ) == 2 );
    assert( inpersonCount( "1s1d1i1p1S1D1I1P" ) == 2 );
    assert( pickupCount( "1s1d1i1p1S1D1I1P" ) == 2 );
    
    return 0;
}



// definition of functions

// defining extractNumber helper function
int extractNumber( string grocerystring, size_t& index )
{
    // track the integer value found
    int quantity = 0;
    // the number can't start with a zero!
    if (grocerystring[index] >= '1' && grocerystring[index] <= '9')
    {
        // the number should be made up of digits
        while( index < grocerystring.length() && isdigit(grocerystring[ index ]) )
        {
            // extract one digit and add it to the cumulative value held in quantity
            int digit = grocerystring[ index ] - '0';
            quantity = quantity * 10 + digit;
            index = index + 1;
        }
    }
    // no zeros
    if (quantity == 0)
    {
        quantity = -1;
    }
    return(quantity);
}

// function isWellFromeGroceryString, see if string is valid

bool isWellFormedGroceryOrderString(string grocerystring)
{
    bool result = true;
    size_t i = 0;
    
    // count variables
    int ShipTotal (0);
    int PickupTotal (0);
    int InpersonTotal (0);
    int DeliveryTotal (0);
    
    // no empty strings
    if (grocerystring == "")
    {
        return false;
    }
    
    // first char has to be a non-zero number
    if (grocerystring.at(0) != '1' && grocerystring.at(0) != '2' && grocerystring.at(0) != '3' && grocerystring.at(0) != '4' && grocerystring.at(0) != '5' && grocerystring.at(0) != '6' && grocerystring.at(0) != '7' && grocerystring.at(0) != '8' && grocerystring.at(0) != '9')
    {
        return false;
    }
   
    // loop running thru each character of string after number
    while (i < grocerystring.size())
    {
        int number = extractNumber(grocerystring, i);
        
        // no leading zeros
        if (number == -1)
        {
            result = false;
        }
        
        // string has to contstrain letters
        if (i >= grocerystring.size())
        {
            result = false;
        }
        
        if (i < grocerystring.size())
        {
            // no spaces
            if (grocerystring.at(i) == ' ')
            {
                result = false;
            }
            
            // checking ship number
            if (grocerystring.at(i) == 's' || grocerystring.at(i) == 'S')
            {
                ShipTotal = ShipTotal + number;
            }
        
            // chekcing pickup number
            else if (grocerystring.at(i) == 'p' || grocerystring.at(i) == 'P')
            {
                PickupTotal = PickupTotal + number;
            }
            
            // checking inperson number
            else if (grocerystring.at(i) == 'i' || grocerystring.at(i) == 'I')
            {
                InpersonTotal = InpersonTotal + number;
            }
        
            //checking delivery number
            else if (grocerystring.at(i) == 'd' || grocerystring.at(i) == 'D')
            {
                DeliveryTotal = DeliveryTotal + number;
            }
            else
            {
            result = false;
            }
        }
        
        i++;
        
    }
    // cant have more than 20 pickups
    if (PickupTotal > 20)
    {
        result = false;
    }
    
    // cant have more than 10 deliveries
    if (DeliveryTotal > 10)
    {
        result = false;
    }
    
    // cant have more than 99 orders
    if (PickupTotal + DeliveryTotal + InpersonTotal + ShipTotal > 99)
    {
        result = false;
    }
    
    return (result);
}


int pickupCount(string grocerystring)
{
    size_t i = 0;
    int PickupQuantity (0);
    
    if (isWellFormedGroceryOrderString(grocerystring)== true)
    {
        // loop to check number before p or P
        while (i < grocerystring.size())
        {
            int number = extractNumber(grocerystring, i);
            if (grocerystring.at(i) == 'p' || grocerystring.at(i) == 'P')
            {
                PickupQuantity = PickupQuantity + number;
            }
            i++;
        }
        return (PickupQuantity);
    }
    return (-1);
}

int deliveryCount(string grocerystring)
{
    size_t i = 0;
    int DeliveryQuantity (0);
    
    if (isWellFormedGroceryOrderString(grocerystring)== true)
    {
        // loop to check number before d or D
        while (i < grocerystring.size())
        {
            int number = extractNumber(grocerystring, i);
            if (grocerystring.at(i) == 'd' || grocerystring.at(i) == 'D')
            {
                DeliveryQuantity = DeliveryQuantity + number;
            }
            i++;
        }
        return (DeliveryQuantity);
    }
    return (-1);
}

int shipCount (string grocerystring)
{
 // initialize variable
    size_t i = 0;
    int ShipQuantity (0);
    
    if (isWellFormedGroceryOrderString(grocerystring)== true)
    {
        // loop to check number before s or S
        while (i < grocerystring.size())
        {
            int number = extractNumber(grocerystring, i);
            if (grocerystring.at(i) == 's' || grocerystring.at(i) == 'S')
            {
                ShipQuantity = ShipQuantity + number;
            }
            i++;
        }
        return (ShipQuantity);
    }
    return (-1);
}

int inpersonCount(string grocerystring)
{
    size_t i = 0;
    int InpersonQuantity (0);
    
    if (isWellFormedGroceryOrderString(grocerystring)== true)
    {
        // loop to check number before i or I
        while (i < grocerystring.size())
        {
            int number = extractNumber(grocerystring, i);
            if (grocerystring.at(i) == 'i' || grocerystring.at(i) == 'I')
            {
                InpersonQuantity = InpersonQuantity + number;
            }
            i++;
        }
        return (InpersonQuantity);
    }
    return (-1);
}
