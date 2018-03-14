#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char basePath[] = "/sys/class/backlight/";

const char* getBacklight() {
  DIR *d;
  struct dirent *dir;
  d = opendir(basePath);

  char* retval = NULL;

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type == DT_LNK) {
        retval = dir->d_name;
        break;
      }
    }
    closedir(d);
  }
  return retval;
}


int getCurrentValue(char* path) {
  int currentValue;
  FILE* fptr;

  if ((fptr = fopen(path, "r")) == NULL){
    printf("Error! opening file: %s\n", path);
    return 1;
  }

  fscanf(fptr,"%d", &currentValue);
  fclose(fptr);
  printf("Current value: %d\n", currentValue);
  return currentValue;
}

void setNewValue(char* path, int value) {
  FILE *fptr;
  fptr = fopen(path,"w");

  if(fptr == NULL) {
    printf("Error! Could not open file for writing..\n");
    exit(1);
  }

  fprintf(fptr, "%d", value);
  fclose(fptr);
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Error! Expected one argument!\n");
    return 1;
  }

  int requestedChange = atoi(argv[1]);


  const int pathMaxLength = strlen(basePath) + 30;
  char path[pathMaxLength];
  printf("Figuring out backlight directory...\n");
  sprintf(path, "%s%s%s", basePath, getBacklight(), "/brightness");
  printf("Path found: %s\n", path);

  int currentValue = getCurrentValue(path);

  printf("Current value: %d\n", currentValue);

  int newValue = currentValue + requestedChange;

  printf("New value will be: %d\n", newValue);
  setNewValue(path, newValue);

  return 0;
}
