/*
g++ -std=c++14 bibtextomediawiki.cpp
title: bibtex to Wikisyntax converter
description: reads from file "input.bib" and stores result to "output.wiki"
changelog:
  2018-10-13 initial commit
  2018-10-15 minor modication in filename handling
  2018-10-15 shortformat
  2018-10-16 <anchor> tag in fullmode
  2018-10-16 simplify "for loop", put error message to output
  2018-10-17 UML diagram created
to do: 
  - context free grammar, bnf parser (very complicated, perhaps not needed)
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
  std::string filenameinput="input.bib";
  std::string filenameoutput="output.wiki"; 
  
  void readfromfile() {
    std::string line;
    std::ifstream myfile (filenameinput);
    if (myfile.is_open()) {
      while ( getline (myfile,line) ) {
        text.push_back(line);
      }
      myfile.close();  
    }
  }
  void savetofile() {
    std::ofstream myfile;
    myfile.open (filenameoutput);
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
    mytable.push_back({"header","@article","{{cite journal"});
    mytable.push_back({"header","@inproceedings","{{cite conference"});
    mytable.push_back({"header","@phdthesis","{{cite thesis |type = PhD"});
    mytable.push_back({"header","@techreport","{{cite techreport"});
    
    mytable.push_back({"field","booktitle","conference"});
    mytable.push_back({"field","title","title"});
    mytable.push_back({"field","author","author"});
    mytable.push_back({"field","journal","journal"});
    mytable.push_back({"field","pages","pages"});
    mytable.push_back({"field","year","year"});
    mytable.push_back({"field","publisher","publisher"});
    mytable.push_back({"field","organization","publisher"});
    mytable.push_back({"field","school","publisher"});
    mytable.push_back({"field","volume","volume"});
    mytable.push_back({"field","institution","institution"});
  }
};

class Converter {
public:
  Textfile mytextfile;
  Lookuptable mylookuptable;
  bool fullformat;
  bool parsesuccess;
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
  void parseline(int inputlineid, int lookupid) {
    std::string result;
    auto type=mylookuptable.mytable[lookupid].type;
    auto wikisyntax=mylookuptable.mytable[lookupid].wikisyntax;
    auto line=mytextfile.text[inputlineid];
    if (type=="header" and fullformat==true) {
      result+="<ref name=\"";
      result+=stripline(line,"{",",");
      result+="\">";
      result+=wikisyntax;
    }
    if (type=="header" and fullformat==false) {
      result+="<ref>";
      result+=wikisyntax;
    }
    if (type=="field") {
      result=" |";
      result+=wikisyntax;
      result +="=";
      result +=stripline(line,"{","}");     
    }
    if (fullformat==true)
      result+="\n"; // linebreak
    mytextfile.output.push_back(result); // store to file
    
  }
  void formattextfile(bool _fullformat) {
    fullformat=_fullformat;
    for (auto i=0;i<mytextfile.text.size();i++) {
      parsesuccess=false;
      for (auto k=0;k<mylookuptable.mytable.size();k++) { // match lookuptable
        if (findstring(mytextfile.text[i], mylookuptable.mytable[k].bibtex)) {
          parseline(i,k);
          parsesuccess=true;
        }
      }
      if (mytextfile.text[i].find("}")== 0) { // closing brackets at position 0
        mytextfile.output.push_back("}}</ref>\n\n"); // store to file
        parsesuccess=true;
      }
      if (parsesuccess==false) {
        std::string result="??error?? "+std::to_string(i);
        mytextfile.output.push_back(result); // store to file
      }
    }    
  }
  Converter() {
    mytextfile.readfromfile();
    formattextfile(true);
    formattextfile(false);
    mytextfile.savetofile();
  }
};

int main() { 
  Converter myconverter;
}
