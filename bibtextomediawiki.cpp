/*
g++ -std=c++14 bibtextomediawiki.cpp
title: bibtex to Wikisyntax converter
description: reads from file "input.txt" and stores result to out.txt
date: 2018-10-13
to do: 
*/

#include <iostream>
#include <string>
#include <complex>
#include <math.h>
#include <random>
#include <algorithm>
#include <fstream> // textfile

class Textfile {
public:
  std::vector<std::string> text; 
  std::vector<std::string> output; 
  
  void readfromfile(std::string filename) {
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()) {
      while ( getline (myfile,line) ) {
        text.push_back(line);
      }
      myfile.close();  
    }
  }
  void savetofile() {
    std::ofstream myfile;
    myfile.open ("out.txt");
    for (auto i=0;i<output.size();i++)
      myfile << output[i];
    myfile.close();
  }
};

class Item {
public:
  std::string type;
  std::string bibtex;
  std::string wikisyntax;
};

class Lookuptable {
public:
  std::vector<Item> mytable;
  Lookuptable() {
    // organization is open
    mytable.push_back({"header","@article","{{cite journal"});
    mytable.push_back({"header","@inproceedings","{{cite conference"});
    mytable.push_back({"header","@phdthesis","{{cite thesis\n| type = PhD"});
    
    mytable.push_back({"field","booktitle","conference"});
    mytable.push_back({"field","title","title"});
    mytable.push_back({"field","author","author"});
    mytable.push_back({"field","journal","journal"});
    mytable.push_back({"field","pages","pages"});
    mytable.push_back({"field","year","year"});
    mytable.push_back({"field","publisher","publisher"});
    mytable.push_back({"field","school","publisher"});
    mytable.push_back({"field","volume","volume"});

  }
};
  
class Lineparser {
public:
  Lookuptable mylookuptable;
  
  /// extract text between characters
  std::string stripline(std::string text, std::string leftsymbol, std::string rightsymbol) {
    int p1=text.find(leftsymbol);
    int p2=text.find(rightsymbol,p1+1);
    return text.substr(p1+1, p2-p1-1);
  }
  /// checks if s is in line
  auto findstring(std::string line, std::string s) {
    if (line.find(s)!= std::string::npos)
      return true;
    else return false;
  }
  std::string run(std::string line) {
    std::string result="??parseerror??";
    /// match lookuptable against line
    for (auto i=0;i<mylookuptable.mytable.size();i++) {
      if (findstring(line, mylookuptable.mytable[i].bibtex)) {
        if (mylookuptable.mytable[i].type=="header") {
          result="<ref name=\"";
          result+=stripline(line,"{",",");
          result+="\"> ";
          result+=mylookuptable.mytable[i].wikisyntax;
        }
        if (mylookuptable.mytable[i].type=="field") {
          result="| ";
          result +=mylookuptable.mytable[i].wikisyntax;
          result +=" = ";
          result +=stripline(line,"{","}");     
          break; // only search for first entry in table
        }
      }
      if (line.find("}")== 0) // closing brackets on position 0
        result="}}</ref>\n";
    }
    result+="\n";
    return result;
  }
};

class Converter {
public:
  Textfile mytextfile;
  Lineparser mylineparser;
  int verbose=0; //1==on
  Converter() {
    mytextfile.readfromfile("input.txt");
    for (auto i=0;i<mytextfile.text.size();i++) { // go through text
      auto line=mytextfile.text[i];
      auto wikisyntax=mylineparser.run(line);
      if (verbose==1) 
        std::cout<<i<<" "<<line<<"\n";
      mytextfile.output.push_back(wikisyntax); // store to file
    }
    mytextfile.savetofile();
  }
};

int main() { 
  Converter myconverter;
}
