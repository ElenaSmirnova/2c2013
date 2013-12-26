#include <iostream>
#define n 100

using namespace std;
double q[n];
class Vector {
public:
    double v[n];
    int len;
public:
    Vector(double vect[], int len){
        Set(vect,len);
    }
    Vector() {
    }

    void Print(){
        for (int i = 0;i < len;i++) cout<<v[i]<<" ";
        cout<<"\n";
    }

    void Set(double vNew[], int sizeNew) {
        len = sizeNew;
        for (int i = 0;i < len;i++) v[i] = vNew[i];
    }

    int Size() {
        return(len);
    }

    Vector operator+(Vector nVect) const{
        Vector Vect(q,len);
        for (int i = 0;i < len;i++) Vect.v[i] = v[i] + nVect.v[i];
        return(Vect);
    }

    Vector operator-(Vector nVect) const{
        Vector Vect(q,len);
        for (int i = 0;i < len;i++) Vect.v[i] = v[i] - nVect.v[i];
        return(Vect);
    }

    Vector operator*(int a) const{
        Vector Vect(q,len);
        for (int i = 0;i < len;i++) Vect.v[i] = a*v[i];
        return(Vect);
    }

    Vector operator/(int a) const{
        Vector Vect(q,len);
        for (int i = 0;i < len;i++) Vect.v[i] = v[i]/a;
        return(Vect);
    }

    bool operator==(Vector nVect) const{
        for (int i = 0;i < len;i++) if (v[i] != nVect.v[i]) return(false);
        else return(true);
    }

    void operator+=(Vector nVect) {
        for (int i = 0;i < len;i++) v[i] += nVect.v[i];
    }

    ~Vector() {
 //       delete [] v;
    }
};

class Matrix {
public:
    Vector* A;
    int w, h;
public:
    Matrix(int a, int b, Vector v[]) {
        SetMatrix(a, b, v);
    }

    Matrix(){
    }

    void SetMatrix(int a, int b, Vector v[]) {
        h = a;
        w = b;
        A = new Vector[b];
        for(int i = 0;i < a;i++) A[i] = v[i];
    }

    int SizeH() {
        return(h);
    }

    int SizeW() {
        return(w);
    }

    Matrix Transpose() {
        Vector *z;
        z = new Vector[w];
        Vector zero(q,h);
        for (int i = 0;i < h;i++) z[i] = zero;
        Matrix M(w,h,z);
        for(int i = 0;i < w;i++){
            for(int j = 0;j < h;j++){
                M.A[i].v[j] = A[j].v[i];
            }
        }
        return M;
    }

    int Det() {
        if (w != h) return(0);
        if (w == 1) return A[0].v[0];
        int d = w-1;
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
                    M.A[j].v[k] = A[u].v[r];
                }
            }
            res += M.Det()*A[i].v[0]*(((i+1)%2)*2-1);
        }
        delete M.A;
        return(res);
    }

    Matrix Inverse(double det) {
        int d = w;
        Vector *z;
        z = new Vector[d];
        Vector zero(q,d);
        for (int i = 0;i < d;i++) z[i] = zero;
        Matrix Alg(d,d,z);
        Matrix M(d-1,d-1,z);
        for (int i = 0;i < d;i++) {
            for (int j = 0;j < d;j++) {
                for (int k = 0;k < d-1;k++) {
                    for (int r = 0;r < d-1;r++) {
                        int x = k; if (x >= i) x++; int y = r; if (y >= j) y++;
                        M.A[k].v[r] = A[x].v[y];
                    }
                }
                Alg.A[i].v[j] = M.Det()*(((i+j+1)%2)*2-1);
            }
        }
        Alg = Alg.Transpose();
        for (int i = 0;i < d;i++) {
            for (int j = 0;j < d;j++) Alg.A[i].v[j] /= det;
        }
        return(Alg);
    }

    void Print() {
        for (int i = 0;i < h;i++) {
            A[i].Print();
        }
    }

    Vector Multiply(Matrix M, Vector v){
        int d = M.w;
        Vector z(q,d);
        for (int i = 0;i < d;i++) {
            z.v[i] = 0;
            for (int j = 0;j < d;j++) {
                z.v[i] += M.A[i].v[j]*v.v[j];
            }
        }
        return(z);
    }

    ~Matrix() {
        delete[] A;
    }
};

int main() {
    int d; cin>>d;
    int u = d, v = d;
    for (int i = 0;i < n;i++) q[i] = 0;
    Vector zero(q,u);
    Vector *X;
    X = new Vector[v];
    for (int i = 0;i < v;i++) X[i] = zero;
    Matrix M(u,v,X);
    for (int i = 0;i < u;i++) {
        for (int j = 0;j < v;j++) cin>>M.A[i].v[j];
    }
    for (int i = 0;i < u;i++) cin>>zero.v[i];
    M.Multiply(M,zero).Print();
    return(0);
}
