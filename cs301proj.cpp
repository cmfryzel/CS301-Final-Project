#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include<vector>

using namespace std;

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );


   
    

    return strs.size();
}

int isSubset(string str, string superstr){
    int size = str.size();
    int matches = 0;

    for(int i = 0; i<str.size(); i++){
        for(int j = 0; j<superstr.size(); j++){
            if(str.at(i)==superstr.at(j)){
                matches++;
            }
        }
    }

    //this works assuming no repeats

    if(matches == size && size>0){
        return 1;
    }
    else{
        return 0;
    }
}

int isPrime(string str, vector<string> vec){
    for(int i = 1; i<vec.size(); i++){
        if(isSubset(str, vec[i])){
            return 1;
        }
    }
    return 0;
}

// int isSuper(string str, vector<string> vec){
//     for(int i = 1; i<vec.size(); i++){
//         if(isSubset(str, vec[i])){
//             return 1;
//         }
//     }
//     return 0;
// }

int main(int argc, char** argv)
{

    vector<string> ipt;
    
    
    // create a text string, which is used to output the text file
    string txt;

    // read from the text file
    ifstream myFile("input.txt");

    
    // Use a while loop together with the getline() function to read the file line by line
    while (!myFile.eof()) {
        // Output the text from the file
        getline (myFile, txt);
        ipt.push_back(txt);
    }

    

    // Close the file
    myFile.close();

    

    while(ipt.size()>0){ //until vector is size of 0
        string Table = ipt.front();
        ipt.erase(ipt.begin());
        vector<string> v;
        int find = 0;
        
        string Test = Table;

        int length = 0;
        int origSize = Test.size();
        while(length<origSize){
            

            find = Test.find(' ');
            
            if(find != string::npos){
                
                v.push_back(Test.substr(0, find));
                Test.erase(0, find+1);
                length+=(find+1);
                
            }else{
                
                v.push_back(Test.substr(0, (origSize-length)-1));
                length=origSize;
            }
        }

        // for (int i = 0; i<v.size(); i++){
        //      cout << " veeeye" << endl;
        //       cout << v[i] << endl;
        //       cout << v[i].size() << "\n";
        //       }



        //split(Table, v, ' ');
        // cout << v[0] << endl;
        // for(int i = 0; i< v.size(); i++){
        //     cout << v[i] << "\n" << endl;
        // }
        

        //take away all characters in string after first from first string to get all non-prime keys
        string notPrimes = "";

        vector<string> q;

        int count = 0;

        vector<string> fd;
        char charX = 'x';
        while((ipt.front().at(0))!=charX){ //add all FDs to fd until x character.
            fd.push_back(ipt.front());
            ipt.erase(ipt.begin());
            
            //split(fd[count], q, ')'); //adds separated version of FD to vector q.  every even n is first part of FD, n+1 is second part
            int found = (fd[count]).find(')');
            q.push_back(((fd[count]).substr(1,found-1)));
            q.push_back(((fd[count]).substr(found+2,(fd[count]).size()-4-found)));
            count++;
             
        }
        
        //  for (int i = 0; i<q.size(); i++){
             
        //       cout << q[i] << endl;
        //       }
        

        //MAKE THE NOTPRIMES string HERE
        string str = v[0];
        for(int i = 0; i<str.size(); i++){
            int matches = 0;
            for(int j = 1; j<v.size(); j++){
                for(int x = 0; x<v[j].size(); x++){
                    if(str[i]==(v[j]).at(x)){
                        matches = 1;
                    }
                }
            }
            if(matches==0){
                notPrimes+=str[i];
            }
        }

        //cout << "not Primes are " << notPrimes << endl;

        ipt.erase(ipt.begin());//erase the x

        int normalForm = 0;
        
        

        for(int i =0; i<q.size(); i+=2){//looping through the left side of all functional dependencies
            for(int j = 1; j<v.size(); j++){  //looping through PK and all CKs
            // cout << i << "q[i]      " << q[i] << "\n";
            // cout << v[j] << "\n";
            // cout << Table << "\n";
            // cout << "qi" <<  q[i]<< ((q[i]).size()) << "\n";
            //  cout << "vj" << v[j]<<((v[j]).size()) << "\n";
                if(((q[i]).size())<((v[j]).size())){//making sure left side could be a subset of a PK or CK
                //  cout << notPrimes << "\n";
                //  cout << "qi" <<  q[i]<< ((q[i]).size()) << "\n";
                //  cout << "vj" << v[j]<<((v[j]).size()) << "\n";
                    if(isSubset(q[i], v[j])){//check if q[i] is a subset of a PK or CK
                    // cout << q[i] << endl;
                    // cout << q[i].size() << endl;
                    // cout << "veejay" << v[j] << endl;
                    // cout << v[j].size() << endl;
                        if(isSubset(q[i+1], notPrimes)){//check if q[i+1] is a non-prime key
                            
                            normalForm = 1;
                        }
                    }
                }
            }

        }

        //check for partial dependency-- do any of the CKs 
        //made of >1 values have 1 of the values fd to a notPrime?
        //if so, then print. else, normalForm++ and check for 3NF
        
        if(normalForm ==0){

            int n = 0;
            while(n<q.size()){ 
                // if(isPrime(q[n],v) || isSuper(q[n], v)){//if q[n] is a prime key/super then no transitive depednency
                //     n+=2;
                // }else if(isPrime(q[n+1],v)  || isSuper(q[n+1], v)){//if q[n+1] is a prime key/super then no transitive depednency
                //     n+=2;
                // }else{
                //     normalForm =2;
                //     n=q.size();
                // }

                if(isSubset(q[n], notPrimes) && isSubset(q[n+1], notPrimes)){
                    normalForm =2;
                    n=q.size();
                }
                else{
                    n+=2;
                }
            }
        }
        
            //if no partial dependency, check for transitive: go through 
            //each fd and see if any one is a notPrime to a notPrime
            //if so, then print. else, normalForm++ and print

        if(normalForm==0){normalForm=3;}

        cout << Table << "\n" << normalForm << "NF\n";

        
    }



    return 0;
}