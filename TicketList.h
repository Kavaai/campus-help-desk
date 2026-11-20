#ifndef TICKET_LIST_H
#define TICKET_LIST_H

#include "Ticket.h"
#include <iostream>

class TicketList {
public:
    TicketList();
    ~TicketList();

    void insertByPriority(const Ticket& ticket);
    Ticket* searchByID(int ticketID);
    bool removeByID(int ticketID);
    bool markResolved(int ticketID);
    bool updateTicket(int ticketID, const std::string& description,
                      int priority, const std::string& extraInfo,
                      const Requester& requester);

    void displayAll() const;
    void displayOpenTickets() const;
    void displayResolvedTickets() const;

    int countAll() const;
    int countOpen() const;
    int countResolved() const;
    bool isEmpty() const;

private:
    struct Node {
        Ticket ticket;
        Node* next;
        explicit Node(const Ticket& ticket) : ticket(ticket), next(nullptr) {}
    };

    Node* head;
    void displayMatching(const std::string& status) const;
};

#endif