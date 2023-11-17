#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

static void parseXML(char *fileName) {
    xmlDocPtr doc;
    xmlNodePtr cur;
}

int main(int argc, char **argv) {

	char WHFile;
		
	if (argc <= 1) {
		printf("Usage: %s docname\n", argv[0]);
		return(0);
	}

	WHFile = argv[1];
	parseDoc (WHFile);

	return (1);
}