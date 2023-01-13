#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

#define e 2.718281
#define pi 3.141592

inline float __y(float x) {
    return (1 / (1+x));  // Expression or function will be written here
}

inline float __h(float a, float b, float n) {
    return ((b-a)/n);
}

class Input {
    float a, b;
    int n;

    public:
        // Taking the Given values by using Constructor
        Input() {
            cout << "a = ";
            cin >> a;
            cout << "b = ";
            cin >> b;
            cout << "n = ";
            cin >> n;
        }

        friend class Trapezoidal;
        friend class Simpsons_1by3;
        friend class Simpsons_3by8;
};

class Trapezoidal {
    public: 
        float calculation(Input &obj) {
            float h = __h(obj.a, obj.b, obj.n);
            float x[obj.n];
            float y[obj.n];
            
            // Assining the values of x
            x[0] = obj.a;
            for(int i=1; i<=obj.n; i++) {
                x[i] = x[i-1] + h;
            }

            // Assigning the values to the function
            for(int i=0; i<=obj.n; i++) {
                y[i] = __y(x[i]);
            }

            _sleep(1054);
            cout << endl << "h = " << h;
            for(int i=0; i<=obj.n; i++) {
                cout << endl;
                _sleep(1054);
                cout << "x" << i << " = " << x[i] << " \t f(" << i << ") = " << y[i];
            }

            // Trapezoidal Formula.....  
            float X = (y[0] + y[obj.n]);
            float R = 0;
            for(int i=1; i<obj.n; i++) {
                R += y[i];
            }

            _sleep(1054);
            cout << endl << endl << "By Trapezoidal Formula, We have the Formula, (h/2) * (X + 2R)" << endl << endl;
            _sleep(545);
            cout << "Here, " << endl << "X = " << X << endl;
            _sleep(545);
            cout << "R = " << R << endl;
            float ans = (h/2) * (X + 2*R); 
            _sleep(1054);
            cout << endl << "By Trapezoidal Formula, " << endl << "ans = " << ans;  

            return 0;
        }
};

class Simpsons_1by3 {
    public:     
        float calculation(Input &obj) {
            if(obj.n%2 != 0) {
            cout << endl << "Simpson's 1/3 rd Rule can not be applicable...";
            getch();
            return 0;
            }

            float h = __h(obj.a, obj.b, obj.n);
            float x[obj.n];
            float y[obj.n];
            
            // Assining the values of x
            x[0] = obj.a;
            for(int i=1; i<=obj.n; i++) {
                x[i] = x[i-1] + h;
            }

            // Assigning the values to the function
            for(int i=0; i<=obj.n; i++) {
                y[i] = __y(x[i]);
            }

            _sleep(1054);
            cout << endl << "h = " << h;
            for(int i=0; i<=obj.n; i++) {
                cout << endl;
                _sleep(545);
                cout << "x" << i << " = " << x[i] << " \t f(" << i << ") = " << y[i];
            } cout << endl << endl;

            // Simpson's 1/3 Rule.....
            float X = (y[0] + y[obj.n]);
            float E = 0, O = 0;
            for(int i=1; i<obj.n; i++) {
                if(i%2 == 0) {
                    E += y[i];
                } else {
                    O += y[i];
                }
            }
            _sleep(1054);
            cout << "By Simpson's 1/3 Rule, We have the Formula,\t (h/3) * (X + 2E + 4O)" << endl << endl;
            _sleep(545);
            cout << "X = " << X << endl;
            _sleep(545);
            cout << "E = " << E << endl;
            _sleep(545);
            cout << "O = " << O << endl;
            float ans = (h/3) * (X + 2*E + 4*O); 
            _sleep(1054);
            cout << endl << "By Simpson's 1/3 Rule, " << endl << "ans = " << ans;

            return 0;
        }
};

class Simpsons_3by8 {
    public:
        float calculation(Input &obj) {
            if(obj.n%3 != 0) {
                _sleep(1054);
                cout << endl << "Simpson's 3/8 th Rule can not applicable...";
                getch();
                return 0;
            }

            float h = __h(obj.a, obj.b, obj.n);
            float x[obj.n];
            float y[obj.n];
            
            // Assining the values of x
            x[0] = obj.a;
            for(int i=1; i<=obj.n; i++) {
                x[i] = x[i-1] + h;
            }

            // Assigning the values to the function
            for(int i=0; i<=obj.n; i++) {
                y[i] = __y(x[i]);
            }

            _sleep(1054);
            cout << endl << "h = " << h;
            for(int i=0; i<=obj.n; i++) {
                cout << endl;
                _sleep(545);
                cout << "x" << i << " = " << x[i] << " \t f(" << i << ") = " << y[i];
            } cout << endl << endl;

            // Simpson's 3/8 Rule.....
            float X = (y[0] + y[obj.n]);
            float M3 = 0, R = 0;
            for(int i=1; i<obj.n; i++) {
                if(i%3 == 0) {
                    M3 += y[i];
                } else {
                    R += y[i];
                }
            }

            _sleep(1054);
            cout <<  "By Simpson's 3/8 Rule, We have th formual, \t 3h/8 * (X + 2M3 + 3R)" << endl << endl;  
            _sleep(545);
            cout << "X = " << X << endl;    
            _sleep(545);
            cout << "M3 = " << M3 << endl;  
            _sleep(545);
            cout << "R = " << R << endl;
            float ans = ((3*h)/8) * (X + 2*M3 + 3*R); 
            _sleep(1054);
            cout << endl << "By Simpson's 3/8 Rule, " << endl << "ans = " << ans; 

            return 0;
        }
};

int main() 
{
    Input input;
    int option;
    cout << endl << "Which method you want to perform....." << endl;
    cout << "1. Trapezoidal Rule" << endl;
    cout << "2. Simpson's 1/3 Rule" << endl;
    cout << "3. Simpson's 3/8 Rule" << endl;
    cout << "choose: ";
    cin >> option;

    switch (option) {
        case 1:  {   
            Trapezoidal obj;
            obj.calculation(input);
            break;
        }
        
        case 2: {
            Simpsons_1by3 obj;
            obj.calculation(input);
            break;
        }

        case 3:  {   
            Simpsons_3by8 obj;
            obj.calculation(input);
            break;
        }
        
        default:    {
            cout << endl << "Choose correct option!!!";
            break;
        }
    }
    
    getch();
    return 0;
}
