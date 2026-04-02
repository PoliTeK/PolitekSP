#pragma once
#include <cstdint>

class IIR {
public:
    IIR();
    ~IIR();

    enum FilterType {
        Bessel = 0,
        Bessel4,      // Nuovo
        Butterworth,
        Butterworth4
    };

    void Init(FilterType filter_type);
    float Process(float in);

private:
    FilterType _filterType;

    // --- Butterworth 2nd Order ---
    static const int _ButterORDER = 2;
    float _butter_b[_ButterORDER + 1] = {0.00362168f, 0.00724336f, 0.00362168f};
    float _butter_a[_ButterORDER + 1] = {1.00000000f, -1.82269493f, 0.83718165f};
    float _Butter_buff[_ButterORDER] = {0.0f, 0.0f};

    // --- Butterworth 4nd Order ---
    static const int _Butter4ORDER = 4;
    float _butter4_b[_Butter4ORDER + 1] = {0.00001329f, 0.00005317f, 0.00007976f, 0.00005317f, 0.00001329f};
    float _butter4_a[_Butter4ORDER + 1] = {1.00000000f, -3.67172909f, 5.06799839f, -3.11596693f, 0.71991033f};
    float _Butter4_buff[_Butter4ORDER] = {0.0f, 0.0f, 0.0f, 0.0f};

    // --- Bessel 2nd Order ---
    static const int _BesselORDER = 2;
    float _bessel_b[_BesselORDER + 1] = {0.00540053f, 0.01080106f, 0.00540053f};
    float _bessel_a[_BesselORDER + 1] = {1.00000000f, -1.74020047f, 0.76180259f};
    float _Bessel_buff[_BesselORDER] = {0.0f, 0.0f};

    // --- Bessel 4nd Order ---
    static const int _Bessel4ORDER = 4;
    float _bessel4_b[_Bessel4ORDER + 1] = {0.00002987f, 0.00011946f, 0.00017920f, 0.00011946f, 0.00002987f};
    float _bessel4_a[_Bessel4ORDER + 1] = {1.00000000f, -3.52224590f, 4.66711231f, -2.75679304f, 0.61240450f};
    float _Bessel4_buff[_Bessel4ORDER] = {0.0f, 0.0f, 0.0f, 0.0f};
};