#include <stdio.h>
#include <string.h>
#include <conio.h>

#define MAX_PASSENGERS 100
#define MAX_SEATS 50
#define MAX_TRAINS 20

struct Train {
    char trainNo[10];
    char name[50];
    char from[30];
    char to[30];
    char departure[10];
    char arrival[10];
} trains[MAX_TRAINS] = {
    // Chennai Central Trains (MAS)
    {"12604", "Chennai Express", "Chennai Central", "Mumbai Central", "20:00", "12:30"},
    {"12602", "Chennai Mail", "Chennai Central", "New Delhi", "22:15", "18:45"},
    {"16094", "Lalbagh Express", "Chennai Central", "Bangalore", "06:05", "11:30"},
    {"12606", "Palaruvi Express", "Chennai Central", "Kollam", "21:30", "14:20"},
    {"12670", "Ganga Kaveri Exp", "Chennai Central", "Chhapra", "20:45", "15:30"},
    {"12610", "Cheran Express", "Chennai Central", "Coimbatore", "22:30", "05:45"},
    {"12674", "Kerala Express", "Chennai Central", "Kollam", "16:45", "09:30"},
    {"12640", "Brindavan Exp", "Chennai Central", "Bangalore", "07:10", "12:45"},
    {"12608", "Lalbagh SF Exp", "Chennai Central", "Bangalore", "19:40", "05:25"},
    {"12616", "Grand Trunk Exp", "Chennai Central", "New Delhi", "20:50", "17:40"},
    
    // Chennai Egmore Trains (MS)
    {"12605", "Pallavan Express", "Chennai Egmore", "Karaikal", "07:45", "13:20"},
    {"12607", "Lalbagh SF Express", "Chennai Egmore", "Bangalore", "19:45", "05:30"},
    {"16115", "Chennai Express", "Chennai Egmore", "Tiruchirappalli", "23:15", "04:45"},
    {"12638", "Pandian Express", "Chennai Egmore", "Madurai", "21:45", "05:30"},
    {"12634", "Kanyakumari Exp", "Chennai Egmore", "Kanyakumari", "18:30", "13:45"},
    {"12636", "Vaigai Express", "Chennai Egmore", "Madurai", "07:45", "12:15"},
    {"12632", "Nellai Express", "Chennai Egmore", "Tirunelveli", "20:25", "05:45"},
    {"16127", "Guruvayur Exp", "Chennai Egmore", "Guruvayur", "09:00", "06:40"},
    {"12666", "KKT Express", "Chennai Egmore", "Kacheguda", "21:50", "11:30"},
    {"12654", "NCJ SF Express", "Chennai Egmore", "Nagercoil", "19:00", "05:45"}
};

int trainCount = 20;

struct Passenger {
    int pnr;
    char name[30];
    int age;
    char gender[10];
    char trainNo[10];
    char journeyDate[12];
    int seatNo;
    char status[20];
} passengers[MAX_PASSENGERS];

int passengerCount = 0;

// Function prototypes
void displayTrains();
void bookTicket(int trainIndex);
void checkAvailability();
void cancelTicket();
void prepareChart();

int main() {
    int choice;
    do {
        printf("\n====== Railway Reservation System ======");
        printf("\n1. View Trains & Book Ticket (20 Trains)");
        printf("\n2. Check Availability");
        printf("\n3. Cancel Ticket");
        printf("\n4. Prepare Chart");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayTrains(); break;
            case 2: checkAvailability(); break;
            case 3: cancelTicket(); break;
            case 4: prepareChart(); break;
            case 5: printf("Thank you for using Railway Reservation System!"); break;
            default: printf("Invalid Choice!"); getch();
        }
    } while (choice != 5);
    return 0;
}

void displayTrains() {
    int i, choice;
    printf("\n======== 20 Available Trains from Chennai ========");
    printf("\nSN | Train No  | Name                | From             | To               | Dep   | Arr   ");
    printf("\n--------------------------------------------------------------------");
    
    for (i = 0; i < trainCount; i++) {
        printf("\n%2d | %-7s | %-18s | %-15s | %-14s | %-5s | %-5s", 
               i+1, trains[i].trainNo, trains[i].name, trains[i].from, 
               trains[i].to, trains[i].departure, trains[i].arrival);
    }
    
    printf("\n--------------------------------------------------------------------");
    printf("\nEnter Train Serial No (1-20) to Book: ");
    scanf("%d", &choice);
    
    if (choice >= 1 && choice <= trainCount) {
        bookTicket(choice - 1);
    } else {
        printf("Invalid Train Number!");
        getch();
    }
}

