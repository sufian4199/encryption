//
//  main.cpp
//  encryption project
//
//  Created by Muhammad Sufian on 10/12/2016.
//  Copyright © 2016 Muhammad Sufian. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <sstream>
using namespace std;

//XOR Function
//This function takes two binary numbers return the Result of XOR
uint8_t gadd(uint8_t a, uint8_t b) {
    return a ^ b;
}
//Binary Multiplication Function
//This functions takes two binary numbers and multiply them returning the least 8 bit and ignoring the overflow bits.
uint8_t gmul(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    while (b) {
        if (b & 1)
            p ^= a;
        
        if (a & 0x80)
            a = (a << 1) ^ 0x11b;
        else
            a <<= 1;
        b >>= 1;
    }
    return p;
}
//Convert binary string to HEX
//This function takes a hexadecimal number and returns its binary.
string Hex2Bin(const string& hexaDecimal)
{
    int i = 0;
    string binary = "";
    while(hexaDecimal[i])
    {
        switch(hexaDecimal[i])
        {
            case '0': binary.append("0000"); break;
            case '1': binary.append("0001"); break;
            case '2': binary.append("0010"); break;
            case '3': binary.append("0011"); break;
            case '4': binary.append("0100"); break;
            case '5': binary.append("0101"); break;
            case '6': binary.append("0110"); break;
            case '7': binary.append("0111"); break;
            case '8': binary.append("1000"); break;
            case '9': binary.append("1001"); break;
            case 'a': binary.append("1010"); break;
            case 'b': binary.append("1011"); break;
            case 'c': binary.append("1100"); break;
            case 'd': binary.append("1101"); break;
            case 'e': binary.append("1110"); break;
            case 'f': binary.append("1111"); break;
            default:  cout<<"nInvalid hexadecimal digit "<<hexaDecimal[i];
        }
        i++;
    }
    return binary;
}
//Convert Binary String to Decimal Value
//This functio takes a binary number and return its equivalent decimal value.
int BinToDec(string number)
{
    int result = 0, pow = 1;
    for ( int i = number.length() - 1; i >= 0; --i, pow <<= 1 )
        result += (number[i] - '0') * pow;
    return result;
}
//Convert Binary String to HEX
//This function takes a binary string and converts it to
string Bin2Hex(const string& s)
{
    bitset<8> bs(s);
    unsigned n = bs.to_ulong();
    stringstream ss;
    ss << hex << n;
    return (ss.str());
}

