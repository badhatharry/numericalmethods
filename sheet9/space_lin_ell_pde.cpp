#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<iostream>
using namespace std;

double nonlin(double x, double y);

double analytic(double x, double y);

void gauss_seidel(vector<vector<double>> &y_n, double *y_next,
                  vector<vector<double>> &y_npo, int i, int j, double Del);


main() {

    // NOTE: code is very computationally inefficient at this point
    // since the gauss_seidel function is evaluated at every point in space

    int i1 = 0; int i2 = 0; int i3 = 0;
    int Nt = 10000; int Ns = 32; // timesteps and spacesteps
    double D = M_PI/(double)Ns; 
    vector<vector<vector<double>>> 
        y(Nt, vector<vector<double>>(Ns+2, vector<double>(Ns+2)));
    double y_tmp = 0.0;
 
    // Lnorm: L_inf; LAnorm: L^A_inf; L2norm: L^A_2

    double Lnorm = 0.0; double Ltemp = 0.0; double error = 0.000001;
    vector<double> Lnorms;
    double LAnorm = 0.0; double LAtemp = 0.0; vector<double> LAnorms;
    double L2norm = 0.0; vector<double> L2norms;


    // initial for all timesteps
    // the ghost zones are initialized with the boundary condition
    // here, boundary means phi = phi_A = -1./5.*nonlin(x,y)

    for (i1 = 0; i1 < Nt-1; i1++) {
        for (i2 = 1; i2 < Ns+1; i2++) {
            for (i3 = 1; i3 < Ns+1; i3++) {
                y[i1][0][i3] = analytic(0, (double)i3*D);
                y[i1][Ns+1][i3] = analytic(((double)Ns+1.)*D, (double)i3*D);
                y[i1][i2][i3] = 1.0;
            }
            y[i1][i2][0] = analytic((double)i2*D, 0);
            y[i1][i2][Ns+1] = analytic((double)i2*D, ((double)Ns+1.)*D);
        }
    }


    // for-loop Gauss-Seidel

    for (i1 = 1; i1 < Nt-1; i1++) {
        Lnorm = 0.0; LAnorm = 0.0; L2norm = 0.0;
        for (i2 = 1; i2 < Ns+1; i2++) {
            for (i3 = 1; i3 < Ns+1; i3++) {
                gauss_seidel(y[i1], &y_tmp, y[i1+1], i2, i3, D);
                y[i1+1][i2][i3] = y_tmp;
                
                Ltemp = fabs(5.*sin((double)i2*D+2.*(double)i3*D) + 
                    (-4.*y[i1][i2][i3] + (y[i1][i2+1][i3] + y[i1][i2][i3+1]+
                    y[i1+1][i2-1][i3]+y[i1+1][i2][i3-1])) / (D*D));  
               
                LAtemp = y[i1][i2][i3]-sin((double)i2*D+2*(double)i3*D);
                L2norm += LAtemp*LAtemp;

                if (Ltemp > Lnorm) Lnorm = Ltemp;
                if (LAtemp > LAnorm) LAnorm = LAtemp;
                else continue;
            }
        }
        L2norm /= (Ns*Ns);
        Lnorms.push_back(Lnorm); 
        LAnorms.push_back(LAnorm); 
        L2norms.push_back(L2norm);

        if (fabs(Lnorm) < error) break;
    } 


    // print results

    // task a)
    for (i3 = 0; i3 < Ns+2; i3++) {
        for (i2 = 0; i2 < Ns+2; i2++) {
            printf("%3.8lf,%3.8lf,%3.8lf\n", 
                  (double)i3*D, (double)i2*D, y[i1-1][i3][i2]);   
        }
    }

/*
    // task b)
    double ratio = 0.0;
    for (i3 = 1; i3 < Lnorms.size(); i3++) {
        ratio = Lnorms[i3]/Lnorms[i3-1] - 1.;
        printf("%d,%lf\n", i3, ratio);
    }
*/

/*
    // task c)
    for (i3 = 0; i3 < LAnorms.size(); i3++) 
        printf("%d,%lf\n", i3, LAnorms[i3]);
    for (i3 = 0; i3 < L2norms.size(); i3++) 
        printf("%d,%lf\n", i3, L2norms[i3]);
*/


    return 0;
}


double nonlin(double x, double y){
    return -5.*sin(x+2.*y);
}

double analytic(double x, double y){
    return sin(x+2.*y);
}

void gauss_seidel(vector<vector<double>> &y_n, double *y_next,
                  vector<vector<double>> &y_npo, int i, int j, double Del){
    *y_next = 0.25 * (y_n[i+1][j] + y_n[i][j+1] + y_npo[i-1][j] + 
              y_npo[i][j-1]) - pow((Del/2.),2.) * nonlin(i*Del, j*Del);
}


















