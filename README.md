# bibtextomediawiki
Converts Bibtex format into mediawiki syntax which is spoken by a famous encyclopedia 

**Description**

The aim of this tool is to convert from the Bibtex format into the Wikisyntax which is spoken in the WIkipedia project. The problem is, that literature references are stored in Google Scholar in the common Bibtex format which is from the LaTeX document tool but this format isn't compatible with Wikipedia. Wikipedia is using a different kind of template engine which allows to enter more complex bibliographic references.

In the past some attempts were available which is trying to address the probelm. The Zotero software can export into the WIkisyntax, the Bibdesk manager (a Mac OS software) too. I've found also some questions on stackoverflow in which somebody was trying to use Regex (regular expressions) to parse Bibtex file and in the Pypy repository a software is available called bibtexparser.

Because it is always a good idea to invent the wheel twice here is my suggestion for a bibtex converter. It is not a plugin for a current reference manager like jabref or Zotero because Google Scholar is the best reference manager available. Instead the software takes plaintext textfile as input.

The algorithm was implemented in the C++ language which is a great tool for software prototyping. In contrast to a professional programming language the advantage is, that no FPGA is needed to run the algorithm. A normal Von-neumann CPU is enough.

The core of the software is the class “lookuptable” which defines the translation-matrix from bibtex to Wikisyntax. For example, the term “@article" from Bibtex is equal to "{{cite journal" in Wikisyntax. The main loop goes through each line and and transforms the content with the lookuptable. 

Sometimes, a problem is there and the parser prints out “??error??” which means that something is wrong. The software is only in the beta stadium, that means, there are some bugs which has to be fixed in later iterations. The advantage is, that it is possible to parse a complete textfile. I've tested out an example with 10 bibtex entries and the program generates the appropriate Wikisyntax format. In comparison to manual conversion it is a huge improvement. Putting the Wikisyntax for a journal article together by hand is not very funny.

If somebody want's to fork this project, you're welcome. The programming language itself must stay on C++. That means, Python, Java or AWK is not an option for me. What can be improved is maybe the matching algorithm. Also a commandline option is missing right now.
