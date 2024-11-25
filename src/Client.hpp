/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 08:52:50 by dbaladro          #+#    #+#             */
/*   Updated: 2024/11/24 19:00:35 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <netinet/in.h>
# include <cstring>
# include <string>
# include <ostream>

#include <arpa/inet.h>		//!< Just for struct sockaddr_in operator<<
#include <sys/socket.h>		//!< Just for struct sockaddr_in operator<<

class Client {
public:
	Client( void );
	Client( Client const & rhs );
	~Client();

	Client& operator=( Client const & rhs );

	//* Getters and Setters *//
	struct sockaddr_in	getNetId( void ) const;
	std::string			getHostname( void ) const;
	std::string			getUsername( void ) const;
	std::string			getNickname( void ) const;
	int					getFd( void ) const;
	int					getJoinedChannel( void ) const;

	void	setNetId( struct sockaddr_in addr );
	void	setFd( int fd );

private:
	struct sockaddr_in	_netId;		//!< Client addr
	std::string			_hostname;
	std::string			_username;
	std::string			_nickname;

	int					_fd; //!< Pointer to server_poll fd

	int					_joinedChannel;
};

std::ostream&	operator<<( std::ostream& os, const struct sockaddr_in& rhs );
std::ostream&	operator<<( std::ostream& os, const Client& rhs );

#endif // !CLIENT_HPP
