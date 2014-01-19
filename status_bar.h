#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <QStatusBar>
#include <QString>

class status_bar
{

public:
	status_bar(QStatusBar *status_bar_ptr);
	void update_status_bar_error_status(QString error_status);
	void clear_status_bar_error_status();
	void update_status_bar_connection_status(QString com_port_connect_string);
	void clear_status_bar_connection_status();
	void update_status_bar();

private:
	QStatusBar *status_bar_ptr;
	QString status[2];

};

#endif
