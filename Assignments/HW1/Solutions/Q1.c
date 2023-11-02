#include <stdio.h>

// Define a struct to represent a person with a name, age, and number
struct Person {
    char name[50]; // Assuming names are at most 50 characters long
    int age;
    int number;
};

struct group {
    struct Person people[2];
    double mean;
};

void grouping(struct Person people[], int n) {
    struct group groups[n / 2];
    for (int i = 0; i < n / 2; i++) {
        groups[i].people[0] = people[i];
        groups[i].people[1] = people[n - i - 1];
        groups[i].mean = (people[i].number + people[n - i - 1].number) / 2.0;
    }
    // sort groups by mean in descending order
    for (int i = 0; i < n / 2; i++) {
        for (int j = i + 1; j < n / 2; j++) {
            if (groups[i].mean < groups[j].mean) {
                struct group temp = groups[i];
                groups[i] = groups[j];
                groups[j] = temp;
            }
        }
    }


    // print groups
    for (int i = 0; i < n / 2; i++) {
        printf("%s %d %d, %s %d %d\n", groups[i].people[0].name, groups[i].people[0].age, groups[i].people[0].number, groups[i].people[1].name, groups[i].people[1].age, groups[i].people[1].number);
    }

}

int main() {
    int n; // Number of people
    scanf("%d", &n);

    struct Person people[n]; // Declare an array of structs

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", people[i].name, &people[i].age, &people[i].number);
    }
    // if n is odd, delete the person with least number
    if (n % 2 == 1) {
        int min = 0;
        for (int i = 1; i < n; i++) {
            if (people[i].number < people[min].number) {
                min = i;
            }
        }
        for (int i = min; i < n - 1; i++) {
            people[i] = people[i + 1];
        }
        n--;
    }
    grouping(people, n);
    return 0;
}
