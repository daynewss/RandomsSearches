#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
double branin(double *x){

 double y;
    y = (x[1]-(5.1/(4*M_PI*M_PI))*x[0]*x[0]+5*x[0]/M_PI-6)*(x[1]-(5.1/(4*M_PI*M_PI))*x[0]*x[0]+5*x[0]/M_PI-6)+10*(1-1/(8*M_PI))*cos(x[0])+10;
    return y;
}
double fRand(double a, double b)
{
    double f = (double)rand() / RAND_MAX;
    return a + f * (b - a);
}
void printresults (int n, double *f)
{
    for (int i=0; i<n;i++)
    {
        cout << "f[" << i << "] " <<f[i] << endl;
    }
}

int main()
{
    srand(100); // srand(time(NULL));
    double a[2] = {-5, 0};
    double b[2] = {10, 15};
    double x[2];
    double xMin[2];
    double xAll[100][2];
    double f;
    double fAll[100];
    double fMin = 1000000;
    for (int i=0; i<100;i++)
    {
        x[0]=fRand(a[0], b[0]);
        x[1]=fRand(a[1], b[1]);
        f = branin(&x[0]);
        xAll[i][0]=x[0];
        xAll[i][1]=x[1];
        fAll[i]=f;
        if (f < fMin){
            //isvesti i faila 'rezult_i_f' i ir f
            //isvesti i faila 'rezult_x_f' x ir f
                fMin = f;
                xMin[0] = x[0]; xMin[1] = x[1];
                //isvesti i faila 'rezul_i_fMin.txt' i ir fMin
            }
    }

    //cout << "fMin = " << fMin << endl;
    //cout << "xMin = (" << xMin[0] << ", " << xMin[1] << ")" << endl;
    //realizuoti rezultatu isvedima per f-ja printresults (int n, double *x)
    printresults(100,&fAll[0]);
    printresults(1,&fMin);
    for (int i=0; i<100;i++)
    {
        cout << "xMin = (" << xAll[i][0] << ", " << xAll[i][1] << ")" << endl;
    }
    return 0;
}
