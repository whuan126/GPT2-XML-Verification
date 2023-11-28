#include <stdio.h>
// libxml2 parsing libraries
#include <libxml/parser.h>
#include <libxml/tree.h>
// Library used to read in from directory
#include <dirent.h>
#include <string.h>



void verify(const char *filename) {
    xmlDocPtr doc;

    // Parse the file. If errors are found, the parse is aborted and the errors are printed
    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Errors found in file:  %s\n", filename);
        return;
    }
    // Free the parse tree
    xmlFreeDoc(doc);
    printf("No errors found.\n");

}


void readFromDir(char *path){
    DIR *dir;
    struct dirent *entry;

    // Opens the Directory
    dir = opendir(path);

    // Return if unable to open directory
    if (dir == NULL) {
        printf("Error opening directory\n");
        return;
    }

    // Read in the files from the directory, skipping "." and ".."
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) { continue; }

        // Create path to file
        char filePath[257];
        snprintf(filePath, sizeof(filePath), "%s/%s", path, entry->d_name);
        // Verify the file (regular .xml files only!!) 
        if (entry->d_type == DT_REG && strstr(entry->d_name, ".xml") != NULL) {
            printf("----------------------------------------------------------------\n");
            printf("----------------------------------------------------------------\n");
            printf("Verifying File: %s\n", filePath);
            verify(filePath);
        }

    }

    printf("\n>>>>>>> Scan Complete <<<<<<<\n");
    // Closes the Directory
    closedir(dir);
}



int main(int argc, char *argv[]) {

    printf("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
    // Selecting the path to the directory holding the XML files. If no directory
    // is given when the program is run, it will default to the /verify directory.
    // (That is the directory I used while buildint the program)
    // Note: when feeding in a path, do not use the leading "/"
    char *directoryPath = "verify";
    if (argc != 2){
        printf("For custom directory, pass in path when initiating. Will use default directory path.\n");
        printf("Scanning files in directory: verify\n");
    }
    else{
        directoryPath = argv[1];
        printf("Scanning files in directory: %s\n", argv[1]);
    }
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

    // Initializing the Library
    xmlInitParser();

    // Start the verification Process
    readFromDir(directoryPath);

    // Cleanup
    xmlCleanupParser();

    return 0;
}