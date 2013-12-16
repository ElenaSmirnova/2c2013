#include <iostream>
#include <string.h>
#include <math.h>
#define u 100


//using namespace std;
int s[u][u];
int q[u];




class Matrix(){}
class Vector(){
    private:

        int size;
        int x[u];


    public:

        Vector(int size,int x[u])
        {
            SetVector(size, x[u]);
        }


        ~Vector(void);

        Vector(const Vector &vec) { size = vec.size;  
        for(i=0;i<size;i++){x[i]=vec.x[i];}  }

        int size(){
            return size;
            }

        void GetVector()
        {
            for(i=0;i<size;i++){printf("%d\n", x[i])};
        }


        void SetVector(int size_1, int x_1[u])
        {
            size=size_1;
            for(i=0;i<size;i++){x[i]=x_1[i]};
        }



        Vector operator+(Vector vec) const{

            for(i=0;i<u;i++){q[i]=0;}

            Vector v(size,q[u]);
            for(i=0;i<size;i++){v.x[i]=x[i] + vec.x[i]};
            return v;
            }


        bool operator==(Vector vec) const{
        for(i=0;i<size;i++){
            if(x[i]==vec.x[i])
            {}
            else{return false;}
            return true;
            }}

        Vector operator*(float a) const{

            for(i=0;i<u;i++){q[i]=0;}

            Vector v(size,q[u]);
            for(i=0;i<size;i++){v.x[i]=a*x[i]};
            return v;
            }

        Vector operator/(Vector vec) const{

            for(i=0;i<u;i++){q[i]=0;}

            Vector v(size,q[u]);
            for(i=0;i<size;i++){v.x[i]=x[i]*vec.x[i]};
            return v;
            }

        Vector operator%(Matrix mat) const{

            for(i=0;i<u;i++){q[i]=0;}

            Vector v(size,q[u]);
            for(i=0;i<size;i++)
            {
                for(j=0;j<mat.length;j++)
                {
                    v.x[i]=v.x[i]+x[j]*mat.a[i][j];
                }
            }
                return v;
            }


}

class Matrix(){
    private:

        int length;
        int width;
        int a[u][u];


    public:

        int length(){
            return length;
            }

        Matrix(int length,int width,int a[u][u])
        {
            SetMatrix(length,width,a[u][u]);
        }

        ~Matrix(void);

        Matrix(const Matrix &vec) { length = vec.length;
        width=vec.width;  
        for(i=0;i<width;i++){
                for(j=0;j<length;j++){a[i][j]=vec.a[i][j]};}  }

        int width(){
            return width;
            }



        void SetMatrix(int length_1,int width_1,int a_1[u][u])
        {
            length=length_1;
            width=width_1;
            for(i=0;i<width;i++){
                for(j=0;j<length;j++){a[i][j]=a_1[i][j]};}
        }

        Matrix operator+(Matrix mat) const{

            for(i=o;i<u;i++){for(j=o;j<u;j++){s[i][j]=0;}}

            Matrix m(mat.length,mat.width,s[u][u]);
            for(i=0;i<width;i++){
                for(j=0;j<length;j++){m.a[i][j]=a[i][j]+mat.a[i][j]};}
            return m;
            }


        bool operator==(Matrix mat) const{
        for(i=0;i<width;i++){
        for(j=0;j<length;j++){
            if(a[i][j]==mat.a[i][j])
            {}
            else{return false;}}}
            return true;
            }

        Matrix operator*(float a) const{

            for(i=o;i<u;i++){for(j=o;j<u;j++){s[i][j]=0;}}

            Matrix mat(length,width,s[u][u]);
            for(i=0;i<width;i++){
            for(j=0;j<length;j++){
            {mat.a[i][j]=a[i][j]*a};
            }}
            return mat;
            }

        Matrix operator/(Matrix mat) const{

            for(i=o;i<u;i++){for(j=o;j<u;j++){s[i][j]=0;}}

            Matrix M(mat.length, width, s[u][u]);
            for(i=0;i<M.width;i++){
            for(j=0;j<M.length;j++){

                for(t=0;t<length;t++)
                {
                    M.a[i][j]=M.a[i][j]+a[i][t]*mat.a[t][j];
                }

            }}
            return M;
            }


        Matrix transpose()
        {

            for(i=o;i<u;i++){for(j=o;j<u;j++){s[i][j]=0;}}

            Matrix M(width, length,s[u][u]);
            //M=SetMatrixSet(width, length, s[u][u])
            for(i=0;i<length;i++){
            for(j=0;j<width;j++){
            M.a[i][j]=a[j][i];
            }}
            return M;
        }

        int Determinant()
        {

        }

        Matrix inverse()
        {

        }
}

Vector Hill(string key, string String)
{
    int l,h,l_1,code;
    int a[u][u];
    int x[u];
    for(i=o;i<u;i++){for(j=o;j<u;j++){a[i][j]=0;}}
    for(i=o;i<u;i++){x[i]=0;}

    //
    h=sizeof(key);
    l=sqrt(h);

            for(i=0;i<l;i++){
            for(j=0;j<l;j++){
                code=key[i*l+j]-'A';
                a[i][j]=code;
            }}

    //

    Matrix M(l,l, a[u][u]);

    l_1=sizeof(String);
    for(i=o;i<l_1;i++)
    {
        code=String[i]-'A';
        x[i]=code;}


    Vector V(l,x[u]),V_1(l,x[u]);

    V_1=V_1*M;

    for(i=o;i<l_1;i++)
    {
        V_1.x[i]=V_1.x[i] % 26;}

      for(i=o;i<l_1;i++)
      {
          String[i]='A'+V_1.x[i];
      }

    return String;
}

Vector DeHill(string key, string String)
{
        int l,h,l_1,code;
    int a[u][u];
    int x[u];
    for(i=o;i<u;i++){for(j=o;j<u;j++){a[i][j]=0;}}
    for(i=o;i<u;i++){x[i]=0;}

    //
    h=sizeof(key);
    l=sqrt(h);

            for(i=0;i<l;i++){
            for(j=0;j<l;j++){
                code=key[i*l+j]-'A';
                a[i][j]=code;
            }}

    //

    Matrix M(l,l, a[u][u]);

    l_1=sizeof(String);
    for(i=o;i<l_1;i++)
    {
        code=String[i]-'A';
        x[i]=code;}


    Vector V(l,x[u]),V_1(l,x[u]);

    Matrix mat(l,l,a[u][u]);
    mat=inverse(M);

    V_1=V_1*mat;

    for(i=o;i<l_1;i++)
    {
        V_1.x[i]=V_1.x[i] % 26;}

      for(i=o;i<l_1;i++)
      {
          String[i]='A'+V_1.x[i];
      }

    return String;
}
