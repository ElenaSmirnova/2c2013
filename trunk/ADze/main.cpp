#include <iostream>

using namespace std;
double q[100];
class Vector {
public:
    double a[100];
    int lenght;
    void Pile(double a1[], int reSize) {
        lenght = reSize;
        for (int i = 0;i < lenght;i++)
            a[i] = a1[i];
    }

    int Size() {
        return(lenght);
    }

    Vector(double vect[], long lenght){
        Pile(vect,lenght);
    }
    Vector() {
    }

    void Print(){
        for (int i = 0;i < lenght;i++)
            cout<<((int)a[i]+26000)%26<<" ";
        cout<<"\n";
    }

    bool operator==(Vector Vector1) const{
        for (int i = 0;i < lenght;i++)
            if (a[i] != Vector1.a[i])
             return(false);
        else return(true);
    }

    Vector operator+(Vector Vector1) const{
        Vector Vect(q,lenght);
        for (int i = 0;i < lenght;i++)
            Vect.a[i] = a[i] + Vector1.a[i];
        return(Vect);
    }

    void operator+=(Vector Vector1) {
        for (int i = 0;i < lenght;i++)
            a[i] += Vector1.a[i];
    }

    Vector operator-(Vector Vector1) const{
        Vector Vect(q,lenght);
        for (int i = 0;i < lenght;i++)
            Vect.a[i] = a[i] - Vector1.a[i];
        return(Vect);
    }

    Vector operator*(int x) const{
        Vector Vect(q,lenght);
        for (int i = 0;i < lenght;i++)
            Vect.a[i] = x*a[i];
        return(Vect);
    }

    Vector operator/(int x) const{
        Vector Vect(q,lenght);
        for (int i = 0;i < lenght;i++) Vect.a[i] = a[i]/x;
        return(Vect);
    }

    ~Vector() {
        delete[] a;
    }
};

class Matrix {
public:
    Vector* A;
    int width, height;
public:
    Matrix(int a, int b, Vector v[]) {
        PutMatrix(a, b, v);
    }

    Matrix(){
    }

    Vector Multiply(Matrix M, Vector v){
    int d = M.width;
    Vector z(q,d);
    for (int i = 0;i < d;i++) {
        z.a[i] = 0;
        for (int j = 0;j < d;j++) {
            z.a[i] += M.A[i].a[j]*v.a[j];
        }
    }
    return(z);
    }

    void PutMatrix(int a, int b, Vector v[]) {
        height = a;
        width = b;
        A = new Vector[b];
        for(int i = 0;i < a;i++)
            A[i] = v[i];
    }

    Matrix Transpose() {
        Vector *z;
        z = new Vector[width];
        Vector zero(q,height);
        for (int i = 0;i < height;i++)
            z[i] = zero;
        Matrix M(width,height,z);
        for(int i = 0;i < width;i++){
            for(int j = 0;j < height;j++){
                M.A[i].a[j] = A[j].a[i];
            }
        }
        return M;
    }

    int Determinant() {
        if (width != height) return(0);
        if (width == 1) return A[0].a[0];
        int d = width-1;
        double res = 0;
        Vector *z;
        z = new Vector[d];
        Vector zero(q,d);
        for (int i = 0;i < d;i++) z[i] = zero;
        Matrix M(d,d,z);
        for (int i = 0;i < d+1;i++) {
            for (int j = 0;j < d;j++) {
                for (int k = 0;k < d;k++) {
                    int u = j; if (u >= i) u++; int r = k+1;
                    M.A[j].a[k] = A[u].a[r];
                }
            }
            res += M.Determinant()*A[i].a[0]*(((i+1)%2)*2-1);
        }
        delete M.A;
        return(res);
    }

    int Height() {
    return(height);
    }

    int Width() {
        return(width);
    }


    Matrix Inverse(double det) {
        int dim = width;
        Vector *z;
        z = new Vector[dim];
        Vector zero(q,dim);
        for (int i = 0; i < dim; i++)
            z[i] = zero;
        Matrix Alg(dim, dim, z);
        Matrix M(dim - 1, dim - 1, z);
        for (int i = 0;i < dim;i++) {
            for (int j = 0;j < dim;j++) {
                for (int k = 0; k < dim - 1; k++) {
                    for (int r = 0;r < dim - 1; r++) {
                        int x = k;
                        if (x >= i) x++;
                        int y = r;
                        if (y >= j) y++;
                        M.A[k].a[r] = A[x].a[y];
                    }
                }
                Alg.A[i].a[j] = M.Determinant()*(((i + j + 1) % 2) * 2 - 1);
            }
        }
        Alg = Alg.Transpose();
        int x = det;
        int a = 1;
        while ((a * x) % 26 != 1) a++;
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++)
                Alg.A[i].a[j] *= a;
        }
        return(Alg);
    }

    void Print() {
        for (int i = 0;i < height;i++) {
            A[i].Print();
        }
    }

    ~Matrix() {
        delete[] A;
    }
};

int main() {
    cout<<"Insert dimension\n";
    int dim; cin>>dim;
    cout<<"Insert matrix\n";
    int u = dim, v = dim;
    for (int i = 0; i < 100; i++)
        q[i] = 0;
    Vector zero(q,u);
    Vector *X;
    X = new Vector[v];
    for (int i = 0; i < v; i++) X[i] = zero;
    Matrix M(u, v, X);
    for (int i = 0; i < u; i++) {
        for (int j = 0; j < v; j++)
         cin>>M.A[i].a[j];
    }
    cout<<"Write string length of dim\n";
    string s;
    cin>>s;
    cout<<"Write the cipher length of dim\n";
    for (int i = 0; i < u; i++)
     cin>>zero.a[i];
    Vector S;
    for (int i = 0;i < dim; i++)
        S.a[i] = (int)s.at(i) - (int)'A';
    cout<<"The encoded string is\n";
    M.Multiply(M,S).Print();
    cout<<"The decoded string is\n";
    Vector T;
    T = M.Multiply(M.Inverse(M.Determinant()),zero);
    for (int i = 0;i < dim; i++)
     cout<<(char)(((int)T.a[i]+26000000)%26+'A');
    return(0);
}
