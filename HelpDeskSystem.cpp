#include "HelpDeskSystem.h"
#include <iostream>
#include <sstream>

namespace {
bool readInteger(int& value) {
    std::string line;
    if (!std::getline(std::cin, line)) {
        return false;
    }
    std::stringstream input(line);
    char extra;
    if (input >> value && !(input >> extra)) {
        return true;
    }
    return false;
}
}

void HelpDeskSystem::printMenu() const {
    std::cout << "==============================\n"
              << "Campus Help Desk Ticket Tracker\n"
              << "==============================\n"
              << "1. Add New Ticket\n"
              << "2. Display All Tickets\n"
              << "3. Search Ticket by ID\n"
              << "4. Mark Ticket as Resolved\n"
              << "5. Update Ticket Information\n"
              << "6. Remove Ticket by ID\n"
              << "7. Display Open Tickets\n"
              << "8. Display Resolved Tickets\n"
              << "9. Display Ticket Statistics\n"
              << "10. Exit\n"
              << "Enter your choice: ";
}

int HelpDeskSystem::getValidMenuChoice() {
    int choice;
    while (true) {
        if (!readInteger(choice)) {
            if (!std::cin.eof()) {
                std::cout << "Invalid choice. Enter a number from 1 to 10: ";
                continue;
            }
            return -1;
        }
        if (choice >= 1 && choice <= 10) {
            return choice;
        }
        std::cout << "Invalid choice. Enter a number from 1 to 10: ";
    }
}

std::string HelpDeskSystem::readRequiredText(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, value)) {
            return "";
        }
        if (!value.empty()) {
            return value;
        }
        std::cout << "Input cannot be empty. Please try again.\n";
    }
}

std::string HelpDeskSystem::getValidTicketType() {
    int choice;
    while (true) {
        std::cout << "Enter ticket type:\n"
                  << "1. Hardware\n"
                  << "2. Software\n"
                  << "Choice: ";
        if (!readInteger(choice)) {
            if (!std::cin.eof()) {
                std::cout << "Invalid ticket type. Enter 1 or 2.\n";
                continue;
            }
            return "";
        }
        if (choice == 1) {
            return "Hardware";
        }
        if (choice == 2) {
            return "Software";
        }
        std::cout << "Invalid ticket type. Enter 1 or 2.\n";
    }
}

int HelpDeskSystem::getValidPriority(bool updating) {
    int priority;
    while (true) {
        if (updating) {
            std::cout << "Enter new priority (1 = High, 2 = Medium, 3 = Low): ";
        } else {
            std::cout << "Enter priority (1 = High, 2 = Medium, 3 = Low): ";
        }
        if (!readInteger(priority)) {
            if (!std::cin.eof()) {
                std::cout << "Invalid priority. Enter 1, 2, or 3.\n";
                continue;
            }
            return -1;
        }
        if (priority >= 1 && priority <= 3) {
            return priority;
        }
        std::cout << "Invalid priority. Enter 1, 2, or 3.\n";
    }
}

int HelpDeskSystem::getValidTicketID() {
    int ticketID;
    while (true) {
        if (!readInteger(ticketID)) {
            if (!std::cin.eof()) {
                std::cout << "Invalid ticket ID. Enter an ID greater than or equal to 1000: ";
                continue;
            }
            return -1;
        }
        if (ticketID >= 1000) {
            return ticketID;
        }
        std::cout << "Invalid ticket ID. Enter an ID greater than or equal to 1000: ";
    }
}

std::string HelpDeskSystem::getValidRole() {
    std::string role;
    while (true) {
        std::cout << "Enter requester role (Student/Faculty/Staff): ";
        if (!std::getline(std::cin, role)) {
            return "";
        }
        if (role == "Student" || role == "Faculty" || role == "Staff") {
            return role;
        }
        std::cout << "Invalid role. Enter Student, Faculty, or Staff.\n";
    }
}

Requester HelpDeskSystem::readRequesterInfo() {
    std::string name = readRequiredText("Enter requester name: ");
    std::string role = getValidRole();
    std::string email = readRequiredText("Enter requester email: ");
    return Requester(name, role, email);
}

