//Азбиль Александр
#include <iostream>
#include <cmath>

using namespace std;

class Line
{
    public:
    double x0;
    double k;
   void writeIt()
   {
       cout << x0 << "\n";
       cout <<  k << "\n\n";;
   }
};
class Circle
{
    public:
   double R;
   double x;
   double y;
   void writeIt()
   {
       cout << R << "\n";
       cout << x << "\n";
       cout <<  y << "\n\n";;
   }
};
double** crossPoints(Line line, Circle circle)
{
    double** target = new double*[2];
    for (int i = 0; i < 2; ++i)
    {
       target[i] = new double[2];
    }
    double Discr = (line.k*(line.x0 - circle.y) - circle.x)*(line.k*(line.x0 - circle.y) - circle.x) -
    ((line.k)*(line.k) + 1) * ((line.x0 - circle.y)*(line.x0 - circle.y) + (circle.x)*(circle.x) - (circle.R)*(circle.R));
    if (Discr > 0)
    {
        target[0][0] = (circle.x - line.k*(line.x0 - circle.y) + sqrt(Discr))/ ((line.k*line.k + 1));
        target[0][1] = line.k*target[0][0] + line.x0;
        target[1][0] = (circle.x - line.k*(line.x0 - circle.y) - sqrt(Discr))/ ((line.k*line.k + 1));
        target[1][1] =  line.k*target[1][0] + line.x0;
    }
    if (Discr == 0)
    {
        target[0][0] = (- line.k*(line.x0 - circle.y) + circle.x)/ (line.k *line.k + 1);
        target[0][1] = sqrt((circle.R)*(circle.R) - (target[0][0] - circle.x)*(target[0][0] - circle.x)) + circle.y;
        target[1] = NULL;
    }
    if (Discr < 0)
    {
        target = NULL;
    }
    return target;
}
int main()
{
    Circle * circle = new Circle();
    cout << "Enter R\n";
    cin >> circle->R;
    cout << "Enter x\n";
    cin >> circle->x;
    cout << "Enter y\n";
    cin >> circle->y;
    Line * line = new Line();
    cout << "Enter k\n";
    cin >> line->k;
    cout << "Enter x0\n";
    cin >> line->x0;
    cout << "\n";
    circle->writeIt();
    line->writeIt();

    int i = 0;
    double** a = crossPoints(*line, *circle);
    if ((a==NULL))
    {
        cout << "The intersection is empty." ;
    }
    else
    {
        cout << "Intersection points:\n";
    while ((a[i]!=NULL )&&(i<2))
       {
           if ((a[i][0]==NAN)||(a[i][1]==NAN))
            return 0;
           cout << a[i][0] << "\n" ;
           cout <<  a[i][1] << "\n\n";
           i++;
       }
    }
    delete circle;
    delete line;
    cout << endl;
    return 0;
}
