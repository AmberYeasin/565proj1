/*  Author: Amber Yeasin
**  Class: EECS565, Spring2018
**  Project: Vigenere Cipher
**  Note: Easiest to run within Atom IDE using [f5]
**        otherwise, manually make
**  Refrences:
**    conversion loop -
**    https://www.geeksforgeeks.org/vigenere-cipher/
**    permutation function -
**    https://disqus.com/home/discussion/geeksforgeeks/print_all_possible_strings_of_length_k_that_can_be_formed_from_a_set_of_n_characters/
**    searching an input file -
**    https://stackoverflow.com/questions/12463750/c-searching-text-file-for-a-particular-string-and-returning-the-line-number-wh
**
*/

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <string.h>
#include <cmath>
#include <chrono>

using namespace std;

set<string> dictionary;

//grows the pre-set key to the appropriate lenth
string generateKey(string ciph, string key)
{
  int x = ciph.size();

  for (int i = 0; i < ciph.size(); i++)
  {
      if (key.size() <= ciph.size())
        key.push_back(key[i]);
      else
        return key;
  }
}

//encrypt a given plaintext string and a pre-set key ("AMBER")
string encrypt(string ciph, string key)
{
  string encrypted_text;

  //uses key to calculate conversion
  for (int i = 0; i < ciph.size(); i++)
  {
        // converting in range 0-25
        int x = (ciph[i] + key[i]) %26;

        // convert into alphabets(ASCII)
        x += 'A';

        //append to string
        encrypted_text.push_back(x);
  }
  return encrypted_text;
}

// decrypts the encrypted text using passed in key
//reverse process of encrypt function
string decrypt(string encrypted_text, string key)
{
    string decrypt_text;
    for (int i = 0 ; i < encrypted_text.size(); i++)
    {
        int x = (encrypted_text[i] - key[i] + 26) %26;

        // convert into alphabets(ASCII)
        x += 'A';
        decrypt_text.push_back(x);
    }
    return decrypt_text;
}

//checks dictionary file for decrypted word
bool isWord(string word)
{
  bool b = false;
  if (dictionary.count(word) > 0)
    b = true;
  return b;
}

void checkKey(string ciph, string key, int fwl)
{
  string first(ciph.substr(0,fwl));
  if(isWord(decrypt(first,generateKey(first,key))))
    cout << "Decryption using key [" << key << "] is : "<< decrypt(ciph,generateKey(ciph,key)) << endl;
}

string intToKey(int n, int length)
{
  string key(length, 'A');
  for(int i = length - 1; i >= 0; i--)
  {
    key[i] = (n % 26) + 'A';
    n = (n / 26);
  }
  return key;
}

void bruteForce(string ciph, int keyLength, int fwl)
{
  for(int i = 0; i < pow(26, keyLength); i++)
  {
    string key = intToKey(i, keyLength);
    checkKey(ciph, key, fwl);
  }
}


//  n=setSize, k=keyLength
void crack(const char set[],string prefix,const int n, const int k, string ciph)
{
  string possKey;
  unsigned int curLine = 0;

  if (k == 1)
  {
    for (int j = 0; j < n; j++)
    {
      possKey = prefix + set[j];
      cout << decrypt(ciph, generateKey(ciph, possKey));
//      generateKey(ciph, possKey);

//      cout << prefix + set[j] << endl;
    }
  }//Base case: k = 1, print the string k times + the remaining letter
  else
  {
    for (int i = 0; i < n; i++)
    crack(set, prefix + set[i], n, k - 1, ciph);
  }//Call the function with k - 1 and the added letter

}



void checkFile(string possKey, int keylength)
{
/*  unsigned int curLine = 0;
  while(getline(fileInput, line)) {
    curLine++;
    if (line.find(search, 0) != string::npos) {
        cout << "found: " << search << "line: " << curLine << endl;
    }
}*/
}


int main() {
  //take in cipher to decode, key length, and first word length
  string ciph;
  int keyLength, firstWordLength;
  // set<string> dictionary;
//
//   cout << "Ciphertext to decode: ";
//   cin  >> ciph;
//   cout << "Enter key length: ";
//   cin  >> keyLength;
//   cout << "Enter first word length: ";
//   cin  >> firstWordLength;
//
//   //cout << "Cipher is: " << ciph << ", key is: " << keyLength << ", fwl is: " << firstWordLength;
//
  ifstream dictFile("dict.txt");
  if(!dictFile)
  {
    cout << "While opening a file an error is encountered" << endl;
  }
  else
  {
    cout << "File is successfully opened" << endl;
    string word;
    while(getline(dictFile,word))
    {
      dictionary.insert(word);
    }
  }
//
// //TODO: add all letters
//     char set[] = {'A', 'B', 'C', 'D'};
//     int n = 3;//later change to 26
//     string keyword = "AMBER";
//     string key = generateKey(ciph, keyword);
//     string encrypted_text = encrypt(ciph, key);
//
//     cout << "key : "
//          << key << "\n";
//
//     cout << "Ciphertext : "
//          << encrypted_text << "\n";
//          //TODO: keylength as input
//     crack(set, "", 3, 4, ciph);
  ciph = "MSOKKJCOSXOEEKDTOSLGFWCMCHSUSGX";
  keyLength = 2;
  firstWordLength = 6;



  ciph = "OOPCULNWFRCFQAQJGPNARMEYUODYOUNRGWORQEPVARCEPBBSCEQYEARAJUYGWWYACYWBPRNEJBMDTEAEYCCFJNENSGWAQRTSJTGXNRQRMDGFEEPHSJRGFCFMACCB";
  keyLength = 3;
  firstWordLength = 7;

  ciph = "MTZHZEOQKASVBDOWMWMKMNYIIHVWPEXJA";
  keyLength = 4;
  firstWordLength = 10;


  ciph = "HUETNMIXVTMQWZTQMMZUNZXNSSBLNSJVSJQDLKR";
	keyLength = 5;
	firstWordLength = 11;


  ciph = "LDWMEKPOPSWNOAVBIDHIPCEWAETYRVOAUPSINOVDIEDHCDSELHCCPVHRPOHZUSERSFS";
	keyLength = 6;
	firstWordLength = 9;
  cout << "Start Brute Force Attack\n";

  auto start = chrono::system_clock::now();

  bruteForce(ciph, keyLength, firstWordLength);

  auto end = chrono::system_clock::now();
  std::chrono::duration<double>  duration = end-start;
  cout << "print decrypt Time: " << duration.count() << endl;

  return 0;
}
