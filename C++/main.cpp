#include <iostream>
#include "bond.h"
#include <cmath>
#include <string>
#include <utility>
#include <map>


using std::cout;
using std::endl;
using std::string;

void print_problem(const std::string& text) {
    cout << endl;
    if(text != "a"){
        for (int i = 0; i<5; i++){
        cout << endl;
    }
    }
    
    cout <<"------------------------ " <<"\033[1m\033[31m" << "Problem 1" << text << ":" << "\033[0m" << " ------------------------"<< endl;
     cout << endl;
}

void print_answer(const std::string& text) {
    cout << "\033[1m\033[31m" << "Answer: " << "\033[0m" << text  << endl;
}

void print_response(const std::string& text) {
    cout << "\033[1m\033[31m" << "Response: " << "\033[0m" << text  << endl;
}

int main() {

    int maturities[6] = {1,2,3,5,10,30};
    float yields[6] = {0.055, 0.052, 0.05, 0.047, 0.046, 0.048};

    // -------------------------------------------------- PROBLEM 1A ---------------------------------------------------

    print_problem("a");

    // Setting pointers for indices and max price
    std::pair<int, float> max_indices = {0,0};
    float max_price = 0;

    // Creating a map for the prices maturities and yields
    std::map<std::pair<int, float>, Bond> zeroBondMap;

    for (int i = 0; i < 6; i++) {

            // Constructing the bond
            Bond bond(100, maturities[i], yields[i], 0, 0);

            std::pair<int, float> cur_indices = std::make_pair(maturities[i], yields[i]);

            zeroBondMap[cur_indices] = bond;

            // Setting current price
            double cur_price = bond.price();
            cout << "The price of a bond with maturity " << maturities[i] << " and yield " << yields[i] << " is " << cur_price << endl;

            // Setting the max price
            if (cur_price > max_price) {
                max_price = cur_price;
                max_indices = std::make_pair(maturities[i],yields[i]);
            }
    }

    cout << endl;

    // Construct the answer string
    std::string problem1aanswer = "The maximum price is " + std::to_string(max_price) +
                                 " and occurs when maturity is " + std::to_string(max_indices.first) +
                                 " and yield is " + std::to_string(max_indices.second);

    print_answer(problem1aanswer);

    std::string problem1aresponse = "This is reasonable since a negative exponential is an inverse relationship, \n so the minimum product produced by the combinations of yields and maturities produces the highest price.";

    print_response(problem1aresponse);


    // -------------------------------------------------- PROBLEM 1B ---------------------------------------------------
    print_problem("b");

    for (int i = 0; i < 6; i++) {

            //hashing the already created bonds
            std::pair<int, float> cur_pair = std::make_pair(maturities[i], yields[i]);
            Bond cur_bond = zeroBondMap[cur_pair];

            cout << "The duration for a bond with price = "<< cur_bond.price() << 
            ", maturity = " << maturities[i] << ", yield = " << yields[i]<< ", is = " << cur_bond.duration_f_diff()<< endl;
    
    }
    cout<<endl;

    string problem1bresponse = "As the yield goes up, the price goes down, and vice versa" ;

    print_response(problem1bresponse);


    // -------------------------------------------------- PROBLEM 1C ---------------------------------------------------
    print_problem("c"); 

    // Creating a map for the prices above 100
    std::map<std::pair<int, float>, Bond> cBondMap;

    for (int i = 0; i < 6; i++) {

            // Constructing the bond
            Bond cbond(100, maturities[i], yields[i], 1, .05);

            // Constructing the pair for hashing using std::make_pair
            std::pair<int, float> cur_indices = std::make_pair(maturities[i], yields[i]);

            cBondMap[cur_indices] = cbond;

            // deciding whether a price is above or below 100
            if(cbond.price() > 100){
                std::cout << "Bond Price is above 100"<< std::endl;
            }
            else{
                std::cout << "Bond Price is below 100"<< std::endl;
            }

            // Setting current price
            double cur_price = cbond.price();
            cout << "The price of a bond with maturity " << maturities[i] << " and yield " << yields[i] << " is " << cur_price << endl;
            cout << endl;
    }

    string problem1cresponse = "Similar to the yield, the bond price and time till maturity have an inverse relationship. \n The lower yields and lower times till maturity are above 100, and the higher yields and time till maturity are below zero";

    print_response(problem1cresponse);


    // -------------------------------------------------- PROBLEM 1D ---------------------------------------------------
    print_problem("d");

    for (int i = 0; i < 6; i++) {

            //hashing the already created bonds
            std::pair<int, float> cur_pair = std::make_pair(maturities[i], yields[i]);
            Bond cur_bond = cBondMap[cur_pair];

            cout << "The duration for a bond with price = "<< cur_bond.price() << 
            ", maturity = " << maturities[i] << ", yield = " << yields[i]<< ", and duration = " << cur_bond.duration_f_diff()<< endl;
    
    }
    cout<<endl;

    string problem1danswer = "The coupon bond durations are a lot higher because we are taking the derivative of the discounted coupon \n payments with respect to the yield in addition to the discounted face value. In other words, more terms means more sensitivity" ;

    print_response(problem1danswer);


    // -------------------------------------------------- PROBLEM 1E ---------------------------------------------------
    print_problem("e");
    cout<< "-----------------------------------" << "Zero Coupon Bonds" << "----------------------------------- \n" << endl;

    for (int i = 0; i < 6; i++) {

            //hashing the already created bonds
            std::pair<int, float> cur_pair = std::make_pair(maturities[i], yields[i]);
            Bond cur_bond = zeroBondMap[cur_pair];

            cout << "The second derivative for a zero coupon bond with price = "<< cur_bond.price() << 
            ", maturity = " << maturities[i] << ", yield = " << yields[i]<< ", is der2 = " << cur_bond.der2()<< endl;
    
    }
    cout<<endl;


    cout<< "-----------------------------------" << "Coupon Bonds" << "----------------------------------- \n" << endl;

    for (int i = 0; i < 6; i++) {

            //hashing the already created bonds
            std::pair<int, float> cur_pair = std::make_pair(maturities[i], yields[i]);
            Bond cur_bond = cBondMap[cur_pair];


            cout << "The second derivative for a coupon bond with price = "<< cur_bond.price() << 
            ", maturity = " << maturities[i] << ", yield = " << yields[i]<< ", is der2 = " << cur_bond.der2() << endl;
    
    }
    cout<<endl;

    string problem1eanswer = "The second derivatives are positive" ;

    print_response(problem1eanswer);


    // -------------------------------------------------- PROBLEM 1F ---------------------------------------------------

    print_problem("f");

    Bond ptf1_1longzero(100, 1, .055, 0, 0);
    Bond ptf1_3longzero(100, 3, .05, 0, 0);
    Bond ptf1_2shortzero(100, 2, .052, 0, 0);

    double iv_ptf1 = ptf1_1longzero.price() +  ptf1_3longzero.price() - 2*ptf1_2shortzero.price();

    print_answer("The initial value of the portfolio is $" + std::to_string(iv_ptf1));


    // -------------------------------------------------- PROBLEM 1G ---------------------------------------------------

    print_problem("g");

    double ptf1_weight1 = ptf1_1longzero.price()/ iv_ptf1;
    double ptf1_weight2 = ptf1_2shortzero.price()/ iv_ptf1;
    double ptf1_weight3 = ptf1_3longzero.price()/iv_ptf1;

    double ptf1_duration = ptf1_weight1 * ptf1_1longzero.duration() + ptf1_weight3 * ptf1_3longzero.duration() - 2* ptf1_weight2 * ptf1_2shortzero.duration();
    double ptf1_convexity = ptf1_weight1 * ptf1_1longzero.convexity() + ptf1_weight3 * ptf1_3longzero.convexity() - 2* ptf1_weight2 * ptf1_2shortzero.convexity();
    
    print_answer("The portfolio duration is " + std::to_string(ptf1_duration) + " and the convexity is " + std::to_string(ptf1_convexity));
    print_response("The convexity is bigger");


    // -------------------------------------------------- PROBLEM 1H ---------------------------------------------------
    print_problem("h");

    print_answer("The portfolio is already duration neutral");

    // -------------------------------------------------- PROBLEM 1I ---------------------------------------------------
    print_problem("i");

    Bond ptf1a_1longzero(100, 1, .065, 0, 0);
    Bond ptf1a_3longzero(100, 3, .06, 0, 0);
    Bond ptf1a_2shortzero(100, 2, .062, 0, 0);

    double iv_ptf1a = ptf1a_1longzero.price() +  ptf1a_3longzero.price() - 2*ptf1a_2shortzero.price();

    print_answer("The initial value of the adjusted portfolio is $" + std::to_string(iv_ptf1a));
    print_response("The value of the portfolio increases");

    // -------------------------------------------------- PROBLEM 1J ---------------------------------------------------

    print_problem("j");

    Bond ptf1g_1longzero(100, 1, .045, 0, 0);
    Bond ptf1g_3longzero(100, 3, .04, 0, 0);
    Bond ptf1g_2shortzero(100, 2, .042, 0, 0);

    double iv_ptf1g = ptf1g_1longzero.price() +  ptf1g_3longzero.price() - 2*ptf1g_2shortzero.price();

    print_answer("The initial value of the adjusted portfolio is $" + std::to_string(iv_ptf1g));
    print_response("The value of the portfolio dropped, meaning an investor should prefer this portfolio to the other one. \n However, since the investor is short two units of a 2 year bond, they need to make sure that they have enough cash to pay this back.");


    // -------------------------------------------------- PROBLEM 1K ---------------------------------------------------

    print_problem("k");

    Amoritizing_Bond abond(100, 5, .047, 1, .05, .2, 1);

    abond.print_cashflows();


    // -------------------------------------------------- PROBLEM 1J ---------------------------------------------------

    print_problem("j");

    print_answer("The price of the amoritizing bond is " + std::to_string(abond.price()) + " and the duration is " + std::to_string(abond.duration_f_diff()));


    return 0;
}