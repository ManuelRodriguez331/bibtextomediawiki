# bibtextomediawiki
Converts Bibtex format into mediawiki syntax which is spoken by a famous encyclopedia 

### Description
Creating a Wikipedia article or extending an existing one is only possible, if academic references are used. Unfortunately, the mediawiki system isn't using the bibtex format, but has developed it's own citation template. Converting from existing bibtex bibliographic references into the Mediawiki citation format is possible with the following Javascript project.

What the user has to do is to download the HTML file into a working directory, and open it in a webbrowser. Then, the bibtex citation is put into the left window and the converter produces the appropriate Mediawiki syntax.

The software is in a beta stadium, which means, that sometimes a parsing error is available. Another problem is, that special characters in the TeX format aren't converted correctly. So the user has to manual improve the generated text.



### Screenshot

![screenshot](/screenshot.png)

### Changelog
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
