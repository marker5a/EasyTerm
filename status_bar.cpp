/*
 * status_bar.cpp is part of EasyTerm, and is Copyright Christopher M
 * Hamilton (marker5a@gmail.com), 2014.
 *
 * EasyTerm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * EasyTerm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "status_bar.h"
#include <QString>

status_bar::status_bar(QStatusBar *status_bar_ptr)
{
	this->status_bar_ptr = status_bar_ptr;
	
	this->status[0] = "Disconnected";
	this->status[1] = "";
	
	this->update_status_bar();
}

void status_bar::update_status_bar_error_status(QString error_status)
{
	status[1] = error_status;
	
	this->update_status_bar();
}

void status_bar::update_status_bar_connection_status(QString com_port_connect_string)
{
	
	status[0] = com_port_connect_string;
	
	this->update_status_bar();
}

void status_bar::update_status_bar()
{
	
	QString comnbined_status = this->status[0];
	
	if( this->status[1] != "" )
		comnbined_status += " : " + this->status[1]; 
	
	this->status_bar_ptr->showMessage(comnbined_status);

}

void status_bar::clear_status_bar_error_status()
{
	status[1] = "";
	
	this->update_status_bar();
}

void status_bar::clear_status_bar_connection_status()
{
	status[0] = "";
	
	this->update_status_bar();
}
