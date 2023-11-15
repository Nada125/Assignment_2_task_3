#include <iostream>
#include<bits/stdc++.h>
#include <fstream>

using namespace std;
bool fileloaded=true;
string DtH(int n) {
    // ans string to store hexadecimal number
    string ans = "";

    while (n != 0) {
        // remainder variable to store remainder
        int rem = 0;

        // ch variable to store each character
        char ch;
        // storing remainder in rem variable.
        rem = n % 16;

        // check if temp < 10
        if (rem < 10) {
            ch = rem + 48;
        } else {
            ch = rem + 55;
        }

        // updating the ans string with the character variable
        ans += ch;
        n = n / 16;
    }

    // reversing the ans string to get the final result
    int i = 0, j = ans.size() - 1;
    while (i <= j) {
        swap(ans[i], ans[j]);
        i++;
        j--;
    }
    return ans;
}

int HtD(string hexVal) {
    int len = hexVal.size();

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    int dec_val = 0;

    // Extracting characters as digits from last
    // character
    for (int i = len - 1; i >= 0; i--) {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

            // if character lies in 'A'-'F' , converting
            // it to integral 10 - 15 by subtracting 55
            // from ASCII value
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            dec_val += (int(hexVal[i]) - 55) * base;

            // incrementing base by power
            base = base * 16;
        }
    }
    return dec_val;
}


class Register {
    string arr[16] = {"0"};
public:
    void setval(int index, string val) {
        arr[index] = val;

    }
    Register()
    {
        for(int i=0;i<16;i++)
        {
            arr[i]="00";
        }
    }

    string getval(int index) {
        return arr[index];
    }
};

class Memory {
    string arr[256] = {"0"};

public:
    Memory()
    {
        for(int i=0;i<256;i++)
        {
            arr[i]="00";
        }
    }
    void setval(int index, string val) {
        arr[index] = val;

    }

    string getval(int index) {
        return arr[index];
    }
    
};

class Machine {
public:
    Memory m;
    Register r;
    
    void load_file(string a) {
        ifstream x(a);
        if (!x.is_open()) {
            cout << "Failed to open the file" <<endl<<"Program terminated"<<endl;
            fileloaded=false;
        }
        string line;
        int i = 0;
        while (getline(x, line)) {
            m.setval(i, line.substr(0, 2));
            m.setval(i + 1, line.substr(2, 4));
            i += 2;
        }
        x.close();
    }

    void execute_command(string line) {
        if (line[0] == '1') {
            string s(1, line[1]);//14A3
            r.setval(HtD(s), m.getval(HtD(line.substr(2, 4))));
        }
        if (line[0] == '2') {
            string s(1, line[1]);
            r.setval(HtD(s), line.substr(2, 4));

        }
        if (line[0] == '3' && line[2] !='0'&& line[3]!='0') {
            string s(1, line[1]);//35B1
            m.setval(HtD(line.substr(2, 4)), r.getval(HtD(s)));
        }
        if (line[0] == '3'&& line[2] =='0'&& line[3]=='0') {
            string s(1, line[1]);//35B1
            cout<<"Number printed to screen by the simulator : "<<r.getval(HtD(s))<<endl;
        }

        if (line[0] == '4') {
            string s(1, line[2]);
            string s2(1, line[3]);
            r.setval(HtD(s2), r.getval(HtD(s)));
        }
        if (line[0] == '5') {
            string s(1, line[1]);
            string s2(1, line[2]);
            string s3(1, line[3]);
            int val1 = HtD(r.getval(HtD(s2)));
            int val2 = HtD(r.getval(HtD(s3)));
            string result = DtH(val1 + val2);
            if(result.size()==1)
            {
                r.setval(HtD(s), "0"+result);
            }
            else
            {
                r.setval(HtD(s),result);
            }
            
        }

    }

    void run_program() {
        int i = 0;
        while (true) {
            string code = m.getval(i) + m.getval(i + 1);
            if (code[0] == 'C') {
                break;
            }
            if (code[0] == 'B') {//b403
                string s(1, code[1]);
                if (HtD(r.getval(HtD(s))) == HtD(r.getval(0))) {
                    i = HtD(code.substr(2, 4));
                } else {
                    i += 2;
                    continue;
                }
            } else {
                execute_command(code);
                i += 2;
            }
        }
    }

void printmem()
{   
    
    for(int i=0;i<256;i++)
    {
        if(i==0)
        {
            cout<<"00"<<" - "<<m.getval(i)<<endl;
        }
        else if(i<=15)
        {
            cout<<"0"<<DtH(i)<<" - "<<m.getval(i)<<endl;
        }
        else{
        cout<<DtH(i)<<" - "<<m.getval(i)<<endl;
        }
    }
    
}
void printreg()
{
    
    for(int i=0;i<16;i++)
    {
        if(i==0)
        {
            cout<<"00"<<" - "<<r.getval(i)<<endl;
        }
        else if(i<=15)
        {
            cout<<"0"<<DtH(i)<<" - "<<r.getval(i)<<endl;
        }
    }
    
}
};


int main() {
    Machine ma;
    string a;
    int x;
    cout<<"Enter the file name to load the memory from : "<<endl;
    cin>>a;
    ma.load_file(a + ".txt");
    if(fileloaded==false)
    {
        return 0;
    }
    while(true){
    cout<<"____________________________________________________________"<<endl;
    cout<<"Please choose the operation : "<<endl<<"1 - print out the current memory"<<endl<<"2 - print out the current register"<<endl<<"3 - Run the program with the current loaded txt file "<<endl<<"4 - Terminate the code"<<endl;
    cin>>x;
     
    switch (x)
    {
   
    case 1:
        ma.printmem();
        
        break;
    
    case 2:
        ma.printreg();
        
        break;
    case 3:
        ma.run_program();
        cout<<"Done"<<endl;
        break;
    case 4:
        cout<<"Done"<<endl;
        return 0;
    }
    }
    return 0;
}
