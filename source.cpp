#include"polynomial.h"
#include<iostream>
#include<fstream>
#include"timer.h"

using namespace std;

void multiply_from_file(const char*,bool);

int main(int argc,char* argv[])
{
 multiply_from_file(argv[1],true);
 multiply_from_file(argv[1],false);
 fft_time.print_time_elapsed();   
 return 0;
}


void multiply_from_file(const char* filename,bool fft)
{
    ifstream file(filename);
    ofstream result;
    if(fft)
        result.open("fftmult"); 
    else
        result.open("normalmult");
 if(!file)
    {
        cerr<<"FILE NOT FOUND";
        exit(-1);
    } 
 timer t;
    while(! file.eof())
    {
        string l1,l2;
    
        while(l1.empty() && !file.eof())
        getline(file,l1);
    
        while(l2.empty() && !file.eof())
        getline(file,l2);
    
        if(file.eof())
        break;
    
        if(l1.empty() || l2.empty())
        {
            cerr<<"test file should have even no. of polynomials for multiplying pairwise\n";
            exit(-2);
        }    
        stringstream buff1(l1),buff2(l2);
        double c;
        vector<double> c1,c2;
        while(buff1>>c)
            c1.push_back(c);
        while(buff2>>c)
            c2.push_back(c);
        polynomial p1(c1),p2(c2);
    
        polynomial ans;
        if(fft)      
        {
         ans = polynomial::fft_mult(c1,c2);
         result<<ans<<"\n\n";
        }
        else
        {
            t.start_timer();
            ans = polynomial::mult(c1,c2);
            t.stop_timer();
            result<<ans<<"\n\n";
        }             
    }
    t.print_time_elapsed();
}

