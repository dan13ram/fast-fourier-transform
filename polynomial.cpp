#include"polynomial.h"
#include<iostream>
#include<complex>
#include<bitset>
#include<cmath>
#include"timer.h"

using std::cout;
using std::cin;
using std::bitset;
using std::vector;
using std::complex;

timer fft_time;

const double pi = 4*atan(1);

size_t polynomial::pow2_roundup(size_t num)
{
    if((num & (num-1)) == 0)
        return num;
    const size_t size = 8*sizeof(size_t);
    bitset<size> bits(num);
    size_t pmsb(0);
    for(size_t i=0; i < size; i++)
        if(bits.test(i))
            pmsb = i;

    bitset<size> bits2(0);
    bits2.set(pmsb+1);
    return bits2.to_ulong();
}


polynomial::polynomial():degree(0),coefficient(1,0)
{
    //ZERO POLYNOMIAL CONSTRUCTED WITH DEGREE 1 
}

polynomial::polynomial(const vector<double>& v):coefficient(v),degree(v.size()-1)
{  

}

polynomial::polynomial(size_t n):degree(n)
{
    cout<<"Enter Coefficients in increasing power order:\n";
    for(size_t i=0; i <= degree; i++)
    {
        double t;
        cin>>t;        
        coefficient.push_back(t);
    }
}

ostream & operator <<(ostream &out , const polynomial& p)
{
    for(size_t i=0 ; i <= p.degree ;i++)
        out<<p.coefficient[i]<<" ";
    return out;
}

vector<complex<double> > polynomial::FFT(const vector<double> & P)
{ 
    size_t n = P.size();
    complex<double> w_n = std::polar(1.0,(2*pi/n));
    if(n == 1)
        return(vector<complex<double> >(1,complex<double>(P[0],0.0))); 
    complex<double> w(1);
    vector< complex<double> > y;
    vector<double> o,e;

    for(size_t i=0,j=1; (i<n) && (j<n); i+=2,j+=2)
        {
            e.push_back(P[i]);
            o.push_back(P[j]);
        }
    
    vector< complex<double> > v0 = FFT(e);
    vector< complex<double> > v1 = FFT(o);
        
    vector< complex<double> > v(n,0);

    for(size_t k=0; k < n/2 ; k++)
    {
        v[k] = v0[k] + w*v1[k];
        v[k + n/2] =  v0[k]  - w*v1[k];
        w = w * w_n;   
    }

    return v;
}

vector<complex<double> > polynomial::IFFT(const vector<complex<double> >& P)
{ 
    size_t n = P.size();
    complex<double> w_n = std::polar(1.0,(-2*pi/n));
    if(n == 1)
        return P;
    
    complex<double> w(1);
    vector< complex<double> > y;
    vector<complex <double> > o,e;

    for(size_t i=0,j=1; (i<n) && (j<n); i+=2,j+=2)
        {
            e.push_back(P[i]);
            o.push_back(P[j]);
        }
    
    vector<complex<double> > v0 = IFFT(e);
    vector<complex<double> > v1 = IFFT(o);
        
    vector<complex<double> > v(n,0);

    for(size_t k=0; k < n/2; k++)
    {
        v[k] = v0[k] + w*v1[k];
        v[k + n/2] =  v0[k] - w*v1[k];
        w = w * w_n;   
    }

    return v;
}

polynomial polynomial::fft_mult(const polynomial& p1,const polynomial& p2)
{
 const size_t ans_deg = p1.degree + p2.degree;
 size_t padd = pow2_roundup(ans_deg + 1); 

 vector<double> t1(p1.coefficient),t2(p2.coefficient);
 for(size_t i = p1.degree + 1;i < padd;i++)
    t1.push_back(0.0);
 for(size_t i = p2.degree + 1;i < padd;i++)
    t2.push_back(0.0);   
 fft_time.start_timer();
 vector<complex<double> > v1(FFT(t1));
 vector<complex<double> > v2(FFT(t2));
 
 vector<complex<double> > v;
 
 for(size_t i = 0;i < v1.size() && i<v2.size();i++)
 {
    v.push_back(v1[i]*v2[i]);
 } 
 vector<complex<double> > a(IFFT(v));
 vector<double> coeff;

 for(size_t i=0; i <= ans_deg;i++)
    coeff.push_back(a[i].real()/a.size());              //NOTE a.size() will not be (ans_deg + 1)

 fft_time.stop_timer();
 return polynomial(coeff);
}

polynomial polynomial::mult(const polynomial& p1,const polynomial& p2)
{
 vector<double> p(p1.degree+p2.degree + 1,0);
  
 for(size_t i=0;i <= p1.degree ;i++)
    for(size_t j = 0; j <= p2.degree; j++)
        p[i+j] += p1.coefficient[i]*p2.coefficient[j];
 return polynomial(p);
}
