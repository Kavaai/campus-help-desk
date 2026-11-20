#include "Ticket.h"

int Ticket::nextTicketID = 1000;
int Ticket::totalTicketsCreated = 0;

Ticket::Ticket()
    : ticketID(-1), type(""), description(""), priority(3), status("Open"),
      extraInfo(""), requester() {}

Ticket::Ticket(const std::string& type, const std::string& description,
               int priority, const std::string& extraInfo,
               const Requester& requester)
    : ticketID(nextTicketID++), type(type), description(description),
      priority(priority), status("Open"), extraInfo(extraInfo),
      requester(requester) {
    ++totalTicketsCreated;
}

int Ticket::getTicketID() const {
    return ticketID;
}

const std::string& Ticket::getType() const {
    return type;
}

const std::string& Ticket::getDescription() const {
    return description;
}

int Ticket::getPriority() const {
    return priority;
}

const std::string& Ticket::getStatus() const {
    return status;
}

const std::string& Ticket::getExtraInfo() const {
    return extraInfo;
}

const Requester& Ticket::getRequester() const {
    return requester;
}

void Ticket::setTicketID(int newTicketID) {
    ticketID = newTicketID;
}

void Ticket::setType(const std::string& newType) {
    type = newType;
}

void Ticket::setDescription(const std::string& newDescription) {
    description = newDescription;
}

void Ticket::setPriority(int newPriority) {
    priority = newPriority;
}

void Ticket::setStatus(const std::string& newStatus) {
    status = newStatus;
}

void Ticket::setExtraInfo(const std::string& newExtraInfo) {
    extraInfo = newExtraInfo;
}

void Ticket::setRequester(const Requester& newRequester) {
    requester = newRequester;
}

int Ticket::getTotalTicketsCreated() {
    return totalTicketsCreated;
}

bool Ticket::operator<(const Ticket& other) const {
    return priority < other.priority;
}

std::ostream& operator<<(std::ostream& out, const Ticket& ticket) {
    out << "Ticket ID: " << ticket.ticketID << '\n'
        << "Type: " << ticket.type << '\n'
        << "Description: " << ticket.description << '\n'
        << "Priority: " << ticket.priority << '\n'
        << "Status: " << ticket.status << '\n'
        << "Extra Info: " << ticket.extraInfo << '\n'
        << ticket.requester;
    return out;
}