int main() {
    //Vigenère cipher Matrix
    char substitutionArray[26][26];
    //26*26 Matrix to store the cipher matrix
    for(int i= 0 ; i < 26; i++){
        for(int j = 0 ; j < 26; j++){
            //Array initialized with #
            substitutionArray[i][j]='#';
        }
    }
    //A vector that holds the 26 characters and rotate them as per requirement
    vector<char> arr;
    for(int i = 0 ; i < 26 ; i++){
        //Enter all 26 elemebst in the array
        arr.push_back(65+i);
    }
    for(int i= 0 ; i < 26; i++){
        for(int j = 0 ; j < 26; j++){
            //all 26 elements are copied to row i of matrix in order from arr
            substitutionArray[i][j] = arr[j];
        }
        //First element is put at the back and removed from the front.
        //This causes the required rotation
        arr.push_back(arr[0]);
        arr.erase(arr.begin());
    }
    
    //Input
    string path,key;
    cout<<"Please enter path to input and key file respectively"<<endl;
    cin>>path>>key;
    ifstream fpath(path);
    if(!fpath.is_open()){
        cout<<"Input file not found!"<<endl;
        return 0;
    }
    ifstream fkey(key);
    if(!fkey.is_open()){
        cout<<"Key file not found!"<<endl;
        return 0;
    }
    
    //Output
    cout<<"Enter the path of output file"<<endl;
    string oPath;
    cin>>oPath;
    ofstream fout(oPath);
    
    fout<<"Enter the name of the input plaintext file: "<<path<<endl;
    
    
    
    //PreProcessing
    string input="";
    string temp;
    while(!fpath.eof()){
        fpath>>temp;
        for(int i = 0 ; i < temp.size(); i++){
            //Only alphabets are stored in the array. All othe character including punctuations are removed
            if(temp[i]>='A'&&temp[i]<='Z')
                input.push_back(temp[i]);
        }
    }
    fkey>>key;
    fout<<"Enter the name of the input key file: "<<key<<endl;
    fout<<"Enter the name of the output ciphertext file: "<<oPath<<endl;
    fout<<"Preprocessing:"<<endl;
    fout<<input<<endl<<endl;
    cout<<"Preprocessing:"<<endl;
    cout<<input<<endl<<endl;
    arr.clear();
    //Substitution
    fout<<"Substitution:"<<endl;
    cout<<"Substitution:"<<endl;
    //Key is copied to arr
    for(int i = 0 ; i < key.length(); i++){
        arr.push_back(key[i]);
    }
    //Key is made equal to the length of input string
    for(int i = 0 ; arr.size()!=input.length(); i++){
        arr.push_back(arr[i]);
    }
    //Correct value is copied and substitued for each index of array from the substitution matrix
    for(int i = 0 ; i<arr.size(); i++){
        arr[i] = substitutionArray[input[i]%65][arr[i]%65];
    }
    //Stored in file
    for(int i = 0 ; i<arr.size(); i++){
        fout<<arr[i];
        cout<<arr[i];
    }
    fout<<endl<<endl;
    cout<<endl<<endl;
    
    //Padding
    fout<<"Padding: "<<endl;
    cout<<"Padding: "<<endl;
    //Required 'A' are appended at the end of arr
    while(arr.size()%16!=0)
        arr.push_back('A');
    //arr is written on the output file in the required format
    for(int i = 0 ; i<arr.size(); i++){
        if(i%16==0&&i!=0){
            fout<<endl;
            fout<<endl;
            cout<<endl;
            cout<<endl;
        }
        else if(i%4==0&&i!=0){
            fout<<endl;
            cout<<endl;
        }
        fout<<arr[i];
        cout<<arr[i];
    }
    fout<<endl<<endl;
    cout<<endl<<endl;
    
    //Shift Rows
    //Every 4 elemenst are taken and are rotated as per required
    fout<<"ShiftRows: "<<endl;
    cout<<"ShiftRows: "<<endl;
    int rotations = 0;
    vector<char> _temp;
    _temp.clear();
    for(int i = 4 ; i <= arr.size() ; i+=4){
        
        for(int j = i-4 ; j < i; j++){
            _temp.push_back(arr[j]);
        }
        for(int t = 0 ; t < rotations; t++){
            _temp.push_back(_temp[0]);
            _temp.erase(_temp.begin());
        }
        //rotations variable is used to track how many rotations are required
        //4 elemensts are copied the _temp vector and them rotated as the rotations variable say and then then re inserted in the original vector arr
        rotations++;
        rotations = rotations%4;
        for(int j = i-4 ; j < i; j++){
            arr[j]=_temp[j%4];
        }
        _temp.clear();
    }
    //Printed to file
    for(int i = 0 ; i<arr.size(); i++){
        if(i%16==0&&i!=0){
            fout<<endl;
            fout<<endl;
            cout<<endl<<endl;
        }
        else if(i%4==0&&i!=0){
            fout<<endl;
            cout<<endl;
        }
        fout<<arr[i];
        cout<<arr[i];
    }
    fout<<endl<<endl;
    cout<<endl<<endl;
    
    //Parity Bit
    fout<<"Parity Bit: "<<endl;
    cout<<"Parity Bit: "<<endl;
    for(int i = 0 ; i<arr.size(); i++){
        if(i%4==0&&i!=0){
            fout<<endl;
            cout<<endl;
        }
        string binary = bitset<8>(arr[i]).to_string(); //Number converted to binary string
        int count = 0;
        for(int j = 0 ; j < 8; j++){
            if(binary[j]=='1')
                count++;
        }
        if(count%2!=0){ //if odd parity found then MSB is set to 1
            binary[0]='1';
        }
        string hexa = Bin2Hex(binary); //Binary number converted to hexadecimal
        fout<<hexa<<" ";//hexadecimal number printed to file
        cout<<hexa<<" ";//hexadecimal number printed to file
    }
    fout<<endl<<endl;
    cout<<endl<<endl;
    //MixColumns
    fout<<"Mix Columns: "<<endl;
    cout<<"Mix Columns: "<<endl;
    //vector final result is created
    vector<int> finalResult;
    for(int j = 0 ; j < 4;j++){//This loop runs 4 times for 4 columns
    for(int i = j; i < arr.size(); i+=16){//This loop runs till all the elements of each row are traversed
        //Each time this loop takes 4 elements are required by the Rijndael’s Galois field. The first element is i, the second element is i+4, the third element is i+8 and the fourth element is i+12. All these elements are then mulitplied in the  Rijndael’s Galois field and the result is printed.
        string binary = bitset<8>(arr[i]).to_string(); //Every number converted to binary
        int count = 0;
        for(int j = 0 ; j < 8; j++){
            if(binary[j]=='1')
                count++;
        }
        if(count%2!=0){
            binary[0]='1';
        }
        uint8_t a0=BinToDec(binary);
        binary.clear();
        binary = bitset<8>(arr[i+4]).to_string();
        count = 0;
        for(int j = 0 ; j < 8; j++){
            if(binary[j]=='1')
                count++;
        }
        if(count%2!=0){
            binary[0]='1';
        }
        uint8_t a1=BinToDec(binary);
        binary.clear();
        binary = bitset<8>(arr[i+8]).to_string();
        count = 0;
        for(int j = 0 ; j < 8; j++){
            if(binary[j]=='1')
                count++;
        }
        if(count%2!=0){
            binary[0]='1';
        }
        uint8_t a2=BinToDec(binary);
        binary.clear();
        binary = bitset<8>(arr[i+12]).to_string();
        count = 0;
        for(int j = 0 ; j < 8; j++){
            if(binary[j]=='1')
                count++;
        }
        if(count%2!=0){
            binary[0]='1';
        }
        uint8_t a3=BinToDec(binary);
        uint8_t res = 0;
        
        //Above we are just taking the hexavalues and converting them to binary so that we can perform binary multiplication and XOR operations.
        
        res = gadd( gadd(gmul(a0, 2), gmul(a1, 3)) ,  gadd(a2, a3) );//Element a0 = rgfMul(c0,2) ⊕ rgfMul(c1,3) ⊕ c2 ⊕ c3
        finalResult.push_back(BinToDec(bitset<8>(res).to_string()));
        res = gadd( gadd(a0, gmul(a1, 2)) ,  gadd(gmul(a2, 3), a3) );//Element a1 = c0 ⊕ rgfMul(c1,2) ⊕ rgfMul(c2,3) ⊕ c3
        finalResult.push_back(BinToDec(bitset<8>(res).to_string()));
        res = gadd( gadd(a0,a1) ,  gadd(gmul(a2, 2), gmul(a3, 3)) );//Element a2 = c0 ⊕ c1 ⊕ rgfMul(c2,2) ⊕ rgfMul(c3,3)
        finalResult.push_back(BinToDec(bitset<8>(res).to_string()));
        res = gadd( gadd(gmul(a0, 3),a1) ,  gadd(a2,gmul(a3, 2)) );//Element a3 = rgfMul(c0,3) ⊕ c1 ⊕ c2 ⊕ rgfMul(c3,2)
        finalResult.push_back(BinToDec(bitset<8>(res).to_string()));
        //a0,a1,a2,a3 are stored in the finalResult vector in order for every iteration.
    }
    }
    for(int i = 0 , j = 0; i < finalResult.size()-48; i++, j++){
        //This loop writes elements to file in the required order as present in finalResult vector
        fout<<Bin2Hex(bitset<8>(finalResult[i]).to_string())<<" "; //Element a0
        fout<<Bin2Hex(bitset<8>(finalResult[i+16]).to_string())<<" "; //Element a1
        fout<<Bin2Hex(bitset<8>(finalResult[i+32]).to_string())<<" "; //Element a2
        fout<<Bin2Hex(bitset<8>(finalResult[i+48]).to_string())<<endl; //Element a3
        
        cout<<Bin2Hex(bitset<8>(finalResult[i]).to_string())<<" "; //Element a0
        cout<<Bin2Hex(bitset<8>(finalResult[i+16]).to_string())<<" "; //Element a1
        cout<<Bin2Hex(bitset<8>(finalResult[i+32]).to_string())<<" "; //Element a2
        cout<<Bin2Hex(bitset<8>(finalResult[i+48]).to_string())<<endl; //Element a3
    }
    
    fout.close();//Output file closed
    fpath.close();//Input path file closed
    fkey.close();//Key file closed
    
    return 0;//Program terminates
}
