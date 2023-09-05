#include <stdio.h>
#include <string.h>

#define MAX_PLACES 100
#define MAX_BOOKINGS 100

// Structure for a place
struct Place {
    char name[100];
};

// Structure for a booking
struct Booking {
    char place_name[100];
    char customer_name[100];
    char booking_date[20];
    char booking_time[20];
};

struct Place places[MAX_PLACES];
struct Booking bookings[MAX_BOOKINGS];
int num_places = 0;
int num_bookings = 0;

// Function to check admin login
int admin_login() {
    char username[100], password[100];
    printf("Admin Login\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    return strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0;
}

// Function to save places and bookings to files
void save_data() {
    FILE *places_file = fopen("places.txt", "w");
    if (places_file) {
        for (int i = 0; i < num_places; i++) {
            fprintf(places_file, "%s\n", places[i].name);
        }
        fclose(places_file);
    }

    FILE *bookings_file = fopen("bookings.txt", "w");
    if (bookings_file) {
        for (int i = 0; i < num_bookings; i++) {
            fprintf(bookings_file, "%s %s %s %s\n", bookings[i].place_name, bookings[i].customer_name, bookings[i].booking_date, bookings[i].booking_time);
        }
        fclose(bookings_file);
    }
}

// Function to load places and bookings from files
void load_data() {
    FILE *places_file = fopen("places.txt", "r");
    if (places_file) {
        while (fscanf(places_file, "%s", places[num_places].name) != EOF) {
            num_places++;
        }
        fclose(places_file);
    }

    FILE *bookings_file = fopen("bookings.txt", "r");
    if (bookings_file) {
        while (fscanf(bookings_file, "%s %s %s %s", bookings[num_bookings].place_name, bookings[num_bookings].customer_name, bookings[num_bookings].booking_date, bookings[num_bookings].booking_time) != EOF) {
            num_bookings++;
        }
        fclose(bookings_file);
    }
}

// Function to add a place
void add_place() {
    if (num_places >= MAX_PLACES) {
        printf("Cannot add more places.\n");
        return;
    }

    printf("Enter the name of the place: ");
    scanf("%s", places[num_places].name);
    num_places++;
    printf("Place added successfully.\n");
}

// Function to edit a place
void edit_place() {
    if (num_places == 0) {
        printf("No places available to edit.\n");
        return;
    }

    printf("Enter the index of the place you want to edit: ");
    int place_index;
    scanf("%d", &place_index);
    place_index--;

    if (place_index >= 0 && place_index < num_places) {
        printf("Enter the new name for the place: ");
        scanf("%s", places[place_index].name);
        printf("Place updated successfully.\n");
    } else {
        printf("Invalid place index.\n");
    }
}

// Function to delete a place
void delete_place() {
    if (num_places == 0) {
        printf("No places available to delete.\n");
        return;
    }

    printf("Enter the index of the place you want to delete: ");
    int place_index;
    scanf("%d", &place_index);
    place_index--;

    if (place_index >= 0 && place_index < num_places) {
        // Shift places in the array to remove the deleted place
        for (int i = place_index; i < num_places - 1; i++) {
            strcpy(places[i].name, places[i + 1].name);
        }
        num_places--;
        printf("Place deleted successfully.\n");
    } else {
        printf("Invalid place index.\n");
    }
}

// Function to view all places
void view_places() {
    printf("Available Places:\n");
    for (int i = 0; i < num_places; i++) {
        printf("%d. %s\n", i + 1, places[i].name);
    }
}

// Function to cancel a booking
void cancel_booking() {
    if (num_bookings == 0) {
        printf("No bookings to cancel.\n");
        return;
    }

    printf("Enter your name: ");
    char customer_name[100];
    scanf("%s", customer_name);

    int found = 0; // To check if a booking was found for the customer

    for (int i = 0; i < num_bookings; i++) {
        if (strcmp(bookings[i].customer_name, customer_name) == 0) {
            printf("Booking %d:\n", i + 1);
            printf("Place: %s\n", bookings[i].place_name);
            printf("Date: %s\n", bookings[i].booking_date);
            printf("Time: %s\n", bookings[i].booking_time);
            printf("Do you want to cancel this booking? (1 for Yes, 0 for No): ");
            int cancel_choice;
            scanf("%d", &cancel_choice);

            if (cancel_choice == 1) {
                for (int j = i; j < num_bookings - 1; j++) {
                    strcpy(bookings[j].place_name, bookings[j + 1].place_name);
                    strcpy(bookings[j].customer_name, bookings[j + 1].customer_name);
                    strcpy(bookings[j].booking_date, bookings[j + 1].booking_date);
                    strcpy(bookings[j].booking_time, bookings[j + 1].booking_time);
                }
                num_bookings--;
                printf("Booking canceled successfully.\n");
            } else {
                printf("Booking not canceled.\n");
            }

            found = 1;
            break; // Exit the loop after processing the booking
        }
    }

    if (!found) {
        printf("No bookings found for the customer: %s\n", customer_name);
    }
}

// Function to book a place
void book_place() {
    if (num_places == 0) {
        printf("No places available for booking.\n");
        return;
    }

    printf("Enter your name: ");
    char customer_name[100];
    scanf("%s", customer_name);

    printf("Enter the index of the place you want to book: ");
    int place_index;
    scanf("%d", &place_index);
    place_index--;

    if (place_index >= 0 && place_index < num_places) {
        printf("Enter booking date: ");
        char booking_date[20];
        scanf("%s", booking_date);

        printf("Enter booking time: ");
        char booking_time[20];
        scanf("%s", booking_time);

        strcpy(bookings[num_bookings].place_name, places[place_index].name);
        strcpy(bookings[num_bookings].customer_name, customer_name);
        strcpy(bookings[num_bookings].booking_date, booking_date);
        strcpy(bookings[num_bookings].booking_time, booking_time);

        num_bookings++;
        printf("Booking successful!\n");
    } else {
        printf("Invalid place index.\n");
    }
}

// Function to view all bookings
void view_bookings() {
    printf("Bookings: \n\n");
    for (int i = 0; i < num_bookings; i++) {
        printf("Booking %d:\n", i + 1);
        printf("Place: %s\n", bookings[i].place_name);
        printf("Customer: %s\n", bookings[i].customer_name);
        printf("Date: %s\n", bookings[i].booking_date);
        printf("Time: %s\n", bookings[i].booking_time);
        printf("\n");
    }
}

int main() {
    load_data();  // Load data from files at the beginning

    while (1) {
        printf("\nWelcome to the Booking System!\n");
        printf("1. Admin Login\n");
        printf("2. Customer Login\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Admin section
                if (admin_login()) {
                    while (1) {
                        printf("\nAdmin Menu:\n");
                        printf("1. Add Place\n");
                        printf("2. Edit Place\n");
                        printf("3. Delete Place\n");
                        printf("4. View Places\n");
                        printf("5. View Bookings\n");
                        printf("6. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1:
                                add_place();
                                break;
                            case 2:
                                edit_place();
                                break;
                            case 3:
                                delete_place();
                                break;
                            case 4:
                                view_places();
                                break;
                            case 5:
                                view_bookings();
                                break;
                            case 6:
                                printf("Admin logged out.\n");
                                break;
                            default:
                                printf("Invalid choice.\n");
                        }

                        save_data();  // Save data to files after each operation

                        if (choice == 6) {
                            break;
                        }
                    }
                } else {
                    printf("Invalid admin credentials.\n");
                }
                break;
            case 2:
                // Customer section
                printf("Welcome, Customer!\n");
                printf("1. View Places\n");
                printf("2. Book Place\n");
                printf("3. Cancel Booking\n");
                printf("4. Quit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        view_places();
                        break;
                    case 2:
                        book_place();
                        break;
                    case 3:
                        cancel_booking();
                        break;
                    case 4:
                        printf("Customer logged out.\n");
                        break;
                    default:
                        printf("Invalid choice.\n");
                }
                break;
            case 3:
                printf("Exiting the Booking System. Goodbye!\n");
                save_data();  // Save data to files before exiting
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