void HelpDeskSystem::run() {
    while (true) {
        printMenu();
        int choice = getValidMenuChoice();
        if (choice == -1) {
            std::cout << "\nExiting program...\n";
            return;
        }

        switch (choice) {
        case 1:
            addTicket();
            break;
        case 2:
            displayAllTickets();
            break;
        case 3:
            searchTicket();
            break;
        case 4:
            markTicketResolved();
            break;
        case 5:
            updateTicket();
            break;
        case 6:
            removeTicket();
            break;
        case 7:
            displayOpenTickets();
            break;
        case 8:
            displayResolvedTickets();
            break;
        case 9:
            displayStatistics();
            break;
        case 10:
            std::cout << "Exiting program...\n";
            return;
        default:
            return;
        }
    }
}

void HelpDeskSystem::addTicket() {
    std::string type = getValidTicketType();
    if (type.empty()) {
        return;
    }
    int priority = getValidPriority();
    if (priority == -1) {
        return;
    }
    std::string description = readRequiredText("Enter description: ");
    std::string prompt = type == "Hardware"
        ? "Enter device type: "
        : "Enter application name: ";
    std::string extraInfo = readRequiredText(prompt);
    Requester requester = readRequesterInfo();
    if (std::cin.eof()) {
        return;
    }

    Ticket ticket(type, description, priority, extraInfo, requester);
    int assignedID = ticket.getTicketID();
    ticketList.insertByPriority(ticket);
    std::cout << "Ticket added successfully.\n"
              << "Assigned Ticket ID: " << assignedID << '\n';
}

void HelpDeskSystem::displayAllTickets() const {
    ticketList.displayAll();
}

void HelpDeskSystem::searchTicket() {
    std::cout << "Enter ticket ID to search: ";
    int ticketID = getValidTicketID();
    if (ticketID == -1) {
        return;
    }
    Ticket* ticket = ticketList.searchByID(ticketID);
    if (ticket == nullptr) {
        std::cout << "Ticket not found.\n";
        return;
    }
    std::cout << "Ticket found:\n" << *ticket << '\n';
}

void HelpDeskSystem::markTicketResolved() {
    std::cout << "Enter ticket ID to mark resolved: ";
    int ticketID = getValidTicketID();
    if (ticketID == -1) {
        return;
    }
    if (ticketList.markResolved(ticketID)) {
        std::cout << "Ticket marked as resolved.\n";
    } else {
        std::cout << "Ticket not found.\n";
    }
}

void HelpDeskSystem::updateTicket() {
    std::cout << "Enter ticket ID to update: ";
    int ticketID = getValidTicketID();
    if (ticketID == -1) {
        return;
    }
    Ticket* existing = ticketList.searchByID(ticketID);
    if (existing == nullptr) {
        std::cout << "Ticket not found.\n";
        return;
    }

    std::string description = readRequiredText("Enter new description: ");
    int priority = getValidPriority(true);
    if (priority == -1) {
        return;
    }
    std::string prompt = existing->getType() == "Hardware"
        ? "Enter new device type: "
        : "Enter new application name: ";
    std::string extraInfo = readRequiredText(prompt);
    Requester requester = readRequesterInfo();
    if (std::cin.eof()) {
        return;
    }

    ticketList.updateTicket(ticketID, description, priority, extraInfo,
                            requester);
    std::cout << "Ticket updated successfully.\n";
}

void HelpDeskSystem::removeTicket() {
    std::cout << "Enter ticket ID to remove: ";
    int ticketID = getValidTicketID();
    if (ticketID == -1) {
        return;
    }
    if (ticketList.removeByID(ticketID)) {
        std::cout << "Ticket removed successfully.\n";
    } else {
        std::cout << "Ticket not found.\n";
    }
}

void HelpDeskSystem::displayOpenTickets() const {
    ticketList.displayOpenTickets();
}

void HelpDeskSystem::displayResolvedTickets() const {
    ticketList.displayResolvedTickets();
}

void HelpDeskSystem::displayStatistics() const {
    std::cout << "--- Ticket Statistics ---\n"
              << "Total tickets currently in system: " << ticketList.countAll()
              << '\n'
              << "Open tickets: " << ticketList.countOpen() << '\n'
              << "Resolved tickets: " << ticketList.countResolved() << '\n'
              << "Total tickets ever created: "
              << Ticket::getTotalTicketsCreated() << '\n';
}
