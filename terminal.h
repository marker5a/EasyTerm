#ifndef TERMINAL_H
#define TERMINAL_H

#include <qextserialport.h>
#include "ui_terminal.h"
#include <QSettings>
#include "macro_editor.h"

class terminal_app : public QMainWindow, public Ui::Terminal
{
    Q_OBJECT
 
public:
    terminal_app(QMainWindow *parent = 0);    
    void connect_widgets();
    QString get_checked_radio(QButtonGroup *);
    void group_radio_buttons(void);
    void toggle_com_port_fields(bool disable);
    void load_settings();
    void set_checked_radio(QButtonGroup *group,QString name);
   	
public slots:
	void connect_serial_port();
	void onReadyRead();
	void populateComPort(void);
	void write_to_port();
	void open_macro_editor();
	
private:
	QextSerialPort *port;
	bool comPortConnected;
	std::string comPortName;	
	QButtonGroup *baud_rate_group;
	QButtonGroup *data_bits_group;
	QButtonGroup *stop_bits_group;
	QButtonGroup *parity_group;
	QButtonGroup *hex_ascii_rx;
	QButtonGroup *hex_ascii_tx;
	QSettings *settings;
	class macro_editor *editor;
}; 

#endif
