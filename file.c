#include <stdio.h>

int main() {
    // باز کردن فایل برای نوشتن
    FILE *file = fopen("example.txt", "w"); 
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // نوشتن داده به فایل
    fprintf(file, "Hello, this is a text file.\n");
    fprintf(file, "It contains some simple text.\n");

    // بستن فایل
    fclose(file);

    // باز کردن فایل برای خواندن
    file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // خواندن داده از فایل
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  // نمایش خط خوانده شده
    }

    // بستن فایل
    fclose(file);

    return 0;
}
