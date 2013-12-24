#include <math.h>
#include <iostream>

using namespace std;

class okrujnost 
   {
   public:
      float x;
      float y;
      float radius;
   public:
       okrujnost(float a, float b, float c) 
          {
            parametrize(a,b,c);
          }

   void write()
      {
        cout<<"Koordinaty centra : ";
        cout<<"x = "<<x<<" ";
        cout<<"y = "<<y<<" ";
        cout<<"radius = "<<radius;
      }


   void parametrize(float a, float b, float c) 
           {
               x = a;
               y = b;
               radius = c;
           }
   
};


class Liniya 
     {
 public:
    int x;
    int y;
 public:
       Liniya(int k, int b) 
        {
          parametrize(k,b);
        }

    void write()
       {
        cout<<"uglovoi koefficient = "<<x<<" ";
        cout<<"svobodnyi 4len = "<<y<<" ";
       }

    void parametrize(int k, int b) 
           {
        x = k;
        y = b;
           }
    
};



class reshenie 
   {
public:
     reshenie(Liniya l, okrujnost c) 
       {
          reshai(l.x,l.y,c.x,c.y,c.radius);
       }
    void reshai(float a, float b, float x, float y, float radius)
        {
        float x1, x2, D;
        D =(((x+a/(b*b)-(y*a)/b))*(x+a/(b*b)-y*a/b)-(1+a*a/(b*b))*(x*x+(1/b-y)*(1/b-y)-radius*radius));
        if (D<0)
             {
            cout<<"oni ne peresekayutsa ";
             }
        else 
            {
              x1=(x+(1/b-y)*a/b+sqrt(D))/(1+a*a/(b*b));
              x2=(x+(1/b-y)*a/b-sqrt(D))/(1+a*a/(b*b));
              cout<<"1-ya tochka peresecheniya = ("<<x1<<";"<<(x1*a+b)<<") ";
              cout<<"2-ya tochka peresecheniya = ("<<x2<<";"<<(x2*a+b)<<") ";
            }
    };
};

   int main()
   {
    float k, b, x ,y, radius;

    cout<<"vvedite parametry linii (ona zadana v vide y=kx+b) : ";
    cin>>k;
    cin>>b;

    cout<<"vvedite koordinaty centra okrujnosti i radius : ";
    cin>>x;
    cin>>y;
    cin>>radius;

    okrujnost okrujnost(x,y,radius);
    okrujnost.write();

   Liniya Liniya(k,b);
    Liniya.write();

    reshenie(Liniya,okrujnost);

    return(0);
   }