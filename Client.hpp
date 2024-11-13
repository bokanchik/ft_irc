#ifndef CLIENT_HPP
# define CLIENT_HPP
# include <iostream>

class Client
{
    public:
        Client(void);
        Client(int socket);
        Client(const Client& other);
        Client &operator=(const Client &other);
        ~Client();

        int getSocket(){return _connectedSocket;}

    private:

        int                 _connectedSocket;
};

#endif

