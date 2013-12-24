#include <iostream>
#define n 50

using namespace std;

double q[n];

class Vector 
    {
    public:
    double v[n];
    int size;

    public:

      Vector(double vect[], int size)
{
        Set(vect,size);
    }
    Vector() 
{
    }

   

    Vector plus(Vector vektor1) const
{
        Vector result(q,size);
        for (int i = 0;i < size;i++) 
              result.v[i] = v[i] + vektor1.v[i];
        return(result);
      }

    Vector minus(Vector vektor1) const
{
        Vector result(q,size);
        for (int i = 0;i < size;i++) 
              result.v[i] = v[i] - vektor1.v[i];
        return(result);
      }

         Vector multiply(int a) const
{
        Vector result(q,size);
        for (int i = 0;i < size;i++) 
              result.v[i] = a*v[i];
        return(result);
      }

    Vector divide(int a) const
{
        Vector result(q,size);
        for (int i = 0;i < size;i++) 
              result.v[i] = v[i]/a;
        return(result);
       }

       bool compare(Vector vektor1) const
{
        for (int i = 0;i < size;i++) if (v[i] != vektor1.v[i]) return(false);
        else return(true);
          }

    void op(Vector vektor1) 
{
        for (int j = 0;j < size;j++) v[j] += vektor1.v[j];
       }
     
     void Write()
{
        for (int j = 0;j < size;j++) cout<<v[j]<<" ";
        cout<<"\n";
           }

        void Set(double vNew[], int sizeNew) 
{
        size = sizeNew;
        for (int j = 0;j < size;j++) v[j] = vNew[j];
    }

             int Size() 
{
        return(size);
      }

     ~Vector() 
{
        delete[] v;
      }
};

class Matrica 
{
public:
    Vector* Z;
    int w, h;
public:
    Matrica(int a, int b, Vector v[]) 
{
        SetMatrica(a, b, v);
    }

    Matrica()
{
    }

    void SetMatrica(int x, int y, Vector v[]) 
{
        h = x;
        w = y;
        Z = new Vector[y];
        for(int i = 0;i < x;i++) Z[i] = v[i];
    }

    
 void Write() 
{
        for (int i = 0;i < h;i++) 
{
            Z[i].Write();
        }
    }

    Matrica transponirovanie() 
{
        Vector *z;
         z = new Vector[w];
        Vector zero(q,h);
        for (int i = 0;i < h;i++) z[i] = zero;
        Matrica M(w,h,z);
        for(int i = 0;i < w;i++)
              {
            for(int j = 0;j < h;j++)
                 {
                M.Z[i].v[j] = Z[j].v[i];
                    }
              }  
        return M;
    }

   

int height() 
{
        return(h);
    }

    int width()
{
        return(w);
      }


    ~Matrica() 
{
        delete[] Z;
    }
};

int main() 
{
    int a = 3;
    int b = 3;
    for (int i = 0;i < n;i++) q[i] = 0;
        Vector zero(q,b);
       Vector *X;
    X = new Vector[a];
        for (int i = 0;i < a;i++) X[i] = zero;
    Matrica Mat(a,b,X);
        for (int i = 0;i < a;i++) 
{
        for (int j = 0;j < b;j++) cin>>Mat.Z[i].v[j];
    }
    Mat.Write();

    Matrica T = Mat.transponirovanie();

    T.Write();

    return(0);
}