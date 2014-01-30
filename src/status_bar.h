/*
 * status_bar.h is part of EasyTerm, and is Copyright Christopher M
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
