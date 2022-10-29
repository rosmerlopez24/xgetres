#include <X11/Xresource.h>
#include <getopt.h>
#include <stdio.h>

static int print_xresource(const char *resource) {
  int result;
  XrmInitialize();

  Display *current_display = XOpenDisplay(NULL);
  if (NULL == current_display) {
    fprintf(stderr, "Can't open display\n");
    result = -1;
    goto cleanup;
  }

  char *resource_manager = XResourceManagerString(current_display);
  if (NULL == resource_manager) {
    fprintf(stderr, "Can't obtain RESOURCE_MANAGER\n");
    result = -1;
    goto cleanup;
  }

  XrmDatabase database = XrmGetStringDatabase(resource_manager);
  if (NULL == database) {
    fprintf(stderr, "Can't open resource database\n");
    result = -1;
    goto cleanup;
  }

  XrmValue value;
  char *type;
  if (XrmGetResource(database, resource, resource, &type, &value)) {
    printf("%s\n", value.addr);
    result = 0;
  } else {
    // Resource not found
    result = 1;
  }

cleanup:
  if (NULL != current_display) {
    XCloseDisplay(current_display);
  }
  return result;
}

int main(int argc, char *const argv[]) {
  struct option options[] = {{"help", no_argument, NULL, 'h'},
                             {"version", no_argument, NULL, 'v'},
                             {0, 0, 0, 0}};
  int option = 0;
  // Parser arguments
  while ((option = getopt_long(argc, argv, "hv", options, NULL)) != -1) {
    if (option == 'h') {
      printf("Usage: xgetres [OPTION] RESOURCE\n"
             "Get the value of the X resource named RESOURCE\n"
             "\n"
             "Options:\n"
             "  -h, --help     Prints this help message\n"
             "  -v, --version  Prints the version\n\n"
             "Written by Rosmer Lopez\n");
      return 0;
    } else if (option == 'v') {
      printf("xgetres v1.0\n");
      return 0;
    }
  }
  // non-option ARGV-elements
  optind < argc ? print_xresource(argv[optind])
                : printf("Try %s --help for more information\n", argv[0]);
  return 0;
}
