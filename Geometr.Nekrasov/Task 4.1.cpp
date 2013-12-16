#include <iostream>
#include <math.h>
using namespace std;



class Line {
    public:

        void set_a(float line_a)
        {
            a = line_a;
        }

        float get_a()
        {
            return a;
        }

        void set_b(float line_b)
        {
            b = line_b;
        }

        float get_b()
        {
            return b;
        }

        void print(){
        cout<<"a = "<<a<<", b = "<<b<<"\n";

        }


    private:

        float a;
        float b;

};

class Circle {
    public:

        void set_x(float line_x)
        {
            x = line_x;
        }

        float get_x()
        {
            return x;
        }

        void set_y(float line_y)
        {
            y = line_y;
        }

        float get_y()
        {
            return y;
        }

        void set_R(float line_R)
        {
            R = line_R;
        }

        float get_R()
        {
            return R;
        }

        void print(){
        cout<<"x = "<<x<<", y = "<<y<<", R = "<<R<<"\n";

        }

    private:

    float x;
    float y;
    float R;

};


void Solve (Line line, Circle circle){

    float a,b,R,x,y;
    float c1, c2, D;

    a=line.get_a;
    b=line.get_b;

    x=circle.get_x;
    y=circle.get_y;
    R=circle.get_R;

    D=(((x+a/b*b-(y*a)/b))*(x+a/b*b-(y*a)/b)-(1+(a)*(a)/((b)*(b)))*(x*x+(1/b-y)*(1/b-y)-R*R));

    if(D<0){
    cout<<"there aren`t roots";
    }
    else{
    c1=(x+(1/b-y)*a/b+sqrt(D))/(1+a*a/(b*b));
    c2=(x+(1/b-y)*a/b-sqrt(D))/(1+a*a/(b*b));
    cout<<"c1 = "<<c1<<"c2 = "<<c2<<"\n";
    };
};

int main()
{
    float a, b, x ,y, R;

    cout<<"Print a and b: \n";

    cin>>a; cin>>b;

    cout<<"Print x, y and R: \n";

    cin>>x;
    cin>>y;
    cin>>R;

    class Line line;
    line.set_a(a);
    line.set_b(b);

    line.print();

    class Circle circle;
    circle.set_R(R);
    circle.set_x(x);
    circle.set_y(y);

    circle.print();

    Solve(line,circle);

    return 0;
}

