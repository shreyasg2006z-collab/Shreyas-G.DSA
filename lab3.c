#include <stdio.h>
#include <string.h>

int main() {
    char operation[50];
    int num1, num2;
    int result;

    printf("Enter an operation (add, sub, mul, div): ");
    fgets(operation, sizeof(operation), stdin);
    operation[strcspn(operation, "\n")] = '\0'; // remove newline

    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    if (strcmp(operation, "add") == 0) {
        result = num1 + num2;
        printf("Result: %d\n", result);
    } else if (strcmp(operation, "sub") == 0) {
        result = num1 - num2;
        printf("Result: %d\n", result);
    } else if (strcmp(operation, "mul") == 0) {
        result = num1 * num2;
        printf("Result: %d\n", result);
    } else if (strcmp(operation, "div") == 0) {
        if (num2 != 0) {
            printf("Result: %.2f\n", (float)num1 / num2);
        } else {
            printf("Error: Division by zero!\n");
        }
    } else {
        printf("Invalid operation!\n");
    }

    return 0;
}
