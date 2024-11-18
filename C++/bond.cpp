/*
@author : Christian Archibald
*/

#include "bond.h"
#include <iostream>
#include <cmath>

Bond::Bond() : 
    face_value_(100), 
    maturity_(1), 
    yield_(0), 
    coupons_per_year_(0), 
    coupon_rate_(0) 
    {}

Bond::Bond(float face_value, float maturity, float yield, int coupons_per_year, float coupon_rate): 
    face_value_(face_value), 
    maturity_(maturity), 
    yield_(yield), 
    coupons_per_year_(coupons_per_year), 
    coupon_rate_(coupon_rate),
    coupon(coupon_rate/coupons_per_year*face_value){};

double Bond::price(){
    price_ = face_value_ * exp(- maturity_ * yield_);

    //discounting the coupon payments

    if(coupons_per_year_ != 0){

        for(int i = 1; i<= maturity_ * coupons_per_year_ ; i++){
            price_ += coupon * exp(- i/coupons_per_year_ * yield_);
        }

    }

    return price_;

}

double Bond::duration_f_diff(){
    //calculating duration using finite differences instead of a derivative

    float eps = pow(10, -4);
    //perturbed bond
    Bond new_bond(face_value_, maturity_, yield_ + eps, 0, 0);

    double derivative = (new_bond.price() - price_)/eps;

    double duration_f_diff_ = -1/price_ *derivative;

    return duration_f_diff_;
}

double Bond::duration(){
    double d = maturity_;

    if (coupons_per_year_ != 0){
        for(int i = 1; i<= maturity_ * coupons_per_year_ ; i++){
            d += i/coupons_per_year_ * coupon * exp(- i/coupons_per_year_ * yield_);
        }
    }

    d =d/price_;

    return d;

}

double Bond::der2(){

    double derivative2 = pow(maturity_,2) * face_value_ * exp(- maturity_ * yield_);

    if (coupons_per_year_ != 0){
        for(int i = 1; i<= maturity_ * coupons_per_year_ ; i++){
            derivative2 += pow(i/coupons_per_year_,2) * coupon * exp(- i/coupons_per_year_ * yield_);
        }

    }
    
    der2_ = derivative2;
    return der2_;

}

double Bond::convexity(){
    return 1/price_ * der2();
}

Amoritizing_Bond::Amoritizing_Bond() 
    : Amoritizing_Bond(100, 1, 0, 0, 0, 0, 0) {}

Amoritizing_Bond::Amoritizing_Bond(float face_value, float maturity, float yield, int coupons_per_year, float coupon_rate, float amoritizing_rate, int amoritizing_payments_per_year): Bond(face_value, maturity, yield, coupons_per_year, coupon_rate),
      amoritizing_rate_(amoritizing_rate),
      amoritizing_payments_per_year_(amoritizing_payments_per_year) {}

void Amoritizing_Bond::print_cashflows(){
    float remaining_fv = face_value_;

    for(int i = 1; i<= coupons_per_year_ * maturity_; i++){
        float amoritization_payment = remaining_fv * amoritizing_rate_;

        if(i != i<= coupons_per_year_ * maturity_){

            float cashflow = coupon + amoritization_payment;
            std::cout<< "At time t = " << i/coupons_per_year_ << " the cashflow is " << cashflow << std::endl;

        }
        else{

            float cashflow = coupon + remaining_fv;
            std::cout<< "At time t = " << i/coupons_per_year_ << " the cashflow is " << cashflow << std::endl;

        }

        remaining_fv -= amoritization_payment;
    }
}

double Amoritizing_Bond::price(){

    float p = 0;

    float remaining_fv = face_value_;

    for(int i = 1; i<= coupons_per_year_ * maturity_; i++){
        float amoritization_payment = remaining_fv * amoritizing_rate_;

        if(i != i<= coupons_per_year_ * maturity_){

            float cashflow = coupon + amoritization_payment;
            p += cashflow * exp(-yield_*i/coupons_per_year_);
    
        }
        else{

            float cashflow = coupon + remaining_fv;
            p += cashflow * exp(-yield_*i/coupons_per_year_);
        }

        remaining_fv -= amoritization_payment;
    }

    return p;

}