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
