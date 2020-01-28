# bibtextomediawiki
Converts Bibtex format into mediawiki syntax which is spoken by a famous encyclopedia 

### Description
It's not possible to enter bibtex formatted bibliographic references directly into the mediawiki editor. If someone likes to contribute to the online encyclopedia, he has to provide the references in the citation format of mediawiki. For doing so, the HTML file is downloaded into a working directory, a bookmark is created for the file and then the user can copy&paste the bibtex file into the left window.

The converter is parsing the items, modifies the special characters and removes the white spaces.

### Screenshot

![screenshot](/screenshot.png)

### Changelog
version 0.7
- remove special characters in bibtex: \" \'
- rule 891 for detecting invalid DOI
- example bibtex with special character

version 0.6

- Javascript prototypes instead of plain functions
- hideurl  
  
version 0.54

- rewrite of parseline
- using dictionary to save parsing
  
version 0.5

- default bibtex entry
- lookupid into markupid 

version 0.3

- convert more than one bibtex entry if an empty line is between them
- remove false as return value
- improved debug mode
- change "citation" into "cite journal"

version 0.2

- @book is recognized
- new fields: doi, url
- general template "Citation" works better than specialized templates

version 0.1

- initial creation of the project folder
- program is written in Javascript
