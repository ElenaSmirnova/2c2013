#include <iostream>
#include <math.h>
using namespace std;

class Line {
public:
    int a;
    int b;
public:
    Line(int par_a, int par_b) {
        setParameters(par_a,par_b);
    }
    void setParameters(int par_a, int par_b) {
        a = par_a;
        b = par_b;
    }
    void print(){
        cout<<"A = "<<a<<", B = "<<b<<"\n";
    }
};

class Circle {
public:
    float x;
    float y;
    float R;
public:
    Circle(float par_x, float par_y, float par_R) {
        setParameters(par_x,par_y,par_R);
    }
    void setParameters(float par_x, float par_y, float par_R) {
        x = par_x;
        y = par_y;
        R = par_R;
    }
    void print(){
        cout<<"x = "<<x<<", y = "<<y<<", R = "<<R<<"\n";
    }
};

class Solve {
public:
    Solve(Line l, Circle c) {
        solve(l.a,l.b,c.x,c.y,c.R);
    }
    void solve(float a, float b, float x, float y, float R){
        float c1, c2, D;
        D =(((x+a/b*b-(y*a)/b))*(x+a/b*b-(y*a)/b)-(1+(a)*(a)/((b)*(b)))*(x*x+(1/b-y)*(1/b-y)-R*R));
        if(D<0){
            cout<<"There's no solutions";
        }
        else {
            c1=(x+(1/b-y)*a/b+sqrt(D))/(1+a*a/(b*b));
            c2=(x+(1/b-y)*a/b-sqrt(D))/(1+a*a/(b*b));
            cout<<"p1 = ("<<c1<<";"<<(c1*a+b)<<") p2 = ("<<c2<<";"<<(c2*a+b)<<")\n";
        }
    };
};

int main()
{

    float a, b, x ,y, R;
    cout<<"Print A and B: \n";
    cin>>a; cin>>b;
    cout<<"Print x, y and R: \n";
    cin>>x; cin>>y; cin>>R;
    Line line(a,b);
    line.print();
    Circle circle(x,y,R);
    circle.print();
    Solve(line,circle);
    return(0);
}
