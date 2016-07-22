#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include<complex>
#include<vector>
#include<iostream>
#include"timer.h"

extern timer fft_time;

using std::complex;

using std::vector;
using std::ostream;
class polynomial
{
    size_t degree; 
    vector<double> coefficient;         
    vector< complex<double> >  dft;
       
    static size_t pow2_roundup(size_t);
    static vector< complex<double> > FFT(const vector<double>&);
    static vector<complex <double> > IFFT(const vector<complex<double> >&);
  public:
    polynomial();
    polynomial(size_t);
    polynomial(const vector<double>&);
    polynomial(const vector<complex<double> >&);
    static polynomial mult(const polynomial&,const polynomial&);
    static polynomial fft_mult(const polynomial&,const polynomial&);
    friend ostream& operator <<(ostream& ,const polynomial&);	
};

#endif
