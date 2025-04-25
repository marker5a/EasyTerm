/*
 * terminal.cpp is part of EasyTerm, and is Copyright Christopher M
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

#include <QtWidgets> 
#include "terminal.h"
#include <QStringList>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QButtonGroup>
#include <QSignalMapper>
#include <QMutex>
#include <QKeySequence>
#include <QShortcut>
#include "macro_editor.h"
#include "about_dialog.h"

void terminal_app::close_terminal_app()
{
	// if com port is created, clean house
	if( this->port )
	{
		this->port->flush();
		delete this->port;
	}
}

terminal_app::terminal_app(QApplication *parent)
{
	setupUi(this); 												// this sets up GUI
	
	// connect closing event of window to cleanup
	connect(parent,SIGNAL(lastWindowClosed()),this,SLOT(close_terminal_app()));
	
	// setup version number in title
	this->setWindowTitle(this->windowTitle() + QString(_VERSION_NUMBER));
	
	// initialize variables
	this->port = 0;	
	this->comPortConnected = 0;
	this->pending_receive_text_newline=false;	
		
	// allocate memory for dynamic memory content
	this->status_bar = new class status_bar(this->statusbar);		// create and instance of the status_bar class
	this->settings = new QSettings("EasyTerm", "EasyTerm");			// create instance of settings container
	this->editor = new macro_editor(this);							// create instance of macro gui
	this->about = new about_dialog();								// create instance of about dialog
	this->port = new QSerialPort();									// create instance of serial port

	group_radio_buttons();											// group the radio buttons together
		
	load_settings();												// load the settings
										
	connect_widgets();												// connect widgets with callbacks
		
	setup_keybindings();											// link F1-F12 buttons to macro buttons
			
	populate_com_port();											// fill in the com port combo box	
		
	update_macro_button_names();									// load in the macro names from the settings and set the button names	

}

void terminal_app::setup_keybindings(void)
{
	// create the keybinding shortcuts
	QShortcut *m1 = new QShortcut(QKeySequence("F1"),this);
	QShortcut *m2 = new QShortcut(QKeySequence("F2"),this);
	QShortcut *m3 = new QShortcut(QKeySequence("F3"),this);
	QShortcut *m4 = new QShortcut(QKeySequence("F4"),this);
	QShortcut *m5 = new QShortcut(QKeySequence("F5"),this);
	QShortcut *m6 = new QShortcut(QKeySequence("F6"),this);
	QShortcut *m7 = new QShortcut(QKeySequence("F7"),this);
	QShortcut *m8 = new QShortcut(QKeySequence("F8"),this);
	QShortcut *m9 = new QShortcut(QKeySequence("F9"),this);
	QShortcut *m10 = new QShortcut(QKeySequence("F10"),this);
	QShortcut *m11 = new QShortcut(QKeySequence("F11"),this);
	QShortcut *m12 = new QShortcut(QKeySequence("F12"),this);
	
	// create a signalmapper to consolidate some of the function calls
	QSignalMapper* signalMapper = new QSignalMapper(this);
	connect(m1 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m2 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m3 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m4 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m5 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m6 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m7 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m8 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m9 ,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m10,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m11,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	connect(m12,SIGNAL( activated() ),signalMapper,SLOT( map() ) );
	
	// map macro names to consolidate into one routine call
	signalMapper->setMapping(m1,  "macro_1_");
	signalMapper->setMapping(m2,  "macro_2_");
	signalMapper->setMapping(m3,  "macro_3_");
	signalMapper->setMapping(m4,  "macro_4_");
	signalMapper->setMapping(m5,  "macro_5_");
	signalMapper->setMapping(m6,  "macro_6_");
	signalMapper->setMapping(m7,  "macro_7_");
	signalMapper->setMapping(m8,  "macro_8_");
	signalMapper->setMapping(m9,  "macro_9_");
	signalMapper->setMapping(m10,"macro_10_");
	signalMapper->setMapping(m11,"macro_11_");
	signalMapper->setMapping(m12,"macro_12_");
	
	// one time connect of macro buttons
	connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(press_macro_button(QString))) ;
}

void terminal_app::load_settings()
{
	// load up settings with default settings if configuration is not set
	if( !this->settings->allKeys().size() )
	{
		
		qDebug() << "Loading default settings";
		
		// set default com port settings
		this->settings->setValue("baud_rate" , "9600");
		this->settings->setValue("data_bits" , "8");
		this->settings->setValue("stop_bits" , "1");
		this->settings->setValue("parity" , "none");
		
		this->settings->setValue("hex_ascii_rx" , "Hex");
		this->settings->setValue("hex_ascii_tx" , "Hex");
		this->settings->setValue("newline_tx" , "CR+LF");
		this->settings->setValue("autoscroll" , true);
		
		// handle the dialog window defaults for macro editing
		this->settings->setValue("macro_1_hex_ascii"  , "Hex" );
		this->settings->setValue("macro_2_hex_ascii"  , "Hex" );
		this->settings->setValue("macro_3_hex_ascii"  , "Hex" );
		this->settings->setValue("macro_4_hex_ascii"  , "Hex" );
		this->settings->setValue("macro_5_hex_ascii"  , "Hex" );
		this->settings->setValue("macro_6_hex_ascii"  , "Hex" );
		this->settings->setValue("macro_7_hex_ascii"  , "Hex" );
		this->settings->setValue("macro_8_hex_ascii"  , "Hex" );
		this->settings->setValue("macro_9_hex_ascii"  , "Hex" );
		this->settings->setValue("macro_10_hex_ascii" , "Hex" );
		this->settings->setValue("macro_11_hex_ascii" , "Hex" );
		this->settings->setValue("macro_12_hex_ascii" , "Hex" );
					
		this->settings->sync();
	}
	// if config is set, load up everything
	else
	{
		
		qDebug() << "Loading saved settings";
		
		set_checked_radio(this->baud_rate_group,this->settings->value("baud_rate").toString());
		set_checked_radio(this->data_bits_group,this->settings->value("data_bits").toString());
		set_checked_radio(this->stop_bits_group,this->settings->value("stop_bits").toString());
		set_checked_radio(this->parity_group,this->settings->value("parity").toString());
		set_checked_radio(this->hex_ascii_rx,this->settings->value("hex_ascii_rx").toString());
		set_checked_radio(this->hex_ascii_tx,this->settings->value("hex_ascii_tx").toString());
		set_checked_radio(this->newline_tx,this->settings->value("newline_tx").toString());
		this->autoscroll_check->setChecked(this->settings->value("autoscroll").toBool());
                this->newline_checkbox->setChecked(this->settings->value("newline_tx_enabled").toBool());
		
		// update the macro names
		this->m1_button->setText(this->settings->value("macro_1_name").toString());
		this->m2_button->setText(this->settings->value("macro_2_name").toString());
		this->m3_button->setText(this->settings->value("macro_3_name").toString());
		this->m4_button->setText(this->settings->value("macro_4_name").toString());
		this->m5_button->setText(this->settings->value("macro_5_name").toString());
		this->m6_button->setText(this->settings->value("macro_6_name").toString());
		this->m7_button->setText(this->settings->value("macro_7_name").toString());
		this->m8_button->setText(this->settings->value("macro_8_name").toString());
		this->m9_button->setText(this->settings->value("macro_9_name").toString());
		this->m10_button->setText(this->settings->value("macro_10_name").toString());
		this->m11_button->setText(this->settings->value("macro_11_name").toString());
		this->m12_button->setText(this->settings->value("macro_12_name").toString());
		
	}
	
	// load the macro editor settings
	this->editor->load_settings();
	
	return;
}

void terminal_app::group_radio_buttons(void)
{
	// baud rate group
	this->baud_rate_group = new QButtonGroup;
	this->baud_rate_group->addButton(this->baud_1000000_radio);
	this->baud_rate_group->addButton(this->baud_256000_radio);
	this->baud_rate_group->addButton(this->baud_9600_radio);
	this->baud_rate_group->addButton(this->baud_56000_radio);
	this->baud_rate_group->addButton(this->baud_4800_radio);
	this->baud_rate_group->addButton(this->baud_600_radio);
	this->baud_rate_group->addButton(this->baud_14400_radio);
	this->baud_rate_group->addButton(this->baud_57600_radio);
	this->baud_rate_group->addButton(this->baud_1200_radio);
	this->baud_rate_group->addButton(this->baud_19200_radio);
	this->baud_rate_group->addButton(this->baud_115200_radio);
	this->baud_rate_group->addButton(this->baud_2400_radio);
	this->baud_rate_group->addButton(this->baud_128000_radio);
	this->baud_rate_group->addButton(this->baud_38400_radio);	
	
	// data bits group
	this->data_bits_group = new QButtonGroup;
	this->data_bits_group->addButton(this->data_bits_5_radio);
	this->data_bits_group->addButton(this->data_bits_6_radio);
	this->data_bits_group->addButton(this->data_bits_7_radio);
	this->data_bits_group->addButton(this->data_bits_8_radio);
	
	// stop bits group
	this->stop_bits_group = new QButtonGroup;
	this->stop_bits_group->addButton(this->stop_bits_1_radio);
	this->stop_bits_group->addButton(this->stop_bits_1_1_2_radio);
	this->stop_bits_group->addButton(this->stop_bits_2_radio);
	
	// parity group
	this->parity_group = new QButtonGroup;
	this->parity_group->addButton(this->parity_none_radio);
	this->parity_group->addButton(this->parity_odd_radio);
	this->parity_group->addButton(this->parity_even_radio);
	this->parity_group->addButton(this->parity_mark_radio);
	this->parity_group->addButton(this->parity_space_radio);
	
	// rx hex/ascii group
	this->hex_ascii_rx = new QButtonGroup;
	this->hex_ascii_rx->addButton(this->hex_rx_radio);
	this->hex_ascii_rx->addButton(this->ascii_rx_radio);
	
	// tx hex/ascii group
	this->hex_ascii_tx = new QButtonGroup;
	this->hex_ascii_tx->addButton(this->hex_tx_radio);
	this->hex_ascii_tx->addButton(this->ascii_tx_radio);
	
	// tx newline group
	this->newline_tx = new QButtonGroup;
	this->newline_tx->addButton(this->cr_radio);
	this->newline_tx->addButton(this->cr_lf_radio);
	this->newline_tx->addButton(this->lf_radio);
	
	// connect radio buttons to updating settings
	connect(this->baud_rate_group	, SIGNAL(buttonClicked(int))	, 	this, SLOT(save_gui_settings()));	
	connect(this->data_bits_group   , SIGNAL( buttonClicked(int))	, 	this, SLOT(save_gui_settings()));
	connect(this->stop_bits_group   , SIGNAL( buttonClicked(int))	, 	this, SLOT(save_gui_settings()));
	connect(this->parity_group		, SIGNAL( buttonClicked(int))	, 	this, SLOT(save_gui_settings()));
	connect(this->hex_ascii_rx	  , SIGNAL( buttonClicked(int))	, 	this, SLOT(save_gui_settings()));
	connect(this->hex_ascii_tx		, SIGNAL( buttonClicked(int))	, 	this, SLOT(save_gui_settings()));
	connect(this->newline_tx		, SIGNAL( buttonClicked(int))	, 	this, SLOT(save_gui_settings()));
	connect(this->autoscroll_check 	, SIGNAL( stateChanged(int))	,	this, SLOT(save_gui_settings()));
	connect(this->newline_checkbox	, SIGNAL( stateChanged(int))    ,       this, SLOT(save_gui_settings()));	


	// group up the radio buttons in the macro editor
	this->editor->group_radio_buttons();
	
}

void terminal_app::populate_com_port()
{		
	// clear the com port
	this->com_port_combo->clear();	
	
	// grab the list and fill them in
	QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
	QStringList com_port_names;
	
	// put com port names into a qstringlist for sorting
	for (int i = 0; i < ports.size(); i++)
	{
	
		qDebug() << "Com Port" << ports[i].portName() << " - Busy:" << (ports[i].isValid() ? QObject::tr("Yes") : QObject::tr("No"));
	
		if( ports[i].isValid() )
		{	
			com_port_names <<  
			#ifdef __unix__
				ports[i].systemLocation();
			#else
				ports[i].portName();
			#endif
		}
	}
	
	// sort the list of com ports by name
	com_port_names.sort();
	
	// iteratively insert into the com port combo box
	for (int i = 0; i < com_port_names.size(); i++)
		this->com_port_combo->addItem(com_port_names[i]);
	
	// try and set the com port last used
	int com_port_index = this->com_port_combo->findText(this->settings->value("com_port").toString());
	
	// if the com port is found in the current menu, select it, otherwise ignore
	if( com_port_index != -1 )
		this->com_port_combo->setCurrentIndex(com_port_index);	
}

void terminal_app::rx_ascii_hex()
{	
	this->pending_receive_text_newline = true;

	return;
}

void terminal_app::open_macro_editor()
{
	this->setDisabled(1);
	this->editor->reset_cursor_positions();
	this->editor->exec();
	update_macro_button_names();
	this->setDisabled(0);
}

void terminal_app::open_about_dialog()
{
	this->setDisabled(1);
	this->about->exec();
	this->setDisabled(0);
}

void terminal_app::connect_widgets()
{
	// basic widget connections to specific actions
	connect(this->connect_button,SIGNAL( clicked() ),this,SLOT( connect_serial_port() ));		
	connect(this->rescan_button,SIGNAL( clicked() ),this,SLOT( populate_com_port() ));		
	connect(this->rx_clear_button,SIGNAL( clicked() ),this->receive_text,SLOT( clear() ));		
	connect(this->rx_clear_button,SIGNAL( clicked() ),this->status_bar,SLOT( clear_rx_counter() ));		
	connect(this->ascii_rx_radio,SIGNAL( clicked() ),this,SLOT( rx_ascii_hex() ));		
	connect(this->hex_rx_radio,SIGNAL( clicked() ),this,SLOT( rx_ascii_hex() ));		
	connect(this->tx_clear_button,SIGNAL( clicked() ),this->transmit_text,SLOT( clear() ));		
	connect(this->tx_clear_button,SIGNAL( clicked() ),this->status_bar,SLOT( clear_tx_counter() ));		
	connect(this->send_button,SIGNAL( clicked() ),this,SLOT( press_transmit_button() ));
	connect(this->transmit_field,SIGNAL( returnPressed() ),this,SLOT( press_transmit_button() ) );
	connect(this->set_macro_button,SIGNAL( clicked() ),this,SLOT( open_macro_editor() ) );
	connect(this->quit_button,SIGNAL( clicked() ),this,SLOT( close() ) );
	connect(this->clear_settings_button,SIGNAL( clicked() ),this,SLOT( clear_settings() ) );
	connect(this->about_button,SIGNAL( clicked() ),this,SLOT( open_about_dialog() ) );
	
	// connect all buttons to update config
	QSignalMapper* signalMapper = new QSignalMapper(this);
	connect(this->m1_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m2_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m3_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m4_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m5_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m6_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m7_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m8_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m9_button	,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m10_button,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m11_button,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	connect(this->m12_button,SIGNAL( clicked() ),signalMapper,SLOT( map() ) );
	
	// map macro names to consolidate into one routine call
	signalMapper->setMapping(this->m1_button, "macro_1_");
	signalMapper->setMapping(this->m2_button, "macro_2_");
	signalMapper->setMapping(this->m3_button, "macro_3_");
	signalMapper->setMapping(this->m4_button, "macro_4_");
	signalMapper->setMapping(this->m5_button, "macro_5_");
	signalMapper->setMapping(this->m6_button, "macro_6_");
	signalMapper->setMapping(this->m7_button, "macro_7_");
	signalMapper->setMapping(this->m8_button, "macro_8_");
	signalMapper->setMapping(this->m9_button, "macro_9_");
	signalMapper->setMapping(this->m10_button,"macro_10_");
	signalMapper->setMapping(this->m11_button,"macro_11_");
	signalMapper->setMapping(this->m12_button,"macro_12_");
	
	// one time connect of macro buttons
	connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(press_macro_button(QString))) ;
	
	// connect widgets for the macro editor
	this->editor->connect_widgets();

}

void terminal_app::clear_settings()
{
	this->settings->clear();
}

void terminal_app::connect_serial_port()
{			
	
	connect(this->port,SIGNAL( error(QSerialPort::SerialPortError) ),this,SLOT( serial_port_error(QSerialPort::SerialPortError) ) );
	
	// check if we are already connected to the com port
	if( !this->comPortConnected )
	{	
		QString comPort = this->com_port_combo->currentText();
		
		this->comPortName = comPort.toStdString();		
		qDebug() << comPort;
		
		this->port->setPortName(this->comPortName.c_str());
		
		// check for error message
		if( !this->port->open(QIODevice::ReadWrite) )
			return;
		
		// configure the port
		
		this->port->setBaudRate(get_checked_radio(this->baud_rate_group).toInt());
		this->port->setFlowControl(QSerialPort::NoFlowControl);
		
		// get the acutal enum for parity
			enum QSerialPort::Parity parity;
			if( get_checked_radio(this->parity_group) == "none" )
				parity = QSerialPort::NoParity;
			if( get_checked_radio(this->parity_group) == "odd" )
				parity = QSerialPort::OddParity;
			if( get_checked_radio(this->parity_group) == "even" )
				parity = QSerialPort::EvenParity;		
			#if defined(Q_OS_WIN) || defined(qdoc)
			if( get_checked_radio(this->parity_group) == "mark" )
				parity = QSerialPort::MarkParity;
			#endif
			if( get_checked_radio(this->parity_group) == "space" )
				parity = QSerialPort::SpaceParity;
			this->port->setParity(parity);
		
		this->port->setDataBits((QSerialPort::DataBits)get_checked_radio(this->data_bits_group).toInt());
		
		// get the acutal stop bits
			enum QSerialPort::StopBits stop_bits;
			if( get_checked_radio(this->stop_bits_group) == "1" )
				stop_bits = QSerialPort::OneStop;
			if( get_checked_radio(this->stop_bits_group) == "2" )
				stop_bits = QSerialPort::TwoStop;
			#if defined(Q_OS_WIN) || defined(qdoc)
			if( get_checked_radio(this->stop_bits_group) == "1.5" )
				stop_bits = QSerialPort::OneAndHalfStop;
			#endif
			this->port->setStopBits(stop_bits);

		this->port->flush();
		
		// connect receiver on serial port to on_ready_read
		connect(this->port, SIGNAL(readyRead()), this, SLOT(rx_data_available()));
				
		if (!this->port->isOpen())
		{
			this->comPortConnected = 0;
			this->send_button->setDisabled(true);
		}
		else
		{
			qDebug("COM port connected");
			this->status_bar->update_status_bar_connection_status("Connected to " + comPort );
			
			// save the gui settings
			save_gui_settings();
			
			
						
			this->comPortConnected = 1;
			this->send_button->setEnabled(true);
		}		
	}
	// if we are disonnecting
	else
	{
		this->port->flush();
		this->port->close();
		this->comPortConnected = 0;
		this->send_button->setDisabled(true);
		qDebug("COM port disconnected");		

		this->status_bar->update_status_bar_connection_status("Disconnected");
		this->status_bar->clear_status_bar_error_status();
	}
	
	// disable the com port fields if we are connected or enable if disconnected
	toggle_com_port_fields(this->comPortConnected);
		
	//change title of connect field
	this->connect_button->setText(this->comPortConnected?"Disconnect":"Connect");
}

void terminal_app::write_to_port(QByteArray array)
{
	
	// append cr and lf if indicated by gui
	if( this->newline_checkbox->checkState() == Qt::Checked )
	{
		if( get_checked_radio(this->newline_tx) == "CR+LF" )
			array.append("\r\n");
		else if( get_checked_radio(this->newline_tx) == "CR" )
			array.append("\r");
		else if( get_checked_radio(this->newline_tx) == "LF" )
			array.append("\n");
	}
	
	// only allow sending when com port is connected
	if( this->comPortConnected )
	{
		// increment the tx counter
		this->status_bar->increment_tx_counter(array.size());
		
		this->port->write(array.data() , array.size() );

	}
}

void terminal_app::set_checked_radio(QButtonGroup *group,QString name)
{
	QList<QAbstractButton *> buttonList = group->buttons();
	for( int i = 0 ; i < buttonList.size(); i++ )
	{
		if( buttonList[i]->text() == name )
		{
			buttonList[i]->setChecked(true);
			return;
		}
	}
}

QString terminal_app::get_checked_radio(QButtonGroup *group)
{
	if( group->checkedButton() )
		return group->checkedButton()->text();
	else 
		return "";
}

void terminal_app::rx_data_available(void)
{	
	QByteArray bytes;
	
	// get count of bytes available for reading
	int rx_byte_count = this->port->bytesAvailable();
	bytes.resize(rx_byte_count);
	
	// resize the byte array buffer
	this->port->read(bytes.data(), bytes.size());
	
	// increment rx counter
	this->status_bar->increment_rx_counter(rx_byte_count);
	
	// force cursor to end of textbox
	QTextCursor cursor = this->receive_text->textCursor();
	cursor.clearSelection();
	cursor.movePosition(QTextCursor::End);
	this->receive_text->setTextCursor(cursor);
	
	// if request for newline in receive field, try and process it
	if( this->pending_receive_text_newline )	
	{
		// clear the flag
		this->pending_receive_text_newline = false;
		
		// only insert the newline if content currently exists in the receive field
		if( this->receive_text->toPlainText().size() > 0 )
			this->receive_text->insertPlainText("\n");
	}
		
	
	// interpret incoming data as hex or ascii
	if( this->get_checked_radio(this->hex_ascii_rx) == "ASCII" )
		this->receive_text->insertPlainText(bytes);
	else
		this->receive_text->insertPlainText(array_to_hex_array(bytes));
	
	// autoscroll receive field if checked
	if( this->autoscroll_check->isChecked() )
	{
		QTextCursor c =  this->receive_text->textCursor();
		c.movePosition(QTextCursor::End);
		this->receive_text->setTextCursor(c);
	}
}

void terminal_app::toggle_com_port_fields(bool disable)
{
	// toggle fields
	this->rescan_button->setDisabled(disable);
	this->com_port_combo->setDisabled(disable);
	this->baud_1000000_radio->setDisabled(disable);
	this->baud_256000_radio->setDisabled(disable);
	this->baud_9600_radio->setDisabled(disable);
	this->baud_56000_radio->setDisabled(disable);
	this->baud_4800_radio->setDisabled(disable);
	this->baud_600_radio->setDisabled(disable);
	this->baud_14400_radio->setDisabled(disable);
	this->baud_57600_radio->setDisabled(disable);
	this->baud_1200_radio->setDisabled(disable);
	this->baud_19200_radio->setDisabled(disable);
	this->baud_115200_radio->setDisabled(disable);
	this->baud_2400_radio->setDisabled(disable);
	this->baud_128000_radio->setDisabled(disable);
	this->baud_38400_radio->setDisabled(disable);	
	this->data_bits_5_radio->setDisabled(disable);
	this->data_bits_6_radio->setDisabled(disable);
	this->data_bits_7_radio->setDisabled(disable);
	this->data_bits_8_radio->setDisabled(disable);
	this->stop_bits_1_radio->setDisabled(disable);
	this->stop_bits_1_1_2_radio->setDisabled(disable);
	this->stop_bits_2_radio->setDisabled(disable);
	this->parity_none_radio->setDisabled(disable);
	this->parity_odd_radio->setDisabled(disable);
	this->parity_even_radio->setDisabled(disable);
	this->parity_mark_radio->setDisabled(disable);
	this->parity_space_radio->setDisabled(disable);
}

void terminal_app::press_transmit_button()
{
	enum Tx_Char_Type tx_char_type;
	QTextCursor c;

	// set the tx string type (hex or ascii)
	if( get_checked_radio(this->hex_ascii_tx) == "Hex" )
		tx_char_type = TX_HEX;
	else
		tx_char_type = TX_ASCII;
		
	// try and validate the tx string and process any errors
	switch( this->validate_and_send_tx_string( this->transmit_field->text() , tx_char_type ) )
	{
		case TX_NO_ERROR:	
			
			// autoscroll tx field
			c =  this->transmit_text->textCursor();
			c.movePosition(QTextCursor::End);
			this->transmit_text->setTextCursor(c);
			
			this->status_bar->clear_status_bar_error_status();
			
		break;
		
		case INVALID_HEX_STRING:				
			this->status_bar->update_status_bar_error_status("Invalid Hex String");			
		break;
		
		case EMPTY_TX_STRING:
		case PORT_NOT_CONNECTED:
		case INVALID_ASCII_STRING:		
		case UNSPECIFIED_ERROR:
		
		break;
	}		
}

void terminal_app::press_macro_button(QString macro_name)
{

	enum Tx_Char_Type tx_char_type;
	QTextCursor c;
	
	// set the tx string type (hex or ascii)
	if( this->settings->value(macro_name + "hex_ascii") == "Hex" )
		tx_char_type = TX_HEX;
	else
		tx_char_type = TX_ASCII;
	
	
	QString newline_str="";	
	
	if( this->settings->value(macro_name + "newline") == "true" )
	{
		if( this->settings->value(macro_name + "crlf") == "CR" )
			newline_str = "\r";
		else if( this->settings->value(macro_name + "crlf") == "LF" )
			newline_str = "\n";
		else if( this->settings->value(macro_name + "crlf") == "CRLF" )
			newline_str = "\r\n";
	}
	
	// try and validate the tx string and process any errors
	switch( this->validate_and_send_tx_string( this->settings->value(macro_name + "content").toString() + newline_str , tx_char_type ) )
	{
		case TX_NO_ERROR:	
			
			// autoscroll tx field
			c =  this->transmit_text->textCursor();
			c.movePosition(QTextCursor::End);
			this->transmit_text->setTextCursor(c);
			
			this->status_bar->clear_status_bar_error_status();
			
		break;
		
		case INVALID_HEX_STRING:	
			this->status_bar->update_status_bar_error_status("Invalid Hex String for Macro \"" + this->settings->value(macro_name + "name").toString() +"\"");
		break;
		
		case EMPTY_TX_STRING:	
			this->status_bar->update_status_bar_error_status("WARNING: Macro '" + this->settings->value(macro_name + "name").toString() + "' is empty");
		break;
		
		case PORT_NOT_CONNECTED:
		case INVALID_ASCII_STRING:		
		case UNSPECIFIED_ERROR:
		
		break;
	}	
}

terminal_app::Tx_Error_Type terminal_app::validate_and_send_tx_string(QString tx_string,terminal_app::Tx_Char_Type tx_char_type)
{
	QByteArray tx_array;
	int hex_string_good=1;

	// dont even try and do anything unless the com port is connected
	if( !this->comPortConnected )
		return this->PORT_NOT_CONNECTED;
	
	// if transmit string is empty, ignore and return warning
	if( !tx_string.size() )
		return terminal_app::EMPTY_TX_STRING;
	
	// force cursor to end of textbox
	QTextCursor cursor = this->transmit_text->textCursor();
	cursor.clearSelection();
	cursor.movePosition(QTextCursor::End);
	this->transmit_text->setTextCursor(cursor);
		
	// determine action based on hex or ascii
		// hex
		if( tx_char_type == terminal_app::TX_HEX )
		{
			
			// strip out all spaces and $ from the hex tx string
			tx_string.replace(" ","");
			tx_string.replace("$","");
			
			// convert the string into a byte array as hex
			hex_string_good = this->hex_qstring_to_hex_array(tx_string,&tx_array);
			
			// if the hex converted properly, show the hex in the tx field
			if( hex_string_good )
			{
				this->transmit_text->insertPlainText(array_to_hex_array(tx_array));
				this->transmit_text->insertPlainText("\n");
			}
			else				
				return this->INVALID_HEX_STRING;
		}
		// ascii
		else
		{
			// just get byte array and send it out
			tx_array = tx_string.toLatin1();
			this->transmit_text->insertPlainText(tx_array);
			this->transmit_text->insertPlainText("\n");
		}
		

	
	// write it out on the serial port and clear the error
	this->write_to_port(tx_array);
	
	// cleanly exit
	return TX_NO_ERROR;
	
}

QByteArray terminal_app::array_to_hex_array(QByteArray array_in)
{
	
	QByteArray out;
	
	for( int i = 0; i < array_in.size(); i++ )
	{
		char string[3]="";
		sprintf( string, "%.2X", (unsigned char)((char)array_in[i]) );
		out.append(string);
		out.append(" ");
	}
	
	return out;
}

int terminal_app::hex_qstring_to_hex_array(QString hex_qstring,QByteArray *result)
{
	// if the string does not contain an even number of characters, return failure
	if( hex_qstring.size()%2 != 0 )
		return 0;
		
	// iterate through each pair (byte) and alter
	for( int i = 0 ; i < hex_qstring.size()/2; i++ )
	{
		bool error[2]={true,true};
		unsigned char byte = (unsigned char)(QString(hex_qstring[2*i]).toLatin1().toInt(&error[0],16))*16;
		byte += QString(hex_qstring[(2*i)+1]).toLatin1().toInt(&error[1],16);
		
		result->insert(i,(unsigned char)QByteArray::number(byte,10).toInt()&0xFF);
		
		if( (!error[0]) | (!error[1]) )
			return 0;
	}
	
	// return success
	return 1;
	
}

void terminal_app::update_macro_button_names(void)
{
	this->m1_button->setText(this->settings->value("macro_1_name").toString());
	this->m2_button->setText(this->settings->value("macro_2_name").toString());
	this->m3_button->setText(this->settings->value("macro_3_name").toString());
	this->m4_button->setText(this->settings->value("macro_4_name").toString());
	this->m5_button->setText(this->settings->value("macro_5_name").toString());
	this->m6_button->setText(this->settings->value("macro_6_name").toString());
	this->m7_button->setText(this->settings->value("macro_7_name").toString());
	this->m8_button->setText(this->settings->value("macro_8_name").toString());
	this->m9_button->setText(this->settings->value("macro_9_name").toString());
	this->m10_button->setText(this->settings->value("macro_10_name").toString());
	this->m11_button->setText(this->settings->value("macro_11_name").toString());
	this->m12_button->setText(this->settings->value("macro_12_name").toString());
}

void terminal_app::save_gui_settings()
{
	
	this->settings->setValue("baud_rate" 	, this->get_checked_radio(this->baud_rate_group));
	this->settings->setValue("data_bits" 	, this->get_checked_radio(this->data_bits_group));
	this->settings->setValue("stop_bits" 	, this->get_checked_radio(this->stop_bits_group));
	this->settings->setValue("parity" 		, this->get_checked_radio(this->parity_group));
	this->settings->setValue("com_port" 	, this->com_port_combo->currentText());
	this->settings->setValue("hex_ascii_rx" , this->get_checked_radio(this->hex_ascii_rx));
	this->settings->setValue("hex_ascii_tx" , this->get_checked_radio(this->hex_ascii_tx));
	this->settings->setValue("newline_tx" , this->get_checked_radio(this->newline_tx));
	this->settings->setValue("autoscroll"	, this->autoscroll_check->isChecked() );
	this->settings->setValue("newline_tx_enabled"	,	this->newline_checkbox->isChecked() );

	this->settings->sync();
}

void terminal_app::serial_port_error(QSerialPort::SerialPortError error)
{
	QString error_string;
	
	// check all error conditions
	switch(error)
	{
		case QSerialPort::NoError:							this->status_bar->clear_status_bar_error_status(); break;
		case QSerialPort::DeviceNotFoundError:				this->status_bar->update_status_bar_error_status("Error: An error occurred while attempting to open an non-existing device.");break;
		case QSerialPort::PermissionError:					this->status_bar->update_status_bar_error_status("Error: An error occurred while attempting to open an already opened device by another process or a user not having enough permission and credentials to open.");break;
		case QSerialPort::OpenError:						this->status_bar->update_status_bar_error_status("Error: An error occurred while attempting to open an already opened device in this object.");break;
		case QSerialPort::ParityError:						this->status_bar->update_status_bar_error_status("Error: Parity error detected by the hardware while reading data.");break;
		case QSerialPort::FramingError:						this->status_bar->update_status_bar_error_status("Error: Framing error detected by the hardware while reading data.");break;
		case QSerialPort::BreakConditionError:				this->status_bar->update_status_bar_error_status("Error: Break condition detected by the hardware on the input line.");break;
		case QSerialPort::WriteError:						this->status_bar->update_status_bar_error_status("Error: An I/O error occurred while writing the data.");break;
		case QSerialPort::ReadError:						this->status_bar->update_status_bar_error_status("Error: An I/O error occurred while reading the data.");break;
		case QSerialPort::ResourceError:					this->status_bar->update_status_bar_error_status("Error: An I/O error occurred when a resource becomes unavailable, e.g. when the device is unexpectedly removed from the system.");break;
		case QSerialPort::UnsupportedOperationError:		this->status_bar->update_status_bar_error_status("Error: The requested device operation is not supported or prohibited by the running operating system.");break;
		default:											this->status_bar->update_status_bar_error_status("Error: An unidentified error occurred.");break;
	}
}
