#ifndef HELPDESKSYSTEM_H
#define HELPDESKSYSTEM_H

#include "TicketList.h"
#include <string>

class HelpDeskSystem {
private:
    TicketList ticketList;

    int getValidMenuChoice();
    std::string getValidTicketType();
    int getValidPriority(bool updating = false);
    int getValidTicketID();
    std::string getValidRole();
    Requester readRequesterInfo();
    std::string readRequiredText(const std::string& prompt);
    void printMenu() const;

public:
    void run();
    void addTicket();
    void displayAllTickets() const;
    void searchTicket();
    void markTicketResolved();
    void updateTicket();
    void removeTicket();
    void displayOpenTickets() const;
    void displayResolvedTickets() const;
    void displayStatistics() const;
};

#endif
