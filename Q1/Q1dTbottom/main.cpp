#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <cmath>


const double PI = 3.14159265358979323846264338327950288419716939937510;

int main(int argc, char* argv[])
{

    //initial Data CASE2 Input
    double alpha = 4.0;
    double theta0 = 0.5*PI;
    double T = 1.0;
    int N;
    int h_num = 5;

    //Vector for different step sizes
    double* h = new double[h_num];
    h[0] = T/16.0;
    for(int i = 1;i<h_num;i++)
    {
        h[i] = h[i-1]/2.0;
    }

    double* pF = new double(2);
    double* pY = new double(2);
    double Y_temp;
    double m;
    double T_h_Bottom;
    double T_Bottom = 1.854074677301/sqrt(alpha);
    std::cout << "Real T " << T_Bottom << std::endl;

    //Set Output Stream
        // Setting stream file precision
        std::ofstream output_file;
        output_file.setf(std::ios::scientific,std::ios::floatfield);
        output_file.precision(8);
        output_file.open("Case2_T_h_Bottom.dat");
        assert(output_file.is_open());

    for(int j = 0;j<h_num;j++)
    {
        //assign new number of points depending on Stepsize
        N = (int)(T/h[j]);

        // EULER's Method
//        std::cout<< "Euler's Method with h = " << h[j] << std::endl;
        std::cout<< h[j] << " ";

        pY[0] = theta0;
        pY[1] = 0.0;
        // std::cout << pY[0] << " " << pY[1];
        //Print out Steps
//            std::cout<<std::scientific;
//            std::cout.precision(3);
//            std::cout << "y("<<0.0<<") ";
//            std::cout.precision(5);
//            std::cout << " = ( " << pY[0] << " , " << pY[1] << " )\n";

        //loop to use Euler's Method
        for(int i=0;i<=N;i++)
        {

            //Calculate f(y)
            pF[0] = pY[1];
            pF[1] = -alpha*sin(pY[0]);

            //saving pY
            Y_temp = pY[0];

            //update Y_n+1 - Euler's Method
            pY[0] = pY[0]+h[j]*pF[0];
            pY[1] = pY[1]+h[j]*pF[1];

            //Print out Steps
//            std::cout<<std::scientific;
//            std::cout.precision(3);
//            std::cout << "y("<<h[j]*(double)i<<") ";
//            std::cout.precision(5);
//            std::cout << " = ( " << pY[0] << " , " << pY[1] << " )\n";

            //check if new updated theta is smaller then 0
            if(pY[0]<0.0 && Y_temp>=0.0)
            {
                // if Yes, do linear interpolation between the two points
                m = (pY[0]-Y_temp)/h[j];
                T_h_Bottom = (i)*h[j]-Y_temp/m;
            }
        }

        output_file << std::setw(20) << h[j]
            << std::setw(20) << T_h_Bottom
            << std::setw(20) << fabs(T_Bottom-T_h_Bottom) << std::endl;

//        std::cout << "T_bottom = " << T_h_Bottom << std::endl;
        std::cout << T_h_Bottom << " " << fabs(T_Bottom-T_h_Bottom) << std::endl;

        delete[] pF;
        delete[] pY;

    }
    output_file.close();

    delete[] h;
}
