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
	this->tx_counter = 0;
	this->rx_counter = 0;
	
	// initialize strings
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
	
	QString combined_status = this->status[0];
	
	// combine error string with connection status
	if( this->status[1] != "" )
		combined_status += " : " + this->status[1];
		
	// insert some dead space and show counters
	combined_status += "      ";	
	combined_status += "Tx Count: ";
	combined_status += QString::number(this->tx_counter);
	combined_status += " Bytes  Rx Count: ";
	combined_status += QString::number(this->rx_counter);
	combined_status += " Bytes";	
	
	this->status_bar_ptr->showMessage(combined_status);

}

void status_bar::increment_tx_counter(unsigned int byte_increment)
{	
	this->tx_counter += byte_increment;
	
	this->update_status_bar();
}

void status_bar::increment_rx_counter(unsigned int byte_increment)
{	
	this->rx_counter += byte_increment;
	
	this->update_status_bar();
}

void status_bar::clear_tx_counter()
{
	this->tx_counter = 0;
	
	this->update_status_bar();
}

void status_bar::clear_rx_counter()
{	
	this->rx_counter = 0;
	
	this->update_status_bar();
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
