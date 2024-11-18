#pragma once


class Bond{
    public:
     // Bond information given face values, maturity, coupon rate, coupons per year, and coupon rate
        Bond();

        Bond(float face_value, float maturity, float yield, int coupons_per_year, float coupon_rate);

        virtual double price();
        double duration_f_diff();
        double der2();
        double duration();
        double convexity();

        float face_value_;
        int maturity_ ;
        float yield_;
        float coupons_per_year_;
        float coupon_rate_;
        float coupon;

    private:
        double price_ ;
        double der2_;
};

class Amoritizing_Bond : public Bond {
    public:
        Amoritizing_Bond();
        Amoritizing_Bond(float face_value, float maturity, float yield, int coupons_per_year, float coupon_rate, float amoritizing_rate, int amoritizing_payments_per_year); // Parameterized constructor

        void print_cashflows();

        float amoritizing_rate_;
        float amoritizing_payments_per_year_;
        double price();
    private:

};