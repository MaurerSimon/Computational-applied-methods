#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <cmath>

const double PI = 3.14159265358979323846264338327950288419716939937510;

int main(int argc, char* argv[])
{
    //initial Data CASE1 Input
    double alpha = 4.0;
    double theta0 = 0.5*PI;
    double T = 4;
    double h = 0.00001;
    int N = 20*(int)(T/h);

    // EULER's Method
    double* pInitalState = new double[2];
    double* pF = new double[2];
    double* pY = new double[2];
    pInitalState[0] = theta0;
    pInitalState[1] = 0.0;

    pY = pInitalState;

    //Set Output Stream
       // Setting stream file precision
    std::ofstream output_file;
    output_file.setf(std::ios::scientific,std::ios::floatfield);
    output_file.precision(8);
    output_file.open("Case3_Data.dat");
    assert(output_file.is_open());

    std::ofstream output_energy;
    output_energy.setf(std::ios::scientific,std::ios::floatfield);
    output_energy.precision(8);
    output_energy.open("Case3_EulerEnergy.dat");
    assert(output_energy.is_open());

    //loop for Euler's Method
    for(int i=0;i<=N;i++)
    {
        //Print out Steps
//        std::cout<<std::scientific;
//        std::cout.precision(3);
//        std::cout << "y("<<h*(double)i<<") ";
//        std::cout.precision(5);
//        std::cout << " = ( " << pY[0] << " , " << pY[1] << " )\n";
        output_file << std::setw(20) << i*h
                    << std::setw(20) << pY[0]
                    << std::setw(20) << pY[1] << "\n";
        //Energy Graph output
                output_energy << std::setw(20) << i*h
                              << std::setw(20) << 0.5*pow(pY[1],2)-alpha*cos(pY[0])
                              << std::endl;

        //Calculate f(y)
        pF[0] = pY[1];
        pF[1] = -alpha*sin(pY[0]);
        //update Y_n+1 - Euler's Method
        pY[0] = pY[0]+h*pF[0];
        pY[1] = pY[1]+h*pF[1];
    }
    output_file.close();
    output_energy.close();

    delete[] pInitalState;
    delete[] pF;
    delete[] pY;
}
