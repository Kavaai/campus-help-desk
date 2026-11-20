#include "Requester.h"

Requester::Requester() : name(""), role(""), email("") {}

Requester::Requester(const std::string& name, const std::string& role,
                     const std::string& email)
    : name(name), role(role), email(email) {}

const std::string& Requester::getName() const {
    return name;
}

const std::string& Requester::getRole() const {
    return role;
}

const std::string& Requester::getEmail() const {
    return email;
}

void Requester::setName(const std::string& newName) {
    name = newName;
}

void Requester::setRole(const std::string& newRole) {
    role = newRole;
}

void Requester::setEmail(const std::string& newEmail) {
    email = newEmail;
}

std::ostream& operator<<(std::ostream& out, const Requester& requester) {
    out << "Requester Name: " << requester.name << '\n'
        << "Requester Role: " << requester.role << '\n'
        << "Requester Email: " << requester.email;
    return out;
}
