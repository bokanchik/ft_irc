/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:00:49 by dbaladro          #+#    #+#             */
/*   Updated: 2024/11/23 22:48:57 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

/* ************************************************************************** */
/* *                       Constructors && Destructors                      * */
/* ************************************************************************** */
Message::Message( void )
	: _prefix(""), _command(""), _param()
{
	return ;
}

Message::Message( const Message& rhs )
	: _prefix(rhs._prefix), _command(rhs._command), _param(rhs._param)
{
	return ;
}

Message::Message( const char *buf, int& i, const int len ) {
	//! Setting default value in case of error
	this->_prefix = "";
	this->_command = "";
	this->_param = std::vector<std::string>();

	this->_init(buf, i, len);
	return ;
}

Message::~Message()
{
	return ;
}

/* ************************************************************************** */
/* *                             Operator Overload                          * */
/* ************************************************************************** */
Message&	Message::operator=( const Message& rhs ) {
	if (this != &rhs) {
		this->_prefix = rhs._prefix;
		this->_command = rhs._command;
		this->_param = rhs._param;
	}
	return (*this);
}

							//! FOR TESTING PURPOSE 
std::ostream&	Message::printParam( std::ostream& os ) const {
	for (std::vector<std::string>::const_iterator it = this->_param.begin(); it != this->_param.end(); it++) {
		os << "[ " << *it << " ] ";
	}
	return (os);
}

std::ostream&	operator<<(std::ostream& os, const Message& rhs) {
	os << "Message:" << std::endl
		<< "  - Prefix : " << rhs.getPrefix()
		<< "  - Command: " << rhs.getCommand()
		<< "  - Param  : ";
	rhs.printParam(os);
	os << std::endl;
	return (os);
}


/* ************************************************************************** */
/* *                            Getters and Setters                         * */
/* ************************************************************************** */
std::string	Message::getPrefix( void ) const {
	return (this->_prefix);
}


std::string	Message::getCommand( void ) const {
	return (this->_command);
}


std::vector<std::string>	Message::getParam( void ) const {
	return (this->_param);
}

/* ************************************************************************** */
/* *                           Getters and Setters                         * */
/* ************************************************************************** */
void	Message::setPrefix( std::string prefix ) {
	int	start = 0;

	while (prefix[start] == ':') //! Skip ':'
		start++;
	this->_prefix = prefix.substr(start, prefix.size());
}

void	Message::setContent( std::string content ) {
	const char	*buf = content.c_str();
	int			i = 0;
	int			len = content.size();

	if (buf[i] == ':') {
		this->_prefix = AParser::getPrefix(buf, i, len);
		i++; //!< Skip Space after prefix
	}

	this->_command = AParser::getCommand(buf, i, len);
	this->_param = AParser::getParam(buf, i, len);

	return ;
}

/* ************************************************************************** */
/* *                              Member function                           * */
/* ************************************************************************** */
std::string	Message::toString( void ) const {
	std::string	str;

	str.reserve(512);
	if (this->_prefix[0] != ':')
		str.append(1, ':');
	str.append(this->_prefix + SPACE);

	str.append(this->_command);

	for (std::vector<std::string>::const_iterator it = this->_param.begin(); it != this->_param.end(); it++) {
		str.append(*it + SPACE);
	}
	str.append("\r\n");
	return (str);
}

/**
<<<<<<< HEAD
 * @brief Check if c is a special char according to RFC2812
 *
 * RFC2812: 2000 IRC Protocol */
static int	isspecial(const char c) {
	switch (c) {
		case LEFT_CURLY_BRACE :
		case RIGHT_CURLY_BRACE :
		case LEFT_BRACKET :
		case RIGHT_BRACKET :
		case CARET :
		case BACKTICK :
		case BACKSLASH :
		case UNDERSCORE :
		case PIPE :
			return (1);
		default :
			return (0);
	}
}

/**
 * @brief Init the Message at construction
 *
 * Parse the buffer as a Message throwing error when needed
 *
 * @param buf The buffer containg the message to parse
 * @param i The buffer index (in case of multile messages in the same buffer)
 * @param len The message len
 */
void	Message::_init(const char *buf, int& i, const int len) {
	if (len == 0) //! security but shouldn't happen
		return ;

	if (buf[i] == ':') {
		this->_prefix = AParser::getPrefix(buf, i, len);
		i++; //!< Skip Space after prefix
	}

	this->_command = AParser::getCommand(buf, i, len);
	this->_param = AParser::getParam(buf, i, len);

	if (std::strncmp(buf + i, "\r\n", 2) != 0)
		throw (Message::InvalidMessageException());
	i += 2; //!< Skip CRLF
	return ;
}

/* ************************************************************************** */
/* *                                 Exceptions                             * */
/* ************************************************************************** */
const char*	Message::InvalidMessageException::what() const throw() {
	return ("Invalid message");
}
