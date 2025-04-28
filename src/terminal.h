/*
 * terminal.h is part of EasyTerm, and is Copyright Christopher M
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

#ifndef TERMINAL_H
#define TERMINAL_H

#include <QSerialPort>
#include <QSettings>
#include <QShortcut>
#include "ui_terminal.h"
#include "ui_about.h"
#include "macro_editor.h"
#include "about_dialog.h"
#include "status_bar.h"

#define _VERSION_NUMBER		"0.9.3"

class terminal_app : public QMainWindow, public Ui::EasyTerm
{
    Q_OBJECT
 
public:

	enum Tx_Char_Type
	{
		TX_ASCII,
		TX_HEX
	};
	
	enum Tx_Error_Type
	{
		TX_NO_ERROR,
		PORT_NOT_CONNECTED,
		INVALID_ASCII_STRING,
		INVALID_HEX_STRING,
		EMPTY_TX_STRING,
		UNSPECIFIED_ERROR
	};

    terminal_app(QApplication *parent = 0);
    void connect_widgets();
    void group_radio_buttons(void);
    void toggle_com_port_fields(bool disable);
    
    void load_settings(void);
    void set_checked_radio(QButtonGroup *group,QString name);
   	void update_macro_button_names(void);
   	void write_to_port(QByteArray array);
   	int hex_qstring_to_hex_array(QString hex_qstring,QByteArray *result);
   	QByteArray array_to_hex_array(QByteArray array_in);
   	void setup_keybindings(void);
   	Tx_Error_Type validate_and_send_tx_string(QString tx_string,Tx_Char_Type type);
   	
    QString get_checked_radio(QButtonGroup *);
   	QSettings *settings;
   	class status_bar *status_bar;
   	
   	
   	
public slots:
	void connect_serial_port(void);
	void rx_data_available(void);
	void check_to_disable_custom_baud(void);
	void populate_com_port(void);
	void press_transmit_button(void);
	void open_macro_editor(void);
	void open_about_dialog(void);
	void press_macro_button(QString macro_name);
	void rx_ascii_hex();
	void save_gui_settings();
	void close_terminal_app();
	void clear_settings();
	void serial_port_error(QSerialPort::SerialPortError error);
	
private:
	QSerialPort *port;
	bool comPortConnected;
	std::string comPortName;	
	QButtonGroup *baud_rate_group;
	QButtonGroup *data_bits_group;
	QButtonGroup *stop_bits_group;
	QButtonGroup *parity_group;
	QButtonGroup *hex_ascii_rx;
	QButtonGroup *hex_ascii_tx;
	QButtonGroup *newline_tx;
	class macro_editor *editor;
	class about_dialog *about;
	bool pending_receive_text_newline;
	
	
	
}; 

#endif
