#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

// Parameters
bool showSize = false;
bool showAddress = true;
char* helptext = "usage: mapfinder <file> <variable> [-hsS]\n\n\
Parameters:\n\n\
\t-h \t Print this help text.\n\n\
\t-s \t Show size of the variable.\n\n\
\t-S \t Show only size of the variable.\n\n\
";

const char *fileName = NULL;
const char *varName = NULL;

int main(int argc, char const *argv[])
{

  if (argc <= 1) {
    printf("%s", helptext);
    exit(-1);
  }
  for (int i = 1; i<argc; i++) {
    if(argv[i][0]=='-') {
      if(argv[i][1]=='s') {
        showSize = true;
      }else if(argv[i][1]=='S') {
        showSize = true;
        showAddress = false;
      } else if(argv[i][1]=='h') {
        printf("%s", helptext);
        return(0);
      } else {
        printf("parameter %s is not known\n", argv[i]);
        exit(-1);
      }
    } else {
      if (fileName == NULL) {
        fileName = argv[i];
      } else if (varName == NULL) {
        varName = argv[i];
      }
    }
  }
  if (fileName == NULL) {
    printf("File name missing\n\n");
    printf("%s", helptext);
    return 0;
  }
  if (varName == NULL) {
    printf("Variable name missing\n\n");
    printf("%s", helptext);
    return 0;
  }
  FILE *mapFile = fopen(fileName, "r");

  if (mapFile == NULL)
  {
    printf("File %s not found.\n", fileName);
    exit(-1);
  }

  char ch[300];
  int lineIndex = 1;
  while(fgets(ch, 300, mapFile) != NULL) {
    if (strstr(ch,varName)) { // found, next line contains the value
      //printf("found it on line %d\n", lineIndex);
      fgets(ch, 300, mapFile);
      char *hex = ch;
      // find the start of the value
      while (isspace(*hex)) hex++;
      *(hex + 18) = 0;
      char *end = hex;
      while (!isspace(*end)) end++;
      *end = 0;
      int numFomratAddress = strtol(hex, NULL, 16);
      if (numFomratAddress == 0) {
        printf("Address 0 given, exit.\n");
        exit(-1);
      }
      if (showAddress) printf("0x%x ", numFomratAddress);

      if (showSize) {
        hex=end+1;
        // Skip next spaces to 
        while (isspace(*hex)) hex++;
        end = hex;
        while (!isspace(*end)) end++;
        *end = 0;
        int numFomratSize = strtol(hex, NULL, 16);
        printf("0x%x", numFomratSize);
      }
      printf("\n");
    }
    lineIndex++;
  }
      

  fclose(mapFile);
  return 0;
}
