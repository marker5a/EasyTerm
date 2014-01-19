#ifndef TERMINAL_H
#define TERMINAL_H

#include <qextserialport.h>
#include "ui_terminal.h"
#include <QSettings>
#include "macro_editor.h"
#include "status_bar.h"


class terminal_app : public QMainWindow, public Ui::Terminal
{
    Q_OBJECT
 
public:
    terminal_app(QMainWindow *parent = 0);
      
    void connect_widgets();
    void group_radio_buttons(void);
    void toggle_com_port_fields(bool disable);
    void load_settings();
    void set_checked_radio(QButtonGroup *group,QString name);
   	void update_macro_button_names(void);
   	void write_to_port(QByteArray array);
   	int hex_qstring_to_hex_array(QString hex_qstring,QByteArray *result);
   	QByteArray array_to_hex_array(QByteArray array_in);
   	
    QString get_checked_radio(QButtonGroup *);
   	QSettings *settings;
   	class status_bar *status_bar;
   	
   	
public slots:
	void connect_serial_port(void);
	void rx_data_available(void);
	void populate_com_port(void);
	void transmit(void);
	void open_macro_editor(void);
	void press_macro_button(QString macro_name);
	
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
	class macro_editor *editor;
}; 

#endif
