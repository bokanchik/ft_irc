/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:34:22 by dbaladro          #+#    #+#             */
/*   Updated: 2024/11/29 15:52:10 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Client.hpp"
#include <string>

/* ************************************************************************** */
/* *                       Constructors && Destructors                      * */
/* ************************************************************************** */
Client::Client( void ) {
	std::memset(&this->_netId, 0, sizeof(this->_netId));
	this->_hostname = "";
	this->_username = "";
	this->_nickname = "";
	this->_servername = "";
	this->_realname = "";
	this->_connected = false;
	this->_registred = false;
	this->_isOperator = false;
	this->_fd = -1;
	this->_mode = 0;
	return ;
}

Client::Client( const Client & rhs ) {
	this->_hostname = rhs._hostname;
	this->_username = rhs._username;
	this->_nickname = rhs._nickname;
	this->_servername = rhs._servername;
	this->_realname = rhs._realname;
	this->_connected = rhs._connected;
	this->_registred = rhs._registred;
	this->_isOperator = rhs._isOperator;
	this->_fd = rhs._fd;
	this->_mode = 0;
	return ;
}

Client::~Client() {
	return ;
}

/* ************************************************************************** */
/* *                            Getters and Setters                         * */
/* ************************************************************************** */
struct sockaddr_in	Client::getNetId( void ) const {
	return (this->_netId);
}

std::string	Client::getHostname( void ) const {
	return (this->_hostname);
}

std::string	Client::getUsername( void ) const {
	return (this->_username);
}

std::string	Client::getNickname( void ) const {
	return (this->_nickname);
}

std::string Client::getRealname( void ) const {
	return (this->_realname);
}

std::string Client::getServername( void ) const {
	return (this->_servername);
}

bool Client::getConnected( void ) const {
	return (this->_connected);
}

bool Client::getRegistred( void ) const {
	return (this->_registred);
}

int	Client::getFd( void ) const {
	return (this->_fd);
}

int		Client::getJoinedChannel( void ) const {
	return (this->_joinedChannel);
}

int		Client::getMode( void ) const {
	return (this->_mode);
}

std::string	Client::getModeStr( void ) const {
	std::string	result = "";
	if (this->_mode & INVISIBLE)
		result += "+i";
	if (this->_mode & WALLOPS)
		result += "+w";
	if (this->_mode & OPERATOR)
		result += "+o";
	if (this->_mode & LOCAL_OPERATOR)
		result += "+O";
	if (this->_mode & RESTRICTED_USER)
		result += "+r";
	return (result);
}

void Client::setConnected( void ){
	this->_connected = true;
}

void Client::setRegistred( void ){
	this->_registred = true;
}

void	Client::setNetId( struct sockaddr_in netId) {
	this->_netId = netId;
}


void	Client::setFd( int fd ) {
	this->_fd = fd;
}

void	Client::setHostname( const std::string& hostname ) {
	this->_hostname = hostname;
}

void	Client::setUsername( const std::string& username ) {
	this->_username = username;
}

void	Client::setNickname( const std::string& nick ) {
	this->_nickname = nick;
}

void	Client::setOperator( void ){
	this->_isOperator = true;
}

bool Client::isOperator( void ) const {
	return (this->_isOperator);
}

void	Client::setServername( const std::string& servername ) {
	this->_servername = servername;
}

void	Client::setRealname( const std::string& realname ) {
	this->_realname = realname;
}

void	Client::setMode(const short mode) {
	this->_mode = mode;
}


/* ************************************************************************** */
/* *                             Operator Overload                          * */
/* ************************************************************************** */
Client&	Client::operator=( Client const& rhs ) {
	if (this != &rhs) {
		this->_netId = rhs._netId;
		this->_hostname = rhs._hostname;
		this->_username = rhs._username;
		this->_nickname = rhs._nickname;
		this->_servername = rhs._servername;
		this->_realname = rhs._realname;
		this->_connected = rhs._connected;
		this->_realname = rhs._registred;
		this->_fd = rhs._fd;
	}
	return (*this);
}

std::ostream&	operator<<( std::ostream& os, const struct sockaddr_in& rhs ) {
	char	ip[INET6_ADDRSTRLEN];

	inet_ntop(AF_INET, &rhs, ip, sizeof(ip));
	os << rhs.sin_family << " " << ip << ":" << ntohs(rhs.sin_port) << std::endl;
	return (os);
}

std::ostream&	operator<<( std::ostream& os, const Client& rhs ) {
	os << "Client:" << std::endl
		<< "  - addr: " << rhs.getNetId() << std::endl
		<< "  - HOST: " << rhs.getHostname() << std::endl
		<< "  - NICK: " << rhs.getNickname() << std::endl
		<< "  - USER: " << rhs.getUsername() << std::endl
		<< "  - REALNAME: " << rhs.getRealname() << std::endl
		<< "  - SERVERNAME: " << rhs.getServername() << std::endl
		<< "  - MODE: << " << std::bitset<8>(rhs.getMode()) << std::endl;
		// << "  - SOCK: " << (rhs.getFd() == NULL ? 0 : *rhs.getFd()) << std::endl;
	return (os);
}
