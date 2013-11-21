#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;

double branin(double *x)
{
 double y;
    y = (x[1]-(5.1/(4*M_PI*M_PI))*x[0]*x[0]+5*x[0]/M_PI-6)*(x[1]-(5.1/(4*M_PI*M_PI))*x[0]*x[0]+5*x[0]/M_PI-6)+10*(1-1/(8*M_PI))*cos(x[0])+10;
    return y;
}
void exch(double &A, double &B)

   { double t = A ; A = B; B = t; }
double fRand(double a, double b)
{
    double f = (double)rand() / RAND_MAX;
    return a + f * (b - a);
}
void printresults (int n, double *f, double x[][2])
{
    for (int i=0; i<n;i++)
    {
        cout << "f[" << i << "] " <<f[i] << "\t";
        cout << "x[" << i << "]= (" << x[i][0] << ", " << x[i][1] << ")" << endl;
    }
}
void selection(double a[], double xAll[][2], int l, int r)
 {
    for (int i = l; i < r; i++)
      {
            int min = i;
            for (int j = i+1; j <= r; j++)
            {
                if (a[j] < a[min]) {min = j; };
            }
            exch(a[i], a[min]);
            exch(xAll[i][0], xAll[min][0]);
            exch(xAll[i][1], xAll[min][1]);
      }
 }

int main(int argc, char *argv[])
{
    ofstream failas;
    failas.open("failas.txt");
    srand(101); // srand(time(NULL));
    double a[2] = {-5, 0};
    double b[2] = {10, 15};
    double fglobmin(0.397887);
    double eps(0.1);
    bool ar = false;
    double x[2];
    double xMin[2];
    double xAll[100][2];
    double f;
    int sizee = 100;
    double *fAll = new double [sizee];
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
                xMin[0] = x[0];
                xMin[1] = x[1];
                if(abs(fglobmin-fMin)<eps)
                {
                    cout << "Surastas sprendinys skiriasi maziau nei per eps\n";
                    ar = true;
                }
                //isvesti i faila 'rezul_i_fMin.txt' i ir fMin
            }
        if(failas.is_open())
        {
            failas << x[0] << "\t" << x[1] << "\t" << f << endl;
        }
        else
            cout << "Failas neatidarytas\n";
    }
    failas.close();
    //cout << "fMin = " << fMin << endl;
    //cout << "xMin = (" << xMin[0] << ", " << xMin[1] << ")" << endl;
    printresults(100,&fAll[0], xAll);
    cout << "********************************************\n";
    // Adaptive RANDOM SEARCH //
    selection(fAll, xAll, 0, 79);
    printresults(80, &fAll[0], xAll);
    for (int i=0; i<5; i++){
        for (int j=0; j<4; j++){
            x[0] = fRand(xAll[i][0]-0.05*(b[0]-a[0]), xAll[i][0]+0.05*(b[0]-a[0]));
            x[1] = fRand(xAll[i][1]-0.05*(b[1]-a[1]), xAll[i][1]+0.05*(b[1]-a[1]));
            f = branin(&x[0]);
            if (f < fMin){
                fMin = f;
                xMin[0] = x[0];
                xMin[1] = x[1];
                 cout << "Pagerinom!--> ";
                cout << "fMin = " << fMin << ", xMin = (" << xMin[0] << ", " << xMin[1] << ")" << endl;
            }
        }
    }
    cout << "********************************************\n";
     fMin = 1000000;
     int iter = sizee;
     double *fAllTemp;
    //srand(101);
    if (ar == false)
    {
        while (abs(fglobmin-fMin)>eps)
        {
            x[0]=fRand(a[0], b[0]);
            x[1]=fRand(a[1], b[1]);
            f = branin(&x[0]);
            if (iter >= sizee){
                fAllTemp=fAll;
                fAll = new double[sizee*2];

                for (int i=0;i<sizee;i++)
                {

                     fAll[i]=fAllTemp[i];
                }
                sizee=sizee*2;
                delete[] fAllTemp;
            }
                else fAll[iter]=f;
            if (f < fMin)
            {
                fMin = f;
                xMin[0] = x[0];
                xMin[1] = x[1];
            }
            iter++;
        }
    }
    cout << iter << endl;
      cout << "fMin = " << fAll[iter-1] << endl;

    system("PAUSE");
}
