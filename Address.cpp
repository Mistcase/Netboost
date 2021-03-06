#include "Address.hpp"

netboost::Address::Address(std::string address)
{
    this->address = 0;
    std::string words[5];

    int index = 0;
    for (auto& symbol : address)
    {
        if (symbol != '.' && symbol != ':')
        {
            words[index] += symbol;
        }
        else
        {
            index++;
        }
    }
    if (index != 4)
    {
        //ERROR
    }
    for (int i = 0; i < 4; i++)
    {
        this->address |= ((atoi(words[i].c_str())) << (8 * (3 - i)));
    }
    port = (unsigned short)(atoi(words[4].c_str()));
    initSockAddr();
}

netboost::Address::Address(std::string address, unsigned short port) : Address(address + ":" + std::to_string(port))
{

}


netboost::Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port)
{
    address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
    this->port = port;
    initSockAddr();
}

netboost::Address::Address(unsigned int destination_address, unsigned short destination_port)
{
    address = destination_address;
    port = destination_port;
    initSockAddr();
}

unsigned int netboost::Address::getAddress() const noexcept
{
    return address;
}

std::string netboost::Address::getAddress(bool addPort) const noexcept
{
    return std::to_string(getA()) + "." + std::to_string(getB()) + "." + std::to_string(getC()) + "."
    + std::to_string(getD()) + (addPort ? ":" + std::to_string(getPort()) : "");
}

sockaddr_in* netboost::Address::getSockAddr() noexcept
{
    return &sockaddrIn;
}

unsigned char netboost::Address::getA() const noexcept
{
    return (address >> 24);
}

unsigned char netboost::Address::getB() const noexcept
{
    return (address & 0xFF0000) >> 16;
}

unsigned char netboost::Address::getC() const noexcept
{
    return (address & 0xFF00) >> 8;
}

unsigned char netboost::Address::getD() const noexcept
{
    return (address & 0xFF);
}

unsigned short netboost::Address::getPort() const noexcept
{
    return port;
}

bool netboost::Address::operator == ( const Address & other ) const noexcept
{
    return ((address == other.address) && (port == other.port));
}

bool netboost::Address::operator != ( const Address & other ) const noexcept
{
    return ((address != other.address) || (port != other.port));
}

void netboost::Address::initSockAddr() noexcept
{
    sockaddrIn.sin_family = AF_INET;
    sockaddrIn.sin_port = htons(port);
    sockaddrIn.sin_addr.s_addr = htonl(address);
}