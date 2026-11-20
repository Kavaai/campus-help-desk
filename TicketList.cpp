#include "TicketList.h"

TicketList::TicketList() : head(nullptr) {}

TicketList::~TicketList() {
    while (head != nullptr) {
        Node* oldHead = head;
        head = head->next;
        delete oldHead;
    }
}

void TicketList::insertByPriority(const Ticket& ticket) {
    Node* newNode = new Node(ticket);

    // Put the new node at the front when it has the highest priority.
    if (head == nullptr || ticket < head->ticket) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;
    // Moving past equal priorities keeps tickets in their insertion order.
    while (current->next != nullptr &&
           !(ticket < current->next->ticket)) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

Ticket* TicketList::searchByID(int ticketID) {
    Node* current = head;
    while (current != nullptr) {
        if (current->ticket.getTicketID() == ticketID) {
            return &current->ticket;
        }
        current = current->next;
    }
    return nullptr;
}

bool TicketList::removeByID(int ticketID) {
    Node* previous = nullptr;
    Node* current = head;
    while (current != nullptr &&
           current->ticket.getTicketID() != ticketID) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr) {
        return false;
    }

    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }
    delete current;
    return true;
}

bool TicketList::markResolved(int ticketID) {
    Ticket* ticket = searchByID(ticketID);
    if (ticket == nullptr) {
        return false;
    }
    ticket->setStatus("Resolved");
    return true;
}

bool TicketList::updateTicket(int ticketID, const std::string& description,
                              int priority, const std::string& extraInfo,
                              const Requester& requester) {
    Node* previous = nullptr;
    Node* current = head;
    while (current != nullptr &&
           current->ticket.getTicketID() != ticketID) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr) {
        return false;
    }

    const int oldPriority = current->ticket.getPriority();
    current->ticket.setDescription(description);
    current->ticket.setPriority(priority);
    current->ticket.setExtraInfo(extraInfo);
    current->ticket.setRequester(requester);

    if (oldPriority == priority) {
        return true;
    }

    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }
    Ticket updatedTicket = current->ticket;
    delete current;
    insertByPriority(updatedTicket);
    return true;
}

void TicketList::displayAll() const {
    if (isEmpty()) {
        std::cout << "No tickets in the system.\n";
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        std::cout << current->ticket << "\n-----------------------------\n";
        current = current->next;
    }
}

void TicketList::displayMatching(const std::string& status) const {
    bool found = false;
    Node* current = head;
    while (current != nullptr) {
        if (current->ticket.getStatus() == status) {
            std::cout << current->ticket << "\n-----------------------------\n";
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        if (status == "Open") {
            std::cout << "No open tickets found.\n";
        } else {
            std::cout << "No resolved tickets found.\n";
        }
    }
}

void TicketList::displayOpenTickets() const {
    displayMatching("Open");
}

void TicketList::displayResolvedTickets() const {
    displayMatching("Resolved");
}

int TicketList::countAll() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        ++count;
        current = current->next;
    }
    return count;
}

int TicketList::countOpen() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        if (current->ticket.getStatus() == "Open") {
            ++count;
        }
        current = current->next;
    }
    return count;
}

int TicketList::countResolved() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        if (current->ticket.getStatus() == "Resolved") {
            ++count;
        }
        current = current->next;
    }
    return count;
}

bool TicketList::isEmpty() const {
    return head == nullptr;
}
