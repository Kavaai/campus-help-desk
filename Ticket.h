#ifndef TICKET_H
#define TICKET_H

#include "Requester.h"
#include <iostream>
#include <string>

class Ticket {
private:
    int ticketID;
    std::string type;
    std::string description;
    int priority;
    std::string status;
    std::string extraInfo;
    Requester requester;

public:
    static int nextTicketID;
    static int totalTicketsCreated;

    Ticket();
    Ticket(const std::string& type, const std::string& description,
           int priority, const std::string& extraInfo,
           const Requester& requester);

    int getTicketID() const;
    const std::string& getType() const;
    const std::string& getDescription() const;
    int getPriority() const;
    const std::string& getStatus() const;
    const std::string& getExtraInfo() const;
    const Requester& getRequester() const;

    void setTicketID(int ticketID);
    void setType(const std::string& type);
    void setDescription(const std::string& description);
    void setPriority(int priority);
    void setStatus(const std::string& status);
    void setExtraInfo(const std::string& extraInfo);
    void setRequester(const Requester& requester);

    static int getTotalTicketsCreated();
    bool operator<(const Ticket& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Ticket& ticket);
};

#endif
