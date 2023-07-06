#include <iostream>
#include <string>

using namespace std;


string M = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.\"'1234567890";
string M1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.\"'1234567890";
string M2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.\"'1234567890";
string M3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.\"'1234567890";
string Rotor1 = "LPGSZMHAEOQKVXRFYBUTNICJDW ,.\"'1234567890";
string Rotor2 = "SLVGBTFXJQOHEWIRZYAMKPCNDU ,.\"'1234567890";
string Rotor3 = "CJGDPSHKTURAWZXFMYNQOBVLIE ,.\"'1234567890";
string Reflector = "IMETCGFRAYSQBZXWLHKDVUPOJN ,.\"'1234567890";
string Entry = "QWERTZUIOASDFGHJKPYXCVBNML ,.\"'1234567890";

void Gearshift(string &Rotor){ //Đã hoạt động ổn định
    char temp = Rotor[0];
    for (int i = 0; i<25; i++) Rotor[i] = Rotor[i+1];
    Rotor[25] = temp;
}

int EntryGear(int CharIn){
    for (int i=0; i<M.size(); i++) if (M[CharIn] == Entry[i]) return i;
    return 26;
}
int Forward(int previous, string Rotor, string Mi){
    for (int i=0; i<M.size(); i++) if (Rotor[previous] == Mi[i]) return i;
    return 26;
}
int ReflectorGear(int previous, string Mi){
    for (int i=0; i<M.size(); i++) if(Reflector[previous] == Mi[i]) return i;
    return 26;
}
int Backward(int previous, string Rotor, string Mi){
    for (int i=0; i<M.size(); i++) if(Mi[previous] == Rotor[i]) return i;
    return 26;
}

char Encrypt(char CharIn){
    int temp=26;
    for (int i=0; i<M.size(); i++){
        if (CharIn == M[i]){
            temp = i;
            break;
        }
    }
    int code = EntryGear(temp);
    code = Forward(code, Rotor3, M3);
    code = Forward(code, Rotor2, M2);
    code = Forward(code, Rotor1, M1);
    code = ReflectorGear(code, M);
    code = Backward(code, Rotor1, M1);
    code = Backward(code, Rotor2, M2);
    code = Backward(code, Rotor3, M3);
    //code = Backward(code, Entry, M);
    if(code == 26) return ' ';
    return Entry[code];
}

int main(){
    string rawInput;
    string Input;
    int I=0;
    int II=0;
    int III=0;
    cout << "Enter text: ";
    getline(cin, rawInput);
    cout << endl << "Enter Rotor 1 setting: "; cin >> I;
    cout << "Enter Rotor 2 setting: "; cin >> II;
    cout << "Enter Rotor 3 setting: "; cin >> III;
    while ((I-1)>25 || (II-1)>25 || (III-1)>25){
        cout << endl << "Invalid Rotor setting!\n Try again!!!\n";
        cout << "Enter Rotor 1 setting: "; cin >> I;
        cout << "Enter Rotor 2 setting: "; cin >> II;
        cout << "Enter Rotor 3 setting: "; cin >> III;
    }
    for (int i=0; i<I-1; i++){
        Gearshift(Rotor1);
        Gearshift(M1);
    }
    for (int i=0; i<II-1; i++){
        Gearshift(Rotor2);
        Gearshift(M2);
    }
    for (int i=0; i<III-1; i++){
        Gearshift(Rotor3);
        Gearshift(M3);
    }
    Input = rawInput;
    for(int i=0; i<rawInput.size(); i++){
        Input[i] = toupper(rawInput[i]);
    }
    cout << endl << "Code: ";
    for (int i=0; i<Input.size(); i++){
        cout << Encrypt(Input[i]);
        Gearshift(Rotor1);
        Gearshift(M1);
        if (M1[0]=='A'){
            Gearshift(Rotor2);
            Gearshift(M2);
            if (M2[0]=='A'){
                Gearshift(Rotor3);
                Gearshift(M3);
            }
        }
    }
}