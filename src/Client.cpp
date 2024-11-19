/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:34:22 by dbaladro          #+#    #+#             */
/*   Updated: 2024/11/19 17:04:43 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

/* ************************************************************************** */
/* *                       Constructors && Destructors                      * */
/* ************************************************************************** */
Client::Client( void ) {
	std::memset(&this->_netId, 0, sizeof(this->_netId));
	this->_nickname = "";
	this->_hostname = "";
	this->_username = "";
	this->_fd = NULL;
	this->_isRegistred = false;
	return ;
}

Client::Client( const Client& rhs )
	: _netId(rhs._netId), _nickname(rhs._nickname), _hostname(rhs._hostname), 
		_username(rhs._username), _fd(rhs._fd) {
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

bool Client::getRegistred( void ) const{
	return (this->_isRegistred);
}

int*	Client::getFd( void ) const {
	return (this->_fd);
}

void Client::setRegistred( int status ){
	this->_isRegistred = status;
}

void	Client::setFd( int *fd ) {
	this->_fd = fd;
}

void	Client::setNetId( struct sockaddr_in netId) {
	this->_netId = netId;
}

void	Client::setNickname( Message *obj ){
	if (obj->getCommand() == "NICK"){
		this->_nickname = obj->getParam().front();
		// chech nickname ? 
	}	
}

void	Client::setUsername( Message *obj ){
		
}

void	Client::setPassword( Message *obj, std::string serverPasswd){
	if (obj->getCommand() == "PASS"){
		if (obj->getParam().size() == 1){
			this->_password = obj->getParam().front();
			if (this->_password == serverPasswd){
				success_log("Password confirmed");
				return ;
			}
			else
				throw std::runtime_error("Wrong password");
		}
		else
			throw std::runtime_error("Wrong PASS cmd format");
	}	
}

/* ************************************************************************** */
/* *                             Operator Overload                          * */
/* ************************************************************************** */
Client&	Client::operator=( Client const& rhs ) {
	if (this != &rhs) {
		this->_netId = rhs._netId;
		this->_nickname = rhs._nickname;
		this->_hostname = rhs._hostname;
		this->_username = rhs._username;
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
		<< "  - USER: " << rhs.getUsername() << std::endl
		<< "  - NICK: " << rhs.getNickname() << std::endl;
		// << "  - SOCK: " << (rhs.getFd() == NULL ? 0 : *rhs.getFd()) << std::endl;
	return (os);
}

