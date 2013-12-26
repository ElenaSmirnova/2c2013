#include <iostream>
#include <string> 
#define n 100

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
        for (int j = 0;j < size;j++) cout<<((int)v[j]+1462448)%26<<" ";
        cout<<"\n";
           }

void Write2()
{
        for (int i = 0;i < size;i++) cout<<(char)(((int)v[i]+1462448)%26+'a');
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
    Matrica(int x, int y, Vector v[]) 
{
        SetMatrica(x, y, v);
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
    
    
Vector Multiply(Matrica Mat, Vector v)
{
        int dim = Mat.w;
        Vector y(q,dim);
        for (int i = 0;i < dim;i++)
                   {
            y.v[i] = 0;
            for (int j = 0;j < dim;j++) 
                         {
                y.v[i] += Mat.Z[i].v[j]*v.v[j];
                 }
        }
        return(y);
    }


    

   int opredelitel() 
   {
        int dim = w-1;
        double det = 0;
        if (w != h) 
           return(0);
         if (w == 1) 
            return Z[0].v[0];
        Vector *y;
        y = new Vector[dim];
        Vector zero(q,dim);
        for (int i = 0;i < dim;i++) 
             y[i] = zero;
        Matrica Mat(dim,dim,y);
        for (int i = 0;i < dim+1;i++) 
              {
              for (int j = 0;j < dim;j++) 
                  {
                for (int k = 0;k < dim;k++) 
                       {
                    int u = j; if (u >= i) u++; int r = k+1;
                    Mat.Z[j].v[k] = Z[u].v[r];
                   }
             }
            det += Mat.opredelitel()*Z[i].v[0]*(((i+1)%2)*2-1);
         }
          delete Mat.Z;
         
        return(det);
    }

    Matrica obratnaya(double det) 
    {
           int dim = w;
           Vector *y;
           int b = det;
           int a = 1;
         y = new Vector[dim];
         Vector zero(q,dim);
        for (int i = 0;i < dim;i++)
             y[i] = zero;
            Matrica Mat1(dim,dim,y);
            Matrica Mat2(dim-1,dim-1,y);
        for (int i = 0;i < dim;i++) 
         {
          for (int j = 0;j < dim;j++) 
                  {
                 for (int k = 0;k < dim-1;k++) 
                               {
                      for (int l = 0;l < dim-1;l++) 
                                     {
                        int x = k; if (x >= i) x++; int c = l; if (c >= j) c++;
                        Mat2.Z[k].v[l] = Z[x].v[c];
                        }
                   }
                Mat1.Z[i].v[j] = Mat2.opredelitel()*(((i+j+1)%2)*2-1);
            }
        }
        Mat1 = Mat1.transponirovanie();
       
        while ((a*b)%26 != 1)
            a++;
           for   (int i = 0;i < dim;i++) 
              {
                 for (int j = 0;j < dim;j++) 
                   Mat1.Z[i].v[j] *= a;
            }
        return(Mat1);
    }

int height() 
{
        return(h);
    }

    int width()
{
        return(w);
      }

Matrica transponirovanie() 
{
        Vector *y;
         y = new Vector[w];
        Vector zero(q,h);
        for (int i = 0;i < h;i++) y[i] = zero;
        Matrica M(w,h,y);
        for(int i = 0;i < w;i++)
              {
            for(int j = 0;j < h;j++)
                 {
                M.Z[i].v[j] = Z[j].v[i];
                    }
              }  
        return M;
    }

    ~Matrica() 
{
        delete[] Z;
    }
};

int main() 
{
    float w;
    string s1,s2;
    cout<<"Vvedite to, chto nado zaschiphrovat\n";
    cin>>s1;
    cout<<"Vvedite to, chto nado raschiphrovat (toi je dliny)\n";
    cin>>s2;
    int a=s1.size();
    int b=a;
    for (int i = 0;i < n;i++) q[i] = 0;
        Vector zero(q,b);
       Vector *X;
    X = new Vector[a];
        for (int i = 0;i < a;i++) X[i] = zero;
    cout<<"Vvedite matricu dliny "<<a<<"\n";    
    Matrica Mat(a,b,X);
        for (int i = 0;i < a;i++) 
{
        for (int j = 0;j < b;j++) cin>>Mat.Z[i].v[j];
    }
    Mat.Write();
    Vector z,y;
    for (int i = 0;i < a;i++) 
       z.v[i] = (int)s1.at(i) - (int)'a';
    for (int i = 0;i < a;i++) 
       y.v[i] = (int)s2.at(i) - (int)'a';
       
  cout<<"vvedite 1 dlya codirovki i 2 dlya decodirovki\n";
  int g;
  cin>>g;
  
 if (g==1) 
   {     
   cout<<"Resultat codirovki \n";
   Mat.Multiply(Mat,z).Write2();
}
else 
   {  
   cout<<"Resultat decodirovki \n"; 
   double c = Mat.opredelitel();
   Matrica T=Mat.obratnaya(c);
   Mat.Multiply(T,y).Write2();
  }

    
    return(0);
}