void bookTicket(int trainIndex) {
    if (passengerCount == MAX_PASSENGERS) {
        printf("\nAll seats are fully booked!\n");
        getch();
        return;
    }

    struct Passenger p;
    strcpy(p.trainNo, trains[trainIndex].trainNo);
    
    printf("\nTrain Selected: %s - %s (%s - %s)", 
           trains[trainIndex].name, trains[trainIndex].trainNo,
           trains[trainIndex].from, trains[trainIndex].to);
    printf("\nDeparture: %s | Arrival: %s", 
           trains[trainIndex].departure, trains[trainIndex].arrival);
    
    printf("\nEnter Journey Date (DD-MM-YYYY): ");
    scanf("%s", p.journeyDate);

    int bookedSeats = 0;
    for (int i = 0; i < passengerCount; i++) {
        if (strcmp(passengers[i].trainNo, p.trainNo) == 0 &&
            strcmp(passengers[i].journeyDate, p.journeyDate) == 0 &&
            strcmp(passengers[i].status, "BOOKED") == 0) {
            bookedSeats++;
        }
    }

    if (bookedSeats >= MAX_SEATS) {
        printf("\nNo seats available on this train for %s.\n", p.journeyDate);
        getch();
        return;
    }

    p.pnr = 1000 + passengerCount;
    printf("\nEnter Passenger Name: ");
    scanf("%s", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Gender (M/F): ");
    scanf("%s", p.gender);
    p.seatNo = bookedSeats + 1;
    strcpy(p.status, "BOOKED");

    passengers[passengerCount++] = p;

    printf("\n======== TICKET BOOKED SUCCESSFULLY ========");
    printf("\nPNR: %d", p.pnr);
    printf("\nTrain: %s - %s", trains[trainIndex].name, p.trainNo);
    printf("\nFrom: %s | To: %s", trains[trainIndex].from, trains[trainIndex].to);
    printf("\nJourney Date: %s | Seat: %d", p.journeyDate, p.seatNo);
    printf("\nDeparture: %s", trains[trainIndex].departure);
    getch();
}

void checkAvailability() {
    char trainNo[10], journeyDate[12];
    printf("\nEnter Train Number: ");
    scanf("%s", trainNo);
    printf("Enter Journey Date (DD-MM-YYYY): ");
    scanf("%s", journeyDate);

    int bookedSeats = 0;
    for (int i = 0; i < passengerCount; i++) {
        if (strcmp(passengers[i].trainNo, trainNo) == 0 &&
            strcmp(passengers[i].journeyDate, journeyDate) == 0 &&
            strcmp(passengers[i].status, "BOOKED") == 0) {
            bookedSeats++;
        }
    }

    printf("\nTrain %s | Date: %s", trainNo, journeyDate);
    printf("\nSeats Booked: %d/%d | Available: %d", bookedSeats, MAX_SEATS, MAX_SEATS - bookedSeats);
    getch();
}

void cancelTicket() {
    int pnr;
    printf("\nEnter PNR Number to cancel: ");
    scanf("%d", &pnr);

    for (int i = 0; i < passengerCount; i++) {
        if (passengers[i].pnr == pnr && strcmp(passengers[i].status, "BOOKED") == 0) {
            strcpy(passengers[i].status, "CANCELLED");
            printf("\nTicket Cancelled Successfully!");
            printf("\nPNR: %d | Name: %s | Train: %s", 
                   passengers[i].pnr, passengers[i].name, passengers[i].trainNo);
            getch();
            return;
        }
    }
    printf("\nPNR not found or already cancelled.");
    getch();
}

void prepareChart() {
    char trainNo[10], journeyDate[12];
    printf("\nEnter Train Number: ");
    scanf("%s", trainNo);
    printf("Enter Journey Date (DD-MM-YYYY): ");
    scanf("%s", journeyDate);

    printf("\n======== RESERVATION CHART ========");
    printf("\nPNR   Name         Age Gender Seat Status");
    printf("\n------------------------------------------------");
    
    int found = 0;
    for (int i = 0; i < passengerCount; i++) {
        if (strcmp(passengers[i].trainNo, trainNo) == 0 &&
            strcmp(passengers[i].journeyDate, journeyDate) == 0) {
            printf("\n%4d  %-12s %3d  %-6s %3d  %-10s", 
                   passengers[i].pnr, passengers[i].name, passengers[i].age, 
                   passengers[i].gender, passengers[i].seatNo, passengers[i].status);
            found = 1;
        }
    }
    
    if (!found) {
        printf("\nNo bookings found for this train/date.");
    }
    getch();
}
